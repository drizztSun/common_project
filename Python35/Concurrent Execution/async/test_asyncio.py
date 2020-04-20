import asyncio
import time
# Coroutine


async def say_after(word, delay):
    await asyncio.sleep(delay)

    # coroutine asyncio.sleep(delay, result=None, *, loop=None)
    # Block for delay seconds.
    #
    # If result is provided, it is returned to the caller when the coroutine completes.
    #
    # sleep() always suspends the current task, allowing other tasks to run.

    print(word)


async def main_coroutine():

    print(f"start time {time.strftime('%X')}")

    await say_after("Hello", 2)
    await say_after("World", 5)

    print(f"end time {time.strftime('%X')}")


def test_basic_asycio():

    # The asyncio.run() function to run the top-level entry point “main()” function
    asyncio.run(main_coroutine())

    # asyncio.run(coro, *, debug=False)
    # Execute the coroutine coro and return the result.
    #
    # This function runs the passed coroutine, taking care of managing the asyncio event loop and finalizing asynchronous generators.
    #
    # This function cannot be called when another asyncio event loop is running in the same thread.
    #
    # If debug is True, the event loop will be run in debug mode.
    #
    # This function always creates a new event loop and closes it at the end. It should be used as a main entry point for asyncio programs, and should ideally only be called once.

    #     loop = asyncio.get_event_loop()
    #     res = loop.run_until_complete(asyncio.wait([buy_potatos(), buy_tomatos()]))
    #     loop.close()

    # The asyncio.create_task() function to run coroutines concurrently as asyncio Tasks.

    # Tasks
    # Tasks are used to schedule coroutines concurrently.
    # When a coroutine is wrapped into a Task with functions like asyncio.create_task() the coroutine is automatically scheduled to run soon:
    task1 = asyncio.create_task(
        say_after(1, 'hello'))

    task2 = asyncio.create_task(
        say_after(2, 'world'))

    # asyncio.create_task(coro, *, name=None)
    # Wrap the coro coroutine into a Task and schedule its execution. Return the Task object.
    #
    # If name is not None, it is set as the name of the task using Task.set_name().
    #
    # The task is executed in the loop returned by get_running_loop(), RuntimeError is raised if there is no running loop in current thread.

    print(f"started at {time.strftime('%X')}")

    # Wait until both tasks are completed (should take
    # around 2 seconds.)
    await task1
    await task2

    print(f"finished at {time.strftime('%X')}")


# Awaitables
# We say that an object is an awaitable object if it can be used in an await expression. Many asyncio APIs are designed to accept awaitables.

# There are three main types of awaitable objects: coroutines, Tasks, and Futures.

# Important In this documentation the term “coroutine” can be used for two closely related concepts:
# a coroutine function: an async def function;
# a coroutine object: an object returned by calling a coroutine function.


# Futures

# A Future is a special low-level awaitable object that represents an eventual result of an asynchronous operation.

# When a Future object is awaited it means that the coroutine will wait until the Future is resolved in some other place.

# Future objects in asyncio are needed to allow callback-based code to be used with async/await.

# Normally there is no need to create Future objects at the application level code.

# Future objects, sometimes exposed by libraries and some asyncio APIs, can be awaited:


async def factorial(name, number):
    f = 1
    for i in range(2, number + 1):
        print(f"Task {name}: Compute factorial({i})...")
        await asyncio.sleep(1)
        f *= i
    print(f"Task {name}: factorial({number}) = {f}")


