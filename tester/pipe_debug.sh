#!/bin/bash

# Create a test directory
mkdir -p pipe_debug
cd pipe_debug

# Helper function to run a command in both bash and your shell
run_comparison() {
    local test_name="$1"
    local cmd="$2"
    
    echo "=== Test: $test_name ==="
    echo "Command: $cmd"
    
    echo -e "\nExpected output (bash):"
    echo "$cmd" | bash
    
    echo -e "\nYour shell output:"
    echo "$cmd" | ../mysh
    
    echo -e "\n"
}

# Test 1: Simplest pipe - echo to wc
run_comparison "Simple pipe - echo to wc" "echo 'hello world' | wc -w"

# Test 2: Verify pipe content transfer
run_comparison "Pipe content transfer" "echo 'transfer test' | cat"

# Test 3: Check if pipe correctly handles whitespace
run_comparison "Pipe with whitespace" "echo 'hello   world' | wc -w"

# Test 4: Multiple pipes with simple commands
run_comparison "Multiple pipes" "echo 'a b c d e' | tr ' ' '\n' | wc -l"

# Test 5: Test with grep to see argument handling
run_comparison "Grep argument handling" "echo -e 'line1\nline2\nline3' | grep line2"

# Test 6: Test pipe with redirection
run_comparison "Pipe with redirection" "echo 'redirection test' | cat > redir_test.txt; cat redir_test.txt"

# Test 7: Generate specific data for the failing test case
echo "=== Test: Recreating failing simple pipe test ==="
echo "Command: ls -l | grep d | wc -l"

mkdir -p test_dir1 test_dir2
touch file1.txt file2.txt

echo -e "\nExpected output (bash):"
echo "ls -l | grep d | wc -l" | bash

echo -e "\nYour shell output:"
echo "ls -l | grep d | wc -l" | ../mysh

echo -e "\nActual ls -l output (for reference):"
ls -l

# Test 8: Test with a binary file to check buffer handling
echo -e "\n=== Test: Binary data through pipe ==="
echo "Command: dd if=/dev/zero bs=1024 count=1 | wc -c"

echo -e "\nExpected output (bash):"
echo "dd if=/dev/zero bs=1024 count=1 | wc -c" | bash

echo -e "\nYour shell output:"
echo "dd if=/dev/zero bs=1024 count=1 | wc -c" | ../mysh

# Test 9: Check handling of quotes in pipes
run_comparison "Quotes in piped commands" "echo 'grep \"test\"' | cat"

# Test 10: Test with specific error in the failing test
run_comparison "Error propagation" "cat nonexistent_file.txt 2>&1 | wc -l"

# Cleanup
cd ..
rm -rf pipe_debug
