"""capacitor.py - Tests the ex1 package capabilities."""

from ex1 import HealingCreatureFactory, TransformCreatureFactory
from ex1.capability import HealCapability, TransformCapability


def test_healing_factory(factory: HealingCreatureFactory) -> None:
    """Test healing factory Creatures: describe, attack, heal."""
    print("Testing Creature with healing capability")

    base = factory.create_base()
    print("base:")
    print(base.describe())
    print(base.attack())
    if isinstance(base, HealCapability):
        print(base.heal())

    evolved = factory.create_evolved()
    print("evolved:")
    print(evolved.describe())
    print(evolved.attack())
    if isinstance(evolved, HealCapability):
        print(evolved.heal())


def test_transform_factory(factory: TransformCreatureFactory) -> None:
    """Test transform factory Creatures: describe, attack, transform."""
    print("Testing Creature with transform capability")

    base = factory.create_base()
    print("base:")
    print(base.describe())
    print(base.attack())
    if isinstance(base, TransformCapability):
        print(base.transform())
        print(base.attack())
        print(base.revert())

    evolved = factory.create_evolved()
    print("evolved:")
    print(evolved.describe())
    print(evolved.attack())
    if isinstance(evolved, TransformCapability):
        print(evolved.transform())
        print(evolved.attack())
        print(evolved.revert())


if __name__ == "__main__":
    heal_factory = HealingCreatureFactory()
    transform_factory = TransformCreatureFactory()

    test_healing_factory(heal_factory)
    test_transform_factory(transform_factory)