async def gathar_factorial():
    # Schedule three calls *concurrently*:
    await asyncio.gather(
        factorial("A", 2),
        factorial("B", 3),
        factorial("C", 4),
    )
    # awaitable asyncio.gather(*aws, loop=None, return_exceptions=False)
    # Run awaitable objects in the aws sequence concurrently.
    #
    # If any awaitable in aws is a coroutine, it is automatically scheduled as a Task.
    #
    # If all awaitables are completed successfully, the result is an aggregate list of returned values. The order of result values corresponds to the order of awaitables in aws.
    #
    # If return_exceptions is False (default), the first raised exception is immediately propagated to the task that awaits on gather(). Other awaitables in the aws sequence won’t be cancelled and will continue to run.
    #
    # If return_exceptions is True, exceptions are treated the same as successful results, and aggregated in the result list.
    #
    # If gather() is cancelled, all submitted awaitables (that have not completed yet) are also cancelled.
    #
    # If any Task or Future from the aws sequence is cancelled, it is treated as if it raised CancelledError – the gather() call is not cancelled in this case. This is to prevent the cancellation of one submitted Task/Future to cause other Tasks/Futures to be cancelled.


def test_gather_asyc():

    asyncio.run(gathar_factorial())

def test_shield_asyc():
    # Shielding From Cancellation
    # awaitable asyncio.shield(aw, *, loop=None)
    # Protect an awaitable object from being cancelled.
    #
    # If aw is a coroutine it is automatically scheduled as a Task.
    #
    # The statement:

    try:
        res = asyncio.shield(say_after("Hello world", 5))

        # except that if the coroutine containing it is cancelled, the Task running in something() is not cancelled.
        # From the point of view of something(), the cancellation did not happen.
        # Although its caller is still cancelled, so the “await” expression still raises a CancelledError.
        #
        # If something() is cancelled by other means (i.e. from within itself) that would also cancel shield().
        #
        # If it is desired to completely ignore cancellation (not recommended) the shield() function should be combined with a try/except clause, as follows:

    except asyncio.CancelledError:
        res = None

    return res

# Timeout

async def eternity():
    # Sleep for one hour
    await asyncio.sleep(3600)
    print('yay!')


async def timeout_wait():
    # Wait for at most 1 second
    try:
        await asyncio.wait_for(eternity(), timeout=1.0)
    except asyncio.TimeoutError:
        print('timeout!')

    # coroutine asyncio.wait_for(aw, timeout, *, loop=None)
    # Wait for the aw awaitable to complete with a timeout.
    #
    # If aw is a coroutine it is automatically scheduled as a Task.
    #
    # timeout can either be None or a float or int number of seconds to wait for. If timeout is None, block until the future completes.
    #
    # If a timeout occurs, it cancels the task and raises asyncio.TimeoutError.
    #
    # To avoid the task cancellation, wrap it in shield().
    #
    # The function will wait until the future is actually cancelled, so the total wait time may exceed the timeout.
    #
    # If the wait is cancelled, the future aw is also cancelled.


def test_timeout_wait_async():
    asyncio.run(timeout_wait())


# Waiting Primitives

# coroutine asyncio.wait(aws, *, loop=None, timeout=None, return_when=ALL_COMPLETED)
# Run awaitable objects in the aws set concurrently and block until the condition specified by return_when.
#
# Returns two sets of Tasks/Futures: (done, pending).
#
# Usage:
#
# done, pending = await asyncio.wait(aws)
# timeout (a float or int), if specified, can be used to control the maximum number of seconds to wait before returning.
#
# Note that this function does not raise asyncio.TimeoutError. Futures or Tasks that aren’t done when the timeout occurs are simply returned in the second set.
#
# return_when indicates when this function should return. It must be one of the following constants:
#
# Constant
#
# Description
#
# FIRST_COMPLETED
#
# The function will return when any future finishes or is cancelled.
#
# FIRST_EXCEPTION
#
# The function will return when any future finishes by raising an exception. If no future raises an exception then it is equivalent to ALL_COMPLETED.
#
# ALL_COMPLETED
#
# The function will return when all futures finish or are cancelled.
#
# Unlike wait_for(), wait() does not cancel the futures when a timeout occurs.
async def foo():
    return 42


