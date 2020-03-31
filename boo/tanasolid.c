//split data used//
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main(int argc, char* argv[]){
	int i,Nparticles,State;
	double Col[8],Noise,Solid=0.0,Count=0.0,qc=0.55;
	FILE *FpR,*FpW;
	if(argc!=4){
		printf("argv should be 4");
		exit (1);
	}
	FpR = fopen(argv[1],"r");  //qcbcc01.dat
//argv[2] //bcc fcc hcp
	FpW = fopen(argv[3],"w");
	if((strcmp(argv[2],"sc"))==0){
		Nparticles=1000;
	}
	else if((strcmp(argv[2],"bcc"))==0){
		Nparticles=2000;
	}
	else if((strcmp(argv[2],"fcc"))==0){
		Nparticles=2048;
	}
	else if((strcmp(argv[2],"hcp"))==0){
		Nparticles=2048;
	}
	else{
		Nparticles=3000;
	}
	while (fscanf(FpR,"%lf %lf %lf %lf %lf %lf %lf %lf",&Col[0],&Col[1],&Col[2],&Col[3],&Col[4],&Col[5],&Col[6],&Col[7])!= EOF){
		if(Col[3]==1 && Col[7]>0)State=1;
		else if(Col[3]==1 && Col[6]<0 && Col[7]<0)State=2;
		else if(Col[3]==1 && Col[6]>0 && Col[7]<0)State=3;
		else State=0;
		fprintf(FpW,"%d\n",State);
	}
	return 0;
}
