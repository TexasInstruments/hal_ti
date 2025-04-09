import os
import shutil
import fnmatch

# Set the input location
import argparse

EXCLUDED_FILE_LIST = ["CMakeLists.txt", "*.cmake", "*.md", "*.yml","*.yaml"]


# Function to copy files from a list of sources to a destination with the same
# folder structure.
def copy_sdk_files_from_source(source_dirs, simplelink_dir):
    """
    Check if the source and destination directories exist and are readable.
    Then copy SDK files from a list of source directories to a destination
    with the same folder structure.

    Files are only copied if they exist in both one of the source directories
    and in the destination. New files should be added manually, if needed.

    Args:
        source_dirs (list): List of source directories.
        simplelink_dir (str): Destination directory.
    """

    # Check if the source_dirs and simplelink_dir exist
    if not all(os.path.exists(d) for d in source_dirs) or not os.path.exists(
        simplelink_dir
    ):
        raise FileNotFoundError("Source or destination directory does not exist")

    # Check if the source_dirs and simplelink_dir are readable
    if not all(os.access(d, os.R_OK) for d in source_dirs):
        raise PermissionError("Source directory is not readable")

    if not os.access(simplelink_dir, os.W_OK):
        raise PermissionError("Destination directory is not readable")

    # Walk through the simplelink family directory and its subdirectories
    for root, _, files in os.walk(simplelink_dir):
        for file in files:
            if any(fnmatch.fnmatch(file, excluded_file) for excluded_file in EXCLUDED_FILE_LIST):
                continue
            # Get the relative path of the file
            relative_path = os.path.relpath(root, simplelink_dir)

            for source_dir in source_dirs:
                # Get the full path of the file in the input location

                input_file_path = os.path.join(source_dir, relative_path, file)

                # Check if the file exists in the input location
                if os.path.exists(input_file_path):
                    # Copy the file to the simplelink_lpf3 directory
                    output_file_path = os.path.join(root, file)
                    shutil.copy(input_file_path, output_file_path)
                    print(f"Copied {input_file_path} to {output_file_path}")
                    break


if __name__ == "__main__":
    # Add command line argument
    parser = argparse.ArgumentParser(
        description="Copy SDK files to a SimpleLink directory. \
                                    This script copies files from a list of source SDK directories to a SimpleLink family directory, such as simplelink_lpf3. \
                                    If a file is found in both the source and destination, script copies it to the SimpleLink family directory. \
                                    New files should be added manually, if needed. \
                                    The script prints the paths of the copied files."+f" The following file types are excluded from copy to prevent overlap: {EXCLUDED_FILE_LIST}",
        allow_abbrev=False,
    )
    parser.add_argument("-s", "--sdk_dir", help="Path to SDK directory.", required=True)
    parser.add_argument(
        "-d",
        "--simplelink_dir",
        help="Path to SimpleLink family directory.",
        required=True,
    )

    # Parse the arguments
    args = parser.parse_args()

    # Set the simplelink_lpf3 directory
    simplelink_dir = args.simplelink_dir

    source_dirs = [args.sdk_dir]

    # Call the function
    copy_sdk_files_from_source(source_dirs, simplelink_dir)
