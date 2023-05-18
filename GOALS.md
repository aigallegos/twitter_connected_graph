<!-----
NEW: Check the "Suppress top comment" option to remove this info from the output.

Conversion time: 0.431 seconds.


Using this Markdown file:

1. Paste this output into your source file.
2. See the notes and action items below regarding this conversion run.
3. Check the rendered output (headings, lists, code blocks, tables) for proper
   formatting and use a linkchecker before you publish this page.

Conversion notes:

* Docs to Markdown version 1.0β31
* Mon Nov 08 2021 19:51:16 GMT-0800 (PST)
* Source doc: CS225 Final Project Proposal
----->


**Final Project Proposal**



1. **Leading Question**
    1. The main question we would like to answer is: <span style="text-decoration:underline;">which accounts were the most influential in propagating the Higgs Boson news story?</span> This should ultimately allow us to highlight general trends in the spread of information via social networks on the internet. 
2. **Dataset Acquisition and Processing**
    1. [https://snap.stanford.edu/data/higgs-twitter.html](https://snap.stanford.edu/data/higgs-twitter.html)
    2. We will download and process our dataset from the stanford.edu page listed above. There are multiple different files that make up the dataset:
        1. Social Network: A file with edges linking users who interacted with the news of the higgs discovery based on who else they follow that interacted
        2. Reply Network: A directed and weighted graph which represents retweets related to the discovery of the higgs boson
        3. Mention Network: A directed and weighted graph representing replies relating to the discovery of the higgs boson
        4. Higgs Activity Time: A file that provides the edge between users A and B, a timestamp, and the type of twitter interaction.
    3. While all the graphs present interesting information, our main goal will be the implementation of the Higgs Activity Time graph, using an adjacency list. We will parse through the provided plaintext and edgelist files to do so. In order to check for data integrity, we can use the other provided datasets to ensure the consistency and fill in any missing entries.
    4. The nodes of our graph will be unique user IDs while the edges represent the interaction type between said users and will be weighted (the distance of the edge) by the elapsed time between that interaction and the next.
3. **Graph Algorithms**
    1. [Betweenness Centrality](https://en.wikipedia.org/wiki/Betweenness_centrality) (uncovered):
        1. We will implement Betweenness Centrality to determine the most influential nodes in the spread of information. To implement this overarching algorithm, we will need to calculate the shortests paths for all vertices and plan on using the [Floyd–Warshall algorithm](https://en.wikipedia.org/wiki/Floyd%E2%80%93Warshall_algorithm) (O(v^3) time). Betweenness centrality then takes in this list of shortest paths that contain a node and the node itself, and outputs a weighted scalar to rank the nodes based on their ce
    2. [Floyd–Warshall algorithm](https://en.wikipedia.org/wiki/Floyd%E2%80%93Warshall_algorithm). (covered)
        1. This algorithm will allow us to find the shortest path from node A to node B with 0(v^3) time complexity. We do this to see how separated two users (nodes) are. This takes in our graph and outputs a list of the shortest path represented through edges and nodes. 
4. **BFS Traversal (traversal) (O(m + n))**
        1. This traversal algorithm will allow us to find the shortest path spanning tree for our graph and check every node in our dataset. This traversal will verify that our tree is connected and can reach every node and verifies that our dataset we are working with is a graph.






1. **Timeline**
    1. **1st Sprint (November 8th - November 22nd)**
        1. Download data set.
        2. Build a working graph with weighted edges using an adjacency list.
        3. Update “Development” file
    2. **2nd Sprint (November 22nd - November 29th)**
        1. Implement the Floyd-Warshall and BFS Algorithm.
        2. Update “Development” file
    3. **Midpoint Check In (November 29th)**
        1. By the midpoint check in, we would like to have our graph fully working (BFS checked) and the Floyd-Warshall algorithm implemented.
    4. **3rd Sprint (November 29th - November 6th)**
        1. Implement the betweenness centrality algorithm. Complete MVP. 
        2. Update “Development” file
    5. **4th Sprint (November 6th - December 13th)**
        1. Finalize graph implementation, hopefully implement a third or fourth algorithm with any remaining time. 
        2. Update “Development” file
        3. Create a final “Report”, touching on all findings. 
        4. Record final presentation
    6. **Final Project Deliverables (December 13th)**
        1. Turn in final project
