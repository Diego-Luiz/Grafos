#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Node{
  public:
    int key;
    vector<Node*> *filhos;  
    
    Node(int key, vector<Node*> *f){
      this->key = key;
      this->filhos = f;
    }
};

Node *root = NULL;
bool flag = false;

void busca(Node *no, Node *pai, int chave){

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
            busca( (*(no->filhos))[i], pai, chave );
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
    vector<Node*> *filhos = new vector<Node*>;
    string P = ""; //pai deste no (N)
    int F = 0; //filhos
    cout<<"Digite a chave: "<<endl;
    cin>>N;
    //--------------
    if(N==-100)
      break;
    
    cout<<"Digite o pai do no "<<endl;
    cin>>P;
    cout<<"Digite a qtd de filhos: "<<endl;
    cin>>F;
    
   while(F--){
      int no = 0;
      cin>>no;
      Node *x = new Node(no,NULL);
      filhos->push_back(x);
    }

    Node *pai = new Node(N, filhos);
    
    if(P == "raiz"){
      root = pai;
    }
    else{ //se nao for o 1º elemento
      int aux = stoi(P); //converte para inteiro a string referente ao pai
      busca(root,pai,aux);
      flag = false;
    }

  }
  
  pos_ordem(root);

	return 0;
}
