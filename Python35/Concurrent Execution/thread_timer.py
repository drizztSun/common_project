from threading import Timer, Thread


def output():

    print("Hello world")

def main():
    
    timer = Timer(30.0, output)

    timer.start()

    

if __name__ == "__main__":

    main()
