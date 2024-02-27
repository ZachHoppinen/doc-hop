#!/bin/bash

cd 16_threads
echo "Using 16 threads"
for f in *.sh; do
  bash "$f"
done