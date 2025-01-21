#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <cstdlib>
#include <cmath>
using namespace std;

class Node {
    private:
        unordered_map<int, string> typeNameTable = {
            {0, "Starting Room"},
            {1, "Combat"},
            {2, "Trade"},
            {3, "Treasure"},
            {4, "Encounter"},
            {5, "Elite Combat"},
            {6, "Boss Battle"}
        };

        bool reachable;
        bool isEnd;
        int nodeLayer;
        int nodeType;
        string typeName;
        string name;
        vector<Node *> next; // nodes that can be reached from this one

    public:
        class Builder;
        friend class Builder;

        Node() : reachable(false), isEnd(false), nodeLayer(-1), nodeType(-1), typeName(""), name("") {}

        void setReachable(bool tog) {
            reachable = tog;
        }

        void setEnd(bool tog) {
            isEnd = tog;
        }

        void setLayer(int newLayer) {
            nodeLayer = newLayer;
        }

        void setType(int newType) {
            if (typeNameTable.find(newType) == typeNameTable.end()) {
                cerr << "Invalid node type" << endl;
                exit(1);
            }
            nodeType = newType;
            typeName = typeNameTable[newType];
        }

        void setName(const string &newName) {
            name = newName;
        }

        void addNextNode(Node *nextNode) {
            next.push_back(nextNode);
        }

        vector<Node *> getNextNodes() {
            return next;
        }

        bool isReachable() {
            return reachable;
        }

        int getLayer() {
            return nodeLayer;
        }
};

class Graph {
    private:
        vector<vector<Node>> layers;
        Node root;
    
    public:
        Graph(int numLayers, vector<int> numLayerNodes) {
            layers.resize(numLayers);
            for (int i = 0; i < numLayers; i++) {
                int numNodes = numLayerNodes[i];
                layers[i].resize(numNodes);

                for (int j = 0; j < numNodes; j++) {
                    layers[i][j].setLayer(i);
                    if (i == numLayers - 1) 
                        layers[i][j].setEnd(true);
                }
            }
        }

        void linkLayers() {
            for (int i = 0; i < layers.size() - 1; i++) {
                for (Node &node: layers[i]) {
                    int curLayerSize = layers[i].size(); 
                    int nextLayerSize = layers[i+1].size();

                    int numLinks = min(
                        rand() % nextLayerSize, 
                        (int)floor(sqrt(curLayerSize * nextLayerSize))
                    ); //at least floor(sqrt(n*m)) links

                    for (int j = 0; j < numLinks; j++) {
                        int nextNodeIndex = rand() % nextLayerSize;
                        node.addNextNode(&layers[i+1][nextNodeIndex]);
                    }
                }
            }
        }

        void ensureReachability() {
            if (layers.empty() || layers[0].empty()) return;

            queue<Node *> q;
            layers[0][0].setReachable(true);
            q.push(&layers[0][0]);

            while (!q.empty()) {
                Node *cur = q.front();
                q.pop();

                for (Node *nextNode: cur->getNextNodes()) {
                    if (!nextNode->isReachable()) {
                        nextNode->setReachable(true);
                        q.push(nextNode);
                    }
                }
            }
            
            for (int i = 1; i < layers.size(); i++) { //since the root is always reachable
                int preLayerSize = layers[i-1].size();
                
                for (int j = 0; j < layers[i].size(); j++) {
                    Node *cur = &layers[i][j];
                    if (!cur->isReachable()) {
                        int preNodeIndex = rand() % preLayerSize;
                        layers[i-1][preNodeIndex].addNextNode(cur);
                        cur->setReachable(true);
                    }
                }
            }
        }

        void drawGraph() {
            const int NODE_SPACING = 8;  // Horizontal spacing between nodes
            vector<vector<string>> canvas;
            int maxNodesInLayer = 0;
            
            // Find maximum width needed
            for (const auto& layer : layers) {
                maxNodesInLayer = max(maxNodesInLayer, (int)layer.size());
            }
            
            // Initialize canvas
            int height = layers.size() * 3;  // 3 rows per layer
            int width = maxNodesInLayer * NODE_SPACING + 1;
            canvas.resize(height, vector<string>(width, " "));
            
            // Draw nodes and connections
            for (int i = 0; i < layers.size(); i++) {
                int y = i * 3;
                int layerSize = layers[i].size();
                int offset = (maxNodesInLayer - layerSize) * NODE_SPACING / 2;
                
                // Draw nodes
                for (int j = 0; j < layerSize; j++) {
                    int x = j * NODE_SPACING + offset;
                    Node* node = &layers[i][j];
                    string nodeSymbol = node->isReachable() ? "[O]" : "[X]";
                    
                    // Place node symbol
                    canvas[y][x] = nodeSymbol[0];
                    canvas[y][x + 1] = nodeSymbol[1];
                    canvas[y][x + 2] = nodeSymbol[2];
                    
                    // Draw connections to next layer
                    if (i < layers.size() - 1) {
                        for (Node* next : node->getNextNodes()) {
                            int nextIndex = 0;
                            // Find index of next node in next layer
                            for (int k = 0; k < layers[i + 1].size(); k++) {
                                if (&layers[i + 1][k] == next) {
                                    nextIndex = k;
                                    break;
                                }
                            }
                            int nextX = nextIndex * NODE_SPACING + 
                                (maxNodesInLayer - layers[i + 1].size()) * NODE_SPACING / 2;
                            
                            // Draw connection line
                            if (x < nextX) {
                                canvas[y + 1][x + 3] = '\\';
                            } else if (x > nextX) {
                                canvas[y + 1][x - 1] = '/';
                            } else {
                                canvas[y + 1][x + 1] = '|';
                            }
                        }
                    }
                }
            }
            
            // Print canvas
            for (const auto& row : canvas) {
                for (const string& cell : row) {
                    cout << cell;
                }
                cout << endl;
            }
        }
};

int main() {
    int numLayers = 6;
    vector<int> numLayerNodes = {1, 2, 3, 3, 2, 4};

    Graph graph(numLayers, numLayerNodes);
    graph.linkLayers();
    graph.ensureReachability();
    graph.drawGraph();

    int c; cin >> c;
    return 0;
}