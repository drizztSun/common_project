import subprocess
from multiprocessing import Pool, Process
from signal import SIGTERM
import os
import shlex


def test_subprocess_basic():

    # stdout, stderr could be subprocess.PIPE, subprocess.DEVNULL

    try:
        args = ['ls', '-l', '|', 'grep', 'python']

        completed_process = subprocess.run( args, shell=True, stderr=subprocess.PIPE, stdout=subprocess.PIPE)

    except subprocess.CalledProcessError as err:
        print('ERROR:', err)
    else:
        print('returncode:', completed_process.returncode)
        print(' args : ', completed_process.args)
        print('Have {} bytes in stdout: {!r}'.format(len(completed_process.stdout), completed_process.stdout.decode('utf-8').split('\n')))
        print('Have {} bytes in stderr: {!r}'.format(len(completed_process.stderr), completed_process.stderr.decode('utf-8')))

def run_multiple_times(n, callback):
    while n > 0:
        callback();
        n -= 1

def test_processpool_pool():
    with Pool(10) as p:
        run_multiple_times(10, test_subprocess_basic)

def test_popen():

    # args = shlex.split('/bin/vikings -input eggs.txt -output "spam spam.txt" -cmd "echo \'$MONEY\'"')
    p = subprocess.Popen(['ls', '-l', '|', 'grep', 'python'])

    print(" args : ", p.args)
    print(" process id : ", p.pid)
    print(" return code :", p.returncode )

    p.stdin = subprocess.PIPE
    p.stdout = subprocess.PIPE
    p.stderr = subprocess.PIPE
    # with subprocess.Popen(['ipconfig'], stdout=PIPE) as proc:
    #    log.write(proc.stdout.read())
    try:
        out, errs = p.communicate(timeout=15)
    except subprocess.TimeoutExpired:
        p.kill()
        outs, errs = p.communicate()
    except:
        print("")

    p.send_signal(subprocess.SIGTERM)
    p.terminate()

    p.kill()

    returncode = p.poll()
    if not returncode:
        p.wait(timeout=200)
        returncode = p.poll()



if __name__ == '__main__':

    test_subprocess_basic()

    test_processpool_pool()

    test_popen()