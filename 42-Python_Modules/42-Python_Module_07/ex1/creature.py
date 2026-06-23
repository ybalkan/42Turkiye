"""Concrete Creature classes with capabilities for ex1."""

from ex0.creature import Creature
from ex1.capability import HealCapability, TransformCapability


class Sproutling(Creature, HealCapability):
    """A Grass type base Creature with healing capability."""

    def __init__(self) -> None:
        """Initialize Sproutling."""
        Creature.__init__(self, "Sproutling", "Grass")

    def attack(self) -> str:
        """Return Sproutling's attack."""
        return "Sproutling uses Vine Whip!"

    def heal(self) -> str:
        """Return Sproutling's heal action."""
        return "Sproutling heals itself for a small amount"


class Bloomelle(Creature, HealCapability):
    """A Grass/Fairy type evolved Creature with healing capability."""

    def __init__(self) -> None:
        """Initialize Bloomelle."""
        Creature.__init__(self, "Bloomelle", "Grass/Fairy")

    def attack(self) -> str:
        """Return Bloomelle's attack."""
        return "Bloomelle uses Petal Dance!"

    def heal(self) -> str:
        """Return Bloomelle's heal action."""
        return "Bloomelle heals itself and others for a large amount"


class Shiftling(Creature, TransformCapability):
    """A Normal type base Creature with transform capability."""

    def __init__(self) -> None:
        """Initialize Shiftling."""
        Creature.__init__(self, "Shiftling", "Normal")
        TransformCapability.__init__(self)

    def attack(self) -> str:
        """Return Shiftling's attack, boosted if transformed."""
        if self.transformed:
            return "Shiftling performs a boosted strike!"
        return "Shiftling attacks normally."

    def transform(self) -> str:
        """Return Shiftling's transform action."""
        self.transformed = True
        return "Shiftling shifts into a sharper form!"

    def revert(self) -> str:
        """Return Shiftling's revert action."""
        self.transformed = False
        return "Shiftling returns to normal."


class Morphagon(Creature, TransformCapability):
    """A Normal/Dragon type evolved Creature with transform capability."""

    def __init__(self) -> None:
        """Initialize Morphagon."""
        Creature.__init__(self, "Morphagon", "Normal/Dragon")
        TransformCapability.__init__(self)

    def attack(self) -> str:
        """Return Morphagon's attack, boosted if transformed."""
        if self.transformed:
            return "Morphagon unleashes a devastating morph strike!"
        return "Morphagon attacks normally."

    def transform(self) -> str:
        """Return Morphagon's transform action."""
        self.transformed = True
        return "Morphagon morphs into a dragonic battle form!"

    def revert(self) -> str:
        """Return Morphagon's revert action."""
        self.transformed = False
        return "Morphagon stabilizes its form."
