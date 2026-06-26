from collections.abc import Callable


def spell_combiner(spell1: Callable, spell2: Callable) -> Callable:
    def combined(target: str, power: int) -> tuple[str, str]:
        return (spell1(target, power), spell2(target, power))
    return combined


def power_amplifier(base_spell: Callable, multiplier: int) -> Callable:
    def amplified(target: str, power: int) -> str:
        return base_spell(target, power * multiplier)
    return amplified


def conditional_caster(condition: Callable, spell: Callable) -> Callable:
    def conditional(target: str, power: int) -> str:
        if condition(target, power):
            return spell(target, power)
        return "Spell fizzled"
    return conditional


def spell_sequence(spells: list[Callable]) -> Callable:
    def sequence(target: str, power: int) -> list[str]:
        return [spell(target, power) for spell in spells]
    return sequence


if __name__ == "__main__":
    def fireball(target: str, power: int) -> str:
        return f"Fireball hits {target}"

    def heal(target: str, power: int) -> str:
        return f"Heals {target}"

    def lightning(target: str, power: int) -> str:
        return f"Lightning strikes {target} for {power} damage"

    print("Testing spell combiner...")
    combined = spell_combiner(fireball, heal)
    result1, result2 = combined("Dragon", 10)
    print(f"Combined spell result: {result1}, {result2}")

    print("Testing power amplifier...")

    def power_spell(target: str, power: int) -> str:
        return f"Power: {power}"

    original_power: int = 10
    amplified = power_amplifier(power_spell, 3)
    orig_val: int = int(power_spell("Enemy", original_power).split(": ")[1])
    amp_val: int = int(amplified("Enemy", original_power).split(": ")[1])
    print(f"Original: {orig_val}, Amplified: {amp_val}")

    print("Testing conditional caster...")

    def is_strong(target: str, power: int) -> bool:
        return power >= 50

    conditional_fireball = conditional_caster(is_strong, fireball)
    print(conditional_fireball("Goblin", 10))
    print(conditional_fireball("Dragon", 100))

    print("Testing spell sequence...")
    sequence = spell_sequence([fireball, heal, lightning])
    results: list[str] = sequence("Troll", 30)
    for res in results:
        print(res)

    print("\nCallable check:")
    print(f"spell_combiner is callable: {callable(spell_combiner)}")
    print(f"combined spell is callable: {callable(combined)}")
