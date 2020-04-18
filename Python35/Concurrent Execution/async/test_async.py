
import types
from time import sleep
import random

from time import time

import asyncio
# async/await



def func_sync():
    return 'func_async'


def generator_sync():
    yield 1


async def func_async():
    return 'func_async'


async def generator_async():
    yield 100


def run(coroutine):
    try:
        assert (isinstance(coroutine, types.CoroutineType))
        coroutine().send(None)
    except StopIteration as e:
        return e.value


def await_coroutine(coroutine):
    # hang current coroutine and wait return value
    # await only works with coroutine, or it can raise SyntaxError
    # await needs a Awaitable object follows, or implement __await__
    assert (isinstance(coroutine, types.CoroutineType))
    result = await coroutine()
    return result


"""
class Awaitable(metaclass=ABCMeta):
    __slots__ = ()

    @abstractmethod
    def __await__(self):
        yield

    @classmethod
    def __subclasshook__(cls, C):
        if cls is Awaitable:
            return _check_methods(C, "__await__")
        return NotImplemented
        
        
class Coroutine(Awaitable):
    __slots__ = ()

    @abstractmethod
    def send(self, value):
        ...

    @abstractmethod
    def throw(self, typ, val=None, tb=None):
        ...

    def close(self):
        ...
        
    @classmethod
    def __subclasshook__(cls, C):
        if cls is Coroutine:
            return _check_methods(C, '__await__', 'send', 'throw', 'close')
        return NotImplemented
"""


def test_basic_concept_async():

    print(type(func_sync) is types.FunctionType)
    print(type(generator_sync) is types.GeneratorType)

    # async function types
    print(type(func_async) is types.CoroutineType)
    print(type(generator_sync) is types.AsyncGeneratorType)

    # async function call returns a 'continue' object, not value
    # <coroutine object async_function at 0x102ff67d8>
    print(func_async())

    try:
        # Coroutine will raise a exception, StopIteration. return value is in StopIteration, e.
        func_async().send(None)
    except StopIteration as e:
        print(e.value)

    all_potatos = Potato.make(5)


# async_generator

class Potato:

    @classmethod
    def make(cls, num, *args, **kwargs):
        potatos = []
        for _ in range(num):
            potatos.append(cls.__new__(cls, *args, **kwargs))
        return potatos


"""
def take_potatos(num):
    count = 0
    while True:
        if len(all_potatos) == 0:
            sleep(.1)
        else:
            potato = all_potatos.pop()
            yield potato
            count += 1
            if count == num:
                break

def buy_potatos():
    bucket = []
    for p in take_potatos(50):
        bucket.append(p)
        
    # above code is using sync call, If there are no enough potatos, 'buy_potatos' has to be waiting.
    # we can use mulitply process/thread to fix it.
    # more we could use 'async/wait'
    
"""

all_potatos = []

async def ask_for_potato():
    await asyncio.sleep(random.random())
    all_potatos.extend(Potato.make(random.randint(1, 10)))


async def take_potatos(num):
    count = 0
    while True:
        if len(all_potatos) == 0:
            await ask_for_potato()
        potato = all_potatos.pop()
        yield potato
        count += 1
        if count == num:
            break


async def buy_potatos():
    bucket = []
    async for p in take_potatos(50):
        bucket.append(p)

async def buy_tomatos():
    return 1


def test_potatos_async():

    # loop = asyncio.get_event_loop()
    # res = loop.run_until_complete(buy_potatos())
    # loop.close()

    loop = asyncio.get_event_loop()
    res = loop.run_until_complete(asyncio.wait([buy_potatos(), buy_tomatos()]))
    loop.close()


"""
class AsyncGenerator(AsyncIterator):
    __slots__ = ()

    async def __anext__(self):
        ...

    @abstractmethod
    async def asend(self, value):
        ...

    @abstractmethod
    async def athrow(self, typ, val=None, tb=None):
        ...

    async def aclose(self):
        ...

    @classmethod
    def __subclasshook__(cls, C):
        if cls is AsyncGenerator:
            return _check_methods(C, '__aiter__', '__anext__',
                                  'asend', 'athrow', 'aclose')
        return NotImplemented
"""

# async list expression
# bucket = [p async for p in take_potatos(50)]
# result = [await fun() for fun in funcs if await condition()]


def test_async_generator():
    pass


