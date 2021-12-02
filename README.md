# Kruskal's Algorithm

This project is an implementation of Kruskal's Algorithm, which finds the minimum spanning tree of an undirected connected graph. It is known to be a greedy algorithm within graph theory. A spanning tree is essentially a subgraph of a graph that contains all vertices. From the subgraph we can calculate the minimum weight by adding all the weights of the edges. Below is a basic description of the flow of the program. 

1. Input file is read and data is stored in corresponding vectors.
2. The vector of pairs that hold the given nodes are then sorted by weight in increasing order.
3. The sorted vector is iterated through, checking to see that if the edge is added, that it will not create a cycle.
    - A recursive function is used to check if a cycle is created, and if not, to find the node's root.
4. If the node can be added to the spanning tree, its root is marked within a vector to ensure future nodes' validity.
5. The total weight is calculated, and the output is written to the output file.

