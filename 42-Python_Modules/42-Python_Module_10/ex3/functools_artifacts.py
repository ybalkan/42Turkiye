import functools
import operator
from collections.abc import Callable
from typing import Any


def spell_reducer(spells: list[int], operation: str) -> int:
    if not spells:
        return 0

    operations: dict[str, Callable] = {
        'add': operator.add,
        'multiply': operator.mul,
        'max': lambda a, b: a if a > b else b,
        'min': lambda a, b: a if a < b else b,
    }

    if operation not in operations:
        raise ValueError(
            f"Unknown operation: '{operation}'. "
            f"Supported: {list(operations.keys())}"
        )

    return functools.reduce(operations[operation], spells)


def partial_enchanter(base_enchantment: Callable) -> dict[str, Callable]:
    fire_enchant: Callable = functools.partial(
        base_enchantment, power=50, element='fire'
    )
    water_enchant: Callable = functools.partial(
        base_enchantment, power=50, element='water'
    )
    earth_enchant: Callable = functools.partial(
        base_enchantment, power=50, element='earth'
    )

    return {
        'fire': fire_enchant,
        'water': water_enchant,
        'earth': earth_enchant,
    }


@functools.lru_cache(maxsize=None)
def memoized_fibonacci(n: int) -> int:
    if n < 0:
        raise ValueError("n must be a non-negative integer.")
    if n == 0:
        return 0
    if n == 1:
        return 1
    return memoized_fibonacci(n - 1) + memoized_fibonacci(n - 2)


def spell_dispatcher() -> Callable[[Any], str]:
    @functools.singledispatch
    def cast_spell(spell: Any) -> str:
        return "Unknown spell type"

    @cast_spell.register(int)
    def _(spell: int) -> str:
        return f"Damage spell: {spell} damage"

    @cast_spell.register(str)
    def _(spell: str) -> str:
        return f"Enchantment: {spell}"

    @cast_spell.register(list)
    def _(spell: list) -> str:
        return f"Multi-cast: {len(spell)} spells"

    return cast_spell


if __name__ == "__main__":
    print("Testing spell reducer...")
    powers: list[int] = [10, 20, 40, 30]
    print(f"Sum: {spell_reducer(powers, 'add')}")
    print(f"Product: {spell_reducer(powers, 'multiply')}")
    print(f"Max: {spell_reducer(powers, 'max')}")

    print("Testing memoized fibonacci...")
    for n in [0, 1, 10, 15]:
        print(f"Fib({n}): {memoized_fibonacci(n)}")
    print(f"Cache info: {memoized_fibonacci.cache_info()}")

    print("Testing spell dispatcher...")
    dispatcher: Callable = spell_dispatcher()
    print(dispatcher(42))
    print(dispatcher("fireball"))
    print(dispatcher(["fire", "ice", "thunder"]))
    print(dispatcher(3.14))

    print("Testing partial enchanter...")

    def base_enchantment(power: int, element: str, target: str) -> str:
        return (
            f"{element.capitalize()} enchantment on {target} "
            f"with power {power}"
        )

    enchanters: dict[str, Callable] = partial_enchanter(base_enchantment)
    print(enchanters['fire'](target="Sword"))
    print(enchanters['water'](target="Shield"))
    print(enchanters['earth'](target="Helm"))
