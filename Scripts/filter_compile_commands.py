
import argparse
import json
import os


# Flags to remove (MSVC-specific)
MSVC_FLAGS = ['/Fo', '/W3', '/GR', '/EHsc', '/std:c++latest']


def filter_compile_commands(input_path, output_path, exclude_dirs):
    if not os.path.exists(input_path):
        raise FileNotFoundError(f"Input file {input_path} not found")

    with open(input_path, 'r', encoding='utf-8') as f:
        compile_db = json.load(f)

    filtered_db = [
        entry for entry in compile_db
        if all(exclude_dir not in entry['file'] for exclude_dir in exclude_dirs)
    ]

    for entry in filtered_db:
        entry['command'] = ' '.join(
            part for part in entry['command'].split()
            if all(flag not in part for flag in MSVC_FLAGS)
        )

    with open(output_path, 'w', encoding='utf-8') as f:
        json.dump(filtered_db, f, indent=2)

    print(f"Filtered compile commands saved to {output_path}")
    print(f"Excluded directories: {exclude_dirs}")
    print(f"Original entries: {len(compile_db)}, Filtered entries: {len(filtered_db)}")


if __name__ == "__main__":
    parser = argparse.ArgumentParser(
        description="Filter compile_commands.json to exclude 3rdparty code"
    )
    parser.add_argument(
        "-i", "--input",
        help="Input compile_commands.json path",
        required=True
    )
    parser.add_argument(
        "-o", "--output",
        help="Output filtered JSON path",
        required=True
    )
    parser.add_argument(
        "-e", "--exclude",
        nargs="+",
        default=["3rdparty", "third_party", "extern"],
        help="Directories to exclude"
    )
    
    args = parser.parse_args()
    filter_compile_commands(args.input, args.output, args.exclude)
