#include <iostream>
#include <vector>
using namespace std;

class QuadPixelGraph {
    private:
        int idx;
        int width;
        int **graph;
        const int dir[4][2] = {{0, 0}, {0, 1}, {1, 1}, {1, 0}};

        bool isUniform(int size, int startX, int startY, int &val) {
            val = graph[startX][startY];

            for (int i = startX; i < startX + size; i++) 
                for (int j = startY; j < startY + size; j++) 
                    if (graph[i][j] != val) return false;
            return true;
        }

        string encoder(int size, int startX, int startY) {
            int uniformVal;

            if (isUniform(size, startX, startY, uniformVal)) {
                return to_string(uniformVal);
            }
            else {
                string parts = "2";
                for (int i = 0; i < 4; i++) {
                    int nextX = startX + dir[i][0]*size/2,
                        nextY = startY + dir[i][1]*size/2;
                    parts += encoder(size/2, nextX, nextY);
                }
                return parts;
            }
        }

        void draw(int size, string s, int curX, int curY) {
            char c = s[idx++];
            if (c == '0' || c == '1'){
                for (int i = curX; i < curX+size; i++)
                    for (int j = curY; j < curY+size; j++) 
                        graph[i][j] = c - '0';
            }
            else if (c == '2'){
                for (int i = 0; i < 4; i++) {
                    int nextX = curX + dir[i][0]*size/2, 
                        nextY = curY + dir[i][1]*size/2;
                    draw(size/2, s, nextX, nextY);
                }
            }
            else {
                cerr << "Invalid expression" << endl;
                exit(1);
            }
        }

    public:
        QuadPixelGraph(): idx(0), width(0), graph(nullptr) {}

        int **decode(int size, string text) {
            idx = 0;
            width = size;
            graph = (int **)malloc(size*sizeof(int *));

            for (int i = 0; i < size; i++) 
                graph[i] = (int *)calloc(size, sizeof(int));

            draw(size, text, 0, 0);
            return graph;
        }

        string encode(int size, int **g) {
            width = size;
            if (graph) free(graph);

            graph = (int **)malloc(width*sizeof(int *));
            for (int i = 0; i < width; i++) {
                graph[i] = (int *)malloc(width*sizeof(int));
                for (int j = 0; j < width; j++) 
                    graph[i][j] = g[i][j];
            }

            return encoder(size, 0, 0);
        }

        void show() {
            if (!width) return;
            for (int i = 0; i < width; i++) {
                for (int j = 0; j < width; j++) 
                    cout << graph[i][j] << " ";
                cout << endl;
            }
        }
};

int main() {
    int width;
    cin >> width;
    
    int **g = (int **)malloc(width*sizeof(int *));
    for (int i = 0; i < width; i++) {
        g[i] = (int *)malloc(width*sizeof(int));
        for (int j = 0; j < width; j++) 
            cin >> g[i][j];
    }

    QuadPixelGraph graph; 
    string text = graph.encode(width, g);
    //cout << text << endl;
    graph.show();
}