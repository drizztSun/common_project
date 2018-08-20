


import os

import shutil

import glob

import sys

import getopt

def main():

    # 10.1. Operating System Interface
    # import os
    os.getcwd()  # Return the current working directory

    os.chdir('/server/accesslogs') # Change current working directory
    
    os.system('mkdir today')  # Run the command mkdir in the system shell

    dir(os)
    help(os)


    #import shutil

    shutil.copyfile('data.db', 'archive.db')

    shutil.move('/build/executables', 'installdir')

    
    # 10.2. File Wildcards
    # import glob
    glob.glob('*.py') # output ['primes.py', 'random.py', 'quote.py']

    
    # 10.3. Command Line Arguments
    # import sys
    print(sys.argv)

    # import getopt
    args = "-a -b -c foo -d bar a1 a2".split()
    options, args = getopt.getopt(args, "abc:d:")
    print(options)  # [('-a', ''), ('-b', ''), ('-c', 'foo'), ('-d', 'bar')]
    print(args) # ['a1', 'a2']

    # 10.4. Error Output Redirection and Program Termination
    # import sys
    sys.stderr.write("Warning, log file not found starting a new one\n")
    # sys.stdout, sys.stdin

    # 10.5. String Pattern Matching
    import re
    re.findall(r'\bf[a-z]*', 'which foot or hand fell fastest')
    # ['foot', 'fell', 'fastest']

    re.sub(r'(\b[a-z]+) \1', r'\1', 'cat in the the hat')
    # 'cat in the hat'

    
    # 10.6. Mathematics
    # The math module gives access to the underlying C library functions for floating point math:
    import math 
    math.cos(math.pi / 4)
    
    math.log(1024, 2)

    # The random module provides tools for making random selections:
    import random
    random.choice(['apple', 'pear', 'banana'])

    random.sample(range(100), 10) 

    random.randrange(6)

    # The statistics module calculates basic statistical properties (the mean, median, variance, etc.) of numeric data:
    import statistics
    data = [2.75, 1.75, 1.25, 0.25, 0.5, 1.25, 3.5]
    statistics.mean(data)

    statistics.variance(data)

# 10.7. Internet Access
def network():
   
    from urllib.request import urlopen
    with urlopen('http://tycho.usno.navy.mil/cgi-bin/timer.pl') as response:
         for line in response:
             line = line.decode('utf-8')  # Decoding the binary data to text.
             if 'EST' in line or 'EDT' in line:  # look for Eastern Time
                 print(line)

    # smtp
    import smtplib
    server = smtplib.SMTP('localhost')
    server.sendmail('soothsayer@example.org', 'jcaesar@example.org',
                     """To: jcaesar@example.org
                     From: soothsayer@example.org

                     Beware the Ides of March.
                     """)

    server.quit()


# 10.9. Data Compression
def dataCompression():
    # Common data archiving and compression formats are directly supported by modules including: zlib, gzip, bz2, lzma, zipfile and tarfile.
    import zlib
    s = b'witch which has which witches wrist watch'
    len(s)
    t = zlib.compress(s)
    len(t)
    zlib.decompress(t)
    zlib.crc32(s)
    

# 10.8. Dates and Times
def dataAndTimes():
    # The datetime module supplies classes for manipulating dates and times in both simple and complex ways.
    from datetime import date

    now = date.today()

    now.strftime("%m-%d-%y. %d %b %Y is a %A on the %d day of %B.")

    birthday = date(1964, 7, 31)
    age = now - birthday
    age.days



# 10.10. Performance Measurement
def PerformanceMeasurement():
    # Some Python users develop a deep interest in knowing the relative performance of different approaches to the same problem. Python provides a measurement tool that answers those questions immediately.
    
    from timeit import Timer
    Timer('t=a; a=b; b=t', 'a=1; b=2').timeit()

    Timer('a,b = b,a', 'a=1; b=2').timeit()

    # In contrast to timeit’s fine level of granularity, the profile and pstats modules provide tools for identifying time critical sections in larger blocks of code.

    import profile
    import pstats

    

# 10.11. Quality Control
def average(values):
    """Computes the arithmetic mean of a list of numbers.

    >>> print(average([20, 30, 70]))
    40.0
    """
    return sum(values) / len(values)

import doctest
doctest.testmod() 


import unittest

class TestStatisticalFunctions(unittest.TestCase):

    def test_average(self):
        self.assertEqual(average([20, 30, 70]), 40.0)
        self.assertEqual(round(average([1, 5, 7]), 1), 4.3)
        with self.assertRaises(ZeroDivisionError):
            average([])
        with self.assertRaises(TypeError):
            average(20, 30, 70)

unittest.main() 


    
#10.12. Batteries Included

# Python has a “batteries included” philosophy. This is best seen through the sophisticated and robust capabilities of its larger packages. For example:

# The xmlrpc.client and xmlrpc.server modules make implementing remote procedure calls into an almost trivial task. Despite the modules names, no direct knowledge or handling of XML is needed.

# The email package is a library for managing email messages, including MIME and other RFC 2822-based message documents. Unlike smtplib and poplib which actually send and receive messages, the email package has a complete toolset for building or decoding complex message structures (including attachments) and for implementing internet encoding and header protocols.

# The json package provides robust support for parsing this popular data interchange format. The csv module supports direct reading and writing of files in Comma-Separated Value format, commonly supported by databases and spreadsheets. XML processing is supported by the xml.etree.ElementTree, xml.dom and xml.sax packages. Together, these modules and packages greatly simplify data interchange between Python applications and other tools.

# The sqlite3 module is a wrapper for the SQLite database library, providing a persistent database that can be updated and accessed using slightly nonstandard SQL syntax.

# Internationalization is supported by a number of modules including gettext, locale, and the codecs package.    


        
    

    
    

if __name__ == "__main__":

    main()


    pass