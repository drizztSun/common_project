

# 11.1. Output Formatting
# The reprlib module provides a version of repr() customized for abbreviated displays of large or deeply nested containers:


def OutputFormatting():

    import reprlib
    reprlib.repr(set('supercalifragilisticexpialidocious'))

    import pprint
    t = [[[['black', 'cyan'], 'white', ['green', 'red']], [['magenta', 'yellow'], 'blue']]]
    pprint.pprint(t, width=30)
#[[[['black', 'cyan'],
#   'white',
#   ['green', 'red']],
#  [['magenta', 'yellow'],
#   'blue']]]

    import textwrap
    doc = """The wrap() method is just like fill() except that it returns
    a list of strings instead of one big string with newlines to separate
    the wrapped lines."""

    print(textwrap.fill(doc, width=40))

    import locale
    locale.setlocale(locale.LC_ALL, 'English_United States.1252')

    conv = locale.localeconv() 
    x = 1234567.8
    locale.format("%d", x, grouping=True)
    locale.format_string("%s%.*f", (conv['currency_symbol'], conv['frac_digits'], x), grouping=True)
    

    import locale
    locale.setlocale(locale.LC_ALL, 'English_United States.1252')
    conv = locale.localeconv()
    x = 1234567.8
    locale.format("%d", x, grouping=True)
    

# 11.2. Templating
def Templating():
    
    # 
    from string import Template
    t = Template('${village} folk send $$10 to $cause')
    t.substitute(village = 'Nottingham', cause = 'the dutch found')

    t = Template('Return the $item to $owner.')
    d = dict(item='unladen swallow')
    t.substitute(d)
    t.safe_substitute(d)

# 11.3. Working with Binary Data Record Layouts
# The struct module provides pack() and unpack() functions for working with variable length binary record formats.
def WorkWithBinary():
    import struct

    with open('myfile.zip', 'rb') as f:
        data = f.read()

    start = 0
    for i in range(3):                      # show the first 3 file headers
        start += 14
        fields = struct.unpack('<IIIHH', data[start:start+16])
        crc32, comp_size, uncomp_size, filenamesize, extra_size = fields

        start += 16
        filename = data[start:start+filenamesize]
        start += filenamesize
        extra = data[start:start+extra_size]
        print(filename, hex(crc32), comp_size, uncomp_size)

        start += extra_size + comp_size     # skip to the next header


# 11.4. Multi-threading
import threading, zipfile

class AsyncZip(threading.Thread):
    def __init__(self, infile, outfile):
        threading.Thread.__init__(self)
        self.infile = infile
        self.outfile = outfile

    def run(self):
        f = zipfile.ZipFile(self.outfile, 'w', zipfile.ZIP_DEFLATED)
        f.write(self.infile)
        f.close()
        print('Finished background zip of:', self.infile)

def TryThread():
    background = AsyncZip('mydata.txt', 'myarchive.zip')
    background.start()
    print('The main program continues to run in foreground.')

    background.join()    # Wait for the background task to finish
    print('Main program waited until background was done.')
    


# 11.5. Logging
def loggingFun():
    import logging
    logging.debug('Debugging information')
    logging.info('Informational message')
    logging.warning('Warning:config file %s not found', 'server.conf')
    logging.error('Error occurred')
    logging.critical('Critical error -- shutting down')


# 11.6. Weak References
import weakref, gc
class A:
    def __init__(self, value):
        self.value = value
    def __repr__(self):
        return str(self.value)


def WeakRef():

    a = A();
    b = weakref.WeakValueDictionary()
    b["abc"] = a
        

    del a
    gc.collect()
    try :
        f = b["abc"]
    except :
        pass

# 11.7. Tools for Working with Lists

from array import array
# The array module provides an array() object that is like a list that stores only homogeneous data and stores it more compactly.
# The collections module provides a deque() object that is like a list with faster appends and pops from the left side but slower lookups in the middle
def useArray():
    a = array('H', [4000, 10, 700, 22222])
    sum(a)
    a[1:3]


    
# 11.8. Decimal Floating Point Arithmetic
# The decimal module offers a Decimal datatype for decimal floating point arithmetic. Compared to the built-in float implementation of binary floating point, the class is especially helpful for

# financial applications and other uses which require exact decimal representation,
# control over precision,
# control over rounding to meet legal or regulatory requirements,
# tracking of significant decimal places, or
# applications where the user expects the results to match calculations done by hand.
from decimal import *

def DecimalTest():
    
    round(Decimal('0.70') * Decimal('1.05'), 2)
    round(.70 * 1.05, 2)

    sum([Decimal('0.1')]*10) == Decimal('1.0') # True

    sum([0.1]*10) == 1.0 # False

    # The decimal module provides arithmetic with as much precision as needed:
    getcontext().prec = 36
    Decimal(1) / Decimal(7)
    # Decimal('0.142857142857142857142857142857142857')

    

if __name__=="__main__":


    

    pass