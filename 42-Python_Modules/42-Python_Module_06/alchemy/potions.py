import elements
from alchemy import elements as alch_elements


def healing_potion() -> str:
    return (
        f"Healing potion brewed with '{alch_elements.create_earth()}' "
        f"and '{alch_elements.create_air()}'"
    )


def strength_potion() -> str:
    return (
        f"Strength potion brewed with '{elements.create_fire()}' "
        f"and '{elements.create_water()}'"
    )
