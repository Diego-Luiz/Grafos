#include <iostream>
#include <queue>
#include <list>
#include <climits>
#include <string>
#include <map>
#include <set>
#include <utility>
// Ao executar o código leia o arquivo "Leia-me", com as instruções de entrada do algorítimo. 
using namespace std;

vector<string> IN; //conjunto IN de vértices
vector<pair<int,string>> d;
vector<pair<int,string>>::iterator d_it;

void dfs(int v, int indice, vector< vector<int> >& grafo, int& tamanho, map<int, string>& nos, vector<string>& retorno, vector<bool>& visitado)
{
    multimap<int,int> menor;//valor da aresta , indice da coluna da matriz referente ao no
    multimap<int,int>::iterator mit;
    multimap<int,int>::iterator mit_aux;
    
    visitado[v] = true;
    grafo[indice][indice] = 0;
    IN.push_back(nos[v]);

    int aux = 0, temp = 0;
    //Atualização dos pesos 
    for(vector<int>::iterator it = grafo[v].begin(); it!=grafo[v].end(); it++){
        if((grafo[v][temp] < grafo[indice][temp]) && (visitado[temp]==false)){
            grafo[indice][temp] = grafo[v][temp];
            d[temp].first = grafo[v][temp];
            d[temp].second = nos[v];
        }
        temp++;
    }
    //Inserindo os valores da coluna após a atualização
    for(vector<int>::iterator it = grafo[indice].begin(); it!=grafo[indice].end(); it++){
        if(*it != INT_MAX)
            menor.insert(pair<int,int>(*it,aux));
        aux++;
    }
  
    string concatenar=""; //string de retorno
    mit = menor.begin();
    while((mit!=menor.end()) && (menor.size()!=0)){
        if(!visitado[mit->second]){
            concatenar+= d[mit->second].second+"--";
            concatenar+= "("+to_string(mit->first)+")"+"--";
            concatenar+= nos[mit->second];

            retorno.push_back(concatenar);

            dfs(mit->second, indice, grafo, tamanho, nos, retorno, visitado);
            mit++;
        }
        else{
            mit_aux = mit;
            mit_aux++;
            menor.erase(mit);//remove do map se caso ja foi visitado
            mit = mit_aux;
        }
    }
    

}

int main()
{

    string x, y;
    int v, e, z; /* Numero de vertices e arestas */

    cin>>v>>e;
    
    vector<vector<int>> grafo(v);
    vector<bool> visitado(v, false); /* Vetor booleano de v�rtices j� visitados */
    
    map<int, string> nos;
    map<string, int> reverso;
    vector<string> retorno; //vector de resposta final
    
    string nome;
    for(int i=0;i<v;i++){
        cout<<"Digite o nome do "<<i+1<<" no: ";
        cin>>nome;
        nos[i] = nome;
        reverso[nome] = i;
    }
   
    for(int i=0;i<v;i++){
        for(int j=0;j<e;j++){
            grafo[i].push_back(INT_MAX);
        }
    }
    
    cout<<"Digite as ligacoes existentes e seu respectivo peso (Digite 0 0 0 para terminar): "<<endl;
    while(cin>>x>>y>>z, x!="0")
    {   
        grafo[reverso[x]][reverso[y]] = z; /* Aresta x -> y */
        grafo[reverso[y]][reverso[x]] = z; /* Aresta y -> x */
    }
    
    cout<<"Digite o no inicial para o caminho minimo: ";
    cin.ignore();
    getline(cin,nome);
    for(vector<int>::iterator it = grafo[reverso[nome]].begin(); it!=grafo[reverso[nome]].end(); it++){
        d.push_back(make_pair(*it,nome));
    }
    
    dfs(reverso[nome], reverso[nome], grafo, v, nos, retorno, visitado); /* Vertice inicial da busca, grafo, vetor booleano de v�rtices visitados */
    cout<<"\n========> Conjunto IN:\n";
    for(vector<string>::iterator it = IN.begin(); it!= IN.end();it++){
        cout<<*it<<", ";
    }
    cout<<"\n=======> AGM [Origem--(Peso)--Destino]:\n";
    for(vector<string>::iterator it = retorno.begin(); it!= retorno.end();it++){
        cout<<*it<<", ";
    }
    cout<<endl;
   
    return 0;
}
