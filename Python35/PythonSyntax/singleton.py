""" Singleton module four ways to implementation """

# 1 __new__

import threading

class Singelton(object):

    def __new__(cls, *args, **kwargs):

        if not hasattr(cls, '_instance'):
            cls._instance = super(Singelton, cls).__new__(cls, *args, **kwargs)

        return cls._instance


class Singelton1(object):

    instance = None

    def __new__(cls, *args, **kwargs):

        if cls.instance is None:
            cls.instance = super().__new__(cls, *args, **kwargs)
        return cls.instance

# 2  shared _state


class Borg(object):

    _state = {}

    def __new__(cls, *args, **kwargs):
        ob = super(Borg, cls).__new__(cls, *args, **kwargs)
        ob.__dict__ = cls._state
        return ob


class SingletonConcur(object):

    vars = {}
    lock = threading.Lock()

    def __new__(cls, *argv, **kwargs):

        if cls in cls.vars:
            return cls.vars[cls]

        cls.lock.acquire()

        try:
            if cls in cls.vars:
                return cls.vars[cls]

            cls.vars[cls] = super().__new__(cls, *argv, **kwargs)
            return cls.vars[cls]
        finally:
            cls.lock.release()


# 3 decorator
def singelton(cls):

    __instance = {}

    def getinstance(*args, **kwargs):

        if cls not in __instance:
            __instance[cls] = cls(*args, **kwargs)
        return __instance[cls]
    return getinstance


@singelton
class MyClass:
    pass


# 4
# from modile import singleobject
class GlobalSingle(object):

    data = 0

    @staticmethod
    def watch():

        print("In singlton GlobalSingle : ", GlobalSingle.data)
        GlobalSingle.data = GlobalSingle.data + 1


def proc(*arg):

    t = SingletonConcur()

    i, lock = arg

    lock.acquire()

    print("Tid: ", threading.current_thread().ident,
            " name: " ,threading.current_thread().name," id: ", id(t))

    lock.release()

if __name__ == "__main__":

    t1 = Singelton()
    t2 = Singelton()

    assert(id(t1) == id(t2))

    threads = []

    lock = threading.RLock()

    for i in range(5):
        a = threading.Thread(target=proc, name="id-" + str(i), args=(i, lock))
        a.start()
        threads.append(a)

    for i in range(len(threads)):
        threads[i].join()






