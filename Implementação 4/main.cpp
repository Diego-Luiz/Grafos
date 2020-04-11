#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <map>
#include<string.h>
#include<vector>

using namespace std;

class caracter_num {
	public :
		char c;
		int freq;
		bool no;
		caracter_num(char c='c', int freq=0, bool no=false){
			this->c = c;
			this->freq = freq;
			this->no = no;
		}
		void setNo(){
			no = true;
		}
};

vector <caracter_num> lista;

void insere(char caracter, int num){
	caracter_num novo(caracter, num);
	
	if(lista.size() == 0){
		lista.push_back(novo);
		return;
	}
	for(vector<caracter_num>:: iterator it=lista.begin(); it!=lista.end(); it++){
		if(num < it->freq){
			lista.insert(lista.begin(), novo);
			return;
		}
	}
	
	lista.push_back(novo);
	
}


class No {
	public:
		caracter_num chave;
		No *FE;
		No *FD;
		
		No(char c, int num, No *FE=NULL, No *FD=NULL){
			chave.c = c;
			chave.freq = num;
			
			this->FE = FE;
			this->FD = FD;
		}
	
	
};

No *raiz = NULL;

/*
void insere_arvore(No *novo, caracter_num novo_caracter){
	
	if(novo == NULL)
		No *novo_no = new No(novo_caracter.c, novo_caracter.freq, NULL, NULL);
	else{
		if(){
			
		}
	}
}
*/

multimap <int, No*> pseudo_arvore;





void gerar_nos(){
	
	while(lista.size() > 0){
		cout<<"tam da lista: "<<lista.size()<<endl;
		vector<caracter_num>:: iterator it = lista.begin();
		int aux = 0;
		if(it->c != '|'){
			aux = it->freq;
			No *esquerdo = new No(it->c, it->freq, NULL, NULL);
				
			lista.erase(it);
			
			it = lista.begin();
			
			if(it->c != '|'){
				
				No *direito = new No(it->c, it->freq, NULL, NULL);
				aux += it->freq;
				No *Pai = new No('|', aux, esquerdo, direito);
				
				lista.erase(it);
				
				pseudo_arvore.insert(pair<int, No*>(aux, Pai));
				
				insere('|', aux);
				
			}
		}
		
		else{
			char c_anterior;
			int freq_anterior;
			if(it->c != '|'){//se o 1 nao for no
				aux = it->freq;
				c_anterior = it->c;
				freq_anterior = it->freq;
				
				lista.erase(it);
				
				it = lista.begin();
				
				aux += it->freq;
				if(it->c == '|'){//se o 2 for um no
					
					No *Pai;
					
					No *esquerda = new No(c_anterior, freq_anterior, NULL, NULL); 
					
					multimap<int, No*>::iterator mult_it = pseudo_arvore.find(it->freq);
					
					if(mult_it != pseudo_arvore.end()){//nao pode ter duas somas iguais
						Pai = new No('|', aux, esquerda, mult_it->second);
					}
					
					lista.erase(it);
					
					insere('|', aux);
						
					pseudo_arvore.insert(pair<int, No*>(aux, Pai));
					
				}
			}else{
				if(it->c == '|'){//se o 1 for um no
					No *esquerdo;
					No *direito;
					aux = it->freq;
					
					multimap<int, No*>::iterator mult_it = pseudo_arvore.find(it->freq);
					
					if(mult_it != pseudo_arvore.end()){//nao pode ter duas somas iguais
						esquerdo = mult_it->second;
					}
					
					lista.erase(it);
					
					it = lista.begin();
					
					if(it->c != '|'){//o 1 eh no e o segundo nao eh no
						direito = new No('|', it->freq, NULL, NULL);
						
					}else{//os dois sao nos
						mult_it = pseudo_arvore.find(it->freq);
						if(mult_it != pseudo_arvore.end()){//nao pode ter duas somas iguais
							direito = mult_it->second;
						}
					}
					
					aux += it->freq;
					
					No *Pai = new No('|', aux, esquerdo, direito);
					
					lista.erase(it);
					
					insere('|', aux);
					
					pseudo_arvore.insert(pair<int, No*>(aux, Pai));
				}
			}
		}
			
	}
	
}

int main(){
	/*
    map<char,int> frequencia;
    map<char,int>::iterator itfreq;
    multimap<int,char> freq_ordenado;
    multimap<int,char>::iterator itord;
    FILE *arq;
    

    //---ARQUIVO
    arq = fopen("Arq.txt", "rt");
    if(arq ==NULL)
        cout<<"Erro! Arquivo nao encontrado!"<<endl;
  
    char c;
    do{
        c = fgetc(arq);
        
		if(c != EOF)
			frequencia[c] += 1;//MAP
		else
			break;
    }while(true);
    
    //MULTIMAP
    for(itfreq=frequencia.begin();itfreq!=frequencia.end();itfreq++){
        freq_ordenado.insert( pair<int,char>(itfreq->second,itfreq->first) );
    }
	
	
    for(itord = freq_ordenado.begin(); itord!=freq_ordenado.end();itord++){
        cout<<itord->first<<" : "<<itord->second<<endl;
    }
	
	//criando arquivo para gravacao
	arq = fopen("Frequencia.txt", "wt");
	
	for(itfreq=frequencia.begin();itfreq!=frequencia.end();itfreq++){
		
		string str;
		str.push_back(itfreq->first);
		
		if(str == "\n")
			str = "newline";
		str += "-" + to_string(itfreq->second) + "\n";
		
		fputs(str.c_str(), arq);
		
		cout<<str<<endl;
	}
	
	*/
	
	
	insere('f', 5);
	insere('e', 9);
	insere('c', 12);
	insere('b', 13);
	insere('d', 16);
	insere('a', 45);
	
	
	for(int i=0; i<lista.size(); i++){
		cout<<lista[i].c<<" "<<lista[i].freq<<endl;
	}
	
	gerar_nos();
	
	//multimap<int, No*>:: iterator iterador = pseudo_arvore.begin();
	
	
	
	multimap<int, No*>:: iterator it = pseudo_arvore.begin();
	
	cout<<"size da arvore: "<<pseudo_arvore.size()<<endl;
	
	for(it; it!= pseudo_arvore.end(); it++){
		cout<<it->first<<endl;
	}
	
	
	
   return 0;
}
