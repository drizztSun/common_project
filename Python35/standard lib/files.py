import os


def ensure_dir(f):
    d = os.path.dirname(f)
    if not os.path.exists(d):
        os.makedirs(d)

def main():
    # 
    filename = '/my/directory/filename.txt'
    dir = os.path.dirname(filename)

    try:
        os.stat(dir)
    except:
        os.mkdir(dir) 
    
        

if __name__ == "__main__":

    main()
