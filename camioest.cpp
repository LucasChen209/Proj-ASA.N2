#include <iostream>
#include <utility>
#include <vector>
#include <queue>

using namespace std;

struct Vertice {
    int id; // Changed to int
    int f;  // Changed to int
    vector<int> neighbors; // Vertex IDs fit in int
};

struct Graph {
    vector<Vertice> Vertices;
};

// Keeps unsigned because it calculates the path remainder
unsigned long long CalcTruckNum(unsigned long long _possiblePaths, unsigned long long _numTrucks) {
    return 1 + (_possiblePaths % _numTrucks);
}

void PossiblePaths(Graph &g, vector<vector<unsigned long long>> &memo, int _numVertices, vector<int> &_listTopo, unsigned long long _nTrucks) {
    int Toposize = (int)_listTopo.size();
    for(int v = 0; v < Toposize; v++) {
        int order = _listTopo[v];
        for(int e = 0; e < _numVertices; e++) {
            unsigned long long a = memo[e][order] % _nTrucks;
            if(a == 0) continue;
            for(int n : g.Vertices[order].neighbors) {
                memo[e][n] += memo[order][n] * a;
            }
        }
    }
}

void CalWhichTruck(vector<vector<unsigned long long>> &sorted, int _numVertices, pair<int, int> &gama, unsigned long long &_numTrucks) {
    int l = gama.first - 1, r = gama.second;

    vector<vector<pair<int,int>>> trucks(_numTrucks);
    for(int i = 0; i < _numVertices; i++) {
        for(int j = 0; j < _numVertices; j++) {
            if(sorted[i][j] == 0) continue;
            unsigned long long truck = CalcTruckNum(sorted[i][j], _numTrucks);
            // Safety check to ensure truck index is within range
            if (truck >= (unsigned long long)gama.first && truck <= (unsigned long long)gama.second) {
                trucks[truck - 1].push_back({i+1,j+1});
            }
        }
    }
    for(int i = l; i < r; i++) {
        cout << 'C' << i+1;
        for(pair<int,int> j : trucks[i]) {
            cout << ' ' << j.first << ',' << j.second;
        }
        cout << '\n';
    }
}

void matrizAdj(Graph &g, int nVertices, vector<vector<unsigned long long>> &Memo){
    for (int n = 0; n < nVertices; n++){
        for(int i : g.Vertices[n].neighbors){
            Memo[n][i]++;
        }
    }
}

vector<int> ordTop(Graph &g, int nVertices){
    queue<int> q;
    vector<int> edges(nVertices, 0);
    vector<int> resultado;

    for(int i = 0; i < nVertices; i++){
        for(int next : g.Vertices[i].neighbors){
            edges[next]++;
        }
    }

    for(int i = 0; i < nVertices; i++){
        if(edges[i] == 0) q.push(i);
    }

    while(!q.empty()){
        int tampa = q.front();
        q.pop();
        resultado.push_back(tampa);
        for(int next : g.Vertices[tampa].neighbors){
            edges[next]--;
            if(edges[next] == 0) q.push(next);
        }
    }
    return resultado;
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    int _nVertices, _nEdges, l, r;
    unsigned long long _nTrucks;

    if (!(cin >> _nVertices >> _nTrucks >> l >> r >> _nEdges)) return 0;

    vector<vector<unsigned long long>> Memo(_nVertices, vector<unsigned long long>(_nVertices, 0));
    pair<int, int> _gamaCamioes = {l, r};

    Graph g;
    g.Vertices.resize(_nVertices);
    for(int i = 0; i < _nEdges; i++) {
        int u, v;
        cin >> u >> v;
        g.Vertices[u-1].neighbors.push_back(v-1);
    }
    
    matrizAdj(g, _nVertices, Memo);
    vector<int> pila = ordTop(g, _nVertices);
    
    PossiblePaths(g, Memo, _nVertices, pila, _nTrucks);
    CalWhichTruck(Memo, _nVertices, _gamaCamioes, _nTrucks);

    return 0;
}
