#include <iostream>
#include <vector>
#include <map>

using namespace std;

class Node{
	public:
		int key;
		Node *left;
		Node *right;	
		Node(int key, Node *left, Node *right){
			this->key = key;
			this->left = left;
			this->right = right;
		}	
};

Node *root = NULL;

void insert(int numb, Node *n){
	if(n==NULL){//significa que vai ser a raiz
		root = new Node(numb,NULL,NULL);
		return;
	}
	else{
		if(numb > n->key){
			if(n->right==NULL){
				n->right = new Node(numb,NULL,NULL);
			}
			else 
				insert(numb,n->right);
			return;
		}
		else if(numb < n->key){
			if(n->left==NULL)
				n->left = new Node(numb,NULL,NULL);
			else 
				insert(numb,n->left);
			return;
		}
		
		cout<<"Nao eh possivel inserir: '"<<numb<<" porque ja esta inserido!"<<endl;
	
	}

}
//root, left, right
void PreOrdem(Node *No){
  if(No == NULL)
    return;
  else{
    cout<<No->key<<" ";
    PreOrdem(No->left);
    PreOrdem(No->right);
  }  
}

//left, root, right
void EmOrdem(Node *No){
  if(No == NULL)
    return;
  else{
    EmOrdem(No->left);
    cout<<No->key<<" ";
    EmOrdem(No->right);
  }
}

//left, right, root
void PosOrdem(Node *No){
  if(No == NULL)
    return;
  else{
    PosOrdem(No->left);
    PosOrdem(No->right);
    cout<<No->key<<" ";
  }
}

void busca(Node *No, int numb){
  if(No == NULL){
    cout<<"O elemento "<<numb<<" nao esta na arvore.";
    return;
  }
  else{
    if(numb > No->key)
      busca(No->right,numb);
    else if (numb < No->key)
      busca(No->left,numb);
    else
      cout<<"O elemento "<<numb<<" esta na arvore.";
  }
  
}

int main(){
  //9, 12, 10, 5, 8, 2, 14
  int num = 0, op, op2;
  
  cout<<"Caso nao deseje inserir mais nos digite 0 \nInsira a raiz:"<<endl;
  
  cin>>num;
  
  if(num == 0)//caso nao sejam inseridos elementos na arvore
	return 0;
  
  while(num != 0){
    insert(num, root);
    cout<<"Insira o proximo elemento: "<<endl;
    cin>>num;
  }
  cout<<"Opcoes: 1 - Impressoes, 2 - Busca, 0 - Terminar a execucao"<<endl;
  while(cin>>op){
    switch(op){
      case 0:
        return 0;
      case 1:
        cout<<"Pre-Ordem: 1, Ordem Simetrica: 2, Pos-Ordem: 3 "<<endl;
        cin>>op2;
		cout<<"\n";
        switch(op2){
          case 1:
            PreOrdem(root);
            break;
          
          case 2:
            EmOrdem(root);
            break;
          case 3:
            PosOrdem(root);
            break;
          default:
            cout<<"Opcao invalida!"<<endl;
			break;
        }
		break;
        
      case 2:
        cout<<"Insira o elemento a ser buscado: "<<endl;
        cin>>num;
		busca(root, num);
        break;
      default: 
        cout<<"Opcao valida!"<<endl;
		break;
    }
	
    cout<<"\n\nOpcoes: 1 - Impressoes, 2 - Busca, 0 - Terminar a execucao"<<endl;
  }

}