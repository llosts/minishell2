#!/bin/bash

# Testing script to verify our fixes
echo "=== Verifying pipe fixes ==="
echo "Make sure you've implemented all the fixes before running this test!"

# Compile the updated shell
echo -e "\nCompiling..."
make re

# Create a test directory
mkdir -p pipe_test
cd pipe_test

# Test 1: Simple Pipe
echo -e "\n=== Test 1: Simple Pipe ==="
echo "Command: echo 'hello world' | wc -w"
echo -e "\nReference output (bash):"
echo "echo 'hello world' | wc -w" | bash
echo -e "\nYour shell output:"
echo "echo 'hello world' | wc -w" | ../mysh

# Test 2: Multiple Pipes
echo -e "\n=== Test 2: Multiple Pipes ==="
echo "Command: ls -l | grep . | wc -l"
echo -e "\nReference output (bash):"
echo "ls -l | grep . | wc -l" | bash
echo -e "\nYour shell output:"
echo "ls -l | grep . | wc -l" | ../mysh

# Test 3: Pipe with redirection
echo -e "\n=== Test 3: Pipe with redirection ==="
echo "Command: echo 'test' | cat > test_file.txt; cat test_file.txt"
echo -e "\nReference output (bash):"
echo "echo 'test' | cat > test_file.txt; cat test_file.txt" | bash
echo -e "\nYour shell output:"
echo "echo 'test' | cat > test_file.txt; cat test_file.txt" | ../mysh

# Test 4: Creating the failing test from earlier
echo -e "\n=== Test 4: Binary Input Test ==="
echo "Command: dd if=/dev/zero bs=1024 count=1 | wc -c"
echo -e "\nReference output (bash):"
echo "dd if=/dev/zero bs=1024 count=1 | wc -c" | bash
echo -e "\nYour shell output:"
echo "dd if=/dev/zero bs=1024 count=1 | wc -c" | ../mysh

# Cleanup
cd ..
rm -rf pipe_test

echo -e "\n=== Tests completed ==="
echo "If your output matches the reference output, your pipe implementation should be working correctly!"
