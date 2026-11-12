# ABOUTME: Picks each token with the model, but only tokens that keep the
# ABOUTME: output a valid prefix of a call are allowed.

import json
import re
from typing import Any

import numpy as np
from llm_sdk import Small_LLM_Model

MAX_TOKENS = 512


def generate_call(
    llm: Small_LLM_Model,
    prompt: str,
    complete: re.Pattern[str],
    prefix: re.Pattern[str],
) -> dict[str, Any]:
    """Generate one function call token by token.

    The tokens are tried from the highest logit down, and the first one that
    keeps the text a valid prefix is kept. Skipping the other tokens is the
    same as setting their logits to -inf and taking the argmax.

    Args:
        llm: Loaded language model.
        prompt: Chat prompt that the call continues.
        complete: Pattern that matches a finished call.
        prefix: Pattern that matches every valid partial call.

    Returns:
        The parsed call, with "name" and "parameters" keys.

    Raises:
        RuntimeError: If no token fits or the token limit is reached.
    """
    ids: list[int] = llm.encode(prompt)[0].tolist()
    text = ""
    for _ in range(MAX_TOKENS):
        logits = np.asarray(llm.get_logits_from_input_ids(ids))
        for token in np.argsort(-logits):
            piece = llm.decode([int(token)])
            # U+FFFD means the token is only part of a UTF-8 character.
            if piece and "\ufffd" not in piece:
                if prefix.fullmatch(text + piece):
                    break
        else:
            raise RuntimeError("no token keeps the output valid")
        ids.append(int(token))
        text += piece
        if complete.fullmatch(text):
            call: dict[str, Any] = json.loads(text)
            return call
    raise RuntimeError(f"no complete call within {MAX_TOKENS} tokens")
