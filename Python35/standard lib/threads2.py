import _thread as thread
import time


def proc(content, sleeptime, lock, *args):
    
    count = 0
    while count < 5:
    
        lock.acquire()
        
        time.sleep(sleeptime)

        print("%s: %s" % (content, time.ctime(time.time())))

        lock.release()

        count += 1



if __name__ == "__main__":

    try:
        lock = thread.allocate_lock()

        thread.start_new_thread(proc, ("Proc1", 2, lock))
        thread.start_new_thread(proc, ("Proc2", 2, lock))

    except:
        print("Error happened")

    print("last one")

        