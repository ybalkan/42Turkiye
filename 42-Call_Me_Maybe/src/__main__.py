# ABOUTME: Entry point for `uv run python -m src`.
# ABOUTME: Passes control to the command-line interface.

from src.cli import main

if __name__ == "__main__":
    main()
