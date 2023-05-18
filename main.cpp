#include "graph.h"

int main(int argc, char *argv[]) {
    std::string arg1;
    int arg2;
    std::string arg3;
    char arg4;
    int arg5;
    int arg6;

    if (argc <= 1) {
        arg1 = "datasets/higgs-reply_network.edgelist";
        arg2 = -1;
        arg3 = "Results";
    } if (argc == 2) {
        if (strcmp(argv[1], "datasets/higgs-social_network.edgelist") != 0 && strcmp(argv[1], "datasets/higgs-retweet_network.edgelist") != 0 && strcmp(argv[1], "datasets/higgs-reply_network.edgelist") != 0 && strcmp(argv[1], "datasets/higgs-mention_network.edgelist") != 0 && strcmp(argv[1], "datasets/higgs-activity_time.txt") != 0) {
            std::cerr << "ERROR: Invalid Dataset Name" << std::endl;
            return 1;
        }
        arg1 = argv[1];
        arg2 = -1;
        arg3 = "Results";
    } if (argc == 3) {
        if (strcmp(argv[1], "tests/test_datasets/bfs_test_simple.edgelist") != 0 && strcmp(argv[1], "datasets/higgs-social_network.edgelist") != 0 && strcmp(argv[1], "datasets/higgs-retweet_network.edgelist") != 0 && strcmp(argv[1], "datasets/higgs-reply_network.edgelist") != 0 && strcmp(argv[1], "datasets/higgs-mention_network.edgelist") != 0 && strcmp(argv[1], "datasets/higgs-activity_time.txt") != 0) {
            std::cerr << "ERROR: Invalid Dataset Name" << std::endl;
            return 1;
        }
        arg1 = argv[1];
        if (strcmp(argv[2], "all") == 0) {
            arg2 = -1;
        } else {
            try {
                arg2 = std::stoi(argv[2]);
            } catch (const std::exception& ex){
                std::cerr << "ERROR: Incorrect Argument Format" << std::endl;
                std::cout << "**CORRECT FORMAT : Dataset: (string)\tRange of Dataset: (int or \"all\")\tName of Result .txt file: (string)\n*OPTIONAL: *\tRun Shortest Path? (Y or N)\t NodeA: (int)\tNodeB: (int)**" << std::endl;
                return 1;
            }
        }
        arg3 = "Results";
    }
    if (argc >= 4) {
        if (strcmp(argv[1], "tests/test_datasets/bfs_test_simple.edgelist") != 0 && strcmp(argv[1], "datasets/higgs-social_network.edgelist") != 0 && strcmp(argv[1], "datasets/higgs-retweet_network.edgelist") != 0 && strcmp(argv[1], "datasets/higgs-reply_network.edgelist") != 0 && strcmp(argv[1], "datasets/higgs-mention_network.edgelist") != 0 && strcmp(argv[1], "datasets/higgs-activity_time.txt") != 0) {
            std::cerr << "ERROR: Invalid Dataset Name" << std::endl;
            return 1;
        }
        arg1 = argv[1];
        if (strcmp(argv[2], "all") == 0) {
            arg2 = -1;
        } else {
            try {
                arg2 = std::stoi(argv[2]);
            } catch (const std::exception& ex){
                std::cerr << "ERROR: Incorrect Argument Format" << std::endl;
                std::cout << "**CORRECT FORMAT : Dataset: (string)\tRange of Dataset: (int or \"all\")\tName of Result .txt file: (string)\n*OPTIONAL: *\tRun Shortest Path? (Y or N)\t NodeA: (int)\tNodeB: (int)**" << std::endl;
                return 1;
            }
        }
        arg3 = argv[3];
    }

    if (argc >= 5 && strcmp(argv[4], "N") == 0) {
        return 0;
    }
    if (argc == 6 || (argc == 5 && strcmp(argv[4], "Y") == 0) ) {
        std::cerr << "ERROR: Incorrect Argument Format" << std::endl;
        std::cout << "**CORRECT FORMAT : Dataset: (string)\tRange of Dataset: (int or \"all\")\tName of Result .txt file: (string)\n*OPTIONAL: *\tRun Shortest Path? (Y or N)\t NodeA: (int)\tNodeB: (int)**" << std::endl;
        return 1;
    }

    if (argc == 7) {
        if (strcmp(argv[4], "Y") != 0 && strcmp(argv[4], "N") != 0) {
            std::cerr << "ERROR: Incorrect Argument Format" << std::endl;
            std::cout << "**CORRECT FORMAT : Dataset: (string)\tRange of Dataset: (int or \"all\")\tName of Result .txt file: (string)\n*OPTIONAL: *\tRun Shortest Path? (Y or N)\t NodeA: (int)\tNodeB: (int)**" << std::endl;
            return 1;
        }
        try {
            arg5 = std::stoi(argv[5]);
            arg6 = std::stoi(argv[6]);
        } catch (const std::exception& ex){
            std::cerr << "ERROR: Incorrect Argument Format" << std::endl;
            std::cout << "**CORRECT FORMAT : Dataset: (string)\tRange of Dataset: (int or \"all\")\tName of Result .txt file: (string)\n*OPTIONAL: *\tRun Shortest Path? (Y or N)\t NodeA: (int)\tNodeB: (int)**" << std::endl;
            return 1;
        }
    }

    if (argc >= 8) {
        std::cerr << "ERROR: Incorrect Argument Format" << std::endl;
        std::cout << "**CORRECT FORMAT : Dataset: (string)\tRange of Dataset: (int or \"all\")\tName of Result .txt file: (string)\n*OPTIONAL: *\tRun Shortest Path? (Y or N)\t NodeA: (int)\tNodeB: (int)**" << std::endl;
        return 1;
    }

    
    // need to take input testset from command line
    Graph graph(arg1, arg2);

    // USE BFS TO GET OUR TOTAL NUMBER OF NODES EXPLORED
    graph.BFStoFile(arg3 + "_BFS_.txt");


    // USE FLOYED WARSHAL TO FIND A SHORTEST PATH
    if (argc >= 5 && strcmp(argv[4], "Y") == 0) {
        graph.FWtoFile(arg3 + "_FW_.txt", arg5, arg6);
    }

    // USE BETWEENNESS CENTRALITY TO FIND THE MOST INFLUENTIAL NODE
    graph.BCtoFile(arg3 + "_BC_.txt", arg1);

    return 0;
}