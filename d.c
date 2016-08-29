#include <stdio.h>
#include <stdlib.h>
#define mxC 20 	//макс колво покупателей
#define mxG 20 //макс колво товаров
main(){
int i,j;
FILE *p;
p = fopen("../in", "w");
srand(time(NULL));
for (i = 0; i < mxC; i++){
	for (j = 0; j <mxG; j++)fprintf(p, "%d", rand() % 2);
	fprintf(p, "\n");
}
fclose(p);
} 


