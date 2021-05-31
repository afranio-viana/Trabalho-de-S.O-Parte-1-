#include<stdio.h>
#include<pthread.h>
/*use gcc -pthread threads1.c -o threads1
para compilar no linux
*/

void *function(void *arg){
    int *valor= (int *)arg;
    printf("\nTread 1#: %d",*valor);
}
void *function2( void *arg){
    int *valor= (int *)arg;
    printf("\nTread 2#: %d",*valor);
}
int main(){
    pthread_t t1,t2;
    int a=1,b=500,c=1;
    for(int i;i<500;i++){
        pthread_create(&t1,NULL,function,(void *)(&a));
        pthread_create(&t2,NULL,function2,(void *)(&b));
        pthread_join(t1,NULL);
        pthread_join(t2,NULL);
        a++;
        b--;
    }
return 0;
}