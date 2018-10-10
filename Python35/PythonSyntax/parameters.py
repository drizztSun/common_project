

def main(a, b, c, *args, **kwargs):

    print("a = {0} b = {1} c = {2}".format(a, b, c))

    print("--- args ---")
    for i, a in enumerate(args):
        print('{0} = {1}'.format(i, a))
    print("--- args ---")

    print("--- kwargs ---")
    for name, val in kwargs.items():
        print('t: {0}, t: {1}'.format(type(name), type(val)))
        print('{0}={1}'.format(name, val))
    print("--- kwargs ---")


if __name__ == "__main__":

    main(1, 2, 3, 'arg1', 'arg2', 'arg3', kwa1 = 'kwa1v', kwa2 = 'kwa2v')

    main(1, 2, 3, 4,'arg1', 'arg2', 'arg3', kwa1 = 'kwa1v', kwa2 = 'kwa2v')

    main(3, 4,'arg1', 'arg2', 'arg3', kwa1 = 'kwa1v', kwa2 = 'kwa2v')

    arg = ['arg1', 'arg2', 'arg3']
    kwarg = {'kwa1': 'kwa1v', 'kwa2': 'kwa2v'}

    main(1, 2, 3, *arg, **kwarg)