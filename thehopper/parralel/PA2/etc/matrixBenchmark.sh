#!/bin/bash

cd MatrixBuilds/
echo "Begin Tests"
for f in *.sh; do
  bash "$f"
done
