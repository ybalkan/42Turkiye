def artifact_sorter(artifacts: list[dict]) -> list[dict]:
    return sorted(
        artifacts, key=lambda artifact: artifact['power'], reverse=True
    )


def power_filter(mages: list[dict], min_power: int) -> list[dict]:
    return list(filter(lambda mage: mage['power'] >= min_power, mages))


def spell_transformer(spells: list[str]) -> list[str]:
    return list(map(lambda spell: f"* {spell} *", spells))


def mage_stats(mages: list[dict]) -> dict:
    powers: list[int] = list(map(lambda mage: mage['power'], mages))
    max_power: int = max(powers, key=lambda p: p)
    min_power: int = min(powers, key=lambda p: p)
    avg_power: float = round(sum(powers) / len(powers), 2)
    return {
        'max_power': max_power,
        'min_power': min_power,
        'avg_power': avg_power,
    }


if __name__ == "__main__":
    artifacts: list[dict] = [
        {'name': 'Crystal Orb', 'power': 85, 'type': 'orb'},
        {'name': 'Fire Staff', 'power': 92, 'type': 'staff'},
        {'name': 'Shadow Cloak', 'power': 60, 'type': 'armor'},
    ]

    mages: list[dict] = [
        {'name': 'Gandalf', 'power': 95, 'element': 'fire'},
        {'name': 'Merlin', 'power': 88, 'element': 'water'},
        {'name': 'Novice', 'power': 20, 'element': 'earth'},
    ]

    spells: list[str] = ['fireball', 'heal', 'shield']

    print("Testing artifact sorter...")
    sorted_artifacts: list[dict] = artifact_sorter(artifacts)
    first = sorted_artifacts[0]
    second = sorted_artifacts[1]
    print(
        f"{first['name']} ({first['power']} power) "
        f"comes before {second['name']} ({second['power']} power)"
    )

    print("Testing spell transformer...")
    transformed: list[str] = spell_transformer(spells)
    print(' '.join(transformed))

    print("Testing power filter...")
    strong_mages: list[dict] = power_filter(mages, min_power=50)
    for mage in strong_mages:
        print(f"{mage['name']} ({mage['power']} power)")

    print("Testing mage stats...")
    stats: dict = mage_stats(mages)
    print(f"Max power: {stats['max_power']}")
    print(f"Min power: {stats['min_power']}")
    print(f"Avg power: {stats['avg_power']}")
