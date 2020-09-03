import sys

class RoundFloat(float):
    """round float """
    # __new__   
    def __new__(cls, val):
        #return float.__new__(cls, round(val, 2))
        return super(RoundFloat, cls).__new__(cls, round(val, 2))

class SortedKeyDict(dict):
    """sorted by dict"""
    #
    def keys(self):
        return sorted(super(SortedKeyDict, self).keys())

class RoundFloatMunual(float):
    """ RoundFloatMunual """
    def __init__(self, val):
        assert isinstance(val, float), \
        "value must be a float"

        self.value = val

    def __str__(self):
        return str(self.value)






class NumStr(object):
    """NumStr """
    def __init__(self, num = 0, str = ''):
        self._num = num
        self._str = str

    def __str__(self):
        return '[%d :: %r]' % (self._num, self._str)

    __repr__ = __str__
    
    def __add__(self, obj) :
        if isinstance(obj, NumStr) :
            return self.__class__(self._num + obj._num, \
                self._str + obj._str)

        else:
            raise TypeError, \
                "Illegal argument type for built-in operation"

    def __mul__(self, num) :
        if isinstance(num, int):
            return self.__class__(self._num * num, self_str * num)
        else:
            raise TypeError, \
                "Illegal argument type for build-in operation"
            
            
    def __nonzero__(self) :
        return self._num or len(self._str)

    def __norm_cval__(self, cmpres) :
        return cmp(cmpres, 0)

    def __cmp__(self, other):
        return self.__norm_cval__(cmp(self._num, other._num)) + \
            self.__norm_cval__(cmp(self._str, other._str))






    
    