from .. import elements as alch_elements
import elements
from alchemy import potions


def lead_to_gold() -> str:
    return (
        f"Recipe transmuting Lead to Gold: "
        f"brew '{alch_elements.create_air()}' "
        f"and '{potions.strength_potion()}' "
        f"mixed with '{elements.create_fire()}'"
    )
