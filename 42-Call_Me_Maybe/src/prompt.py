# ABOUTME: Builds the chat prompt that lists the available functions.
# ABOUTME: Thinking is switched off so that the answer starts with the call.

import json

from src.models import Function

SYSTEM = (
    "Convert the user request into one function call. "
    'Reply with JSON only: {"name": <function name>, '
    '"parameters": {<parameter name>: <value>}}.'
)


def describe(fn: Function) -> str:
    """Write one line with the function's signature and purpose.

    Args:
        fn: Function to describe.

    Returns:
        A line such as "fn_greet(name: string): Generate a greeting."
    """
    params: list[str] = []
    for name, spec in fn.parameters.items():
        text = f"{name}: {spec.type}"
        if spec.enum is not None:
            text += f" one of {json.dumps(spec.enum, ensure_ascii=False)}"
        params.append(text)
    return f"{fn.name}({', '.join(params)}): {fn.description}"


def build_prompt(functions: list[Function], user_prompt: str) -> str:
    """Build the Qwen3 chat prompt, ready to be encoded.

    Args:
        functions: Functions to list for the model.
        user_prompt: Text of the request.

    Returns:
        The full prompt. The empty think block turns thinking off.
    """
    listing = "\n".join(describe(fn) for fn in functions)
    return (
        f"<|im_start|>system\n{SYSTEM}\nFunctions:\n{listing}<|im_end|>\n"
        f"<|im_start|>user\n{user_prompt}<|im_end|>\n"
        "<|im_start|>assistant\n<think>\n\n</think>\n\n"
    )
