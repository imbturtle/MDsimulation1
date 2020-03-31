#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include"gofr.c"
#define Pi M_PI
double dr=0.02;
double boxsize(int,double);
int main(int argc,char* argv[]){
	FILE *fpr, *fpw;
	int i, m, Nparticles, Conf=20, Totaldr, Halfdr;
	double **ArrR, *g, L[3];
	FILE *FpR, *FpW;
	if(argc!=4){
		printf("argv should be 5");
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
	ArrR = Array2nd(Nparticles,3);
	Totaldr = (int)(2.0*L[1]/dr);	
	Halfdr = (int)(Totaldr/2.0);
	g = Array1st(Totaldr);
	for(m=0;m<Conf;m++){//m top
		for(i=0;i<Nparticles;i++) fscanf(FpR,"%lf %lf %lf",&*(*(ArrR+i)+0),&*(*(ArrR+i)+1),&*(*(ArrR+i)+2));
		RDF(Nparticles,ArrR,L,g);
		if(m%(Conf/5)==0)printf("%d down\n",m);	
	}//m tail
	for(i=0;i<Halfdr;i++){
		*(g+i) /= ((4.0/3.0)*Pi*(pow(((i+1)*dr),3.0)-pow(i*dr,3.0)))*(Conf*Nparticles*Nparticles/L[0]/L[1]/L[2])/2.0;
		fprintf(FpW,"%lf\t%lf\n",(dr/2.0)+(double)i*dr,(g[i]));
	}
	fclose(FpR);
	fclose(FpW);
	return 0;
} 
