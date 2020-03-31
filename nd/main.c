#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include"nd.c"

int main(int argc, char* argv[]){
	int i, j, k, m,**Nblist, Nparticles, Nearest=12, Conf=50;
	double **ArrR, **Nbdist,***Nd;
	double L[3],d0;
	FILE *FpR, *FpW;
	if(argc!=4){
		printf("argv should be 4");
		exit (1);
	}
	FpR = fopen(argv[1],"r");  //../bcc.xyz
//argv[2] //bcc fcc hcp
	FpW = fopen(argv[3],"w"); //BAD.dat
	if((strcmp(argv[2],"sc"))==0){
		L[0]=5.0;
		L[1]=5.0;
		L[2]=5.0;
		Nparticles=1000;
	}
	else if((strcmp(argv[2],"bcc"))==0){
		L[0]=6.29961;
		L[1]=6.29961;
		L[2]=6.29961;
		Nparticles=2000;
	}
	else if((strcmp(argv[2],"fcc"))==0){
		L[0]=6.3496;
		L[1]=6.3496;
		L[2]=6.3496;
		Nparticles=2048;
	}
	else if((strcmp(argv[2],"hcp"))==0){
		L[0]=4.48985;
		L[1]=7.77665;
		L[2]=7.33189;
		Nparticles=2048;
	}
	else{
		L[0]=7.2798;
		L[1]=7.2798;
		L[2]=7.2798;
		Nparticles=3000;
	}
	printf("%s %f\n",argv[1],L[0]);
	ArrR = Array2nd(Nparticles,3);
	Nbdist = Array2nd(Nparticles,12);
	Nblist = (int **)calloc(Nparticles,sizeof(int *));
	for(i=0;i<Nparticles;i++) Nblist[i] = (int *)calloc(12,sizeof(int));
	Nd = Array3rd(Nparticles,Nearest,Nearest);
/*********************************************************************************************************/
	for(m=0;m<Conf;m++){
		for(i=0;i<Nparticles;i++) fscanf(FpR,"%lf %lf %lf",&*(*(ArrR+i)+0),&*(*(ArrR+i)+1),&*(*(ArrR+i)+2));
		Reset(Nparticles,Nblist,Nbdist);
		CalNb(Nparticles,Nblist,ArrR,Nbdist,L);
		CalNd(Nparticles,Nblist,ArrR,Nbdist,Nd,L);
		for(i=0;i<Nparticles;i++){
			fprintf(FpW,"%d %d ",m,i);
			for(j=0;j<12;j++)for(k=j+1;k<12;k++)fprintf(FpW,"%lf ",Nd[i][j][k]);
			fprintf(FpW,"\n");
		}
		if(m%(Conf/5)==0)printf("%d step ok\n",m);
	}//m tail
	fclose(FpR);
	fclose(FpW);
	return 0;
} 

