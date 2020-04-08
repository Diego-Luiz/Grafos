#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <map>

using namespace std;

int main(){
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
        c = getc(arq);
        cout<<c<<" ";
        if(c!=' ')
            frequencia[c] += 1;//MAP
    }while(c!=EOF);
    
    //MULTIMAP
    for(itfreq=frequencia.begin();itfreq!=frequencia.end();itfreq++){
        freq_ordenado.insert( pair<int,char>(itfreq->second,itfreq->first) );
    }

    for(itord = freq_ordenado.begin(); itord!=freq_ordenado.end();itord++){
        cout<<itord->first<<" : "<<itord->second<<endl;
    }
   return 0;
}
