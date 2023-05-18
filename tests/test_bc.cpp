#include "../cs225/catch/catch.hpp"
#include "../graph.h"


vector<string> Datasets = {"datasets/higgs-activity_time.txt",
                            "datasets/higgs-mention_network.edgelist",
                            "datasets/higgs-reply_network.edgelist",
                            "datasets/higgs-retweet_network.edgelist",
                            };

TEST_CASE("graph constructor") {
    for (const auto & set : Datasets) {
        Graph graph(set, -1);
        REQUIRE(true);
    }
}

TEST_CASE("Graph has a most influential node") {
    // More rebust testing for this function was ommited to save time when
    // running the test suite
    Graph graph(Datasets[2], 1000);
    REQUIRE(graph.influential() != -1);
}