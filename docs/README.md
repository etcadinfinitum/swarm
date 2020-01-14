# Digest of _Graph Grammars for Self Assembling Robotic Systems_ by Klavins et. al.

The mathematics illustrated in this paper may be confusing and 
appear unapproachable for an engineer without the benefit of advanced 
study of mathematics. The key points of the paper are restated here 
for clarity, and to orient subsequent research in this topic.

## Language Clarification

The following terms are used which are not present in the original 
publication:

1. **Identity** is used to distinguish a single unique vertex or edge. It is 
   distinct from _label_, which is formally defined in the paper. Such 
   a distinction is useful for us when describing the preservation of 
   members between sets and establishing a one-to-one relationship between 
   one or more members of disparate sets. Pointer addresses are a useful analogy for 
   computer science professionals, though not a fully sufficient analogy 
   due to object destruction and the possible of address allocation for 
   a different unique object.

## Defining a Graph

**_G = (V, E, l)_**

A graph is defined as a triple consisting of a set of vertices _V_, a set 
of vertex pairs representing edge relationships between the 
vertices (_E_), and a function _l_ which assigns a string label to each vertex. 

This definition is more explicitly named as a _simple labeled graph_, 
and such a distinction matters due specifically to the labeling mechanism, 
which isn't a typical component of a graph structure in computer science. 

This type of labeling mechanism becomes particularly useful for visually 
interpreting the state of a particular graph, and for identifying 
disparate graphs which have identical or similar states.

#### Graph Connectivity

Two vertices in a graph _G_ are _connected_ if there is a path (sequence 
of edges) connecting them in _G_. 

Graph connectivity serves as an equivalence partition on _V_; each subset 
of _V_ shares the property that all members of the subset are connected 
in _G_. 

For instance, consider the following graph _G_:

![img/connected-graph.png](A partially connected graph)

We suppose _V<sub>G</sub> = { A, B, C, D, E }_. We further deduce that 
the connectivity relation on _V_ is _{ {A, C}, {B}, {D, E} }_. Each 
subset of the connectivity relation is called a component.

Formally, a connected graph _G_ has only a single component; that is, 
there are no two vertices in _G_ that are not connected through one or 
more sequence of edges.

In layman's terms, a connected graph has no nodes which are orphaned 
from each other; all supplied vertices in _V<sub>G</sub>_ are linked 
together by at least one path.

## Defining Embeddings

In Part A, a label preserving embedding (or label-preserving embedding) function 
is defined as ***h : G1 --> G2*** with the following 3 properties:

1. _h_ is injective, implying that G1 is a subset of G2; this does not 
   imply that G1 is a proper subset of G2. If the two edge and vertex sets are equal, 
   _h_ is considered bijective. When this is true, the graph can be 
   considered isomorphic (structurally identical). A review of the formal 
   definition of graph isomorphism (see Rosen et. al.) shows that a one-to-one 
   function exists that relates _l_ of G1 to _l_ of G2, and that the equality 
   of edge sets of G1 and G2 can be demonstrated with the application of this 
   one-to-one function.
2. Each vertex pair present in _E_ of G1 is also present in _E_ of G2, 
   and _h_ relates the two pairs. An application of _h_ may result in a label 
   mapping change, and this property will still be true.
3. The labeling function of G1 may be reproduced by the labeling function 
   of G2 as a function of h.

Embeddings become particularly useful in Definition 3.2, which states that 
an arbitrary graph _L_ may be considered a subsection of an arbitrary graph 
_G_ when an embedding _h_ exists. The function _h_ is called a _witness_ 
when this is true.

In practical terms, an embedding guarantees by definition that _L_ can 
be mapped to a portion of _G_, up to and including the entirety of _G_. 
When _h_ is bijective, _L_ is isomorphic to _G_.

## Defining Rules

