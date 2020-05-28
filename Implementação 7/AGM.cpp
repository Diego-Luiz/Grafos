#include <iostream>
#include <queue>
#include <list>
#include <climits>
#include <string>
#include <map>

using namespace std;

void bfs(int inicial, vector< list<int> >& grafo, vector<bool>& visitado)
{

    queue<int> fila;
    fila.push(inicial); /* V�rtice inicial da busca */
    visitado[inicial] = true;

    while(fila.size()>0)
    {
        int v = fila.front();
        fila.pop();

        cout<<"Vertice "<<v<<" foi visitado."<<endl;
        for(list<int>::iterator it = grafo[v].begin(); it!=grafo[v].end(); it++)
        {
            if(!visitado[*it])
            {
                visitado[*it] = true;
                fila.push(*it);
            }
        }

    }

}

int main()
{

    string x, y;
    int v, e, z; /* N�mero de v�rtices e arestas */

    cin>>v>>e;
    int grafo[v][e];//6x6
    vector<bool> visitado(v, false); /* Vetor booleano de v�rtices j� visitados */
    // vector< vector<int>(v,100000) > grafo(v); /* Grafo com v v�rtices */
    map<int, string> nos;
    map<string, int> reverso;
    string nome;
    for(int i=0;i<v;i++){
        cout<<"Digite o nome do "<<i+1<<" no: ";
        cin>>nome;
        nos[i] = nome;
        reverso[nome] = i;
    }
    // cout<<"MAP: "<<endl;
    // for(int i=0;i<v;i++){
    //     cout<<nos[i]<<endl;
    // }
    for(int i=0;i<v;i++){
        for(int j=0;j<e;j++){
            grafo[i][j] = INT_MAX;
        }
    }
    
    cout<<"Digite as ligacoes existentes e seu respectivo peso (Digite 0 0 0 para terminar): "<<endl;
    while(cin>>x>>y>>z, x!="0")
    {   
        grafo[reverso[x]][reverso[y]] = z; /* Aresta x -> y */
        grafo[reverso[y]][reverso[x]] = z; /* Aresta y -> x */
    }
    for(int i=0;i<v;i++){
        for(int j=0;j<e;j++){
            cout<<grafo[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<"Digite o no inicial para o caminho minimo: ";
    cin>>nome;
    bfs(0, grafo, visitado); /* V�rtice inicial da busca, grafo, vetor booleano de v�rtices visitados */


    return 0;
}