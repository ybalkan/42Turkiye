"""Creature factories for ex1 Creatures with capabilities."""

from ex0.factory import CreatureFactory
from ex0.creature import Creature
from ex1.creature import Sproutling, Bloomelle, Shiftling, Morphagon


class HealingCreatureFactory(CreatureFactory):
    """Factory for creating Creatures with healing capability."""

    def create_base(self) -> Creature:
        """Create and return a Sproutling."""
        return Sproutling()

    def create_evolved(self) -> Creature:
        """Create and return a Bloomelle."""
        return Bloomelle()


class TransformCreatureFactory(CreatureFactory):
    """Factory for creating Creatures with transform capability."""

    def create_base(self) -> Creature:
        """Create and return a Shiftling."""
        return Shiftling()

    def create_evolved(self) -> Creature:
        """Create and return a Morphagon."""
        return Morphagon()
