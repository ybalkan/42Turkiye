import sys
import os
import site


def main() -> None:
    venv = os.environ.get("VIRTUAL_ENV")
    status = "Welcome to the construct" if venv else "You're still plugged in"
    print(f"MATRIX STATUS: {status}")
    print(f"Current Python: {sys.executable}")

    if venv:
        print(f"Virtual Environment: {os.path.basename(venv)}")
        print(f"Environment Path: {venv}")
        print("SUCCESS: You're in an isolated environment!")
        print("Safe to install packages without affecting")
        print("the global system.")
        print("Package installation path:")
        print(site.getsitepackages()[0])
    else:
        print("Virtual Environment: None detected")
        print("WARNING: You're in the global environment!")
        print("The machines can see everything you install.")
        print("To enter the construct, run:")
        print("    python -m venv matrix_env")
        print("    source matrix_env/bin/activate  # On Unix")
        print("    matrix_env\\Scripts\\activate      # On Windows")
        print("Then run this program again.")


if __name__ == "__main__":
    main()
