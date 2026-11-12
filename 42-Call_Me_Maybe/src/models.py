# ABOUTME: Pydantic models for the input files and the output entries.
# ABOUTME: Validation happens here, so the rest of the code can trust the data.

from typing import Annotated, Any, Literal

from pydantic import AfterValidator, BaseModel, Field, TypeAdapter

Scalar = str | int | float | bool
NO_MATCH_NAME = "fn_none"
NO_MATCH_TEXT = (
    "Use this function only when none of the other available functions "
    "matches the user request. It takes no arguments."
)


class ValueSpec(BaseModel):
    """Type of one parameter, optionally limited to a list of values."""

    type: Literal["number", "integer", "string", "boolean"]
    enum: Annotated[list[Scalar], Field(min_length=1)] | None = None


class Function(BaseModel):
    """One entry of functions_definition.json."""

    name: str
    description: str = ""
    parameters: dict[str, ValueSpec] = {}


class Prompt(BaseModel):
    """One entry of the input prompts file."""

    prompt: str


class Result(BaseModel):
    """One entry of the output file."""

    prompt: str
    name: str
    parameters: dict[str, Any]


def _unique_names(functions: list[Function]) -> list[Function]:
    """Reject two functions that share a name."""
    names = [fn.name for fn in functions]
    if len(set(names)) != len(names):
        raise ValueError("function names must be unique")
    return functions


FUNCTION_LIST = Annotated[
    list[Function], Field(min_length=1), AfterValidator(_unique_names)
]
FUNCTIONS_FILE = TypeAdapter(FUNCTION_LIST)
PROMPTS_FILE = TypeAdapter(list[Prompt])


def no_match(functions: list[Function]) -> Function:
    """Build the internal option for prompts that fit no function.

    Args:
        functions: The real functions. The option must not reuse their names.

    Returns:
        A function without parameters and with a name that is not taken.
    """
    name = NO_MATCH_NAME
    while any(fn.name == name for fn in functions):
        name += "_"
    return Function(name=name, description=NO_MATCH_TEXT)
