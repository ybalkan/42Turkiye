import importlib
import importlib.util
from typing import Optional


REQUIRED = ["pandas", "numpy", "matplotlib"]

LABELS: dict[str, str] = {
    "pandas": "Data manipulation ready",
    "numpy": "Numerical computation ready",
    "matplotlib": "Visualization ready",
}


def check_deps() -> bool:
    print("LOADING STATUS: Loading programs...")
    print("Checking dependencies:")
    missing = []
    for pkg in REQUIRED:
        spec = importlib.util.find_spec(pkg)
        if spec is None:
            print(f"  [MISSING] {pkg}")
            missing.append(pkg)
        else:
            mod = importlib.import_module(pkg)
            version: str = getattr(mod, "__version__", "unknown")
            print(f"  [OK] {pkg} ({version}) - {LABELS.get(pkg, '')}")

    if missing:
        print("\nMissing dependencies. Install with:")
        print("  pip:    pip install -r requirements.txt")
        print("  poetry: poetry install")
        return False
    return True


def run_analysis() -> None:
    import numpy as np
    import pandas as pd
    import matplotlib.pyplot as plt

    print("\nAnalyzing Matrix data...")
    np.random.seed(42)
    data = np.random.randn(1000)
    print(f"Processing {len(data)} data points...")

    df = pd.DataFrame({"signal": data})
    df["rolling_mean"] = df["signal"].rolling(50).mean()

    fig, ax = plt.subplots()
    ax.plot(df["signal"], alpha=0.4, label="Raw signal")
    ax.plot(df["rolling_mean"], color="red", label="Rolling mean")
    ax.set_title("Matrix Data Analysis")
    ax.legend()

    print("Generating visualization...")
    fig.savefig("matrix_analysis.png")
    plt.close(fig)

    print("Analysis complete!")
    print("Results saved to: matrix_analysis.png")


def get_versions() -> None:
    print("\nInstalled package versions:")
    for pkg in REQUIRED:
        spec = importlib.util.find_spec(pkg)
        if spec is not None:
            mod = importlib.import_module(pkg)
            version: Optional[str] = getattr(mod, "__version__", None)
            print(f"  {pkg}: {version or 'unknown'}")


def main() -> None:
    if check_deps():
        get_versions()
        run_analysis()


if __name__ == "__main__":
    main()
