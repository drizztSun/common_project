from threading import Event, Thread
import time
import random


class Consumer(Thread):

    def __init__(self, items, event):
        Thread.__init__(self)
        self.__items = items
        self.__event = event

    def run(self):

        while True:
            
            time.sleep(2)
            self.__event.wait()
            item = self.__items.pop()
            print("Consumer notify: %d poped out from %s" % (item, self.name))


class Producer(Thread):

    def __init__(self, items, event):
        Thread.__init__(self)
        self.__items = items
        self.__event = event

    def run(self):

        # while True:
        for _ in range(20):
            global item
            time.sleep(2)
            item = random.randint(1, 1000)
            self.__items.append(item)
            print("Producer notify: item %d appended to list by %s" % (item, self.name))
            print("Producer notify: event set by %s" % self.name)
            self.__event.set()
            print("Producer notify: event clear by %s" % self.name)
            self.__event.clear()


if __name__ == "__main__":

    event = Event()
    items = []

    producer = Producer(items, event)
    consumer = Consumer(items, event)

    producer.start()
    consumer.start()

    producer.join()
    consumer.join()

    print("all done")
                
        


