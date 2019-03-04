import threading

def threading_basic():

    print("Thread name : ", threading.name)

    
def baisc():

    try:
        threading.stack_size(32768)

        print("Thread active count", threading.active_count())

        print("Thread name : ", threading.current_thread().name)

        print("Thread id : ", threading.get_ident())
    
    except RuntimeError as err:
        print("error")


def threading_trace(frame, event, arg):

    print("Calling threading trace")        
        
def threading_profile(frame, event, arg):
    
    print("Calling threading profile")


if __name__ == "__main__":


    threading.settrace(threading_trace)
    threading.setprofile(threading_profile)

    id = []
    for i in range(2):
        c = threading._start_new_thread(basic)
        id.append(c)

    for c in threading.enumerate():
    
        print("iterate threading name : ", c.name)

    basic()

    for i in range(2):
        id.join()
    
