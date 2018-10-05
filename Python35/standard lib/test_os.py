import os
import subprocess

def main():

    # to check if the file existed
    file = '/home/src/a.txt'

    os.path.isfile(file)

    # to call outside command
    # 'system' to execute a command, like command < input | another command > output
    os.system("ipconfig")            
    
    # 'popen' can make a connection to std input and output
    print(os.system("ls"))
    stream = os.popen("ipconfig")
    print(stream.read())

    # subprocss open
    # subprocess.run(["ls", "l", "//c/"])
    print(subprocess.Popen("echo Hello world!", shell=True, stdout=subprocess.PIPE).stdout.read())

    # It will return, after the sub process complete
    print(subprocess.call("echo Hello world!", shell=True))

    res = 1

if __name__ == "__main__":

    main()

