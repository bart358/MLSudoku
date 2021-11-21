#!/usr/bin/env python3

import time
import pathlib
import argparse
import subprocess

DATASET_NAME = "sudoku-3m.csv"
KAGGLE_PATH = "radcliffe/3-million-sudoku-puzzles-with-ratings"


def parse_args() -> argparse.Namespace:
    BUILD_TYPES = ["Debug", "Release", "RelWithDebInfo", "MinSizeRel"]
    parser = argparse.ArgumentParser(description="Process setup arguments.")

    parser.add_argument("-B", "--build_type", default="Release",
                        choices=BUILD_TYPES,
                        help="Type of build passed to CMake")

    parser.add_argument("-G", "--generator", type=str, default="Ninja",
                        help="Generator to use for creating a build")

    parser.add_argument("--run", action="store_true", default=False,
                        help="Run the binary after a succesful build")

    parser.add_argument("--generate", action="store_true", default=False,
                        help="Force to generate CMake configuration")

    return parser.parse_args()


def main() -> None:
    args = parse_args()

    dataset = pathlib.Path(DATASET_NAME)
    build = pathlib.Path("out") / "build" / f"x64-{args.build_type}"

    cmd1 = ["cmake", "-S", ".", "-B", build, "-G", args.generator]
    if not build.exists() or args.generate:
        build.mkdir(parents=True, exist_ok=True)
        p1 = subprocess.run(cmd1)
        if p1.returncode:
            return

    cmd2 = ["cmake", "--build", build]
    p2 = subprocess.run(cmd2)
    if p2.returncode:
        return

    cmd3 = ["kaggle", "datasets", "download", KAGGLE_PATH, "--unzip"]
    if not dataset.exists():
        subprocess.run(cmd3)

    if args.run:
        print("Computing results...")
        start = time.time()
        p3 = subprocess.run("./Sudoku", cwd=build / "Sudoku")
        stop = time.time()
        if p3.returncode:
            return
        print(f"Elapsed time: {stop - start} seconds.")


if __name__ == "__main__":
    main()
