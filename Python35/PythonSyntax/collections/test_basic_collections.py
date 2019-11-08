import collections
from _collections_abc import Sized, Container, Hashable, Awaitable, AsyncIterable, Callable

from threading import Thread


class asyncobject:
    def __aiter__(self):
        pass


class Callobject:
    def __call__(self, *args, **kwds):
        pass


def test_basic_class_support():

    # Sized has __len__
    print("List has __len__ is Sized ", issubclass(list, Sized))

    # Container has __contains__
    print("list has __contains__ is Contains ", issubclass(list, Container))

    # Callable has __call__
    print("Callobject has __call__ is Callable ",
          issubclass(Callobject, Callable))

    # Hashable has __hash__
    print("Dict has __hash__ is Hashable ", issubclass(dict, Hashable))

    # Awaitable has __await__
    print("Thread has __await__ is Awaitalbe ", issubclass(Thread, Awaitable))

    # AsyncIterable has __aiter__
    print("Asyncobject has __aiter__ is AsyncIterable ",
          issubclass(asyncobject, AsyncIterable))


if __name__ == '__main__':

    test_basic_class_support()
