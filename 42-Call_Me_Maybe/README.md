*This project has been created as part of the 42 curriculum by ybalkan.*

# Call Me Maybe

## Description

Call Me Maybe turns a natural-language request into a structured function call.
The program reads a list of function definitions (names, parameter names,
parameter types and a description) and a list of prompts. For each prompt it
chooses the function that fits the request and fills in its arguments with the
right types. It does not answer the question itself:

```text
What is the sum of 40 and 2?
→ {"name": "fn_add_numbers", "parameters": {"a": 40.0, "b": 2.0}}
```

The language model is **Qwen/Qwen3-0.6B**. A model this small often writes
invalid JSON when it is only asked to. The program therefore restricts every
token the model may write (**constrained decoding**), so every output is valid
JSON and uses exactly the function names, parameter names and types from the
definitions.

The result is written to a JSON file with one entry per prompt, in the same
order as the prompts.

## Instructions

### Requirements

- Python 3.10 or later
- [uv](https://docs.astral.sh/uv/), which installs the other dependencies
- The `llm_sdk/` folder, included in this repository
- An internet connection on the first run, to download the model from Hugging Face

No compilation is needed. The project is a Python package started with `python -m`.

### Installation

From the project folder:

```bash
uv sync
```

This creates `.venv/` and installs the locked dependencies from `uv.lock`:
`llm_sdk` (from the local folder), `numpy` and `pydantic`, plus the development
tools `flake8` and `mypy`.

### Execution

Run the program with the default files:

```bash
uv run python -m src
```

| Option | Default file |
|---|---|
| `--functions_definition` | `data/input/functions_definition.json` |
| `--input` | `data/input/function_calling_tests.json` |
| `--output` | `data/output/function_calls.json` |

Any of them can be changed:

```bash
uv run python -m src \
  --functions_definition data/input/functions_definition.json \
  --input data/input/function_calling_tests.json \
  --output data/output/function_calls.json
```

The output folder is created when it does not exist. The program prints the
result of each prompt and then `Wrote N result(s) to <output file>`. Errors are
printed on the standard error output, and the exit code is 1.

Messages from the model libraries, such as the Hugging Face notice about
unauthenticated requests or a torch notice about redirects on macOS, are not
errors of this program.

### Makefile

| Command | What it does |
|---|---|
| `make install` | Runs `uv sync`. |
| `make run` | Runs `uv run python -m src`. Options can be passed with `ARGS`, for example `make run ARGS="--input other.json"`. |
| `make debug` | Runs the program under Python's debugger, `pdb`. |
| `make lint` | Runs `flake8 .` and `mypy` with the flags required for this project. |
| `make lint-strict` | Runs `flake8 .` and `mypy . --strict`. |
| `make clean` | Removes the `__pycache__` and `.mypy_cache` folders. |

### Project structure

```text
.
├── data/
│   ├── input/
│   │   ├── functions_definition.json    function definitions
│   │   └── function_calling_tests.json  prompts
│   └── output/                          created by the program, not committed
├── llm_sdk/                             provided model wrapper
├── src/
│   ├── __init__.py
│   ├── __main__.py                      entry point for python -m src
│   ├── cli.py                           arguments, main loop, error messages
│   ├── models.py                        pydantic models and validation
│   ├── files.py                         reading and writing JSON files
│   ├── values.py                        regular expressions for JSON values
│   ├── grammar.py                       output patterns built from the definitions
│   ├── prompt.py                        chat prompt that lists the functions
│   └── decoder.py                       token-by-token constrained decoding
├── .flake8
├── .gitignore
├── Makefile
├── README.md
├── pyproject.toml
└── uv.lock
```

## Algorithm

The program works in five steps.

1. **Grammar from the definitions.** Each function is split into pieces. A
   piece is either fixed text, such as `{"name": "fn_add_numbers", "parameters": {"a": `,
   or a typed value: `number`, `integer`, `string`, `boolean`, or one of the
   values listed in an `enum`. For every piece, two regular expressions are
   built: one that matches the whole piece, and one that matches every prefix
   of it, including the empty string. Together they give two patterns for the
   whole call. One matches a complete call. The other matches every valid
   prefix of a call, that is, a run of complete pieces followed by a prefix of
   the next piece.

2. **Prompt.** The request is wrapped in the chat format of Qwen3. The system
   message lists the functions with their parameter types and allowed values.
   Thinking is switched off with an empty `<think>` block, so the answer starts
   directly with the call.

3. **Token selection.** The prompt is encoded into token IDs. At each step the
   model returns a logit for every token, and the tokens are sorted from the
   highest logit to the lowest. The first token whose text keeps the output a
   valid prefix is appended. Skipping the other tokens is the same as setting
   their logits to `-inf` and taking the argmax. A token whose text is only part
   of a UTF-8 character is never chosen. Decoding is greedy, so the same input
   always gives the same output.

4. **Stop and parse.** As soon as the text matches the pattern for complete
   calls, it is parsed with `json.loads`. If no complete call appears within
   512 tokens, or no token keeps the output valid, the prompt is reported as an
   error.

5. **Output.** Arguments of type `number` are written as floats (`2.0`, not
   `2`), and the entry is added to the output list. A prompt that fits no
   function gets an entry with an empty `name` and `"parameters": {}`; see the
   design decisions below.

The program uses only the public parts of the SDK: the constructor and the
methods `encode`, `get_logits_from_input_ids` and `decode`.

## Design Decisions

- **The model chooses the function.** The function name and the arguments come
  from the model's logits. There is no keyword matching and no heuristic.
- **The definitions drive the output.** The grammar is built from
  `functions_definition.json`. Changing the definitions changes what the model
  may write, without any code change.
- **Validity by construction.** Only tokens that keep the output a valid prefix
  can be chosen. The output is therefore always parseable and has exactly the
  keys, function names and parameter names of the definitions.
- **One entry per prompt, in order.** The grader compares the output with the
  expected answers by position, so every prompt keeps its entry. A prompt that
  fits no function gets an empty `name` and no parameters. The other entries do
  not move, and `name` stays a string, as the output format requires.
- **Validation before loading the model.** The definitions and the prompts are
  validated with pydantic before the model is loaded. A malformed input file
  fails immediately instead of after the model has been loaded.
- **Errors are short messages.** Bad JSON, missing files, invalid definitions,
  duplicate function names, an output path that cannot be written, and prompts
  that fit no function print a message without a traceback and end with exit
  code 1. A failed prompt does not stop the other prompts.
- **Standard library regular expressions.** The prefix check uses the `re`
  module of the standard library. The runtime dependencies are `numpy`,
  `pydantic` and the provided `llm_sdk`.
- **Small modules.** Each file in `src/` has one job, as shown in the project
  structure.

## Performance Analysis

The results below were measured with Qwen/Qwen3-0.6B on a Mac with Apple
Silicon, using the MPS backend and float16 weights, which the SDK selects
automatically.

**Accuracy**

| Test set | Result |
|---|---|
| The 11 provided prompts (`data/input/function_calling_tests.json`), checked by hand against the expected function and arguments | 11 of 11 correct |
| The evaluation set of the moulinette (6 functions, 11 prompts) | 10 of 11 correct (90.9%) |

The one miss in the evaluation set is a string argument that contains
quotation marks: the model dropped the quotation marks instead of writing them
as `\"`. See Known Limitations.

**Speed**

The 11 provided prompts take about 55 seconds in total, including loading the
model, which is about 5 seconds per prompt. On this machine, about 50 to 60
prompts would reach the five-minute limit. Runs on a CPU were not measured.

Each generated token needs one forward pass over the whole prompt, because the
SDK does not expose a key-value cache. For this reason the list of functions in
the prompt is kept short.

**Reliability**

- Decoding is greedy, so the same input gives the same output. Repeated runs
  produced identical files.
- Every entry for a prompt that fits a function is valid JSON with exactly the
  keys `prompt`, `name` and `parameters`, and every argument has the type of its
  definition.
- Every prompt has an entry, in input order, including the prompts that fit no
  function.

## Challenges Faced

- **Tokens that split UTF-8 characters.** Some tokens hold only part of a
  character, and their text cannot be checked on its own. Such tokens are never
  chosen. Complete characters remain possible through their own tokens.
- **Knowing when a partial text can still become valid.** A pattern for complete
  calls cannot answer this for an unfinished output. The per-piece prefix
  patterns solve it. Step 3 of the testing strategy
  checks this.
- **Numbers.** When the grammar required a decimal point, the model repeated
  zeros. The fraction was made optional, and `number` arguments are converted to
  floats after generation.
- **Prompts that fit no function.** Without an extra option, the model had to
  choose one of the real functions, so unrelated prompts received a wrong call.
  The internal option `fn_none` was added. In the tests the model chose it for
  every unrelated prompt except one (see Known Limitations).
- **Speed.** Every token costs one forward pass over the prompt, and the SDK
  provides no cache. The prompt was therefore kept short.
- **Position-based grading.** Dropping an unmatched prompt would shift all
  following results. This is why every prompt keeps an entry.

## Testing Strategy

Step 2 checks the code itself, and step 3 checks the output patterns without
the model. Steps 4 to 9 check the program from the outside, with the commands
and inputs a user would use. The project has no automated test suite. The
steps can be repeated in this order, and each one states the expected result.

### Step 1: install

```bash
uv sync
```

Expected: the command finishes without errors.

### Step 2: static checks

```bash
make lint
make lint-strict
```

Expected: flake8 prints nothing, and mypy prints `Success: no issues found in
... source files` for both commands.

### Step 3: check the output patterns

The output patterns are what make the output valid, so they are checked on
their own, without the model. Run this from the project folder:

```bash
uv run python - <<'EOF'
from src.grammar import build_grammar
from src.models import Function

fn = Function.model_validate({"name": "fn_greet", "parameters": {"name": {"type": "string"}}})
complete, prefix = build_grammar([fn])
call = '{"name": "fn_greet", "parameters": {"name": "Ada"}}'
print("complete call accepted:", bool(complete.fullmatch(call)))
print("every prefix accepted:", all(prefix.fullmatch(call[:i]) for i in range(len(call) + 1)))
print("wrong function name rejected:", not prefix.fullmatch('{"name": "fn_other"'))
print("wrong argument type rejected:", not prefix.fullmatch('{"name": "fn_greet", "parameters": {"name": 5'))

fn2 = Function.model_validate({"name": "fn_set_unit", "parameters": {"unit": {"type": "string", "enum": ["celsius", "fahrenheit"]}}})
complete2, prefix2 = build_grammar([fn2])
print("allowed enum value accepted:", bool(complete2.fullmatch('{"name": "fn_set_unit", "parameters": {"unit": "celsius"}}')))
print("unknown enum value rejected:", not prefix2.fullmatch('{"name": "fn_set_unit", "parameters": {"unit": "kelvin"'))
EOF
```

Expected: six lines, each ending with `True`.

### Step 4: run on the provided inputs

```bash
make run
```

Expected: one line per prompt with the chosen function and its arguments,
followed by `Wrote 11 result(s) to data/output/function_calls.json`. The exit
code is 0.

### Step 5: check the output file

Run this from the project folder after step 4:

```bash
uv run python - <<'EOF'
import json

defs = {f["name"]: f["parameters"] for f in json.load(open("data/input/functions_definition.json"))}
types = {"number": float, "integer": int, "string": str, "boolean": bool}
for entry in json.load(open("data/output/function_calls.json")):
    assert set(entry) == {"prompt", "name", "parameters"}, entry
    if entry["name"] not in defs:
        print("no function for:", entry["prompt"])
        continue
    params = defs[entry["name"]]
    assert set(entry["parameters"]) == set(params), entry
    for key, spec in params.items():
        value = entry["parameters"][key]
        assert type(value) is types[spec["type"]], entry
        assert "enum" not in spec or value in spec["enum"], entry
print("output checked")
EOF
```

Expected: `output checked`. The script checks that the file is valid JSON, that
every entry has exactly the keys `prompt`, `name` and `parameters`, that every
argument has the right name and type, and that `enum` values are allowed. A
prompt that fits no function is listed as `no function for:`; it is an
expected result, not an error of the file format.

### Step 6: repeat the run and compare

```bash
uv run python -m src --output /tmp/run_1.json
uv run python -m src --output /tmp/run_2.json
diff /tmp/run_1.json /tmp/run_2.json && echo "identical"
```

Expected: `identical`.

### Step 7: error handling

Each command below prints the message shown after it and ends with exit code 1.
`echo "exit code: $?"` prints the exit code. The wording of system errors can
differ between systems.

```bash
printf '[{"prompt": "x",}]' > /tmp/cmm_broken.json
uv run python -m src --input /tmp/cmm_broken.json; echo "exit code: $?"
# Error: '/tmp/cmm_broken.json' is not valid JSON: ...

uv run python -m src --input /tmp/cmm_missing.json; echo "exit code: $?"
# Error: cannot read '/tmp/cmm_missing.json': No such file or directory

uv run python -m src --functions_definition /tmp/cmm_missing_defs.json; echo "exit code: $?"
# Error: cannot read '/tmp/cmm_missing_defs.json': No such file or directory

printf '[]' > /tmp/cmm_empty.json
uv run python -m src --functions_definition /tmp/cmm_empty.json; echo "exit code: $?"
# Error: '/tmp/cmm_empty.json' has the wrong format: ... at least 1 item

printf '[{"name":"fn_x","parameters":{"x":{"type":"float"}}}]' > /tmp/cmm_type.json
uv run python -m src --functions_definition /tmp/cmm_type.json; echo "exit code: $?"
# Error: '/tmp/cmm_type.json' has the wrong format: ... Input should be 'number', 'integer', 'string' or 'boolean'

printf '[{"name":"fn_x","parameters":{}},{"name":"fn_x"}]' > /tmp/cmm_dup.json
uv run python -m src --functions_definition /tmp/cmm_dup.json; echo "exit code: $?"
# Error: '/tmp/cmm_dup.json' has the wrong format: ... function names must be unique

printf '[{"prompt": "What is the capital of France?"}]' > /tmp/cmm_nomatch.json
uv run python -m src --input /tmp/cmm_nomatch.json --output /tmp/cmm_out.json; echo "exit code: $?"
# Error: 'What is the capital of France?': no function matches the request
# Error: 1 prompt(s) could not be processed
# /tmp/cmm_out.json contains one entry with "name": "" and "parameters": {}

uv run python -m src --input /tmp/cmm_nomatch.json --output /nonexistent_dir/out.json; echo "exit code: $?"
# Error: [Errno ...] ... on a system where the folder cannot be created
```

### Step 8: evaluation with the moulinette

The moulinette is the evaluation tool of the project. It is not part of this
repository. Replace `<moulinette_dir>` with its folder and `<project_dir>` with
the folder of this project.

```bash
# 1. install the moulinette
cd <moulinette_dir>
uv sync

# 2. generate the private exercise set
uv run python -m moulinette prepare_exercises --set private

# 3. run the program on the generated inputs
cd <project_dir>
uv run python -m src \
  --functions_definition <moulinette_dir>/data/input/functions_definition.json \
  --input <moulinette_dir>/data/input/function_calling_tests.json \
  --output <moulinette_dir>/data/input/function_calls.json

# 4. grade the answers
cd moulinette
uv sync
uv run python -m moulinette prepare_exercises --set private
cd ..

uv run python -m src \
  --functions_definition moulinette/data/input/functions_definition.json \
  --input moulinette/data/input/function_calling_tests.json \
  --output moulinette/data/input/function_calls.json

cd moulinette
uv run python -m moulinette grade_student_answers \
  --set private --student_answer_path data/input/function_calls.json
```

Expected: the score is greater than 0, and the grading finishes without errors.
The prepare command replaces the input files of the moulinette, so run it
with `--set private` before grading the private set.

### Step 9: manual checks

Beyond the provided prompts, the following were checked by hand:

- an empty prompt, an empty string argument (`Reverse the string ''`), a 30-digit
  number, a non-ASCII name (`Ayşe`), and decimal and negative numbers (`0.5`,
  `-7`);
- `enum`, `integer` and `boolean` parameters, with a custom definitions file;
- an ambiguous prompt, `Who are you?`, which the model matches to `fn_greet`
  (see Known Limitations);
- a list of 19 prompts, 11 of which fit a function and 8 of which fit none. The
  11 calls are correct, and the 8 unmatched prompts get an empty `name` and the
  error message.

## Known Limitations

- **Prompts that fit no function.** The model does not always recognize them.
  `Who are you?` was matched to `fn_greet`.
- **Quotation marks inside strings.** In one case the model wrote `Say hello`
  for `Say "hello"` instead of escaping the quotation marks.
- **Speed.** About 5 seconds per prompt on the test machine (see Performance
  Analysis).
- **Argument types.** `number`, `integer`, `string` and `boolean` are supported.
  Parameters of other types, such as arrays and objects, are rejected with an
  error message.
- **Allowed values.** They are given with the key `enum`, as in JSON Schema.
- **Platforms.** The program was tested on macOS with Apple Silicon only. Runs
  on a CPU or on CUDA were not measured.

## Example Usage

Input file (`data/input/function_calling_tests.json`, shortened):

```json
[
  {"prompt": "What is the sum of 2 and 3?"},
  {"prompt": "Reverse the string 'hello'"}
]
```

Command:

```bash
uv run python -m src
```

Output (`data/output/function_calls.json`):

```json
[
  {
    "prompt": "What is the sum of 2 and 3?",
    "name": "fn_add_numbers",
    "parameters": {"a": 2.0, "b": 3.0}
  },
  {
    "prompt": "Reverse the string 'hello'",
    "name": "fn_reverse_string",
    "parameters": {"s": "hello"}
  }
]
```

A prompt that fits no function, such as `What is the capital of France?`, is
reported on the standard error output and written with an empty name:

```json
{"prompt": "What is the capital of France?", "name": "", "parameters": {}}
```

## Resources

References:

- [Python documentation](https://docs.python.org/3/), for `argparse`, `json`, `re`, `pathlib` and `typing`
- [Regular expression syntax in Python](https://docs.python.org/3/library/re.html)
- [Pydantic documentation](https://docs.pydantic.dev/)
- [uv documentation](https://docs.astral.sh/uv/)
- [JSON specification (RFC 8259)](https://www.rfc-editor.org/rfc/rfc8259)
- [PEP 257: Docstring conventions](https://peps.python.org/pep-0257/)
- [Qwen3-0.6B model card](https://huggingface.co/Qwen/Qwen3-0.6B)
- [Efficient Guided Generation for Large Language Models](https://arxiv.org/abs/2307.09702), on regular-expression guided decoding
- [LM Format Enforcer](https://github.com/noamgat/lm-format-enforcer), a library for constrained decoding

AI usage:

AI tools were used as learning and writing aids. They helped to explain
function calling, logits, tokenization and constrained decoding; to draft the
regular expressions in `src/values.py` and `src/grammar.py`; to review the code against the project
requirements; and to edit this README. Every generated result was run and
checked by the author, who can explain how the code works.
