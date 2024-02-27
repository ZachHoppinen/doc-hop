#!/bin/bash

cd VectorBuilds/
echo "Begin Tests\n"
for f in *.sh; do
  bash "$f"
done
