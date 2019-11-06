from multiprocessing import Pool, Process, ProcessError, BufferTooShort, AuthenticationError, TimeoutError
import os


def nth(n):
    print("module name : ", __name__)
    print("parent process : ", os.getppid())
    print("process : ", os.getpid())

    res = 1
    for i in range(1, n+1):
        res *= i
    print(res)
    return res


def test_multi_process_basic():

    try:
        p = Process(target=nth, args=(10,))
        p.daemon = True

        print(" Process Name : ", p.name)
        print(" Process id : ", p.pid)
        print(" Process islive : ", p.is_alive())
        print(" Process daemon : ", p.daemon)

        p.start()
        p.join()
        p.close()

        print(" Process exit code : ", p.exitcode)
        # p.terminate()
        # p.kill()
    except (ProcessError, BufferTooShort, AuthenticationError, TimeoutError) as e:
        print("Process error: ", e)


if __name__ == '__main__':

    test_multi_process_basic()