#include <iostream>
#include <utility>
#include <vector>
#include <queue>

using namespace std;

struct Vertice { // representa um vertice de uma DFS
    unsigned long long id;
    unsigned long long f;
    vector<unsigned long long> neighbors; //todos os vizinhos desse dado ponto, kinda lista de adjacências
};

struct Graph { //grafo em si, nao é necessária ser uma struct, mas li que é boa pratica entao fiz
    vector<Vertice> Vertices;
};


unsigned long long CalcTruckNum(unsigned long long _possiblePaths, unsigned long long _numTrucks) {
    return 1 + _possiblePaths % _numTrucks;
}

void PossiblePaths(Graph g, vector<vector<unsigned long long>> &memo, unsigned long long _numVertices, vector< unsigned long long> _listTopo, unsigned long long _nTrucks) {
    unsigned long long Toposize = _listTopo.size();
    for(unsigned long long v = 0; v < Toposize; v++) {
        unsigned long long order = _listTopo[v];//elemento em si
        for(unsigned long long e = 0; e < _numVertices; e++) {
            unsigned long long a = memo[e][order] % _nTrucks;
            if(a == 0){ // se não existir conexão de e para order
                continue;
            }
            for(unsigned long long n : g.Vertices[order].neighbors) {
                unsigned long long filamult = memo[order][n] * a;
                memo[e][n] += filamult;
                //cout << memo[e][order-1] << "este é depois de somado com" << filamult << endl;
            }
        }

    }

}

void CalWhichTruck(vector<vector<unsigned long long>> sorted, unsigned long long _numVertices, pair<unsigned long long,unsigned long long> &gama, unsigned long long _numTrucks) {
    unsigned long long l = gama.first - 1,r = gama.second;

    vector<string> trucks(_numTrucks,"");
    for(;l < r;l++) {
        trucks[l].push_back('C');
        trucks[l].append(to_string(l + 1));
    }
    for(unsigned long long i = 0; i < _numVertices; i ++) {
        for(unsigned long long j = 0 ; j < _numVertices; j ++) {
            if(sorted[i][j] == 0) {
                continue;
            }
            unsigned long long truck  = CalcTruckNum(sorted[i][j],_numTrucks);
            trucks[truck - 1].append(" " + to_string(i + 1) + "," + to_string(j + 1));
        }
    }

    l = gama.first - 1;
    r = gama.second;
    for (;l < r; l++) {

        if (!trucks[l].empty()) {
            cout << trucks[l] << endl;  // Only print non-empty truck assignments
        }
    }
    return;
    
}

void matrizAdj(Graph g, unsigned long long nVertices, vector<vector<unsigned long long>> &Memo){
    for (unsigned long long n = 0; n < nVertices; n++){
        unsigned long long tamanho = g.Vertices[n].neighbors.size();
        for(unsigned long long n1 = 0; n1 < tamanho; n1++){
            unsigned long long i = g.Vertices[n].neighbors[n1];
            Memo[n][i]++;
        }

    }
    return;
}

vector<unsigned long long> ordTop(Graph g, unsigned long long nVertices){
    

    queue<unsigned long long> q;
    vector<unsigned long long> edges(nVertices,0);
    vector<unsigned long long> resultado;

    for(unsigned long long i = 0; i < nVertices; i++){
        for(unsigned long long next : g.Vertices[i].neighbors){
            edges[next]++;
        }
    }

    for(unsigned long long i = 0; i < nVertices; i++){
        if(edges[i] == 0){
            q.push(i);
        }
    }

    while(!q.empty()){
        unsigned long long tampa = q.front();
        q.pop();
        resultado.push_back(tampa);
        for(unsigned long long next: g.Vertices[tampa].neighbors){

            edges[next]--;
            if(edges[next] == 0){
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
    unsigned long long _nVertices, _nTrucks, _nEdges, l, r, u, v;
    pair<unsigned long long,unsigned long long> _gamaCamioes;

    cin >> _nVertices;
    vector<vector<unsigned long long>> Memo(_nVertices, vector<unsigned long long>(_nVertices, 0));
    cin >> _nTrucks;
    cin >> l >> r;//limite esquerdo da gama//limite direito da gama
    _gamaCamioes.first = l; _gamaCamioes.second = r; //nao sei se isto vai ser necessário, mas vou deixar so para garantir
    cin >>_nEdges;
    unsigned long long _edgesRead = 0;
    g.Vertices = vector<Vertice>(_nVertices);
    while(_edgesRead < _nEdges) {
        cin >> u;
        cin >> v;
        u--;
        v--;
        g.Vertices[u].neighbors.push_back(v);
        _edgesRead ++;
    }
    
    matrizAdj(g, _nVertices, Memo);
    vector <unsigned long long> pila = ordTop(g, _nVertices);
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
    PossiblePaths(g,Memo,_nVertices,pila,_nTrucks);
    /*for (int n = 0; n < _nVertices; n++){
        for (int n1 = 0; n1 < _nVertices; n1++){
            cout << Memo[n][n1] << ' ';dasdagshhfhqhshdfbeubqsocjioqwshjfj
        }
        cout << endl;
    }
    cout << endl;*/
    CalWhichTruck(Memo, _nVertices, _gamaCamioes, _nTrucks);
    


    return 0;
}