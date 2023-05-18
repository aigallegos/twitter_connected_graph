**CS 225 Data Structures**

**Development Log (gkk2-grantrh2-abramig2-pitocco2)**

**Week of November 16**

We successfully implemented the reading of our datasets into an adjacency list structure. To do so, we created a helper function to determine the maximum user ID which we made the size of our adjacency list. We did so for both .txt files and .edgelist files by making a Node struct that houses all relevant information. Two constructors were necessary to do this, one with a vertex and a weight, and the other with a vertex, weight and type of interaciton. 

**Week of November 22**

We sucessfully implemented the floyd-warshall and shortest path algorithms, as well as a BFS Traversal that visits every node in our tree.

**Week of November 29**

This week we implemented further our Floyd-Washall algorithm and we found a possible solution to our memory allocation problem. We found a way to compress our adjacency list and matrices needed to reduce our time and space complexity errors. 

**Week of December 6th**

This week we finished up our project by implementing our test suite along with the betweenness centrality algorithm. We also cleaner up
bugs in BFS and floyed warshall, and updated the main.cpp and README.md file to be complient with the rubiric. 