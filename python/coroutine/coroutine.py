async def async_function():
    return 1


async def await_coroutine():
    result = await async_function()
    print(result)


def run(coroutine):
    try:
        coroutine.send(None)
    except StopIteration as e:
        return e.value


run(await_coroutine())
