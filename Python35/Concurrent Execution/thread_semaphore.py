from threading import Thread, Semaphore
import time
import random

semaphore = Semaphore(0)
item = ''

def consumer():
    global item    
    print("consumer is waiting")
    semaphore.acquire()
    print("consumer notify: consumer item nums is %d" % item)

def producer():
    global item
    time.sleep(10)
    item = random.randint(1, 1000)
    print("producer notify: producer item nums is %d" % item)
    semaphore.release()


if __name__ == "__main__":

    for _ in range(20):

        con = Thread(target=consumer)
        pro = Thread(target=producer)
        
        con.start()
        pro.start()

        con.join()
        pro.join()

    print("It is done")
        
