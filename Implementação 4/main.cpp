#include <iostream>
#include <string>
#include <map>
#include <vector>

using namespace std;

/*------------------------------Classes----------------------------*/

//Classe que representa cada item (caracter e frequência)
class caracter_num {
	public :
		char c;
		int freq;
		caracter_num(char c='c', int freq=0){
			this->c = c;
			this->freq = freq;
		}
};

//Classe que representa os nós da "árvore"
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
/*-----------------------------------------------------------------*/


/*--------------------------------- Estrutura de dados usadas para conseguir realizar o programa -----------------------------*/
//Lista dos caracteres e suas frequências
vector <caracter_num> lista;
//Árvore de Ruffman
multimap <int, No*> pseudo_arvore;
//Árvore auxiliar para a construção da árvore de Ruffman
multimap <int, No*> pseudo_arvore_copia;
//Raiz da árvore de Ruffman (pseudo_arvore)
No *raiz = NULL;
//Variavel booleana usada para ajudar na criação da representação binária dos caracteres
bool achou = false;
/*-----------------------------------------------------------------------------------------------------------------------------*/

/*---------------------------------------------------------Funções-------------------------------------------------------------*/
//Função que insere os caracteres e suas frequências na lista de forma ordenada
void insere(char caracter, int num){ 
	//criando o item a ser inserido
	caracter_num novo(caracter, num);
	//insere no começo
	if(lista.size() == 0){
		lista.push_back(novo);
		return;
	}
	//insere de forma ordenada 
	for(vector<caracter_num>:: iterator it=lista.begin(); it!=lista.end(); it++){
		if(num < it->freq){
			lista.insert(it, novo);
			return;
		}
	}
	//insere no final
	lista.push_back(novo); 
	
}

//Função que gera os nós da árvore
void gerar_nos(){
	
	while(lista.size() > 1){ //Enquanto tiver elemento na lista para inserir na árvore
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
				
			}
			else{
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
				}
				else{//os dois sao nos
					multimap<int, No*>::iterator mult_it = pseudo_arvore_copia.find(it->freq);
					if(mult_it != pseudo_arvore.end()){//se achou o elemento
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


//Função para criar a representação binária dos caracteres
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
/*----------------------------------------------------------------------------------------------------------------------------*/


int main(){
	
    map<char,int> frequencia;
    map<char,int>::iterator itfreq;
	map<char, string> tabeladecodigos; 
	map<string, char> tabeladecodigos_invertida;
	map<string, char>:: iterator ittabela;
    multimap<int,char> freq_ordenado;
    multimap<int,char>::iterator itord;
    FILE *arq;
    string name_arch="";
	cout<<"Digite o nome do arquivo a ser manipulado(sem a extensao .txt): "<<endl;
	getline(cin,name_arch);
	name_arch+=".txt";
	cout<<"Nome do arquivo: "<<name_arch<<endl;
    //---ARQUIVO
    arq = fopen(name_arch.c_str(), "rt");
    if(arq ==NULL){
        cout<<"Erro! Arquivo nao encontrado!"<<endl;
		exit(1);
	}
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
	
	cout<<"\nFrequencia do caracter : Caracter"<<endl;
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
		if(str == " ")
			str= "space";
		str += "-" + to_string(itfreq->second) + "\n";
		
		fputs(str.c_str(), arq);
	}
	
	fclose(arq);
	
	//Preenchendo a lista, para conseguir construir a árvore 
	for(itfreq=frequencia.begin(); itfreq != frequencia.end(); itfreq++){
		insere(itfreq->first, itfreq->second);
	}
	
	//Gerando os nós da árvore
	gerar_nos();
		
	multimap<int, No*>:: iterator it = pseudo_arvore.begin();
	
	cout<<"\nArvore gerada: "<<endl;
	for(it; it!= pseudo_arvore.end(); it++){
		cout<<"No: "<<it->first<<" : Esquerda: "<<it->second->FE->chave.c<<", "<<it->second->FE->chave.freq<<" : Direita: "<<it->second->FD->chave.c<<", "<<it->second->FD->chave.freq<<endl;
	}
	
	/*--- Definindo a raiz da arvore*/
	it = pseudo_arvore.end();
	it--;
	raiz = it->second;
	/*------------------------------*/
	
	arq = fopen("TABELADECODIGOS.txt", "wt");
	for(itfreq=frequencia.begin(); itfreq != frequencia.end(); itfreq++){
		
		string codigo = criar_codigo(raiz, itfreq->first, "", 'n');
		codigo = codigo.erase(codigo.size()-1);//tirando o n do final da string
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
	do{
        c = fgetc(arq);
		
        deco += c;
		if(c != EOF){
			
			ittabela = tabeladecodigos_invertida.find(deco);
			
			if(ittabela != tabeladecodigos_invertida.end()){
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
