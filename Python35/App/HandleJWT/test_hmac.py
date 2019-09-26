import hmac



def test_hmac_basic():
    
    hmac_obj = hmac.new(b'123456', msg=b"Hello World!", digestmod='sha256')
    print('hexdigest : ', hmac_obj.hexdigest())

    print('hexdigest sha256 : ', hmac.digest(b'123456', msg=b"Hello World!", digest='sha256'))

    h1 = hmac.new(b'123456', digestmod='sha256')
    for c in [b'Hello', b' ', b'workld!']:
        h1.update(c)
    print('hexdigest sha356 ', h1.hexdigest())

    h3 = h1.copy()
    print('hexdigest sha356 ', h3.hexdigest())

    print('Hmac name: ', h1.name)
    print('Hmac digest size: ', h1.digest_size)
    print('Hmac block size: ', h1.block_size)

    print('hmac are equatl: ', hmac.compare_digest(h1.hexdigest(), h3.hexdigest()))

if __name__ == '__main__':

    test_hmac_basic()