class ThreeTwoOne:

    async def begin(self):
        print(3)
        await asyncio.sleep(1)
        print(2)
        await asyncio.sleep(1)
        print(1)
        await asyncio.sleep(1)
        return

    @classmethod
    async def begin_cls(cls):
        print(3)
        await asyncio.sleep(1)
        print(2)
        await asyncio.sleep(1)
        print(1)
        await asyncio.sleep(1)
        return


class GameContext:
    async def __aenter__(self):
        print('game loading...')
        await asyncio.sleep(1)

    async def __aexit__(self, exc_type, exc, tb):
        print('game exit...')
        await asyncio.sleep(1)


async def game():
    async with GameContext():
        print('game start...')
        await asyncio.sleep(2)


async def game():

    await ThreeTwoOne().begin()
    print('start')

    await ThreeTwoOne.begin()
    print('start')


def test_post():
    function = ThreeTwoOne.begin
    method = function.__get__(ThreeTwoOne, ThreeTwoOne())
    import inspect
    assert inspect.isfunction(function)
    assert inspect.ismethod(method)
    assert inspect.iscoroutine(method())


# async could be used on 'context_management', with __aenter__ and __aexit__ and return Awaitable
class GameContext:
    async def __aenter__(self):
        print('game loading...')
        await asyncio.sleep(1)

    async def __aexit__(self, exc_type, exc, tb):
        print('game exit...')
        await asyncio.sleep(1)


async def game():
    async with GameContext():
        print('game start...')
        await asyncio.sleep(2)

from contextlib import asynccontextmanager

@asynccontextmanager
async def get_connections():
    conn = await acquire_db_connection()
    try:
        yield
    finally:
        await release_db_connection(conn)


# async could use on __call__
class GameContext:
    async def __aenter__(self):
        self._started = time()
        print('game loading...')
        await asyncio.sleep(1)
        return self

    async def __aexit__(self, exc_type, exc, tb):
        print('game exit...')
        await asyncio.sleep(1)

    async def __call__(self, *args, **kws):
        if args[0] == 'time':
            return time() - self._started


async def game():
    async with GameContext() as ctx:
        print('game start...')
        await asyncio.sleep(2)
        print('game time: ', await ctx('time'))


# async and yield from
# yield from can help to delegate a generator to another generator
def sub_gen():
    yield 1
    yield 2
    yield 3


def gen():
    return (yield from sub_gen())


def test_genetator_yeild_from():
    for val in gen():
        print(val)


# before python 3.5, asyncio use @asyncio.coroutine and yield from
# using async.coroutine decorator, to build coroutine
@asyncio.coroutine
def compute(x, y):
    print("Compute %s + %s ..." % (x, y))
    yield from asyncio.sleep(1.0)
    return x + y


@asyncio.coroutine
def print_sum(x, y):
    result = yield from compute(x, y)
    print("%s + %s = %s" % (x, y, result))


# using types.coroutine to make async coroutine
@types.coroutine
def compute_1(x, y):
    print("Compute %s + %s ..." % (x, y))
    yield from asyncio.sleep(1.0)
    return x + y


async def print_sum_1(x, y):
    result = await compute_1(x, y)
    print("%s + %s = %s" % (x, y, result))


def test_basic_decorator_coroutine():
    loop = asyncio.get_event_loop()
    loop.run_until_complete(print_sum(1, 2))
    loop.close()

# async.Future
future = asyncio.Future()

"""
Future is able to use 'await' because it is Awaitable, by imple,ent '__await__' 

class Future:
    ...
    # When execute await Future, __iter__ will be called. check if it is done. if not, hang it self. 
    # send current task, wait to Future end
    def __iter__(self):
        if not self.done():
            self._asyncio_future_blocking = True
            yield self  # This tells Task to wait for completion.
        assert self.done(), "yield from wasn't used with future"
        return self.result()  # May raise too.
        
    # In the end, Future will schedule the callback function, trigger Task._step() and tell Future get back hangout point.

    if compat.PY35:
        __await__ = __iter__ # make compatible with 'await' expression
        
    # when Future finished executing, it will set the result.
    def set_result(self, result):
         ...
        if self._state != _PENDING:
            raise InvalidStateError('{}: {!r}'.format(self._state, self))
        self._result = result
        self._state = _FINISHED
        self._schedule_callbacks()
        
"""


async def coro1():
    await asyncio.sleep(1)
    future.set_result("data")


async def coro2():
    print(await future)


def test_future_async():
    loop = asyncio.get_event_loop()
    loop.run_until_complete(asyncio.wait([
        coro1(),
        coro2()
    ]))
    loop.close()




# capture generator to be coroutine


if __name__ == '__main__':

    test_basic_concept_async()

















































