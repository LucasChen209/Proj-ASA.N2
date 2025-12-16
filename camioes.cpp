#include <iostream>
#include <utility>
#include <vector>

using namespace std;

struct Vertice { // representa um vertice de uma DFS
    int id;
    int f;
    vector<int> neighbors; //todos os vizinhos desse dado ponto, kinda lista de adjacências
};

struct Graph { //grafo em si, nao é necessária ser uma struct, mas li que é boa pratica entao fiz
    vector<Vertice> Vertices;
};



int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    Graph g;
    int _nVertices, _nTrucks, _nEdges, l, r, u, v;
    vector<int> _gamaCamioes;
    vector<pair<int, int>> _edges;

    cin >> _nVertices;
    cin >> _nTrucks;
    cin >> l;//limite esquerdo da gama
    cin >> r;//limite direito da gama
    _gamaCamioes.push_back(l); _gamaCamioes.push_back(r); //nao sei se isto vai ser necessário, mas vou deixar so para garantir
    cin >>_nEdges;
    int _edgesRead = 0;
    g.Vertices.resize(_nVertices);
    
    while(_edgesRead < _nEdges) {
        cin >> u;
        cin >> v;
        g.Vertices[u].neighbors.push_back(v);
        _edgesRead ++;
    }
    /*cout << _nVertices << endl;
    cout << _nTrucks << endl;
    cout << l << endl;
    cout << r << endl;
    cout << _nEdges << endl;
    for(size_t i = 0; i < g.Vertices.size(); i++) {
        for(size_t j = 0; j < g.Vertices[i].neighbors.size(); j++) {
            cout << g.Vertices[i].neighbors[j] << endl;
        }
    } // foi só para testar se o output copiado era o correto*/
   


    return 0;
}