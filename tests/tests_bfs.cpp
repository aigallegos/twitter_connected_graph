#include "../cs225/catch/catch.hpp"
#include "../graph.h"


//test that it runs at all
TEST_CASE("Test BFS Running") {
    Graph graph("tests/test_datasets/bfs_test_simple.edgelist", -1);
    graph.BFSTraversal();
    REQUIRE(true);
}


//test functionalities on a simple yet non-trivial sample dataset
TEST_CASE("Test Simple BFS") {
    Graph graph("tests/test_datasets/bfs_test_simple.edgelist", -1);
    vector<int> BFSOrder = graph.BFSTraversal();
    std::cout << '\n' << "BFS" << std::endl;
    for (auto it: BFSOrder) {
        std::cout << it << ' ';
    }
    std::cout << std::endl;
    //check size: expected = 10
    REQUIRE(graph.numNodesExplored() == 10);
    //check bottom-to-top BFS
    vector<int> expected = {10, 9, 8, 3, 1, 7, 5, 2, 6, 4};
    REQUIRE(BFSOrder == expected);


}

TEST_CASE("Test BFS on full dataset") {
    Graph graph("datasets/higgs-reply_network.edgelist", -1);
    vector<int> BFSOrder = graph.BFSTraversal();
    REQUIRE(BFSOrder.size() == 38918);


    // for (auto it: BFSOrder) {
    //     std::cout << it << ' ';
    // }
    // std::cout << std::endl;

    // REQUIRE(BFSOrder.size() == 38918);
}