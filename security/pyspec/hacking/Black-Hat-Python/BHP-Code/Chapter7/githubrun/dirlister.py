import os


def run():

    print("[*] in dirlister module")

    files = os.listdir('.')
    return str(files)
