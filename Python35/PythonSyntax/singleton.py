""" Singleton module four ways to implementation """

# 1 __new__


class Singelton(object):

    def __new__(cls, *args, **kwargs):

        if not hasattr(cls, _instance):
            cls._instance = super(Singelton, cls).__new__(cls, *args, **kwargs)

        return cls._instance


# 2  shared _state


class Borg(object):

    _state = {}

    def __new__(cls, *args, **kwargs):
        ob = super(Borg, cls).__new__(cls, *args, **kwargs)
        ob.__dict__ = cls._state
        return ob

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


if __name__ == "__main__":

    pass



