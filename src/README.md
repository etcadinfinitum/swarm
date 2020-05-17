# Software Usage

## Quickstart

Run the following commands in a Linux terminal:

```console
$ ./run config/yoyo.txt
[... rule output here ...]
```

You can specify any valid filepath instead of `config/yoyo.txt`; the 
`config/` directory contains several example graph files to parse.

## Creating and Using Input Graphs

Currently, only predefined graph files are supported. These predefined 
graphs can be written to any valid path on the existing system. The 
[config/](./config) directory is used to provide graph schematics for 
this project.

#### File Format for Graphs

Each line in the graph file has the format `name*name`, with the `*` 
symbol representing an edge between the indicated nodes. The node's `name` 
is considered a unique identifier and will be used to provide lookups 
for previously added nodes when constructing the graph. 

The graph 
builder does not truncate whitespace or tokenize the node name, so 
entries with surrounding whitespace will be considered unique.

For example, to build a [3-node cycle](./config/cycleThree.txt), the 
following input could be used:

```
X*Y
X*Z
Y*Z
```

This produces a graph which looks like the following:

```
    Y
   / \
  Z---X
```
