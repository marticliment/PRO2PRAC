#!/bin/bash

rm mart
rm hect

while ! cmp -s mart hect; do
    g++ testgen.cc ; ./a.out >test_in
    ./program.exe <test_in >mart
    ./hector.exe <test_in >hect_out
    echo "Successful run"
done