# gkk2-grantrh2-abramig2-pitocco2

All code relevant to our graph algorithms are located in the  graph.cpp/h files, and our test suite can be found in the tests directory. Results are outputted as BFS_results_Main, and the results of floyed warshall and influential nodes are outputted to the command line. 

The graph interface has four public functions: BFSTraversal, numNodesExplored, shortest_path, and influential. Respectively, these functions return: a minimum spanning tree of the graph, the number of nodes explored in the bfs traversal, the shortest path between two nodes and the cost of that path, and the most influential node in the graph (via the Brandes angorithm [link in description]). 

Our assignment can be compiled with the “make” command on the commandline, and our tests can be compiled with the “make test” command. Our program can be run with the following command: ./main &lt;dataset> &lt;first_n_nodes> &lt;Name of Result .txt file> *OPTIONAL: * &lt;Run Shortest Path? (Y or N)> &lt;NodeA: (int)> &lt;NodeB: (int)>

Note that the second flag can be omitted for all nodes to be explored, and ommiting the first flag runs the code on the reply network dataset

To manage time complexity of the test suite, we wrote tests on sample datasets or on our robust datasets with a limited sample of nodes. BFS was tested through the public BFSTraversal and numNodesExplored functions, the former returning a minimum spanning tree and the latter returning the number of nodes explored in the traversal (note that this is equal to the number of nodes in the graph for a connected graph. Our floyd warshall algorithm was tested through our shortest_path algorithm, which verifies that the matrix containing the distances between nodes and that the matrix containing the next node in a shortest path is initialized. Then, our shortest path algorithm can quickly find the shortest path between two nodes. Finally, our betweenness centrality algorithm was tested through our public influential function, which runs the betweenness centrality algorithm to find the most influential node in a graph. 


Link to Final Project Presentation:
https://drive.google.com/file/d/16Imoq15gKZSC_vXW76ReRtMPwoDnJm7-/view?usp=sharing
