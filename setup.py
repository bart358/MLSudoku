#!/usr/bin/env python3

import pathlib
import argparse
import subprocess

BUILD_TYPES = ["Debug", "Release", "RelWithDebInfo", "MinSizeRel"]


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(description="Process setup arguments.")

    parser.add_argument("-B", "--build_type", default="Debug",
                        choices=BUILD_TYPES,
                        help="Type of build passed to CMake")
    parser.add_argument("-G", "--generator", type=str, default="Ninja",
                        help="Generator to use for creating a build")
    parser.add_argument("--run", action="store_true", default=False,
                        help="Run the binary after a succesful build")

    return parser.parse_args()


def main() -> None:
    args = parse_args()

    path = pathlib.Path(f"out/build/x64-{args.build_type}")
    path.mkdir(parents=True, exist_ok=True)

    cmd1 = ["cmake", "-S", ".", "-B", path, "-G", args.generator]
    cmd2 = ["cmake", "--build", path]

    subprocess.run(cmd1)
    subprocess.run(cmd2)

    if args.run:
        subprocess.call("./Sudoku", cwd=path / "Sudoku",
                        stdout=subprocess.PIPE, stderr=subprocess.PIPE)


if __name__ == "__main__":
    main()
