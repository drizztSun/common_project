from PythonSyntax.WithStatement import WithStateMent

from PythonSyntax.classproperties import CProp



def main():

    # test 'WithStatement'
    with WithStateMent('./functions.py') as f:
        print(f.read())

    obj = CProp(100)
    print("x is {0}", obj.x)    

    res = 1


if __name__ == "__main__":

    main()    
