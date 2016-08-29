#include <stdio.h>
#include <stdlib.h>
#define mxC 32 	//макс колво покупателей
#define mxG 256 //макс колво товаров
#define mxF mxC*mxG //макс Число фактов(кортежей) в файле f.csv
int F[mxF][2];//факты не повторяются
int nCbyG[mxG];//колво покупателей у товара
unsigned char *bGbyC[mxC];//биты товаров по покупателям
unsigned char *bGbySC[mxC];//биты товаров по выбранным покупателям
unsigned char bGC[mxG/8+1];//биты товаров sochetaniya покупателям
main(int argc, char *argv[]){
int i=0,nC=0,nG=0,maxC=0,j,m,r,f,n;
unsigned b=0,k,l;
unsigned char c;
if (argc != 2) {	printf("format: exe facts. Facts is file with 2 number columns)");	exit(1);}
FILE *s = fopen(argv[1], "r");
if (s == NULL) {	printf("Facts file don't exist"); return -1;}
while (EOF != fscanf(s, "%d,%d", &F[i][0], &F[i][1])){//Читаем факты
	i++;
	if (i == mxF){ 		printf("%d >= %d\n", i, mxF); 		return -1; }
}
F[i][0]=F[i][1]=-1;
for(i=0;i<mxG;i++)nCbyG[i]=0;
i=0;
while(F[i][0]!=-1){
	nCbyG[F[i][1]]++;
	if(F[i][0]>nC)nC=F[i][0];
	if(F[i][1]>nG)nG=F[i][1];
	i++;
}
if(nC>=mxC){printf("%d>=%d\n",nC,mxC);return -1;}
if(nG>=mxG){printf("%d>=%d\n",nG,mxG);return -1;}		
for(i=0;i<nG;i++)if(nCbyG[i]>maxC)maxC=nCbyG[i];//Любой товаров покупался не больше,чем maxC различными покупателями  
for (i = 0; i <= nC; i++)bGbyC[i] = (unsigned char*)malloc(nG / 8 + 1);
for (i = 0; i <= nC; i++)for (j = 0; j < nG / 8 + 1; j++) bGbyC[i][j] = '\0';
i=0;
while(F[i][0]!=-1){
	bGbyC[F[i][0]][F[i][1]/8]|=(unsigned char)(1<<(F[i][1]%8)); //Устанавливаем биты купленных товаров по покупателям
	i++;
}
for(i=0;i<=nC;i++)b|=(unsigned)(1<<i);
for(k=1;k<b;k++){//Генерируем сочетания из nC по 2,3 .. maxC покупателям. Сочетание это биты в k
	int cu=0;	
	for(l=0;l<=nC;l++) if((k>>l)&1)cu++;
	if(cu>maxC||cu<2)continue;
//	printf("%u ",k);
	for(i=0;i<=nC;i++)bGbySC[i]=(unsigned char *)'\0';
	i=0;
	for(l=0;l<=nC;l++) if((k>>l)&1) { //Для очередного сочетания (для ненулевых бит в k) составляем матрицу битов товаров 
		bGbySC[i]=bGbyC[l];
		i++;
	}
	f=0;
	for(j=0;j<=nG;j++){//Просматриваем матрицу битов товаров по столбцам
		r=0;
		for(m=0;m<i;m++)
			if((bGbySC[m][j/8]>>(j%8))&'\1')
				r++; //сколько покупателей купило  j-й товар
		for (n = 0; n < nG / 8 + 1; n++) bGC[n] = '\0';
		if(r>=i/2+1){
			bGC[j/8]|=(unsigned char)(1<<(j%8));
			printf("%d ",j);
			f=1;
		}
	}
	if(f){
		printf("   ");
		for(l=0;l<=nC;l++) if((k>>l)&1) printf("%d ",l);// Выводим номера ненулевых бит в к (номера покупателей)
		for(n=0;n<=nG;n++) if((bGC[n/8]>>(n%8))&'\1')printf("%d ",n);
 		printf("\n");
	}
}
fclose(s);
getchar();
}




