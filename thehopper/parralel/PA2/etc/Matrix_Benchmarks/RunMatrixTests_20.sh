#!/bin/bash

cd 20_threads
echo "Using 20 threads"
for f in *.sh; do
  bash "$f"
done