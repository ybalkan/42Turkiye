# ABOUTME: Regular expressions for the JSON values the model may write.
# ABOUTME: Each value comes as a pair: the full pattern and its prefixes.

import re

# (pattern for the whole piece, pattern for every prefix of the piece)
Piece = tuple[str, str]

INTEGER = r"-?(?:0|[1-9][0-9]*)"
CHAR = r'(?:[^"\\\x00-\x1f]|\\["\\/bfnrt]|\\u[0-9a-fA-F]{4})'
STRING = '"' + CHAR + '*"'
# A string may also stop inside an escape, such as "abc\ or "abc\u00.
STRING_PREFIX = '"' + CHAR + r'*(?:\\(?:u[0-9a-fA-F]{0,3})?)?|' + STRING


def prefixes(words: list[str]) -> str:
    """Build a regex that matches every prefix of the words, including "".

    Args:
        words: Texts the output must spell out exactly.

    Returns:
        An alternation of all their prefixes.
    """
    return "|".join(re.escape(w[:i]) for w in words for i in range(len(w) + 1))


VALUES: dict[str, Piece] = {
    "integer": (INTEGER, r"-?(?:0|[1-9][0-9]*)?"),
    "number": (
        INTEGER + r"(?:\.[0-9]+)?",
        r"-?(?:(?:0|[1-9][0-9]*)(?:\.[0-9]*)?)?",
    ),
    "string": (STRING, STRING_PREFIX),
    "boolean": ("true|false", prefixes(["true", "false"])),
}
