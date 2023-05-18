#include "../cs225/catch/catch.hpp"

#include "../graph.h"



TEST_CASE("Test FW Running") {
    REQUIRE(true);
}


/**
 * @brief 
 * 
 * 1: test data is retrieved correctly
 * 
 * 2: test if graph stored the correct number of items
 * 
 * 3: adj has correct size
 * 
 * 4: test that floyed warshall acctually creates something
 * 
 * 5: test that shortest paths exist on test txt file
 * 
 * 6: BFS test that every node is reached
 * 
 */


vector<string> datasets = {"datasets/higgs-activity_time.txt",
                            "datasets/higgs-mention_network.edgelist",
                            "datasets/higgs-reply_network.edgelist",
                            "datasets/higgs-retweet_network.edgelist",
                            };

TEST_CASE("test basic shortest path") {
    Graph graph("tests/test_datasets/bfs_test_simple.edgelist", -1);
    REQUIRE(graph.shortest_path(10, 3) == std::vector<unsigned int>({ 10, 9, 8, 3, 3 }));
}

TEST_CASE("test complex shortest path") {
    Graph graph(datasets[2], 2000);
    REQUIRE(graph.shortest_path(119135, 13537) == std::vector<unsigned int>({119135, 3228, 13537, 2}));
}