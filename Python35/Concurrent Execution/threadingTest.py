import os



try:
    import threading
except ImportError:
    import dummy_threading as threading



class Output(threading.Thread):
    
    def __init__(self, message, times):
        threading.Thread.__init__(self)
        self.name = "name : " + message 
        self._msg = message
        self._times = times

    def run(self):
        id = str(threading.get_ident())

        print('id is ', id)
        
        
        for i in range(self._times):

            print("msg: ", self._msg, " t: ", i)
    
    





def main():

    print("Current Active Thread", threading.active_count())

    ct = threading.current_thread()

    id = threading.get_ident()

    for item in threading.enumerate():
        pass

    d = threading.main_thread()

    #threading.settrace()

    oldstacksize = threading.stack_size(0) 
    
    
    # Thread-Local Data
    tlcData = threading.local()
    tlcData.x = 1


    a = Output("Daemon test", 50)

    a.start()

    print("alive ", a.is_alive())

    print("deamon ", a.daemon)



    # wait
    a.join()
    
    

    pass




if __name__=='__main__':

    main()
    pass