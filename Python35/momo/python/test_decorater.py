
def test(f):
    def innerf(*args):
        print("begin", *args)
        f(*args)
        print("end")
    return innerf


@test
def f():
    print('test fff')


@test
def with_par(a, b):
    print(f'{a}/{b} = {a/b}')


def articles(*args, **kwargs):
    print('start')
    for i in args:
        print(i)
    for k, v in kwargs.items():
        print(k, v)




if __name__ == "__main__":
    f()
    with_par(10, 5)
    articles('sports', 'music', 'games', 'hot', a = 'test' , b = 'test1')
