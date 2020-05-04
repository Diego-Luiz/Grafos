#include <iostream>

using namespace std;

int main(){
   int TAM = 0;
   cout<<"Digite o numero de nos: ";
   cin>>TAM;
   int matriz[TAM][TAM];
   cout<<"Digite a matriz: "<<endl;
   for(int i=0;i<TAM;i++){
      for(int j=0;j<TAM;j++){
         cin>>matriz[i][j];
      }
   }
   cout<<"Printando a matriz recebida: "<<endl;
   for(int i=0;i<TAM;i++){
      for(int j=0;j<TAM;j++){
         cout<<matriz[i][j]<<" ";
      }
      cout<<endl;
   }
   /*
      --> Algoritmo de Warshall
      aux = linha com que a operação de adição booleana será realizada 
      temp = coluna sendo analisada (se tem 0 ou 1)
      i = linha que esta sendo percorrida
      j = coluna que esta sendo percorrida
   */
   int temp = 0;
   for(int aux=0;aux<TAM;aux++){
      for(int i=0;i<TAM;i++){
         if(matriz[i][temp]){
            for(int j=0;j<TAM;j++){
               if(matriz[i][j] || matriz[aux][j])
                  matriz[i][j] = 1;
               else
                  matriz[i][j] = 0;
            }
         }
      }
      temp++;
   }

   cout<<"Printando a matriz apos o algoritmo de Warshall: "<<endl;
   for(int i=0;i<TAM;i++){
      for(int j=0;j<TAM;j++){
         cout<<matriz[i][j]<<" ";
      }
      cout<<endl;
   }

   return 0;
}