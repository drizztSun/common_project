
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

    def __getitem__(self, key):
        pass

    def __len__(self):
        return 0

    def __iter__(self):
        pass


class MutSetting(MutableMapping):
    pass


def test_setting():

    pass


if __name__ == '__main__':

    test_setting()
