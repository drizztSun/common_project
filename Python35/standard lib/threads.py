import time, threading

def proc(*arg):
    
    id = threading.get_ident()
    count = 0

    while count < 5:
        
        print(str(id) + " " + content + time.ctime(time.time()))

        count += 1
    

def main():

    lock = threading.Lock()

    for i in range(5):
        threading.Thread(target= proc, name= "Thread id = " + str(i), args=("content ", lock), daemon= False).start()


    print("current alive thread {0}".format(threading.active_count()))

    print("thread id %d" % (threading.get_ident()))

    pass
    

if __name__ == "__main__":

    main()