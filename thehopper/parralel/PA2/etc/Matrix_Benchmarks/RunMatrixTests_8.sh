#!/bin/bash

cd 8_threads
echo "Using 8 threads"
for f in *.sh; do
  bash "$f"
done