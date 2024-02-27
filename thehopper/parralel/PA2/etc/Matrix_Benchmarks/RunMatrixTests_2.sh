#!/bin/bash

cd 2_threads
echo "Using 2 threads"
for f in *.sh; do
  bash "$f"
done