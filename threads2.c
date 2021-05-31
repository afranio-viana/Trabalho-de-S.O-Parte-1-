#include<stdio.h>
#include<pthread.h>
/*use gcc -pthread threads2.c -o threads2
para compilar no linux
*/
MAT[3][3];
int K=0;

void *function1(void *arg){
    int *valor= (int *)arg;
    MAT[0][K]=*valor;
}
void *function2(void *arg){
    int *valor= (int *)arg;
    MAT[1][K]=*valor;
}
void *function3(void *arg){
    int *valor= (int *)arg;
    MAT[2][K]=*valor;
}

int main(){
    pthread_t t1,t2,t3;
    int a=1,b=500,c=1, v=1;
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            MAT[i][j]=v;
            v++;
        }
    }
     for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            printf("%d ",MAT[i][j]);
        }
        printf("\n");
    }
    printf("\n\n");
    int aux1=MAT[0][0],aux2=MAT[1][0],aux3=MAT[2][0];

    for(int i=2;i>0;i--){
        pthread_create(&t1,NULL,function1,(void *)(&MAT[0][i]));
        pthread_join(t1,NULL);
        pthread_create(&t2,NULL,function2,(void *)(&MAT[1][i]));
        pthread_join(t2,NULL);
        pthread_create(&t3,NULL,function3,(void *)(&MAT[2][i]));
        pthread_join(t3,NULL);
        K++;
    }
    pthread_create(&t1,NULL,function1,(void *)(&aux1));
    pthread_join(t1,NULL);
    pthread_create(&t2,NULL,function2,(void *)(&aux2));
    pthread_join(t2,NULL);
    pthread_create(&t3,NULL,function3,(void *)(&aux3));
    pthread_join(t3,NULL);
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            printf("%d ",MAT[i][j]);
        }
        printf("\n");
    }
return 0;
}