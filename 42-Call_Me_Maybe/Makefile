.PHONY: install run debug lint lint-strict clean

install:
	uv sync

run:
	uv run python -m src $(ARGS)

debug:
	uv run python -m pdb -m src $(ARGS)

lint:
	uv run flake8 .
	uv run mypy . --warn-return-any --warn-unused-ignores --ignore-missing-imports --disallow-untyped-defs --check-untyped-defs

lint-strict:
	uv run flake8 .
	uv run mypy . --strict

clean:
	find . -path ./.venv -prune -o \( -name __pycache__ -o -name .mypy_cache \) -type d -exec rm -rf {} +
