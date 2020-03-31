//split data used//
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main(int argc, char* argv[]){
	int i,Nparticles;
	double Col[3],Noise,Solid=0.0,Count=0.0,qc=0.55;
	FILE *FpR,*FpW1, *FpW2;
	if(argc!=6){
		printf("argv should be 4");
		exit (1);
	}
	FpR = fopen(argv[1],"r");  //qcbcc01.dat
//argv[2] //bcc fcc hcp
	FpW1 = fopen(argv[3],"w");
	FpW2 = fopen(argv[4],"a");
	Noise = atof(argv[5]);
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
	while (fscanf(FpR,"%lf %lf %lf",&Col[0],&Col[1],&Col[2])!= EOF){
		if(Col[2]>qc && strcmp(argv[2],"bcc")==0){
			fprintf(FpW1,"1\n");
			Solid++;
		}
		else if(Col[2]>qc && strcmp(argv[2],"fcc")==0){
			fprintf(FpW1,"2\n");
			Solid++;
		}
		else if(Col[2]>qc && strcmp(argv[2],"hcp")==0){
			fprintf(FpW1,"3\n");
			Solid++;
		}
		else fprintf(FpW1,"0\n");
		Count++;
	}
	fprintf(FpW2,"%lf %lf \n",Noise,Solid/Count);
	return 0;
}
