#include "graph.h"

Graph::Graph(string file_name, int arg1) {
    if (file_name.find(".edgelist") != file_name.npos) {
        read_edglist_to_graph(file_name, arg1);
    } else if (file_name.find(".txt") != file_name.npos) {
        read_txt_to_graph(file_name);
    } else {
        std::cout << "Incorrect file type passed" << std::endl;
    }
    unsigned int k = 0;
    for (auto & data : _vertex_table) {
        _vertex_key.push_back(data.first);
        data.second = k;
        ++k;
    }
}

void Graph::read_edglist_to_graph(string file_name, int arg1) {
    ifstream ifs(file_name);
    string line;
    int counter = 0;
    bool flag = false;
    if (ifs.is_open()) {
        while (getline(ifs, line)) {
            /* Used to break the line by whitespace. The CMU Dict does this for
             * separating words from their pronunciations. */
            stringstream line_ss(line);
            istream_iterator<string> line_begin(line_ss);
            istream_iterator<string> line_end;
            if (line[0] != '#' && *line_begin != ";;;") {
                istream_iterator<string> temp_itr = line_begin;
                if (counter >= arg1 && arg1 >= 0) {
                    std::cout << "** IMPORTANT: Graph not guaranteed to be connected due to use of subset of data **" << std::endl;
                    break;
                }
                unsigned int userA = std::stoi(*temp_itr);
                ++temp_itr;
                unsigned int userB = std::stoi(*temp_itr);
                ++temp_itr;
                unsigned int timePeriod = std::stoi(*temp_itr);
                Node node(userB, timePeriod);
                if ( _adj_list.find (userA) == _adj_list.end()) {
                    _adj_list.insert({ userA, list<Node>{node} });
                } else {
                    _adj_list.at(userA).push_back(node);
                }
                // 
                if ( _vertex_table.find (userA) == _vertex_table.end()) {
                    _vertex_table.insert({ userA, 0 });
                }
                if ( _vertex_table.find (userB) == _vertex_table.end()) {
                    _vertex_table.insert({ userB, 0 });
                }
                counter ++;
            }
        }
    }
    /* If it's not open then... well... just don't do anything for the sake
     * of simplicity. */
}

void Graph::read_txt_to_graph(string file_name) {
    ifstream ifs(file_name);
    string line;
    if (ifs.is_open()) {
        while (getline(ifs, line)) {
            /* Used to break the line by whitespace. */
            stringstream line_ss(line);
            istream_iterator<string> line_begin(line_ss);

            istream_iterator<string> line_end;
            if (line[0] != '#' && *line_begin != ";;;") {
                /* Associate the word with the rest of the line
                 * (its pronunciation). */
                istream_iterator<string> temp_itr = line_begin;
                unsigned int userA = std::stoi(*temp_itr);
                ++temp_itr;
                unsigned int userB = std::stoi(*temp_itr);
                ++temp_itr;
                unsigned int time = std::stoi(*temp_itr);
                ++temp_itr;
                std::string type = *(temp_itr);
                Node node(userB, time, type);
                if (userA == userB) {
                    continue;
                }
                if ( _adj_list.find (userA) == _adj_list.end()) {
                    _adj_list.insert({ userA, list<Node>{node} });
                } else {
                    _adj_list.at(userA).push_back(node);
                }
                if ( _vertex_table.find (userA) == _vertex_table.end()) {
                    _vertex_table.insert({ userA, 0 });
                }
                if ( _vertex_table.find (userB) == _vertex_table.end()) {
                    _vertex_table.insert({ userB, 0 });
                }
            }
        }
    }
}

unsigned int Graph::numNodesExplored() {
    return BFSTraversal().size();
}

