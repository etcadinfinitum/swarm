#!/bin/bash

# check if argument was supplied to bash script
if [[ $# != 1 ]]; then
    echo "Please provide a single filename argument for graph generation."
    exit 1
fi

if [[ ! -f $1 ]]; then
    echo "A file with name $1 does not exist."
    exit 1
fi

g++ -o execute -I rule_creation -I graph grammar.cpp

if [[ $? != 0 ]]; then
    echo "Compilation of rule generator failed; exiting."
    exit 1
fi

./execute $1

rm ./execute
