#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 5000
 
typedef struct
{
    char origem[10];
    char X;
    char Destino[10];
    char trocaX;
    char Sentido;
}Transicao;
 
char estados[50][5],estado_inicial[5],estados_finais[50][5],alfabeto[10],alfabeto_fita[10];
int cont_transicoes,cont_estados_finais,cont_comp,cont_estados,cont_alfa_fita,cont_alf;
Transicao vet_Tran[50];
 
void ler_arquivo(FILE *arq)
{
        cont_transicoes = 0;
        cont_estados_finais = 0;
        cont_estados = 0;
        cont_alfa_fita = 0;
        cont_alf = 0;
        char aux1[5];
        char aux;       
        char linha[100];
        int k=0;
         
        fscanf(arq,"%c\n",&aux);
        fgets(linha,100,arq);
        strcpy(estados[k],(char*)strtok(linha, "{(,"));
        do{
            k++;
            strcpy(estados[k], (char*)strtok(NULL, "{,}"));
        }while(strcmp(estados[k],"\n") != 0);
        cont_estados = k;
         
        k=0;
        int c=0;
        fscanf(arq,"%c",&aux);
        do{
            if(aux != ',' && aux!='{' && aux != '}' && aux !=' ' && aux != '\t'){
                alfabeto[c]=aux;
                cont_alf++;
                c++;
            }
            k++;
            fscanf(arq,"%c",&aux);
        }while(aux != '}');
         
         
        k=0;
        c=0;
        fscanf(arq,"%c",&aux);
        do{
            if(aux != ',' && aux!='{' && aux != '}' && aux !=' ' && aux != '\t'){
                alfabeto_fita[c]=aux;
                cont_alfa_fita++;
                c++;
            }
            k++;
            fscanf(arq,"%c",&aux);
        }while(aux != '}');
        cont_alfa_fita--;
         
        fscanf(arq,"%c\n",&aux);
        fscanf(arq,"%c\n",&aux);
        k=0;
         
        while(aux!='}'){        
             
            cont_transicoes++;
            fgets(linha,100,arq);
            strcpy(aux1,(char*)strtok(linha, "(,"));
            strcpy(vet_Tran[k].origem,aux1);
            strcpy(aux1,(char*)strtok(NULL, ")"));
            vet_Tran[k].X = aux1[0];
            strcpy(aux1,(char*)strtok(NULL, "->(,"));
            strcpy(vet_Tran[k].Destino,aux1);
            strcpy(aux1, (char*)strtok(NULL, ","));
            vet_Tran[k].trocaX = aux1[0];
            strcpy(aux1, (char*)strtok(NULL, ")"));
            vet_Tran[k].Sentido = aux1[0];              
            k++;
             
             
            fscanf(arq,"%c\n",&aux);
            fscanf(arq,"%c\n",&aux);
             
        }
         
    fscanf(arq,"%c\n",&aux);
    fgets(linha,100,arq);
    strcpy(estado_inicial, (char*)strtok(linha, ","));
     
    k = 0;
    fgets(linha,100,arq);
    strcpy(estados_finais[k], (char*)strtok(linha, "{,}"));
    do{
        k++;
        strcpy(estados_finais[k], (char*)strtok(NULL, "{,}"));
    }while(strcmp(estados_finais[k],"\n") != 0);
    cont_estados_finais = k;
     
}
int testa_palavra(char palavra[]){
    int i,j,cont;
    for(i=1;i<strlen(palavra)-1;i++){
        cont=0;
        for(j=0;j<cont_alf;j++){
            if(palavra[i] != alfabeto[j]){
                 cont++;                
            }
        }
        if(cont == cont_alf){
            return 1;
        }
    }
    return 0;
}
 
int main (int argc, char** argv)
{
    FILE *arq ;
    arq=fopen(argv[1],"r");
    ler_arquivo(arq);
    fclose(arq);
     
    cont_comp = 0;
    char palavra[100],estado_atual[5],palavra_aux[100],estado_aux[5];
    char* Aux;
    Aux = malloc(100*sizeof(char));
    strcpy(palavra,"B");
    strcat(palavra,argv[2]);
    strcat(palavra,"B");
     
    strcpy(estado_atual,"{");
    strcat(estado_atual,estado_inicial);
    strcat(estado_atual,"}");
    strcpy(estado_aux,estado_inicial);
     
    strcpy(Aux,estado_atual);
    strcat(Aux,palavra);
     
    strcpy(palavra_aux,Aux);
    free(Aux);
     
    FILE* saida;
    saida = fopen(argv[3],"w");
     
    int i=0;
    int parou = 0;
    if(testa_palavra(palavra) == 1){
        fprintf(saida,"Palavra fora do alfabeto.\n");
        fclose(saida);
        return 0;
    }
    do{
        int k=0;
        fprintf(saida,"%s\n",palavra_aux);
        while(k < cont_transicoes){
            if(palavra[i] == vet_Tran[k].X && strcmp(estado_aux,vet_Tran[k].origem)==0)
                break;
            k++;
        }
        if(k == cont_transicoes){
            int w=0;
            while(w < cont_estados_finais){
                if((strcmp(estado_aux,estados_finais[w])==0)){
                    parou = 1;
                    fprintf(saida,"aceita\n");
                }
                w++;
            }
            if(parou == 0){
                fprintf(saida,"rejeita\n");
                parou = 1;
            }
        }
        else{
            strcpy(estado_atual,"{");
            strcat(estado_atual,vet_Tran[k].Destino);
            strcat(estado_atual,"}");
            strcpy(estado_aux,vet_Tran[k].Destino);
             
            palavra[i] = vet_Tran[k].trocaX;
            if(vet_Tran[k].Sentido == 'D'){
                int j;
                char s[100];
                int c=0;
                for(j=i+1;j<strlen(palavra);j++){
                    s[c] = palavra[j];          
                    c++;        
                }
                s[c] = '\0';
                strncpy(palavra_aux,palavra,i+1);
                palavra_aux[i+1] = '\0';
                strcat(palavra_aux,estado_atual);
                strcat(palavra_aux,s);
                i++;
                 
            }
            else if(vet_Tran[k].Sentido == 'N'){
                int j;
                char s[50];
                int c=0;
                for(j=i;j<strlen(palavra);j++){
                    s[c] = palavra[j];          
                    c++;        
                }
                s[c] = '\0';
                strncpy(palavra_aux,palavra,i);
                palavra_aux[i] = '\0';
                strcat(palavra_aux,estado_atual);
                strcat(palavra_aux,s);
             
            }
            else if(vet_Tran[k].Sentido == 'E'){
                int j;
                char s[50];
                int c=0;
                for(j=i-1;j<strlen(palavra);j++){
                    s[c] = palavra[j];          
                    c++;        
                }
                s[c] = '\0';
                strncpy(palavra_aux,palavra,i-1);
                palavra_aux[i-1] = '\0';
                strcat(palavra_aux,estado_atual);
                strcat(palavra_aux,s);
                i--;
             
            }
        }
        cont_comp++;
        if(cont_comp >= MAX){
            printf("Essa maquina pode ter entrado em loop, deseja continuar? <S/N>\n");
            char op;
            scanf("%c%*c",&op);
            if(op == 'S' || op == 's'){
                cont_comp = 0;
            }
            else{
                parou = 1;
            }
        }
    }while(parou == 0);
    fclose(saida);
     
    return 0;
}
