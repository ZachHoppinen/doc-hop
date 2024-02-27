#!/bin/bash

cd 28_threads
echo "Using 28 threads"
for f in *.sh; do
  bash "$f"
done