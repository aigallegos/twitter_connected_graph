#pragma once

#include <vector>
#include <list> 
#include <string> 
#include <queue> // for BFS
#include <unordered_map>
#include <limits>
#include <algorithm>

// for reading in files
#include <iterator> 
#include <sstream> 
#include <fstream> 
#include <iostream> // used in print()
#include <cstring>  
#include <stack>

using std::vector;
using std::list;
using std::string;
using std::queue;
using std::ifstream;
using std::istream;
using std::istream_iterator;
using std::stringstream;
using std::unordered_map;
using std::stack;

class Graph {
    public:
    
        /**
         * @brief Construct a new empty Graph object
         * 
         */
        Graph();

        /**
         * @brief Construct a new Graph object from a file, initilizing:
         *                                                              _size,
         *                                                              _adj_list,
         *                                                              _d
         * 
         * @param file_name the name of the file of edges, nodes, and weights
         */
        Graph(string file_name, int arg1);

        /**
         * @brief returns the shortest path between two nodes and the summed weight og the path
         * 
         * @param a starting node
         * @param b terminating node
         * @return vector<unsigned int> shortest path between node a and node b, with the summed weight appened to the end
         */
        vector<unsigned int> shortest_path(unsigned int a, unsigned int b);


        /**
         * @brief This traversal will verify that our tree is connected and can reach every node
         * 
         * Helper function BFSTraversal(vector<list<Node> >, Node) used
         * 
         * @return vector<int> the shortest spanning tree of our graph
         */
        vector<int> BFSTraversal();


        /**
         * @brief A function to write the bottom-up BFS to a file
         * 
         * @param filename the location at which to save the file.
         * 
         * @return void
         */
        void BFStoFile(string filename);

        void BCtoFile(string filename, string arg1);

        void FWtoFile(string filename, int arg5, int arg6);

        
        /**
         * @brief This function calls BFSTraversal and determines how many nodes were explored
         * 
         * @returns number of nodes explored by BFSTraversal
         */
        unsigned int numNodesExplored();

        /**
         * @brief Uses the results of betweeness centrality to return the most influential node. If two nodes have
         *      the same influence, return the one that appeared first.
         * 
         * @return int The most influential node in the graph. -1 if node not found
         */
        int influential();

    private:

        /**
         * @brief Custom struct of nodes of vertices and weights for the adjacency list
         * 
         */
        struct Node
        {
            /**
             * @brief two argument constructor for edgelist input files
             * 
             * @param vertex userB
             * @param weight action
             */
            Node(unsigned int vertex, unsigned int weight) {
                vertex_ = vertex;
                weight_ = weight;
            }

            /**
             * @brief three argument constructor for text input files
             * 
             * @param vertex userB
             * @param weight time
             * @param type type of interaction (retweet - RT, mention - MT, reply - RE)
             */
            Node(unsigned int vertex, unsigned int weight, std::string type) {
                vertex_ = vertex;
                weight_ = weight;
                type_ = type;
            }

            /**
             * @brief prints a node object to terminal
             */
            void print() {
                std::cout << "Vertex:\t" << vertex_ << "\t| Weight:\t" << weight_ << "\t| Type:\t" << type_ << std::endl;
            }
        
            unsigned int vertex_;
            unsigned int weight_;
            string type_ = "";
        };
        
        /**
         * @brief Adjacency list of edges and their weights.
         * 
         */
        unordered_map<unsigned int, list<Node> > _adj_list;


        /**
         * @brief A hash map off all the vertices in our graph to their respective index value
         * 
         */
        unordered_map<unsigned int, unsigned int > _vertex_table;


        /**
         * @brief A mapping from _adj_list indx to node vertices
         * 
         */
        vector<unsigned int> _vertex_key;

        /**
         * @brief a matrix of distances between two nodes used by the floyd warshall and betweenness centrality algorithms
         * 
         */
        vector<vector<int>> _d; 

        /**
         * @brief A vector of vertices in the graph that represent the next vertex in a sortest path. Matrix will be initilized to null
         * 
         */
        vector<vector<int>> _n;


        /**
         * @brief Helper function for BFSTraversal() to populate the visited nodes vector
         * 
         * @returns void
         */ 
        void BFSTraversal(vector<bool>& explored, vector<int>& visited, unsigned int idx);


        /**
         * @brief Helper function called by the constructor to parse an edgelist into a graph
         * 
         * @param file_name The name of the file to be read from
         */
        void read_edglist_to_graph(string file_name, int arg1);

        
        /**
         * @brief Helper function called by the constructor to parse a txt file into a graph
         * 
         * @param file_name the name of the file to be read from
         */
        void read_txt_to_graph(string file_name);


        /**
         * @brief Using Brandes algorithm for unweighted graphs (need to walk before we can run)
         * 
         * The algorithm can be found here
         * 
         * www.uvm.edu/pdodds/research/papers/others/2001/brandes2001a.pdf
         * 
         * @return a vector of the betweenness ranking for every node
         */
        vector<int> betweenness_centrality();

        
        /**
         * @brief [Floyd–Warshall algorithm](https://en.wikipedia.org/wiki/Floyd%E2%80%93Warshall_algorithm). (covered)
         * This algorithm will allow us to find the shortest path from node a to node b with 0(v^3) time complexity.
         * We do this to see how separated two users (nodes) are. 
         *  
         */
        void floyd_warshall();

        /**
         * @brief Helper function used by floyed warshall to find the cost of going from one node to another
         * 
         * @param int node a
         * @param int node b
         * @return int cost
         */
        int cost(unsigned int, unsigned int);
};