In Definition 3.1, a rule _r_ is given as a pair of graphs _(L, R)_. In a rule, 
_V_ in _L_ is equal to _V_ in _R_ (both in magnitude and member identity). 

In essence, a rule acts on a fixed number of vertices in isolation from 
the rest of the universe.

### Rule Types

If we assume that _L_ and _R_ are not necessarily equal, then _E_ and/or 
_l_ must differ. The paper further quantifies types of rules:

* A constructive rule is symbolically defined by _E_ of _L_ being a proper subset of _R_'s 
edge set.
* In a destructive rule set, _E_ of _R_ is a proper subset of _L_'s edge set. 

However, the symbology of this definition is in debate due to inconsistency 
in the notation of proper subsets. 

The paper further defines mixed rulesets as being neither constructive 
nor destructive. We have interpreted this new rule type to imply one of 
the two properties:

1. Under the constraints listed above, the rule neither produces a new 
   identified edge nor removes an edge which existed in _L_. Such an interpretation 
   implies that only _l_ is changed between _L_ and _R_, since the identitified 
   edges between _L_ and _R_ would remain the same. The trivial example 
   given in the paper's Example 3.3 supports this interpretation of a mixed 
   rule, and all given examples of constructive and destructive rules imply 
   proper containment based on vertex and edge identities.
2. If we do not require that _L_ and _R_ are inequal or that the edge sets 
   are required to be proper subsets for constructive or destructive rules, 
   the possible behaviors for rules grow and additional options for mixed 
   rules present themselves. Such a rule may simultaneously create a new edge 
   and destroy an existing edge, relabel vertices only (as in #1), 
   or perform no action at all (so that _L_ and _R_ are equal).

Some clarification on the types of rules and rule behavior is needed.

### Rule Applicability

Revisiting Definition 3.2, we understand that a rule is applicable to 
some arbitrary graph _G_ when an embedding function _h_ exists between 
_L_ and _G_. This does not imply that _R_ is applicable to graph _G_; 
_R_'s applicability is determined by a separate rule that uses _R_ as the 
first member of its pair.

## Action Definition

An action on a graph _G_ is the pair _(r, h)_ such that _r_ is applicable 
to _G_ when witnessed by function _h_.

Essentially, an action is a codified transformative event for some portion of _G_; 
the transformation is effected on a portion of _G_ defined by _r_.

### Action's Impact on _G_

The application of an action to _G_, producing _G'_, has the following effects:

* _V' = V_; the magnitude and member identities of _V_ do not change.
* _E'_ is produced; it consists of the union of all edges in _R_ and the 
  set difference _E - { e | e is a member of L }_.
* _l'_ is produced; it stipulates that labels do not for all vertices which 
  were not present in _L_, and labels for _L_'s vertices are changed 
  according to _R_'s labeling function.

## Graph Assembly

### Graph Assembly Systems

An assembly system for a graph is formally defined in Definition 3.4 and 
consists of a pair: _(G<sub>0</sub>, _&Phi;_)_.

_G<sub>0</sub>_ represents an initial unbounded graph defined by the following 
graph tuple:

***G<sub>0</sub> = (&naturals;, &empty;, &lambda;x.a)***

We can consider _&naturals;_ to be vertex identities for G<sub>0</sub>; 
however, Example 3.1 in the paper demonstrates that these vertex labels 
may be used interchangably with rule graphs and that they do not uniquely 
identify vertex members in the way _identity_ is used in our definitions.

&Phi; denotes a set of rules (referred to interchangably as a rule set).

### Assembly Sequences

An assembly sequence is defined in Definition 3.5 and describes the possible 
graph configurations that can be produced from _G<sub>0</sub>_ using &Phi;. 

It is in this definition that we begin to understand that the witness function 
_h_ refers to a **unique identified** portion of _G_; to quote the paper 
directly:

> The [graph assembly] system is non-deterministic since, at any step, many 
> rules in &Phi; may be simultaneously applicable, each possibly **via several 
> witnesses**.


