#include <iostream>
#include <utility>
#include <vector>
#include <queue>

using namespace std;

struct Vertice { // representa um vertice de uma DFS
    int id;
    int f;
    vector<int> neighbors; //todos os vizinhos desse dado ponto, kinda lista de adjacências
};

struct Graph { //grafo em si, nao é necessária ser uma struct, mas li que é boa pratica entao fiz
    vector<Vertice> Vertices;
};

void matrizAdj(Graph g, int nVertices, vector<vector<int>> &Memo){
    for (int n = 0; n < nVertices; n++){
        int tamanho = g.Vertices[n].neighbors.size();
        for(int n1 = 0; n1 < tamanho; n1++){
            int i = g.Vertices[n].neighbors[n1];
            Memo[n][i-1]++;
        }

    }
    return;
}

vector<int> ordTop(Graph g, int nVertices){
    

    queue<int> q;
    vector<int> edges(nVertices,0);
    vector<int> resultado;

    for(int i = 0; i < nVertices; i++){
        for(int next : g.Vertices[i].neighbors){
            edges[next-1]++;
        }
    }

    for(int i = 1; i <= nVertices; i++){
        if(edges[i-1] == 0){
            q.push(i);
        }
    }

    while(!q.empty()){
        int tampa = q.front();
        q.pop();
        resultado.push_back(tampa);
        for(int next: g.Vertices[tampa-1].neighbors){

            edges[next-1]--;
            if(edges[next-1] == 0){
                q.push(next);
            }
        }
    }
    return resultado;

}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    Graph g;
    int _nVertices, _nTrucks, _nEdges, l, r, u, v;
    vector<int> _gamaCamioes;
    vector<pair<int, int>> _edges;

    cin >> _nVertices;
    vector<vector<int>> Memo(_nVertices, vector<int>(_nVertices, 0));
    cin >> _nTrucks;
    cin >> l >> r;//limite esquerdo da gama//limite direito da gama
    _gamaCamioes.push_back(l); _gamaCamioes.push_back(r); //nao sei se isto vai ser necessário, mas vou deixar so para garantir
    cin >>_nEdges;
    int _edgesRead = 0;
    g.Vertices.resize(_nVertices);
    
    while(_edgesRead < _nEdges) {
        cin >> u;
        cin >> v;
        u--;
        g.Vertices[u].neighbors.push_back(v);
        _edgesRead ++;
    }

    matrizAdj(g, _nVertices, Memo);
    vector <int> pila = ordTop(g, _nVertices);
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
    for (int next: pila){
        cout << next << ' ';
    }
    cout << endl;


    return 0;
}