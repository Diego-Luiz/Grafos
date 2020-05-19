#include<iostream>

using namespace std;

int main(){
	int tamanho, elemento;
	
	cout<<"Digite o numero de nos: ";
	cin>>tamanho;
	
	int matriz[tamanho][tamanho];
	
	cout<<"Digite a matriz: "<<endl;
	//LENDO A MATRIZ DE ADJACENCIA
	for(int i=0; i<tamanho;i++){
		for(int j=0; j<tamanho; j++){
			cin>>elemento;
			matriz[i][j] = elemento;
		}
	}
	
	cout<<"Matriz recebida: "<<endl;
	for(int i=0; i<tamanho;i++){
		for(int j=0; j<tamanho; j++){
			cout<<matriz[i][j]<<" ";
		}
		cout<<"\n";
	}
	
	//--------Caminho de Euler--------//
	int total, grau, i, j;
	total=0;
	i=0;
	while(total <=2 && i< tamanho){
		grau = 0;
		for(j=0; j<tamanho; j++)
			grau = grau + matriz[i][j];
		
		if(grau % 2)
			total = total + 1;
		
		i++;
	}
	
	if(total == 1 || total > 2)
		cout<<"\nNao existe um caminho de Euler"<<endl;
	else
		cout<<"\nExiste um caminho de Euler"<<endl;
	
	return 0;
}