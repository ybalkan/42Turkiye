"""Creature factory abstract base and concrete factory implementations."""

from abc import ABC, abstractmethod
from ex0.creature import Creature, Flameling, Pyrodon, Aquabub, Torragon


class CreatureFactory(ABC):
    """Abstract factory for creating Creature families."""

    @abstractmethod
    def create_base(self) -> Creature:
        """Create and return the base Creature of the family."""
        ...

    @abstractmethod
    def create_evolved(self) -> Creature:
        """Create and return the evolved Creature of the family."""
        ...


class FlameFactory(CreatureFactory):
    """Factory for creating Fire-type Creatures."""

    def create_base(self) -> Creature:
        """Create and return a Flameling."""
        return Flameling()

    def create_evolved(self) -> Creature:
        """Create and return a Pyrodon."""
        return Pyrodon()


class AquaFactory(CreatureFactory):
    """Factory for creating Water-type Creatures."""

    def create_base(self) -> Creature:
        """Create and return an Aquabub."""
        return Aquabub()

    def create_evolved(self) -> Creature:
        """Create and return a Torragon."""
        return Torragon()
