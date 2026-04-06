import sys
import subprocess
import argparse
from pathlib import Path


def main():
    parser = argparse.ArgumentParser(description="Run tests for a cpp file")
    parser.add_argument("path", type=Path, help="Path to the .cpp file")
    args = parser.parse_args()

    src: Path = args.path
    if not src.exists():
        print(f"[Error] {src} not found")
        sys.exit(1)

    binary = src.with_suffix(".a")

    compile_result = subprocess.run(
        ["g++-15", "-std=c++23", "-Iinclude", "-o", str(binary), str(src)],
        capture_output=True,
        text=True,
    )
    if compile_result.returncode != 0:
        print("[Compile Error]")
        print(compile_result.stderr)
        sys.exit(1)

    run_result = None
    try:
        run_result = subprocess.run(
            [str(binary)], capture_output=True, text=True, timeout=5
        )
    except subprocess.TimeoutExpired:
        print("[Timeout] running time of the program exceeded 5 seconds")
        sys.exit(1)
    print(run_result.stdout)
    if run_result.returncode != 0:
        print(run_result.stderr)
        sys.exit(run_result.returncode)


if __name__ == "__main__":
    main()
