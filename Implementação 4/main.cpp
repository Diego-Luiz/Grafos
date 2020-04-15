#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <map>
#include<string.h>
#include<vector>

using namespace std;

int contador=0;//contador para verificar a ordem dos elementos e elementos repetidos

multimap<int, int> mapa_de_verificacao;//multimap para verificar a ordem de elementos repetidos

class caracter_num {
	public :
		char c;
		int freq;
		caracter_num(char c='c', int freq=0){
			this->c = c;
			this->freq = freq;
		}
};

vector <caracter_num> lista;

void insere(char caracter, int num){
	caracter_num novo(caracter, num);
	contador += 1;
	mapa_de_verificacao.insert(pair<int, int>(num, contador));
	
	
	if(lista.size() == 0){
		lista.push_back(novo);
		return;
	}
	for(vector<caracter_num>:: iterator it=lista.begin(); it!=lista.end(); it++){
		if(num < it->freq){
			lista.insert(it, novo);
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


multimap <int, No*> pseudo_arvore;
multimap <int, No*> pseudo_arvore_copia;

No *raiz = NULL;


void gerar_nos(){
	
	while(lista.size() > 1){
		vector<caracter_num>:: iterator it = lista.begin();
		int aux = 0;
		if(it->c != '|'){
			
			it++;
			if(it->c != '|'){
				it--;
				aux = it->freq;
			No *esquerdo = new No(it->c, it->freq, NULL, NULL);
				
			lista.erase(it);
			
			it = lista.begin();
				No *direito = new No(it->c, it->freq, NULL, NULL);
				aux += it->freq;
				No *Pai = new No('|', aux, esquerdo, direito);
				
				lista.erase(it);
				
				pseudo_arvore.insert(pair<int, No*>(aux, Pai));
				
				pseudo_arvore_copia.insert(pair<int, No*>(aux, Pai));
				
				insere('|', aux);
				
			}else{
				it--;
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
					
					multimap<int, No*>::iterator mult_it = pseudo_arvore_copia.find(it->freq);
					
					if(mult_it != pseudo_arvore.end()){//-----------
						Pai = new No('|', aux, esquerda, mult_it->second);
						pseudo_arvore_copia.erase(mult_it);
					}
					
					lista.erase(it);
					
					insere('|', aux);
					
					pseudo_arvore.insert(pair<int, No*>(aux, Pai));
					pseudo_arvore_copia.insert(pair<int, No*>(aux, Pai));
					
				}
			}
			}
		}
		
		else{
			
				if(it->c == '|'){//se o 1 for um no
					No *esquerdo;
					No *direito;
					aux = it->freq;
					
					multimap<int, No*>::iterator mult_it = pseudo_arvore_copia.find(it->freq);
					
					if(mult_it != pseudo_arvore.end()){//---------
						esquerdo = mult_it->second;
						pseudo_arvore_copia.erase(mult_it);
					}
					
					lista.erase(it);
					
					it = lista.begin();
					
					if(it->c != '|'){//o 1 eh no e o segundo nao eh no
						direito = new No(it->c, it->freq, NULL, NULL);
						
					}else{//os dois sao nos
						multimap<int, No*>::iterator mult_it = pseudo_arvore_copia.find(it->freq);
						if(mult_it != pseudo_arvore.end()){//------------
							direito = mult_it->second;
							pseudo_arvore_copia.erase(mult_it);
						}
					}
					
					aux += it->freq;
					
					No *Pai = new No('|', aux, esquerdo, direito);
					
					lista.erase(it);
					
					insere('|', aux);
					
					pseudo_arvore.insert(pair<int, No*>(aux, Pai));
					pseudo_arvore_copia.insert(pair<int, No*>(aux, Pai));
					
				}
			
		}
			
	}
	
}


bool achou = false;

string criar_codigo(No *no, char caracter, string str, char direcao){
	
	if(no == NULL){
		return str;
	}
	else{
		if(no->chave.c == caracter){//achou
			achou = true;
			return str + direcao;	
		}
		str += criar_codigo(no->FE, caracter, str, '0');
		if(achou)
			return str + direcao;
		else{
			str += criar_codigo(no->FD, caracter, str, '1');
			if(achou)
				return str + direcao;
			else
				return str;
		}
	}
}

int main(){
	
    map<char,int> frequencia;
    map<char,int>::iterator itfreq;
	map<char, string> tabeladecodigos; 
	map<string, char> tabeladecodigos_invertida;
	map<string, char>:: iterator ittabela;
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
    
	fclose(arq);
	
    //MULTIMAP
    for(itfreq=frequencia.begin();itfreq!=frequencia.end();itfreq++){
        freq_ordenado.insert( pair<int,char>(itfreq->second,itfreq->first) );
    }
	
	
    for(itord = freq_ordenado.begin(); itord!=freq_ordenado.end();itord++){
        cout<<itord->first<<" : "<<itord->second<<endl;
    }
	
	//criando arquivo para gravacao
	arq = fopen("FREQUENCIA.txt", "wt");
	
	for(itfreq=frequencia.begin();itfreq!=frequencia.end();itfreq++){
		
		string str;
		str.push_back(itfreq->first);
		
		if(str == "\n")
			str = "newline";
		str += "-" + to_string(itfreq->second) + "\n";
		
		fputs(str.c_str(), arq);
	}
	
	fclose(arq);
	
	//---------
	for(itfreq=frequencia.begin(); itfreq != frequencia.end(); itfreq++){//populando a lista
		insere(itfreq->first, itfreq->second);
	}
	
	for(int i=0; i<lista.size(); i++){
		cout<<"lista"<<endl;
		cout<<lista[i].c<<" "<<lista[i].freq<<endl;
	}
	
	gerar_nos();
		
	
	multimap<int, No*>:: iterator it = pseudo_arvore.begin();
	
	
	for(it; it!= pseudo_arvore.end(); it++){
		cout<<it->first<<" : esquerda: "<<it->second->FE->chave.c<<", "<<it->second->FE->chave.freq<<" : direita: "<<it->second->FD->chave.c<<", "<<it->second->FD->chave.freq<<endl;
	}
	
	
	it = pseudo_arvore.end();//definindo a raiz da arvore
	it--;
	raiz = it->second;
	
	
	arq = fopen("TABELADECODIGOS.txt", "wt");
	for(itfreq=frequencia.begin(); itfreq != frequencia.end(); itfreq++){
		
		string codigo = criar_codigo(raiz, itfreq->first, "", 'n');
		codigo = codigo.erase(codigo.size()-1);//tirando o n do final da string
		cout<<codigo<<endl;
		string invertida="";
		
		for(string::reverse_iterator rit=codigo.rbegin(); rit!=codigo.rend(); ++rit){
			invertida += *rit;
		}
		
		codigo = itfreq->first;
		codigo +=  "-";
		codigo += invertida;
		codigo += "\n";
		
		fputs(codigo.c_str(), arq);
		
		achou = false;
		
		tabeladecodigos[itfreq->first] = invertida;//guardando representacao do codigo dos caracterem em um mapa
		tabeladecodigos_invertida[invertida] = itfreq->first; //guardando a tabeladecodigos invertida
	}
	
	fclose(arq);
	
	//CODIFICANDO O ARQUIVO
	arq = fopen("Arq.txt", "rt");
	
	FILE *novo_arq = fopen("CODIFICADO.txt", "wt");
	
	do{
        c = fgetc(arq);
        
		if(c != EOF)
			fputs(tabeladecodigos[c].c_str(), novo_arq);
		else
			break;
    }while(true);
	
	fclose(arq);
	fclose(novo_arq);
	
	//DECODIFICANDO O ARQUIVO
	
	arq = fopen("CODIFICADO.txt", "rt");
	FILE *decodificado = fopen("DECODIFICADO.txt", "wt");
	

	string deco="";
	cout<<"antes do while"<<endl;
	do{
        c = fgetc(arq);
		
        deco += c;
		cout<<"deco: "<<deco<<endl;
		if(c != EOF){
			
			ittabela = tabeladecodigos_invertida.find(deco);
			
			if(ittabela != tabeladecodigos_invertida.end()){
				cout<<ittabela->second<<endl;
				fputc(ittabela->second, decodificado);
				deco = "";
			}
		}
		else
			break;
    }while(true);
	
	fclose(decodificado);
	
   return 0;
}
