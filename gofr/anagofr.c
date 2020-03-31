//split data used//
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<time.h>

int main(int argc,char* argv[]){
	int i;
	double col[2],max=0.0,min=20.0,rmin,rmax;
	FILE *FpR,*FpW;
	if(argc!=4){
		printf("argv should be 4");
		exit (1);
	}
	FpR = fopen(argv[1],"r");
	FpW = fopen(argv[3],"a");	
	while(fscanf(FpR,"%lf %lf",&col[0],&col[1]) != EOF){//find maximun
		if(col[1] > max && col[0]>1.0) {
			rmax = col[0];
			max = col[1];
		}
		if(col[1] < max) break;
	}	
	while(fscanf(FpR,"%lf %lf",&col[0],&col[1]) != EOF){//find mimun
		if(col[1] < min) {
			rmin = col[0];
			min = col[1];
		}	
		if(col[0] > 2.0) break;
	}
	fprintf(FpW,"%s %lf %lf %lf %lf\n",argv[2],rmax,max,rmin,min);
	fclose(FpR);
	fclose(FpW);
	return 0;
}
