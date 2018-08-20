
import numpy as np


if __name__=="__main__":


    mylist = [1, 2, 3]
    x = np.array(mylist)


    print('List is :', mylist)
    print('Array :', x)

    print( np.array([1, 2, 3]) - np.array([4, 5, 6]) )

    
    #
    m = np.array([[1, 2, 3], [4, 5, 6]])
    print(m)
    print('sharp : ', m.shape)
    #[[1 2 3]
    # [4 5 6]]
    #shape:  (2, 3)




    n = np.arange(0, 30, 2).reshape(3, 5)
    print(n)
    # [ 0  2  4  6  8 10 12 14 16 18 20 22 24 26 28]

    # n.reshape(3, 5)
    # np.reshape(n, (3, 5))
    print('after reshape')
    print(n)
    print(n.shape)
    # after reshape
    # [[ 0  2  4  6  8]
    #  [10 12 14 16 18]
    #  [20 22 24 26 28]]


    print('ones:\n', np.ones((3, 2)))
    print('zeros:\n', np.zeros((3, 2)))
    print('eye:\n', np.eye(3))
    print('diag:\n', np.diag(mylist))
    
    print('* operator?\n', np.array([1, 2, 3] * 3))
    print('repeat?\n', np.repeat([1, 2, 3], 3))    

    p1 = np.ones((3, 3))
    p2 = np.arange(9).reshape(3, 3)
    print('Vertical added: \n', np.vstack((p1, p2)))
    print('Horizental added: \n', np.hstack((p1, p2)))


    print('p1: \n', p1)
    print('p2: \n', p2)

    print('p1 + p2 = \n', p1 + p2)
    print('p1 * p2 = \n', p1 * p2)
    print('p2^2 = \n', p2 ** 2)
    print('p1.p2 = \n', p1.dot(p2))

    
    p3 = np.arange(6).reshape(2, 3)
    print('p3 shaape: ', p3.shape)
    print(p3)
    p4 = p3.T
    print('???p3??: ', p4.shape)
    print(p4)

    a = np.array([-4, -2, 1, 3, 5])
    print('sum: ', a.sum())
    print('min: ', a.min())
    print('max: ', a.max())
    print('mean: ', a.mean())
    print('std: ', a.std())
    print('argmax: ', a.argmax())
    print('argmin: ', a.argmin())


    # Array 1D
    s = np.arange(13) ** 2
    print('s: ', s)
    print('s[0]: ', s[0])
    print('s[4]: ', s[4])
    print('s[0:3]: ', s[0:3])
    print('s[[0, 2, 4]]: ', s[[0, 2, 4]])


    # Array 2D
    r = np.arange(36).reshape((6, 6))
    print('r: \n', r)
    print('r[2, 2]: \n', r[2, 2])
    print('r[3, 3:6]: \n', r[3, 3:6])
    
    print( r > 30 )
    print( r[r > 30] )
    
    r[r>30] = 30
    print(r)


    # copy()
    r2 = r[:3, :3]
    print(r2)

    # set r2 to be 0
    r2[:] = 0

    # And then r is
    print(r)
    
    # copy
    r3 = r.copy()
    r3[:] = 0
    print(r)


    # iterrate Array
    t = np.random.randint(0, 10, (4, 3))
    print(t)

    for row in t:
        print(row)

    # enumerate()
    for i, row in enumerate(t):
        print('row {} is {}'.format(i, row))

    t2 = t ** 2
    print(t2)

    # zip to zip two arrays
    for i, j in zip(t, t2):
        print('{} + {} = {}'.format(i, j, i + j))
    
    pass



