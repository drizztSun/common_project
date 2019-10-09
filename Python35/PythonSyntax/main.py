from enums import Color
from singleton import GlobalSingle
from metaclass import access_global_class
import threading

def proc1():
    for _ in range(20):
        access_global_class()

def proc2():
    for _ in range(20):
        GlobalSingle.watch()

if __name__ == '__main__':

    print(Color.RED)
    print(Color.BLUE)

    GlobalSingle.data = 100
    print('GlobalSingle value : ', GlobalSingle.data)

    access_global_class()

    GlobalSingle.watch()

    access_global_class()

    GlobalSingle.watch()

    access_global_class()

    GlobalSingle.watch()

    a = [threading._start_new_thread(proc1, ()),
         threading._start_new_thread(proc2, ())]

    for c in a:
        c.join()