# Distributed Robotic Assembly Systems

A CSSE capstone project in collaboration with Dr. Casey Mann and Dr. 
Clark Musselman, Department of Mathematics, University of Washington Bothell.

## Background

This project was conceived from existing research that deals with special 
cases of [graph grammars](https://en.wikipedia.org/wiki/Graph_rewriting) 
which are used to construct graphs from an initial swarm of singleton nodes.

The team at UW Bothell is interested in the applicability of these formulae 
to physical robotic systems, and the topological properties of the graphs and 
synthesized graph assembly systems.

## Project Objectives

1. Produce general implementation of the graph rewriting algorithm described in [Klavins et al](./docs/klavins_graphgrammars.pdf)
2. Produce a code generator which takes a grammar as input and outputs correct code for programmable nodes (Arduino devices with additional future support for Raspberry Pis, Adafruit/Circuit Python devices, or embedded devices)
3. Test resulting code using an array of 3-5 programmed Arduino boards

Essentially, the goal of the software development effort is to pipe an 
unlabeled graph into the system and receive assembly rules embedded in 
Arduino code as output.

## Future Work

* Demonstrate correctness of existing algorithms for general graph formations
* Extend software framework to account for 3-dimensional nodes
  * Explore mechanisms of modeling structure and dimensions of physical nodes in software
  * Validate input graphs to ensure the desired input graph can be produced given the shape of the provided nodes (see Figure 1)
  * Extrapolate all permutations of node assemblies which are isomorphic to a general input graph (see Figure 2)
* Create a visualization mechanism for assembly systems and simulate system behavior under various constraints

### Graph Validation

The motivation for this problem is easily demonstrated with a simple example. 
We inspect  a programmable node which is a geometric cube and attempt to construct 
representations of the graph with copies of the cubic node. We discover that we 
cannot produce certain arbitrary graphs and retain local isomorphism properties.

Figure 1: Producing 4- and 5-node cycles using cubes.
[figure 1 image](./docs/img/readme_fig1.png)

In this example, no matter where we place the 5th node (gold), the local 
isomorphic properties of each node in a 5-node cycle cannot be upheld; there 
is always 1 node which has 3 edges and 1 node which has only one edge.

A system which builds grammars for graph formation should be able to 
analyze graph input and specified node structure to determine whether 
the graph can be formed with the provided nodes.

### Assembly Permutation

A simple example is sufficient to demonstrate that a single input graph 
could produce a wide variety of physical node configurations which are 
isomorphic to the input.

We consider a very simple graph which models a 4-node list, and see that 
many 3-dimensional graphs can be produced with cubic nodes.

Figure 2: Producing 4-node "list" graphs.
[figure 2 image](./docs/img/readme_fig2.png)

Each of the configurations provided in Fig 2 is a valid isomorphism of the 
input graph, and a system which builds grammars for graph formation where 
the graph has a single stable configuration should be able to generate 
these permutations and allow the user to select the desired result.
