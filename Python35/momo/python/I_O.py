import os

def test_write_file():
    
    # how to write file
    file = open('test.txt', 'w+', buffering=1)
    print(file.name)
    print(file.mode)
    print(file.closed)
    print(file.errors)
    print(file.buffer)

    file.write("1.the first line of the file\n")
    assert(False, file.read)
    file.flush()

    file.writelines(['2. empty the file and replace it with this', 'the second line of the file'])
    file.seek(0)
    print(file.read())
    file.close()


def test_read_file():

    # how to read file
    with open('test.txt', 'r') as f:
        read_data = f.read()
    f.closed

    file = open('test.txt', 'r+')
    file.readline()

    print(file.read())
    file1 = open("tset1", "w")
    os.remove(file1)
    os.rename("test.txt", 'test_new')

def test_append_file():
    file = open('test_new, a')
    file.write('the pointer is at the end with append')
    file.seek(0)
    print(file.read())

def test_seek_file():





if __name__ == "__main__":

    test_write_file()

    test_append_file()

    test_seek_file()

    test_read_file()

    test_clear_file()
