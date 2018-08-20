import os
import sys
import getopt


def main():

    try:
        cmd = sys.argv[1:]
        opts, args = getopt.getopt(cmd, "ho:v", ["help", "output="])

    except getopt.GetoptError as err:
        print(err)
        usage()
        sys.exit(2)

    output, verbose = None, False

    for v, o in opts:
        
        if o == '-v':
            verbose = True
        elif o in ("-h", "--help"):
            usage()
            sys.exit()
        elif o in ('-o', '--output'):
            output = a
        else:
            assert False, "unhandle option"        
        

if __name__=="__main__":

    main()

    pass