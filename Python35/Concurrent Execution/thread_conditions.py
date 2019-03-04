from threading import Thread, Condition
import time


items = []

class Consumer(Thread):

    def __init__(self, cv):
        super(Consumer, self).__init__()
        self.__cv = cv

    def run(self):
        for _ in range(20):
            time.sleep(4)
            self.conosume()

    def conosume(self):
        print("consume")
        global items
        
        self.__cv.acquire()

        if len(items) == 0:
            print("consumer notify: no items to consume")
            self.__cv.wait()

        items.pop()
        print("consumer notify: consumed 1 item")
        print("consumer notify: items to consume are "\
                + str(len(items)))

        self.__cv.notify()
        self.__cv.release()        


class Producer(Thread):

    def __init__(self, cv):
        Thread.__init__(self)
        self.__cv = cv

    def run(self):
        for _ in range(20):
            time.sleep(1)
            self.produce()

    def produce(self):
        print("produce")

        global items
        self.__cv.acquire()

        if len(items) == 10:
            print("Producer notify: items are full")
            self.__cv.wait()
            print("Producer notify: items producted now")
            print("Producer notify: stop the production")

        
        items.append(1)
        print("Producer notify: total items producted" + str(len(items)))

        self.__cv.notify()
        self.__cv.release()


def main():
    
    cond = Condition()

    consumer = Consumer(cond)
    producer = Producer(cond)

    consumer.start()
    producer.start()

    consumer.join()
    producer.join()

if __name__ == "__main__":

    main()
