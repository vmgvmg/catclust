#include <stdio.h>
#include <string.h>

#define nC 300 //nGoods
#define nR 64  //nCust
int facts[nC*nR*3][2];

main(){	
	char arr[nC];
	int x=0,y,nf=0,i,j;
	FILE *p;
	p=fopen("../in","r"); 
	while (fgets (arr, nC, p) != NULL){
		//printf("%s", arr); 
		//printf("\n");
		int sl=strlen(arr);
		for(y=0;y<sl;y++){
			if(arr[y]=='1') {
		//		printf("%d %d\n",x,y);
				facts[nf][0]=x;
				facts[nf][1]=y;
				nf++;
			}
		}
		x++;		
	}
	fclose(p);
//	facts[nf][0]=-1;
//	facts[nf][1]=-1;
	p = fopen("../f.csv", "w");
	for (i = 0; i<nf; i++)fprintf(p, "%d,%d\n", facts[i][0], facts[i][1]);
	fclose(p);

}
