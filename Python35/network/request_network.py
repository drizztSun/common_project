

import time
import requests
from multiprocessing import Process, Queue


uri = 'http://www.google.com'
q = Queue()
session = requests.Session()


def req(args):
    while 1:
        response = session.get(uri)
        print(response)
        time.sleep(3)


def feed():
    q.put("sss")


if __name__ == '__main__':
    response = session.get(uri)

    pids = []
    for num in range(5):
        p = Process(target=req, args=(11, ))
        p.start()
        pids.append(p)

    for pid in pids:
        pid.join()
