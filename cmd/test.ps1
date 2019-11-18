Set-ExecutionPolicy Unrestricted  -Scope LocalMachine 
#RemoteSigned




$currentWi = [Security.Principal.WindowsIdentity]::GetCurrent() 
$currentWp = [Security.Principal.WindowsPrincipal]$currentWi
 
if( -not $currentWp.IsInRole([Security.Principal.WindowsBuiltInRole]::Administrator)) 
{
    $boundPara = ($MyInvocation.BoundParameters.Keys | foreach{
        '-{0} {1}' -f  $_ ,$MyInvocation.BoundParameters[$_]} ) -join ' '
  
    $currentFile = (Resolve-Path  $MyInvocation.InvocationName).Path 
 
    $fullPara = $boundPara + ' ' + $args -join ' '
    Start-Process "$psHome\powershell.exe"   -ArgumentList "$currentFile $fullPara" -verb runas 
    return
} 


$DpcExt = 'C:\ProgramData\osquery\akadp.ext.exe'
$Folder = 'C:\ProgramData\osquery'
$DPCService = 'Akamai Device Posture'
$OSQueryService = 'Akamai Osquery Daemon'

if (Test-Path $DpcExt) {

    # stop dpclient.ext and osquery service
    $services = ('Akamai Device Posture', 'Akamai Osquery Daemon')

    foreach ($serviceName in $services) {

        Write-Output ' stop {0} ' -f $serviceName 
        # Write-Verbose("stop service {0}"-f $serviceName)

        For ($i=0; $i -le 3; $i++) {

            if (Get-Service $serviceName -ErrorAction SilentlyContinue) {
                Stop-Service -Name $serviceName
                
                # Remove-Service -Name $serviceName
                sc.exe delete $serviceName
            } else {
                Write-Verbose("service {0} has been removed"-f $serviceName)
                break
            }

            # net stop 'Akamai Device Posture'
            $target = Get-Service $serviceName -ErrorAction SilentlyContinue
            if (-not $target)
            {
                Write-Output "service " + $serviceName + " has been removed"
                break
            }
        }
    } 

    # clear the installation folder
    Remove-Item $Folder -Recurse;
    
    Read-Host
}

