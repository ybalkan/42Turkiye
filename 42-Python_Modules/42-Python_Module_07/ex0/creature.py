from abc import ABC, abstractmethod


class Creature(ABC):

    def __init__(self, name: str, creature_type: str) -> None:
        self.name = name
        self.creature_type = creature_type

    def describe(self) -> str:
        return f"{self.name} is a {self.creature_type} type Creature"

    @abstractmethod
    def attack(self) -> str:
        ...


class Flameling(Creature):

    def __init__(self) -> None:
        super().__init__("Flameling", "Fire")

    def attack(self) -> str:
        return "Flameling uses Ember!"


class Pyrodon(Creature):
    def __init__(self) -> None:
        super().__init__("Pyrodon", "Fire/Flying")

    def attack(self) -> str:
        return "Pyrodon uses Flamethrower!"


class Aquabub(Creature):
    def __init__(self) -> None:
        """Initialize Aquabub."""
        super().__init__("Aquabub", "Water")

    def attack(self) -> str:
        """Return Aquabub's attack."""
        return "Aquabub uses Water Gun!"


class Torragon(Creature):
    def __init__(self) -> None:
        """Initialize Torragon."""
        super().__init__("Torragon", "Water")

    def attack(self) -> str:
        """Return Torragon's attack."""
        return "Torragon uses Hydro Pump!"
