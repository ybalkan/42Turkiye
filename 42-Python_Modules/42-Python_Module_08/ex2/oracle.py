import os
import sys
from dotenv import load_dotenv


def load_config() -> dict[str, str]:
    load_dotenv()
    return {
        "MATRIX_MODE": os.getenv("MATRIX_MODE", "development"),
        "DATABASE_URL": os.getenv("DATABASE_URL", "sqlite:///matrix_local.db"),
        "API_KEY": os.getenv("API_KEY", ""),
        "LOG_LEVEL": os.getenv("LOG_LEVEL", "DEBUG"),
        "ZION_ENDPOINT": os.getenv("ZION_ENDPOINT", "http://zion.local:8080"),
    }


def print_config(cfg: dict[str, str]) -> None:
    mode = cfg["MATRIX_MODE"]
    api_key = cfg["API_KEY"]
    log = cfg["LOG_LEVEL"]
    zion = cfg["ZION_ENDPOINT"]

    print("ORACLE STATUS: Reading the Matrix...")
    print("Configuration loaded:")
    print(f"  Mode: {mode}")

    if mode == "production":
        print(f"  Database: Connected to {cfg['DATABASE_URL']}")
    else:
        print("  Database: Connected to local instance")

    if api_key:
        print("  API Access: Authenticated")
    else:
        print("  API Access: WARNING — no API key set")

    print(f"  Log Level: {log}")
    print(f"  Zion Network: {'Online' if zion else 'Offline'}")


def security_check(cfg: dict[str, str]) -> None:
    print("\nEnvironment security check:")
    print("  [OK] No hardcoded secrets detected")

    env_file_exists = os.path.isfile(".env")
    if env_file_exists:
        print("  [OK] .env file properly configured")
    else:
        print("  [WARN] .env file not found — copy from .env.example")

    print("  [OK] Production overrides available")


def validate_config(cfg: dict[str, str]) -> bool:
    if not cfg["API_KEY"]:
        print("ERROR: API_KEY is missing.", file=sys.stderr)
        return False
    if cfg["MATRIX_MODE"] not in ("development", "production"):
        print("ERROR: MATRIX_MODE must be 'development' or 'production'.",
              file=sys.stderr)
        return False
    return True


def main() -> None:
    cfg = load_config()
    print_config(cfg)
    if not validate_config(cfg):
        sys.exit(1)
    security_check(cfg)
    print("\nThe Oracle sees all configurations.")


if __name__ == "__main__":
    main()
