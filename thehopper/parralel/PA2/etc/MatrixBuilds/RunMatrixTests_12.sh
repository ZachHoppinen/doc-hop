#!/bin/bash

cd 12_threads
echo "Using 12 threads"
for f in *.sh; do
  bash "$f"
done