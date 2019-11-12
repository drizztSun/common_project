# A UNIX socket is an inter-process communication mechanism that allows bidirectional data exchange between processes running on the same machine.

# IP sockets (especially TCP/IP sockets) are a mechanism allowing communication between processes over the network.
# In some cases, you can use TCP/IP sockets to talk with processes running on the same computer (by using the loopback interface).

# UNIX domain sockets know that they’re executing on the same system, so they can avoid some checks and operations (like routing);
# which makes them faster and lighter than IP sockets. So if you plan to communicate with processes on the same host, this is a better option than IP sockets.
# Edit: As per Nils Toedtmann's comment: UNIX domain sockets are subject to file system permissions, while TCP sockets can be controlled only on the packet filter level.

# netstat -a -p --unix

# UDS support streams (TCP equivalent) and datagrams (UDP equivalent); this post focuses on the stream APIs.
# IPC with UDS looks very similar to IPC with regular TCP sockets using the loop-back interface (localhost or 127.0.0.1),
# but there is a key difference: performance.
# While the TCP loop-back interface can skip some of the complexities of the full TCP/IP network stack,
# it retains many others (ACKs, TCP flow control, and so on). These complexities are designed for reliable cross-machine communication,
# but on a single host they're an unnecessary burden. This post will explore some of the performance advantages of UDS.

# There are some additional differences. For example, since UDS use paths in the filesystem as their addresses,
# we can use directory and file permissions to control access to sockets, simplifying authentication.
# I won't list all the differences here; for more information feel free to check out the Wikipedia link and additional resources like Beej's UNIX IPC guide.

# The big disadvantage of UDS compared to TCP sockets is the single-host restriction, of course.
# For code written to use TCP sockets we only have to change the address from local to remote and everything keeps working.
# That said, the performance advantages of UDS are significant enough, and the API is similar enough to TCP sockets
# that it's quite possible to write code that supports both (UDS on a single host, TCP for remote IPC) with very little difficulty.

# From the programmer’s perspective there are two essential differences between using a Unix domain socket and an TCP/IP socket.
# First, the address of the socket is a path on the filesystem, rather than a tuple containing servername and port.
# Second, the node created in the filesystem to represent the socket persists after the socket is closed, and needs to be removed each time the server starts up.
#   The echo server example from earlier can be updated to use UDS by making a few changes in the setup section.

import socket
import sys
import os

import subprocess

socket_address = './uds_socket'


def uds_sever():

    try:
        os.unlink(socket_address)
    except OSError as err:
        if os.path.exists(socket_address):
            raise

    # create uds
    uds_socket = socket.socket(socket.AF_UNIX, socket.SOCK_STREAM)

    print('starting up on %s' % socket_address)

    uds_socket.bind(socket_address)
    uds_socket.listen()

    while True:

        connection, client_address = uds_socket.accept()
        print('connection from %s' % client_address)
        try:
            while True:

                data = connection.recv(16)
                print('received %s' % data)
                if data:
                    print('sending data back to client %s' % data)
                    connection.sendall(data)
                else:
                    print("no data more from %s" % data)
                    break
        finally:
            connection.close()


def uds_client():

    uds_socket = socket.socket(socket.AF_UNIX, socket.SOCK_STREAM)

    try:
        print("Connecting to %s" % socket_address)
        uds_socket.connect(socket_address)
    except socket.error as msg:
        print("error ", msg)
        sys.exit()

    try:
        # sending message
        message = 'Message coming, then repeated'
        uds_socket.sendall(message)

        amount_received = 0
        amount_expected = len(message)

        while amount_received < amount_expected:
            message = uds_socket.recv(16)
            amount_received += len(message)
            print('received %s' % message)

    finally:
        print("closing the socket")
        uds_socket.close()


def Communication_Between_Parent_Child_Processes():

    parent, child = socket.socketpair()
    pid = os.fork()

    if pid:
        print("In parent, parent sending message")
        child.close()
        parent.sendall('ping')
        response = parent.recv(1024)
        print('Parent receivd %s' % response)
        parent.close()
    else:
        print("In child, child receiving message")
        parent.close()
        response = child.recv(1024)
        print("Child recv %s" % response)
        child.sendall('pong')
        child.close()


def fork_client_sever():

    pid = os.fork()

    if pid:
        uds_sever()
    else:
        uds_client()


if __name__ == '__main__':

    # Communication Between Parent and Child Processes
    Communication_Between_Parent_Child_Processes()

    fork_client_sever()
