"""Capability abstract classes for Creatures."""

from abc import ABC, abstractmethod


class HealCapability(ABC):
    """Abstract capability class for Creatures that can heal."""

    @abstractmethod
    def heal(self) -> str:
        """Return a string describing the heal action."""
        ...


class TransformCapability(ABC):
    """Abstract capability class for Creatures that can transform."""

    def __init__(self) -> None:
        """Initialize the transform state."""
        self.transformed: bool = False

    @abstractmethod
    def transform(self) -> str:
        """Return a string describing the transform action."""
        ...

    @abstractmethod
    def revert(self) -> str:
        """Return a string describing the revert action."""
        ...
