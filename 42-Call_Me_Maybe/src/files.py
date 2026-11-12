# ABOUTME: Reads and writes the JSON files used by the program.
# ABOUTME: Read errors become one readable message instead of a traceback.

import json
from pathlib import Path
from typing import TypeVar

from pydantic import TypeAdapter

from src.models import Result

T = TypeVar("T")


def load_json(path: str, adapter: TypeAdapter[T]) -> T:
    """Read a JSON file and validate its content.

    Args:
        path: File to read.
        adapter: Type that the content must have.

    Returns:
        The validated content.

    Raises:
        OSError: If the file cannot be read.
        ValueError: If the JSON is malformed or has the wrong shape.
    """
    try:
        with open(path, encoding="utf-8") as f:
            data = json.load(f)
    except OSError as e:
        raise OSError(f"cannot read '{path}': {e.strerror}") from e
    except ValueError as e:
        raise ValueError(f"'{path}' is not valid JSON: {e}") from e
    try:
        return adapter.validate_python(data)
    except ValueError as e:
        raise ValueError(f"'{path}' has the wrong format: {e}") from e


def save_results(path: str, results: list[Result]) -> None:
    """Write the results as a JSON array, creating folders if needed.

    Args:
        path: File to write.
        results: Entries, in prompt order.
    """
    output = Path(path)
    output.parent.mkdir(parents=True, exist_ok=True)
    data = [r.model_dump() for r in results]
    text = json.dumps(data, indent=2, ensure_ascii=False, allow_nan=False)
    output.write_text(text + "\n", encoding="utf-8")
