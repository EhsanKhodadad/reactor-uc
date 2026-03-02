#!/bin/bash

set -e

while getopts ":s" opt; do 
  case $opt in
    s) SLEF_HOSTED=true;;
    :) echo "Option -$OPTARG requires an argument." >&2; exit 1;;
    \?) echo "Invalid option -$OPTARG" >&2; exit 1;;
  esac
done

if ! command -v pasim &> /dev/null; then
  echo "Error: pasim command not found. Please ensure it is installed and available in your PATH."
else
    # Iterate over each folder and execute the command
    for dir in ./*; do
        if [ -d "$dir" ]; then
            # Skip directories that should not be built via this runner
            case "$dir" in
              "./s4noc_fed")
                echo "Skipping $dir (disabled for buildAll.sh)"
                continue
                ;;
            esac

            echo "Entering $dir"
            pushd "$dir"
            chmod +x build.sh
            if [ "$SLEF_HOSTED" = true ]; then
              echo "Running build.sh for self-hosted runner"
              ./build.sh -f
            else
              echo "Running build.sh for non-self-hosted runner"
              ./build.sh -e
            fi
            popd
        fi
    done
fi