#!/bin/bash

cd 4_threads
echo "Using 4 threads"
for f in *.sh; do
  bash "$f"
done