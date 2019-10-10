import copy
import time


def get_cache(cache, key):
    """

    :param cache: dict
    :param key:
    :return:
    """

    val = cache.get(key, None)
    if val is None:
        return None

    if val[0] < time.monotonic():
        del cache[key]
        return None

    return copy.deepcopy(val[1])


def put_cache(cache, key, val, max_age_sec=300):
    """

    :param cache: dict
    :param key: key
    :param val: value for a given key
    :param max_age_sec: how many seconds the cache is valid
    :return: val
    """

    cache[key] = time.monotonic() + max_age_sec, copy.deepcopy(val)
    return val


def clear_cache(cache, key):
    """

    :param cache:
    :param key:
    :return:
    """

    cache.pop(key, None)


def main():
    pass


if __name__ == '__main__':

    main()