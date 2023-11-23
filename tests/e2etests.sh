#!/bin/bash

# Run the tests

# Exit on any failure
set -euo pipefail
# set -x

# Run the tests
echo "Running map comparison tests"

for file in $(find example_files/maps/ -name 'intermediate*'); do
  echo "Running test for $file"
  if ! ./setting_up $file | diff - example_files/solved/$(basename $file); then
    echo "Test failed for $file"
    exit 1
  fi
done

echo "Running big map tests (does not check correctness of result)"

for file in $(find example_files/maps/ -name 'generated*'); do
  echo "Running test for $file"
  if ! ./setting_up $file >/dev/null; then
    echo "Test failed for $file"
    exit 1
  fi
done

echo "Running map generation tests"

export IFS=$'\n'
for file in $(find example_files/generate/ -type f -name '*' -printf '%f'); do
  echo "Running test for $file"
  export IFS=$' \t\n'
  if ! ./setting_up $file | diff - "example_files/generate/$file"; then
    echo "Test failed for $file"
    exit 1
  fi
  export IFS=$'\n'
done
export IFS=$' \t\n'

echo "Running failure tests"

for file in $(find example_files/faulty -name 'generated*'); do
  echo "Running test for $file"
  if ./setting_up $file >/dev/null; then
    echo "Test failed for $file"
    exit 1
  fi
done

echo "Running test for Negative size"
if ./setting_up -+5 '.' >/dev/null; then
  echo "Test failed for Negative size"
  exit 1
fi

echo "Running test for Empty Pattern"
if ./setting_up 5 '' >/dev/null; then
  echo "Test failed for Empty Pattern"
  exit 1
fi

echo "Running test for Inexistent file"
if ./setting_up 'inexistent_file' >/dev/null; then
  echo "Test failed for Inexistent file"
  exit 1
fi

echo "All tests passed"
