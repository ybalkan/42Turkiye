# ABOUTME: Turns the function definitions into the two output patterns.
# ABOUTME: One pattern accepts whole calls, the other accepts partial ones.

import json
import re

from src.models import Function, ValueSpec
from src.values import VALUES, Piece, prefixes


def literal(text: str) -> Piece:
    """Build the piece for fixed text such as JSON punctuation.

    Args:
        text: Text the output must contain exactly.

    Returns:
        The pattern for the text and for its prefixes.
    """
    return re.escape(text), prefixes([text])


def value_piece(spec: ValueSpec) -> Piece:
    """Build the piece for one argument.

    Args:
        spec: Type of the argument and its allowed values, if any.

    Returns:
        The pattern for a complete value and for its prefixes.
    """
    if spec.enum is None:
        return VALUES[spec.type]
    words = [json.dumps(v, ensure_ascii=False) for v in spec.enum]
    return "|".join(re.escape(w) for w in words), prefixes(words)


def function_pieces(fn: Function) -> list[Piece]:
    """Split one call into fixed text and argument values, in output order.

    Args:
        fn: Function whose call format is needed.

    Returns:
        The pieces of the call, from its first character to its last.
    """
    name = json.dumps(fn.name, ensure_ascii=False)
    pieces = [literal('{"name": ' + name + ', "parameters": {')]
    for i, (param, spec) in enumerate(fn.parameters.items()):
        key = json.dumps(param, ensure_ascii=False)
        pieces.append(literal((", " if i else "") + key + ": "))
        pieces.append(value_piece(spec))
    pieces.append(literal("}}"))
    return pieces


def sequence(parts: list[str]) -> str:
    """Join regexes so that they must match one after another.

    Args:
        parts: Regexes to join; each one is grouped.

    Returns:
        The joined regex.
    """
    return "".join(f"(?:{part})" for part in parts)


def choice(parts: list[str]) -> str:
    """Join regexes so that any one of them may match.

    Args:
        parts: Regexes to join; each one is grouped.

    Returns:
        The joined regex.
    """
    return "|".join(f"(?:{part})" for part in parts)


def build_grammar(
    functions: list[Function],
) -> tuple[re.Pattern[str], re.Pattern[str]]:
    """Compile the calls of all functions into two patterns.

    A valid prefix is a run of complete pieces followed by a prefix of the
    next piece. One alternative per piece position covers all of them.

    Args:
        functions: Functions the model is allowed to call.

    Returns:
        The pattern for complete calls and the pattern for their prefixes.
    """
    full_calls: list[str] = []
    call_prefixes: list[str] = []
    for fn in functions:
        pieces = function_pieces(fn)
        full_calls.append(sequence([whole for whole, _ in pieces]))
        for i, (_, partial) in enumerate(pieces):
            done = [whole for whole, _ in pieces[:i]]
            call_prefixes.append(sequence(done + [partial]))
    return re.compile(choice(full_calls)), re.compile(choice(call_prefixes))
