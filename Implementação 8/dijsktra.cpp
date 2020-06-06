#include <iostream>
#include <climits>
#include <queue>
#include <vector>
#include <string>

#define INF INT_MAX/2

using namespace std;

class Aresta
{

public:
    int valor;
    int no;

    Aresta(int a, int b)
    {
        valor = a;
        no = b;
    }
    bool operator>(const Aresta& b)const
    {
        return valor > b.valor;
    }

};


void dijkstra(vector< vector<Aresta> >& grafo, int ini, int fim)
{
    vector<int> dist(grafo.size(), INF);
    vector<int> s(grafo.size(), ini);//vetor S q pega o caminho
    dist[ini] = 0;
  
    priority_queue<Aresta, vector<Aresta>, greater<Aresta> > pq;
    
    pq.push(Aresta(0, ini));

    while(!pq.empty())
    {
        
        Aresta x = pq.top();
        pq.pop();
        
        if(dist[x.no] == x.valor)
        {
            for(int i=0; i< grafo[x.no].size(); i++)
            {
                Aresta y = grafo[x.no][i];
                if(dist[x.no] + y.valor < dist[y.no])
                {
                    if(x.no!=ini) s[y.no] = x.no;//pegando o caminho
                    dist[y.no] = dist[x.no] + y.valor;
                    pq.push(Aresta(dist[y.no], y.no));
                    
                }
                
            }

        }
    }
    
   
    cout<<endl<<ini<<"-"; 
    for(int i =0; i< s.size();i++){
        if(s[i]!=ini && s[i]!=fim)
            cout<<s[i]<<"-";
    }
    cout<<fim<<endl;
    
   

}

int main()
{
    int n, m, ini, fim, peso, consultas;
    cout<<"Digite o numero de nos e o de arestas do grafo: "<<endl;
    cin>>n>>m; /* Numero de vertices e arestas */
    cout<<"\nn: "<<n<<", m: "<<m<<endl;

    vector< vector<Aresta> > grafo(n);
    int x, y;
    
    for(int i = 0; i < m; i++) /* Leitura do grafo */
    {
        cout<<"Digite as extremidades do arco e seu respectivo peso: ";
        cin>>x>>y>>peso;
        cout<<endl;
        
        // Aresta ar(peso, y-1);
        // grafo[x-1].push_back(ar);
        Aresta ar(peso, y);
        grafo[x].push_back(ar);
    }

    cout<<"Digite a quantidade de consultas desejadas: ";
    cin>>consultas; /* Consulta de caminho minimo */
    cout<<endl;
    for(int i = 0; i < consultas; i++){
      cin>>ini>>fim;
    //   cout<<"Distancia entre "<<ini<<" e "<<fim<<" : "<<dijkstra(grafo, ini-1, fim-1)<<endl;
      cout<<"Caminho entre "<<ini<<" e "<<fim<<" : ";
      dijkstra(grafo, ini, fim);
      cout<<endl;
    }

    cout<<endl;


    return 0;
}
