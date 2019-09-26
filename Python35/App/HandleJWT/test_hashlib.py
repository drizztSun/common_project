import hashlib
from hashlib import shake_128
from hashlib import blake2b

import hmac

# https://docs.python.org/3.7/library/hashlib.html#module-hashlib

def test_hash_basic():

    print('hashlib.algorithms_guaranteed : ', hashlib.algorithms_guaranteed)

    print('hashlib.algorithms_available : ', hashlib.algorithms_available)

    m = hashlib.sha256()

    # Update, the hash object with the bytes-like object. 
    # Repeated calls are equivalent to a single call with the concatenation of all the arguments: m.update(a); 
    # m.update(b) is equivalent to m.update(a+b).
    m.update(b"Nobody inspects")
    m.update(b' the spammish repetition')

    # digest, Return the digest of the data passed to the update() method so far. 
    # This is a bytes object of size digest_size which may contain bytes in the whole range from 0 to 255.
    c = m.digest()
    print('digest : ', c)

    print('hash name : ', m.name)
    print('digest size : ', m.digest_size)
    print('block size : ', m.block_size)

    # Return a copy (“clone”) of the hash object. This can be used to efficiently compute the digests of data sharing a common initial substring.
    new_hash_obj = m.copy()

    print('sha224 hash : ', hashlib.sha224(b"Noboday inspects the spammish repetition").hexdigest())


    # hashlib.new(name[, data])
    # Is a generic constructor that takes the string name of the desired algorithm as its first parameter. 
    # It also exists to allow access to the above listed hashes as well as any other algorithms that your OpenSSL library may offer. 
    # The named constructors are much faster than new() and should be preferred.
    h = hashlib.new('ripemd160')
    h.update(b'Nobody inspects the spammish repetition')
    print('ripemd160 hash : ', h.hexdigest())


def test_hash_shake_basic():

    # The shake_128() and shake_256() algorithms provide variable length digests with length_in_bits//2 up to 128 or 256 bits of security. 
    # As such, their digest methods require a length. Maximum length is not limited by the SHAKE algorithm.
    shake_128.digest(156)

def test_hash_blake():
    h = blake2b()
    h.update(b'Hello world')
    print('hex digest : ', h.hexdigest())

    print("blake2 hex digest : ", blake2b(b'Hello world').hexdigest())

    h1 = blake2b(key='key-to-encrypt')
    items = [b'Hello', b' ', b'World']
    for item in items:
        h1.update(item)
    print('blake2 update hex digest : ', h1.hexdigest())

    h2 = blake2b(digest_size=20)
    h2.update(b'Hello world')
    print("blake2 size20 digest: ", h2.hexdigest())
    print("digest size ", h2.digest_size)
    print("length of digest ", len(h2.digest()))


def test_keyed_hash():
    # Keyed hashing
    # Keyed hashing can be used for authentication as a faster and simpler replacement for Hash-based message authentication code (HMAC). 
    # BLAKE2 can be securely used in prefix-MAC mode thanks to the indifferentiability property inherited from BLAKE.
    h = blake2b(key=b'pseudorandom key', digest_size=16)
    h.update(b'message data')
    print('keyed hash code : ', h.hexdigest())

    # Even though there’s a native keyed hashing mode, BLAKE2 can, of course, be used in HMAC construction with hmac module:
    m = hmac.new(b'secret key', digestmod=hashlib.blake2s)
    m.update(b'message to send')
    print('keyed message ', m.hexdigest())


def test_hash_tree_mode():
    FANOUT = 2
    DEPTH = 2
    LEAF_SIZE = 4096
    INNER_SIZE = 64

    buf = bytearray(6000)

    h00 = blake2b(buf[0:LEAF_SIZE], fanout=FANOUT, depth=DEPTH,
            leaf_size = LEAF_SIZE, inner_size=INNER_SIZE,
            node_offset=0, node_depth=0, last_node=False)
    
    h01 = blake2b(buf[LEAF_SIZE:], fanout=FANOUT, depth=DEPTH,
            leaf_size=LEAF_SIZE, inner_size=INNER_SIZE,
            node_offset=1, node_depth=0, last_node=True)

    h10 = blake2b(digest_size=32, fanout=FANOUT, depth=DEPTH,
            leaf_size=LEAF_SIZE, inner_size=INNER_SIZE,
            node_offset=0, node_depth=1, last_node=True)
    
    h10.update(h00.digest())
    h10.update(h01.digest())
    c = h10.hexdigest()
    print('tree mode digest : ', c)


if __name__ == '__main__':

    test_hash_basic()

    test_hash_shake_basic()

    test_keyed_hash()