vector<int> Graph::BFSTraversal() { 
    /**
     * BFS(G):
     *      foreach(Vertex v : G.vertices()):
     *          setLabel(v, UNEXPLORED)
     *      foreach(Edge e : G.edges()):
     *          setLabel(e, UNEXPLORED)
     *      foreach(Vertex v : G.vertices):
     *          if getLabel(v) == UNEXPLORED;
     *          BFS(G, V)
     */

    auto n = _vertex_table.size();
    vector<bool> explored(n, false);
    vector<int> visited;
    for (unsigned i = 0; i < _adj_list.size(); ++i) {
        if (!(explored[i])) {
            BFSTraversal(explored, visited, i);
        }
    }
    return visited;
}

void Graph::BFSTraversal(vector<bool>& explored, vector<int>& visited, unsigned int idx) {
    /**
     * BFS(G, v):
     *      Queue q
     *      setLabel(v, VISITED)
     *      q.enqueue(v)
     * 
     *      while (!q.empty())
     *          v = q.dequeue()
     *          foreach(Vertex w : G.adjacent(v)):
     *              if (getLabel(w) == UNEXPLORED)
     *                  setLabel(v, w, DISCOVERY)
     *                  setLable(w, VISITED)
     *                  q.enqueue(w)
     *              else if (getLabel(v, w) == UNEXPLORED):
     *                  setLabel(v, w, CROSS)
     */

    queue<unsigned int> q;
    q.push(idx);
    explored[idx] = true;
    while (!q.empty()) {
        auto i = q.front();
        q.pop();
        for (auto & node : _adj_list[_vertex_key[i]]) {
            auto k = _vertex_table.find(node.vertex_)->second;
            if (!(explored[k])) {
                explored[k] = true;
                q.push(k);
            }
        }
        explored[i] = true;
        visited.push_back(_vertex_key[i]);
    }
}

vector<unsigned int> Graph::shortest_path(unsigned int u, unsigned int v) { 
    
    if (_d.empty()) floyd_warshall();

    int indexu = _vertex_table.find(u)->second;
    int indexv = _vertex_table.find(v)->second;
    vector<unsigned int> path = {};
    if (_n[indexu][indexv] == -1) return path;
     path.push_back(u);
     unsigned int total = 0;
     unsigned int i = 0;
     while (u != v)
     {
         indexu = _vertex_table.find(u)->second;
         
         if (i > _adj_list.size() || _n[indexu][indexv] == -1) {
             std::cout << "NODES ARE NOT CONNECTED" << std::endl;
             return path;
         } 
         total += cost(u , _vertex_key[_n[indexu][indexv]]);
         u = _vertex_key[_n[indexu][indexv]];
         path.push_back(u);
         ++i;
     }
     if (total > 0 ) path.push_back(total);
     return path;
     
}




void Graph::floyd_warshall() {
    /**
     * FloydWarshall(G):
     *      Let d be a adj. matrix initialized to +inf
     *          foreach (Vertex v : G):
     *              d[v][v] = 0
     *          foreach (Edge (u, v) : G):
     *              d[u][v] = cost(u, v)
     *          foreach (Vertex w : G):
     *              foreach (Vertex u : G):
     *                  foreach (Vertex v : G):
     *                      if (d[u, v] > d[u, w] + d[w, v])
     *                          d[u, v] = d[u, w] + d[w, v]
     */    

    

    int INFTY = std::numeric_limits<int>::max();
    // initilize the matrix 
    auto _size = _vertex_table.size();
    _d = vector<vector<int>> (_size, vector<int>(_size, INFTY));
    _n = vector<vector<int>> (_size, vector<int>(_size, -1));
    for (const auto & entry : _adj_list) {
        auto u = entry.first;
        auto i = _vertex_table.find(u)->second;
        for (const auto & edge : entry.second) {
            auto v = edge.vertex_;
            auto j = _vertex_table.find(v)->second;
            _d[i][j] = edge.weight_;
            _n[i][j] = j;
        }
    }
    for (unsigned int i = 0; i < _size; ++i) {
        _d[i][i] = 0;
        _n[i][i] = i;
    }
    for (unsigned int w = 0; w < _size; ++w) {
        for (unsigned int u = 0; u < _size; ++u) {
            for (unsigned int v = 0; v < _size; ++v) {
                // find node 
                if (_d[u][w] != INFTY && _d[w][v] != INFTY && _d[u][v] > _d[u][w] + _d[w][v]) {
                    _d[u][v] = _d[u][w] + _d[w][v];
                    _n[u][v] = _n[u][w];
                }
            }
        }
    }
    
}

