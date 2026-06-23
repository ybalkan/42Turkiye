from abc import ABC, abstractmethod


class HealCapability(ABC):
    @abstractmethod
    def heal(self) -> str:
        ...


class TransformCapability(ABC):

    def __init__(self) -> None:
        self.transformed: bool = False

    @abstractmethod
    def transform(self) -> str:
        """Return a string describing the transform action."""
        ...

    @abstractmethod
    def revert(self) -> str:
        """Return a string describing the revert action."""
        ...
