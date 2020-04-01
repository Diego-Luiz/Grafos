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
		
		cout<<"It's not possible to insert: '"<<numb<<"' because it's already inserted!"<<endl;
	
	}

}

int main(){
	insert(10,root);
	insert(5,root);
	insert(30,root);
	insert(25,root);
	insert(6,root);

	cout<<root->key<<" "<<root->left->key<<" "<<root->right->key<<" "<<root->right->left->key<<" "<<root->left->right->key<<"\n";
	
return 0;
}