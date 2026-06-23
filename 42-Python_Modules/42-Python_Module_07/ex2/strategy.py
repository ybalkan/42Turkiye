"""Battle strategy abstract class and concrete strategy implementations."""

from abc import ABC, abstractmethod
from ex0.creature import Creature
from ex1.capability import HealCapability, TransformCapability


class BattleStrategy(ABC):
    """Abstract strategy for Creature battle actions."""

    @abstractmethod
    def is_valid(self, creature: Creature) -> bool:
        """Return True if the strategy is valid for the given Creature."""
        ...

    @abstractmethod
    def act(self, creature: Creature) -> None:
        """Execute the battle strategy for the given Creature."""
        ...


class NormalStrategy(BattleStrategy):
    """A strategy suitable for any Creature: simply attacks."""

    def is_valid(self, creature: Creature) -> bool:
        """Always valid for any Creature."""
        return True

    def act(self, creature: Creature) -> None:
        """Execute a normal attack."""
        print(creature.attack())


class AggressiveStrategy(BattleStrategy):
    """Strategy for Creatures with TransformCapability."""

    def is_valid(self, creature: Creature) -> bool:
        """Valid only for Creatures with TransformCapability."""
        return isinstance(creature, TransformCapability)

    def act(self, creature: Creature) -> None:
        """Transform, attack, then revert."""
        if not self.is_valid(creature):
            raise ValueError(
                f"Invalid Creature '{creature.name}' "
                "for this aggressive strategy"
            )
        assert isinstance(creature, TransformCapability)
        print(creature.transform())
        print(creature.attack())
        print(creature.revert())


class DefensiveStrategy(BattleStrategy):
    """A strategy for Creatures with HealCapability: attack then heal."""

    def is_valid(self, creature: Creature) -> bool:
        """Valid only for Creatures with HealCapability."""
        return isinstance(creature, HealCapability)

    def act(self, creature: Creature) -> None:
        """Attack then heal."""
        if not self.is_valid(creature):
            raise ValueError(
                f"Invalid Creature '{creature.name}' "
                "for this defensive strategy"
            )
        assert isinstance(creature, HealCapability)
        print(creature.attack())
        print(creature.heal())
