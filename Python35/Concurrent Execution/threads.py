import time, threading

def proc(*arg):
    
    if len(arg) != 2:
        return

    id = threading.get_ident()
    count = 0
    content, lock = arg

    while count < 5:
        
        lock.acquire()

        print(str(id) + " " + content + time.ctime(time.time()))

        lock.release()

        count += 1
    

def proc1(*arg):

    content = arg

    tls_data = threading.local()
    tls_data.x = 1
    tls_data.id = threading.get_ident()
    count = 0

    while count < 5:
        
        print("id: %d tid: %d" % (tls_data.id, threading.get_ident()))        
    
        count += 1

def main():
    # reenter-lock 
    lock = threading.RLock()

    for i in range(5):
        threading.Thread(target= proc, name= "Thread id = " + str(i), args=("content ", lock), daemon= False).start()


    print("current alive thread {0}".format(threading.active_count()))
    print("thread id %d" % (threading.get_ident()))

    lock.acquire()

    thread_objs = threading.enumerate()
    for c in thread_objs:
        print("thread id: %d name: %s daemon: %s alive: %s" % (c.ident, c.name, c.daemon, c.is_alive()))

    lock.release()

    # local-data
    for i in range(2):
        threading.Thread(target= proc1, name= "Thread id = " + str(i), daemon= False).start()

    pass

class PrintThread(threading.Thread):

    def __init__(self, content, id):
        threading.Thread.__init__(self)
        self.__content = content
        self.__id = id
   
    def run(self):
        for i in range(5):
            print("times ", i , " : ", self.__content)

def base():

    printer = PrintThread("testing basic thread create and run", 100)
    printer.start()

    printer.join()
    

if __name__ == "__main__":

    base()

    main()