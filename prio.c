#include <stdio.h>
#include <malloc.h>
#include <stdbool.h>
#include<string.h>
typedef int TIPOCHAVE; 

typedef struct {
    TIPOCHAVE X;
    int Y;
    int Z;
    int K;
    char nome[50];
    int saida;
    int sensor;
} REGISTRO;

typedef struct aux {
    REGISTRO reg;
    struct aux* prox;
} ELEMENTO, * PONT;

typedef struct {
    PONT inicio;
    PONT fim;
} FILA;

void inicializarFila(FILA* f) {
    f->inicio = NULL;
    f->fim = NULL;
}

int tamanho(FILA* f) {
    PONT end = f->inicio;
    int tam = 0;
    while (end != NULL) {
        tam++;
        end = end->prox;
    }
    return tam;
}

void fifo(FILA *f, char *ordem[100], int tempo,int N,float turn, float te,int quantum){
    PONT a=f->inicio,b=a->prox,aux=f->inicio,aux=a;
    while(a!=NULL){
        if(a->reg.sensor==0){
            if(a->reg.X<=tempo){
                while(b!=NULL){
                    if(b->reg.X<=tempo&&b->reg.Z<aux->reg.Z){
                        aux=b;
                        break;
                    }
                    a->reg.Y--;
                    
                    b=b->prox;
                }
                aux->reg.sensor=1;
                tempo=tempo+aux->reg.Y;
                strcat(ordem,aux->reg.nome);
                strcat(ordem," ");
                a=f->inicio;
            }else{
                tempo++;
            }
        }else{
            a=a->prox;
        }
    }

    printf("Tempo medio de execução: %.2fs\n",turn/(N*1.0));
    printf("Tempo medio de espera: %.2fs\n",te/(N*1.0));
    printf("%s",ordem);
}

void exibirFila(FILA* f) {
    PONT end = f->inicio;
    printf("Fila: \" ");
    while (end != NULL) {
        printf("%i ", end->reg.X);
        printf("%i ", end->reg.Y);
        printf("%s \n",end->reg.nome);
        end = end->prox;
    }
    printf("\"\n");
}


bool inserirNaFila(FILA* f,REGISTRO reg) {
    PONT novo = (PONT) malloc(sizeof(ELEMENTO));
    novo->reg = reg;
    novo->prox = NULL;
    if (f->inicio==NULL) f->inicio = novo;
    else f->fim->prox = novo;
    f->fim = novo;
    return true;
}

bool excluirDaFila(FILA* f, REGISTRO* reg) {
    if (f->inicio==NULL) return false;
    *reg = f->inicio->reg;
    PONT apagar = f->inicio;
    f->inicio = f->inicio->prox;
    free(apagar);
    if (f->inicio == NULL) f->fim = NULL;
    return true;
}

void reinicializarFila(FILA* f) {
    PONT end = f->inicio;
    while (end != NULL) {
        PONT apagar = end;
        end = end->prox;
        free(apagar);
    }
    f->inicio = NULL;
    f->fim = NULL;
}

int main(){
    FILA f;
    REGISTRO r;
    int N,X,Y,M=1,i,tempo=0,cont=1,Z;
    float turn=0,te=0;
    char ordem[100];
    strcpy(ordem,"");
    printf("Digite o numero de M:\n");
    scanf("%d",&M);
    do{
        printf("\nDigite o numero de N:");
        scanf("%d",&N);
        if(N<0) printf("\nPonha um numero maior ou igual a que zero!!!\n");
        else{
            for(i=0;i<N;i++){
                do{
                    printf("\nDigite o valor de X e Y:\n");
                    scanf("%d %d %d",&X,&Y,&Z);
                    if(X<0 ||Y<0) printf("\nPonha um numero maior que zero!!!\n");
                }while(X<0||Y<0||Z<0);
                r.X=X;
                r.Y=Y;
                r.K=Y;
                r.Z=Z;
                r.sensor=0;
                snprintf (r.nome, 50, "%c%d", 'P', i+1 );
                inserirNaFila(&f,r);
            }
            if (N!=0){
                printf("TESTE %d\n",cont);
                fifo(&f,&ordem,tempo,N,turn,te,M);
            }
        }    
        reinicializarFila(&f);
        strcpy(ordem," ");
        cont++;
    }while (N!=0);   
    return 0;
}