#!/bin/bash

# Find all .cpp files in the current directory
cpp_files=$(find . -maxdepth 1 -type f -name "*.cpp")

# Loop through each .cpp file
for file in $cpp_files; do
    # Strip the ./ and .cpp extension to get the base name
    base=$(basename "$file" .cpp)
    output="${base}.exe"

    echo "Compiling $file -> $output"
    g++ -std=c++17 -Wall -Wextra -o "$output" "$file"

    if [ $? -eq 0 ]; then
        echo "✅ Built $output successfully"
    else
        echo "❌ Failed to build $file"
    fi
done
