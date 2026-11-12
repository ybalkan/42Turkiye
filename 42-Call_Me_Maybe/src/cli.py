# ABOUTME: Command-line interface: loads the inputs, makes one call per prompt
# ABOUTME: and writes the results. Every failure ends with a short message.

import argparse
import sys
from typing import Any

from llm_sdk import Small_LLM_Model

from src.decoder import generate_call
from src.files import load_json, save_results
from src.grammar import build_grammar
from src.models import FUNCTIONS_FILE, PROMPTS_FILE, Function, Result, no_match
from src.prompt import build_prompt

MODEL = "Qwen/Qwen3-0.6B"
DEFAULT_DEFINITIONS = "data/input/functions_definition.json"
DEFAULT_INPUT = "data/input/function_calling_tests.json"
DEFAULT_OUTPUT = "data/output/function_calls.json"


def parse_args() -> argparse.Namespace:
    """Read the optional file paths from the command line.

    Returns:
        The parsed arguments.
    """
    parser = argparse.ArgumentParser(description="Turn prompts into calls.")
    parser.add_argument("--functions_definition", default=DEFAULT_DEFINITIONS)
    parser.add_argument("--input", default=DEFAULT_INPUT)
    parser.add_argument("--output", default=DEFAULT_OUTPUT)
    return parser.parse_args()


def to_result(prompt: str, call: dict[str, Any], fn: Function) -> Result:
    """Build one output entry. Number arguments are written as floats.

    Args:
        prompt: The original request.
        call: The parsed call, with "name" and "parameters" keys.
        fn: The function that was called.

    Returns:
        The entry for the output file.
    """
    params = {
        key: float(value) if fn.parameters[key].type == "number" else value
        for key, value in call["parameters"].items()
    }
    return Result(prompt=prompt, name=fn.name, parameters=params)


def no_call(prompt: str) -> Result:
    """Build the entry for a prompt that got no call.

    The entry is kept so that the output stays in the same order as the
    prompts; the grader compares entries by position.

    Args:
        prompt: The original request.

    Returns:
        An entry with an empty name and no parameters.
    """
    return Result(prompt=prompt, name="", parameters={})


def run(args: argparse.Namespace) -> None:
    """Make one call per prompt and save the results.

    Args:
        args: Parsed command-line arguments.

    Raises:
        SystemExit: If some prompts could not be processed.
    """
    functions = load_json(args.functions_definition, FUNCTIONS_FILE)
    prompts = load_json(args.input, PROMPTS_FILE)
    fallback = no_match(functions)
    options = [*functions, fallback]
    complete, prefix = build_grammar(options)
    by_name = {fn.name: fn for fn in functions}
    llm = Small_LLM_Model(MODEL)

    results: list[Result] = []
    failed = 0
    for item in prompts:
        try:
            text = build_prompt(options, item.prompt)
            call = generate_call(llm, text, complete, prefix)
            if call["name"] == fallback.name:
                raise RuntimeError("no function matches the request")
        except RuntimeError as e:
            print(f"Error: {item.prompt!r}: {e}", file=sys.stderr)
            results.append(no_call(item.prompt))
            failed += 1
            continue
        result = to_result(item.prompt, call, by_name[call["name"]])
        results.append(result)
        print(f"{item.prompt} -> {result.name} {result.parameters}")

    save_results(args.output, results)
    print(f"Wrote {len(results)} result(s) to {args.output}")
    if failed:
        sys.exit(f"Error: {failed} prompt(s) could not be processed")


def main() -> None:
    """Run the program. Any error becomes a short message and exit code 1."""
    try:
        run(parse_args())
    except Exception as e:  # never show a traceback to the user
        sys.exit(f"Error: {e}")
