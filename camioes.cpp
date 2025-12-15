#include <iostream>
#include <vector>

using namespace std;

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    string nCruzamentos, nCamioes, gamas, nCaminhos, individual;
    vector<string> caminhos;
    int numero;
    
    getline(cin,nCruzamentos);
    getline(cin,nCamioes);
    getline(cin,gamas);
    getline(cin,nCaminhos);

    numero = stoi(nCaminhos);
    caminhos.reserve(numero);

    for (int i = 0; i < numero; i++){

        getline(cin, individual);
        caminhos.push_back(individual);

    }
    
    cout << caminhos.size() << endl;


    return 0;
}