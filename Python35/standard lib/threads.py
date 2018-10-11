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
    

def main():
    lock = threading.Lock()

    for i in range(5):
        threading.Thread(target= proc, name= "Thread id = " + str(i), args=("content ", lock), daemon= False).start()


    print("current alive thread {0}".format(threading.active_count()))
    print("thread id %d" % (threading.get_ident()))

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