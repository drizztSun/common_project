import os
import time
from multiprocessing import pool, Process, Manager, mp, Queue, Pipe, Lock, Value, Array

# multiprocessing is a package that supports spawning processes using an API similar to the threading module. 
# The multiprocessing package offers both local and remote concurrency, effectively side-stepping the Global Interpreter Lock by using subprocesses instead of threads. 
# Due to this, the multiprocessing module allows the programmer to fully leverage multiple processors on a given machine. 
# It runs on both Unix and Windows.

# The multiprocessing module also introduces APIs which do not have analogs in the threading module. 
# A prime example of this is the Pool object which offers a convenient means of parallelizing the execution of a function across multiple input values, 
# distributing the input data across processes (data parallelism). 
# The following example demonstrates the common practice of defining such functions in a module so that child processes can successfully import that module. 
# This basic example of data parallelism using Pool,


def test_pool():
    with pool(5) as p:
        print(map(lambda x: x**2, [ i for i in range(100)]))


def info(title):
    print('Info: ', title)
    print('module name: ', __name__)
    print('parent process id: ', os.getppid())
    print('process id: ', os.getpid())


def process_func(name):
    print("from: ", name)
    info(name)


# In multiprocessing, processes are spawned by creating a Process object and then calling its start() method. 
# Process follows the API of threading.Thread. A trivial example of a multiprocess program is
def test_start_process():
    p = Process(target = process_func, args = ("syx", ))
    p.start()
    p.join()


# Depending on the platform, multiprocessing supports three ways to start a process. These start methods are

# *** spawn
# The parent process starts a fresh python interpreter process. The child process will only inherit those resources necessary to run the process objects run() method. 
# In particular, unnecessary file descriptors and handles from the parent process will not be inherited. 
# Starting a process using this method is rather slow compared to using fork or forkserver.
# Available on Unix and Windows. The default on Windows.

# *** fork
# The parent process uses os.fork() to fork the Python interpreter. 
# The child process, when it begins, is effectively identical to the parent process. 
# All resources of the parent are inherited by the child process. Note that safely forking a multithreaded process is problematic.
# Available on Unix only. The default on Unix.

# *** forkserver
# When the program starts and selects the forkserver start method, a server process is started. 
# From then on, whenever a new process is needed, the parent process connects to the server and requests that it fork a new process. 
# The fork server process is single threaded so it is safe for it to use os.fork(). No unnecessary resources are inherited.
# Available on Unix platforms which support passing file descriptors over Unix pipes.
def mp_process(q):
    q.put('hello')


# To select a start method you use the set_start_method() 
def test_mp_process():
    mp.set_start_method('spawn')  # set_start_method() should not be used more than once in the program
    q = mp.Queue()
    p = mp.Process(target = mp_process, args = (q, ))
    p.start()
    print(q.get())
    p.join()



# Alternatively, you can use get_context() to obtain a context object. 
# Context objects have the same API as the multiprocessing module, and allow one to use multiple start methods in the same program.
def test_context_process():
    ctx = mp.get_context('spawn')
    q = ctx.Queue()
    p = q.Process(target = mp_process, args = (q, ))
    p.start()
    print(q.get())
    p.join()
# Note that objects related to one context may not be compatible with processes for a different context. 
# In particular, locks created using the fork context cannot be passed to processes started using the spawn or forkserver start methods.

# A library which wants to use a particular start method should probably use get_context() to avoid interfering with the choice of the library user.


# *** multiprocessing supports two types of communication channel between processes:
# *** Queues
def queue_process(q):
    q.put([42, None, 'hello'])


def test_queue_process():
    q = Queue()
    p = q.Process(target=queue_process, args = (q, ))
    p.start()
    print(q.get())
    p.join()


# *** Pipes
def pipe_process(conn):
    conn.send([42, None, 'hello pipe_process'])
    conn.close()


def test_pipe_process():
    parent_conn, child_conn = Pipe()
    p = Process(target = pipe_process, args =(child_conn, ))
    p.start()
    print(parent_conn.recv()) # [42, None, 'hello pipe_process']
    p.join()


# *** Synchronization between processes
# multiprocessing contains equivalents of all the synchronization primitives from threading. 
# For instance one can use a lock to ensure that only one process prints to standard output at a time:
def sync_process(l, num):
    l.acquire()
    try:
        print("hello : ", num)
    finally:
        l.release()


def test_lock_process():

    l = Lock()
    processes = []
    for num in range(10):
        p = Process(target = sync_process, args = (l, num, ))
        p.start()
        processes.append(p)

    for i in range(len(processes)):
        processes[i].join()


# *** Sharing state between processes

# *** Shared memory
# Data can be stored in a shared memory map using Value or Array. For example, the following code
def share_memory_process(n, a):
    n.value = 3.1415926
    for i in range(len(a)):
        a[i] = -a[i]


def test_share_memory():

    num = Value('d', 0.0)
    arr = Array('i', range(10))

    p = Process(target = share_memory_process, args = (num, arr, ))
    p.start()    
    p.join()

    print(num.value)
    print(num[:])

# For more flexibility in using shared memory one can use the 'multiprocessing.sharedctypes' module which supports the creation of arbitrary ctypes objects allocated from shared memory.

# *** Server process
# A manager object returned by M    anager() controls a server process which holds Python objects and allows other processes to manipulate them using proxies.
# A manager returned by Manager() will support types list, dict, Namespace, Lock, RLock, Semaphore, BoundedSemaphore, Condition, Event, Barrier, Queue, Value and Array. For example,
def server_manager_process(d, l):
    d['1'] = '1'
    d['2'] = 2
    d[0.25] = None
    l.reverse()


def test_manager_process():
    with Manager() as mgr:
        d = mgr.dict()
        l = mgr.list(range(10))

        p = Process(target = server_manager_process, args = (d, 1))
        p.start()
        p.join()

        print(d)
        print(l)


def f_pool(x):
    return x ** 2


def test_pool_logic():

    with pool(processes = 4) as pool:

                # print "[0, 1, 4,..., 81]"
        print(pool.map(f_pool, range(10)))

        # print same numbers in arbitrary order
        for i in pool.imap_unordered(f_pool, range(10)):
            print(i)

        # evaluate "f(20)" asynchronously
        res = pool.apply_async(f_pool, (20,))      # runs in *only* one process
        print(res.get(timeout=1))             # prints "400"

        # evaluate "os.getpid()" asynchronously
        res = pool.apply_async(os.getpid, ()) # runs in *only* one process
        print(res.get(timeout=1))             # prints the PID of that process

        # launching multiple evaluations asynchronously *may* use more processes
        multiple_results = [pool.apply_async(os.getpid, ()) for i in range(4)]
        print([res.get(timeout=1) for res in multiple_results])

        # make a single worker sleep for 10 secs
        res = pool.apply_async(time.sleep, (10,))
        try:
            print(res.get(timeout=1))
        except TimeoutError:
            print("We lacked patience and got a multiprocessing.TimeoutError")

        print("For the moment, the pool remains available for more work")

    # exiting the 'with'-block has stopped the pool
    print("Now the pool is closed and no longer available")


def test_process_basic_funcs():

    test_pool()

    test_start_process()

    test_mp_process()

    test_context_process()

    test_queue_process()

    test_pipe_process()

    test_lock_process()

    test_pool_logic()


if __name__ == '__main__':

    test_pool()

    test_start_process()

    test_mp_process()

    test_context_process()

    test_queue_process()

    test_pipe_process()

    test_lock_process()

    test_pool_logic()