def test_wait_async():

    # Note wait() schedules coroutines as Tasks automatically and later returns those implicitly created Task objects in (done, pending) sets.
    # Therefore the following code won’t work as expected:
    coro = foo()
    done, pending = await asyncio.wait({coro})

    if coro in done:
        pass
        # This branch will never be run!

    task = asyncio.create_task(foo())
    done, pending = await asyncio.wait({task})

    if task in done:
        pass
        # Everything will work as expected now.


# Scheduling From Other Threads
# asyncio.run_coroutine_threadsafe(coro, loop)
# Submit a coroutine to the given event loop. Thread-safe.
#
# Return a concurrent.futures.Future to wait for the result from another OS thread.



# Task Object
# class asyncio.Task(coro, *, loop=None, name=None)
# A Future-like object that runs a Python coroutine. Not thread-safe.
#
# Tasks are used to run coroutines in event loops. If a coroutine awaits on a Future,
# the Task suspends the execution of the coroutine and waits for the completion of the Future.
# When the Future is done, the execution of the wrapped coroutine resumes.
#
# Event loops use cooperative scheduling: an event loop runs one Task at a time. While a Task awaits for the completion of a Future,
# the event loop runs other Tasks, callbacks, or performs IO operations.

# Use the high-level asyncio.create_task() function to create Tasks, or the low-level loop.create_task() or ensure_future() functions.
# Manual instantiation of Tasks is discouraged.
#
# To cancel a running Task use the cancel() method. Calling it will cause the Task to throw a CancelledError exception into the wrapped coroutine.
# If a coroutine is awaiting on a Future object during cancellation, the Future object will be cancelled.
#
# cancelled() can be used to check if the Task was cancelled.
# The method returns True if the wrapped coroutine did not suppress the CancelledError exception and was actually cancelled.
#
# asyncio.Task inherits from Future all of its APIs except Future.set_result() and Future.set_exception().
#
# Tasks support the contextvars module. When a Task is created it copies the current context and later runs its coroutine in the copied context.

# cancelled()
# Return True if the Task is cancelled.

# done()
# Return True if the Task is done.

# result()
# Return the result of the Task.
# If the Task is done, the result of the wrapped coroutine is returned (or if the coroutine raised an exception, that exception is re-raised.)
# If the Task has been cancelled, this method raises a CancelledError exception.
# If the Task’s result isn’t yet available, this method raises a InvalidStateError exception.

# exception()
# Return the exception of the Task.
# If the wrapped coroutine raised an exception that exception is returned. If the wrapped coroutine returned normally this method returns None.
# If the Task has been cancelled, this method raises a CancelledError exception.
# If the Task isn’t done yet, this method raises an InvalidStateError exception.

async def cancel_me():
    print('cancel_me(): before sleep')

    try:
        # Wait for 1 hour
        await asyncio.sleep(3600)
    except asyncio.CancelledError:
        print('cancel_me(): cancel sleep')
        raise
    finally:
        print('cancel_me(): after sleep')


async def task_async():
    # Create a "cancel_me" Task
    task = asyncio.create_task(cancel_me())

    # Wait for 1 second
    await asyncio.sleep(1)

    task.cancel()
    # cancel()
    # Request the Task to be cancelled.
    # This arranges for a CancelledError exception to be thrown into the wrapped coroutine on the next cycle of the event loop.
    # The coroutine then has a chance to clean up or even deny the request by suppressing the exception with a try … … except CancelledError … finally block.
    # Therefore, unlike Future.cancel(), Task.cancel() does not guarantee that the Task will be cancelled, although suppressing cancellation completely is not common and is actively discouraged.
    try:
        await task
    except asyncio.CancelledError:
        print("main(): cancel_me is cancelled now")

# Expected output:
#
#     cancel_me(): before sleep
#     cancel_me(): cancel sleep
#     cancel_me(): after sleep
#     main(): cancel_me is cancelled now

def test_async_basic():
    asyncio.run(task_async())





if __name__ == '__main__':

    test_basic_asycio()

    test_gather_asyc()

    test_shield_asyc()

    test_timeout_wait_async()

    pass
