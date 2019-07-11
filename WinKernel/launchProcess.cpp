#include "processLauncher.h"
#include <windows.h>
#include <winbase.h>
#include <userenv.h>
#include <tchar.h>
#include <wtsapi32.h>
#include <strsafe.h>
#include <processthreadsapi.h>

#define BUFSIZE 4096 
#define PROC_THREAD_ATTRIBUTE_HANDLE_LIST ( 2 | 0x00020000)

typedef struct _STARTUPINFOEXA {
    STARTUPINFOA StartupInfo;
    LPPROC_THREAD_ATTRIBUTE_LIST lpAttributeList;
} STARTUPINFOEXA, *LPSTARTUPINFOEXA;

char* ReadAndHandleOutput(HANDLE hPipeRead)
{
    CHAR lpBuffer[256];
    int bytes_written = 0;
    DWORD nBytesRead;
    char *resultValue = malloc(BUFSIZE);
    while (TRUE) {
        if (!ReadFile(hPipeRead, lpBuffer, 256, &nBytesRead, NULL) || !nBytesRead)
        {
            if (GetLastError() == ERROR_BROKEN_PIPE) {
                break; // pipe done - normal exit path.
            }
        }
        memcpy(resultValue + bytes_written, lpBuffer, strlen(lpBuffer));
        bytes_written += nBytesRead;
    }
    resultValue[bytes_written] = '\0';
    return resultValue;
}

char* LaunchProcess(char *process_path)
{
    DWORD SessionId = WTSGetActiveConsoleSessionId();
    if (SessionId == -1) { // no-one logged in 
        return "error";
    }

    HANDLE hToken;
    BOOL ok = WTSQueryUserToken(SessionId, &hToken);
    if (!ok) {
        return "error";
    }

    void *environment = NULL;
    ok = CreateEnvironmentBlock(&environment, hToken, TRUE);

    if (!ok)
    {
        CloseHandle(hToken);
        return "error";
    }

    HANDLE hServerPipe = CreateNamedPipe("\\\\.\\Pipe\\akamai-dp-pipe.em", PIPE_ACCESS_DUPLEX, PIPE_TYPE_BYTE|PIPE_READMODE_BYTE, 1, 0, 0, 0, 0);
    HANDLE hClientPipe;
    if (hServerPipe != INVALID_HANDLE_VALUE)
    {
        static SECURITY_ATTRIBUTES sa = { sizeof(sa), 0, TRUE };

        hClientPipe = CreateFile("\\\\.\\Pipe\\akamai-dp-pipe.em", FILE_GENERIC_READ|FILE_GENERIC_WRITE, 0, &sa, OPEN_EXISTING, 0, 0);

        if (hClientPipe == INVALID_HANDLE_VALUE)
        {
            CloseHandle(hServerPipe);
            return "error";
        }
    } else {
        return "error";
    }
    
    STARTUPINFOEXA si = { { sizeof(si) } };
    PROCESS_INFORMATION pi;
    si.StartupInfo.dwFlags = STARTF_USESTDHANDLES;
    si.StartupInfo.hStdInput = si.StartupInfo.hStdOutput = si.StartupInfo.hStdError = hClientPipe;
    DWORD dwCreationFlags = CREATE_NO_WINDOW | CREATE_UNICODE_ENVIRONMENT;
    
    BOOL fInit = FALSE;
    SIZE_T Size;
    if (!InitializeProcThreadAttributeList(0, 1, 0, &Size) && GetLastError() == ERROR_INSUFFICIENT_BUFFER &&
            InitializeProcThreadAttributeList(si.lpAttributeList = (LPPROC_THREAD_ATTRIBUTE_LIST)alloca(Size), 1, 0, &Size))
    {
        fInit = TRUE;
        if (UpdateProcThreadAttribute(si.lpAttributeList, 0, PROC_THREAD_ATTRIBUTE_HANDLE_LIST, &si.StartupInfo.hStdError, sizeof(HANDLE), 0, 0)) {
                dwCreationFlags |= EXTENDED_STARTUPINFO_PRESENT;
        }
    }
    
    ok = CreateProcessAsUser(hToken, NULL, process_path, NULL, NULL, TRUE, dwCreationFlags, environment, NULL, &si.StartupInfo, &pi);
    if (!ok) {
        return "error";
    } else {
        CloseHandle(pi.hThread);
        CloseHandle(pi.hProcess);
    }
    
    // Close pipe handles (do not continue to modify the parent).
    // You need to make sure that no handles to the write end of the
    // output pipe are maintained in this process or else the pipe will
    // not close when the child process exits and the ReadFile will hang.
    if (!CloseHandle(si.StartupInfo.hStdError)) {
        return "error";    
    } 
    char *returnVal = ReadAndHandleOutput(hServerPipe);
    CloseHandle(hServerPipe);
    return returnVal;

Cleanup:
    return "error";
}