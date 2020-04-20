#include <iostream>
#include <map>
#include <string>

using namespace std;

int main(){
    map<string, char> tabeladecodigos_invertida;
    map<string, char>::iterator it;
    FILE *aux= fopen("TABELADECODIGOS.txt","rt");
    FILE *decodificado = fopen("DECODIFICADO.txt","wt");
    char c;
    char caracter;
    string codigo="";
    do
    {
        c = fgetc(aux);
        if(c!=EOF){
            caracter = c;
            c = fgetc(aux);//lendo o " - " do arquivo da tabela
            while(true){
                c = fgetc(aux);
                if(c!='\n')
                    codigo += c;
                else
                    break;
            }
            tabeladecodigos_invertida[codigo] = caracter;   
            codigo="";  
        }
        else
            break;
        
    } while (true);
    
    fclose(aux);
    cout<<"printando a tabela a ser gravada no arquivo de decodificacao!"<<endl;

    for(it=tabeladecodigos_invertida.begin();it!=tabeladecodigos_invertida.end();it++){
        cout<<"codigo: "<<it->first<<", caracter: "<<it->second<<endl;
    }

    /*---> Criando o arquivo decodificado ----*/ 
    aux = fopen("CODIFICADO.txt","rt");
    codigo="";
	do{
        c = fgetc(aux);
        codigo += c;
		if(c != EOF){
			
			it = tabeladecodigos_invertida.find(codigo);
			
			if(it != tabeladecodigos_invertida.end()){
				fputc(it->second, decodificado);
				codigo = "";
			}
		}
		else
			break;
    }while(true);
    
    fclose(aux);
    fclose(decodificado);
    return 0;
}
