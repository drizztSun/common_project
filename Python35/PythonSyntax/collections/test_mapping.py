
# mapping
# A container object that supports arbitrary key lookups and implements the methods specified in the Mapping or MutableMapping abstract base classes.
# Examples include dict, collections.defaultdict, collections.OrderedDict and collections.Counter.

# Collections Abstract Base Class
# Collection ==> Container, Sized, Iterable
#
# Mapping ==> Collection, (__getitem__, __iter__, __len__) and __contains__, keys, items, values, get, __eq__, and __ne__
#
# MutableMapping ==> Mapping, (__getitem__, __setitem__, __delitem__, __iter__, __len__) and pop, popitem, clear, update, and setdefault


from collections.abc import Mapping, MutableMapping


class Setting(Mapping):

    def __init__(self, data=None):
        pass
        # self.update(data)

    def __getitem__(self, key):
        return self.get(key)

    def __len__(self):
        return len(self.keys())

    def __iter__(self):
        return self


class MutSetting(MutableMapping):

    def __getitem__(self, key):
        pass

    def __setitem__(self, key, val):
        pass

    def __delitem__(self, key):
        pass

    def __iter__(self):
        return self

    def __len__(self):
        return 0


def test_setting():

    s = Setting(a=1, b=2, c=3)

    print(s.get('key'))


if __name__ == '__main__':

    test_setting()
