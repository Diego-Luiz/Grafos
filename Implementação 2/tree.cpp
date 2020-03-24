#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Node{
  public:
    int key;
    vector<Node*> *filhos;  
    
    Node(int key, vector<Node*> *f){
      this->key = key;  //chave 
      this->filhos = f; //lista de nós em relação à aquela chave
    }
};

Node *root = NULL; //raiz da árvore
bool flag = false; //variável usada para inserção

/*  ->Parametros
    no: nó atual que esta sendo usado para as comparações
    pai: nó que deseja ser inserido 
    chave: valor do nó onde o pai deve ser inserido
*/
void adiciona(Node *no, Node *pai, int chave){

  if(no!=NULL){
    if(no->key == chave){
      if(no->filhos == NULL)
        no->filhos = new vector<Node*>;

      no->filhos->push_back(pai);
      flag = true;
    }
    else{

      if(no->filhos != NULL){
        for(int i=0; i<no->filhos->size(); i++){
          if(!flag)
            adiciona( (*(no->filhos))[i], pai, chave );
        }
      }

    }

  }
 
}

void pre_ordem(Node *n){
  if(n!=NULL){
    cout<<n->key<<" ";
    if(n->filhos != NULL){
      for(int i=0; i<n->filhos->size(); i++){
        pre_ordem( (*(n->filhos))[i] );
      }
    }
  }
}

void em_ordem(Node *n){
  if(n!=NULL){
    if(n->filhos != NULL){
      for(int i=0; i<n->filhos->size(); i++){
        em_ordem( (*(n->filhos))[i] );
        if(i==0)
          cout<<n->key<<" ";
      }
    }
    else{
      cout<<n->key<<" ";
    }

  }
}

void pos_ordem(Node *n){
  if(n!=NULL){
    if(n->filhos != NULL){
      for(int i=0; i<n->filhos->size(); i++){
        pos_ordem( (*(n->filhos))[i] );
      }
    }
    cout<<n->key<<" ";
  }
}

int main() {
  int N = 0; //chave
  
  while(true){
    string P = ""; //pai deste no (N)
    int F = 0; //filhos
    
    vector<Node*> *filhos = new vector<Node*>;

    cout<<endl<<"============================================================================"<<endl;
    cout<<"Digite o valor da chave (se quiser nao quiser mais inserir digite -9999): "<<endl;
    cin>>N;
    //--------------
    if(N==-9999)
      break;
    
    cout<<"Digite o Pai do no "<<N<<":(para o primeiro caso digite 'raiz') "<<endl;
    cin>>P;
    cout<<"Digite a quantidade de filhos do no "<<N<<": "<<endl;
    cin>>F;
    
    cout<<"Agora digite os valores das chaves dos nos: ";
    while(F--){
        int no = 0;
        cin>>no;
        Node *x = new Node(no,NULL);
        filhos->push_back(x);
    }
    cout<<endl<<"============================================================================"<<endl;

    Node *pai = new Node(N, filhos);
      
    if(P == "raiz"){
        root = pai;
    }
    else{ //se nao for o 1º elemento
      int aux = stoi(P); //converte para inteiro a string referente ao pai
      adiciona(root,pai,aux);
      flag = false;
    }
    
  }

    
  while(true){
    int op = 0;
    cout<<endl<<"============================================================================"<<endl;
    cout<<"Selecione a opcao de impressao 1(pre ordem), 2(em ordem), 3(pos ordem) ou qualquer outro numero para sair: ";
    cin>>op;
    switch(op){
      case 1:
        pre_ordem(root);
        cout<<endl<<"============================================================================"<<endl;
        break;
      case 2:
        em_ordem(root);
        cout<<endl<<"============================================================================"<<endl;
        break;
      case 3:
        pos_ordem(root);
        cout<<endl<<"============================================================================"<<endl;
        break;
      default:
        return 0;
    }
  }

	return 0;
}