int Graph::cost(unsigned int u, unsigned int v) {
    int INFTY = std::numeric_limits<int>::max();
    if (_adj_list.find(u) == _adj_list.end()) {
        return INFTY;
    }

    for (const auto & edge : _adj_list.at(u)) {
        if (edge.vertex_ == v) {
            return edge.weight_;
        }
    }
    return INFTY;
}


vector<int> Graph::betweenness_centrality() {
    auto n = _vertex_key.size();
    vector<int> betweenness(n, 0);
    for (const auto & s : _vertex_key) {
        stack<unsigned int> S;
        vector<list<unsigned int>> P(n);
        vector<double> sigma(n, 0.0);
        vector<int> d(n, -1);
        auto k = _vertex_table.find(s);
        sigma[k->second] = 1;
        d[k->second] = 0;
        queue<unsigned int> Q;
        Q.push(s);
        while (!Q.empty()) {
            auto v  = Q.front();
            Q.pop();
            S.push(v);
            auto k = _vertex_table.find(v);
            // for each neighbor of w to v
            for (const auto & w : _adj_list[v]) {
                auto j = _vertex_table.find(w.vertex_);
                if (d[j->second] < 0) {
                    Q.push(w.vertex_);
                    d[j->second] = d[k->second] + 1;
                }
                if (d[j->second] == d[k->second] + 1) {
                    // do stuff
                    sigma[j->second] = sigma[j->second] + sigma[k->second];
                    P.at(j->second).push_back(k->first);
                }
            }

        }
        vector<double> delta(n, 0.0);
        while (!S.empty()) {
            auto w = S.top();
            auto j = _vertex_table.find(w);
            S.pop();
            for (const auto & v : P[j->second]) {
                auto k = _vertex_table.find(v);
                delta[k->second] += (sigma[k->second] / sigma[j->second]) * (1 + delta[j->second]);
            }
            if (w != s) {
                betweenness[j->second] += delta[j->second];
            }
        }
    }
    return betweenness;
}


int Graph::influential() {
    auto betweenness = betweenness_centrality();
    int max = -1;
    int node = -1;
    for (unsigned int i = 0; i < betweenness.size(); ++i) {
        if (betweenness[i] > max) {
            max = betweenness[i];
            node = _vertex_key[i];
        }
    }
    return node;
}


void Graph::FWtoFile(string filename, int arg5, int arg6) {
    std::vector<unsigned int> path = shortest_path(arg5, arg6);
    std::ofstream out(filename);
    if (out.is_open()) {
        if (path.size() >= 1) { 
            out << "LENGTH OF PATH: " << path.at(path.size() - 1);
        } else {
            out << "SHORTEST PATH NOT FOUND";
        }
        out << "\n\n";
        for (int i = 0; i < (((int)path.size()) - 1); ++i) {
            out << path.at(i) << "\n";
        }
        
        out.close();
    }
}

void Graph::BFStoFile(string filename) {
    vector<int> bfs_ = BFSTraversal();
    std::ofstream out(filename);
    if (out.is_open()) {
        out << "NUMBER OF NODES EXPLORED:\t" <<  numNodesExplored() << "\n\n";
        for (auto it : bfs_) {
            out << it << '\n';
        }
        out.close();
    }
}

void Graph::BCtoFile(string filename, string arg1) {
    auto betweenness = betweenness_centrality();
    std::ofstream out(filename);
    if (out.is_open()) {
        out << "THE MOST INFLUENTIAL NODE IN THE " << arg1 << " GRAPH IS NODE:\t" << influential() << "\n\n";
        for (auto it : betweenness) {
            out << it << '\n';
        }
        out.close();
    }
}