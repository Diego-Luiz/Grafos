#include <iostream>
#include <deque>

using namespace std;

class par{
	public:
		int x;
		int y;
		par(int x, int y){
			this->x = x;
			this->y = y;
		}
};

deque<deque<par>> adjacencias;

deque<par> nova_lista(int a, int b){
	deque<par> temp1 = adjacencias[a];
	deque<par> temp2 = adjacencias[b];
	deque<par> res;
	
	for(int i=0; i<temp1.size(); i++){
		for(int j=0; j<temp2.size(); j++){
			if(temp1[i].y == temp2[j].x){
				if(temp1[i].x != temp2[j].x || temp1[i].y != temp2[j].y){
					par novo(temp1[i].x, temp2[j].y);
					res.push_back(novo);
				}
			}
		}
	}
	
	return res;
}

int main(){
	int tamanho, elemento;
	deque<par> lista;
	
	cout<<"Digite o numero de nos: ";
	cin>>tamanho;
	
	int matriz[tamanho][tamanho];
	
	cout<<"Digite a matriz: "<<endl;
	//LENDO A MATRIZ DE ADJACENCIA
	for(int i=0; i<tamanho;i++){
		for(int j=0; j<tamanho; j++){
			cin>>elemento;
			matriz[i][j] = elemento;
			if(elemento == 1){
				par temp(i+1, j+1);
				lista.push_back(temp);
			}
		}
	}
	
	cout<<"Printando a matriz recebida: "<<endl;
	for(int i=0; i<tamanho;i++){
		for(int j=0; j<tamanho; j++){
			cout<<matriz[i][j]<<" ";
		}
		cout<<"\n";
	}
	
	adjacencias.push_back(lista);
	lista.clear();
	
	while((adjacencias.size() + 1) <= tamanho){
		adjacencias.push_back(nova_lista(0, (adjacencias.size() - 1)));
		
		for(int i=0; i<adjacencias[adjacencias.size()-1].size(); i++){
			if(matriz[adjacencias[adjacencias.size()-1][i].x-1][adjacencias[adjacencias.size()-1][i].y-1] == 0)
				matriz[adjacencias[adjacencias.size()-1][i].x-1][adjacencias[adjacencias.size()-1][i].y-1] = 1;
		}
		
	}
	
	cout<<"\nMatriz de acessibilidade R: "<<endl;
	
	for(int i=0; i<tamanho; i++){
		for(int j=0; j<tamanho; j++){
			cout<<matriz[i][j]<<" ";
		}
		cout<<"\n";
	}
	
	return 0;
}


