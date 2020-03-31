#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include"boo.c"
#define pi M_PI

int main(int argc, char* argv[]){
	int i, m, *Solid, *Connect, **Nblist, Nparticles, Conf=50;//parameter
	double ***F4, ***F6, **Nbdist, **ArrR, **Rq4, **Iq4, **Rq6, **Iq6, *Locq4sq, *Locq6sq, *w4top, *w6top\
		, *Locq4, *Locq6, *Locw4, *Locw6,*Si,*Aveq4, *Aveq6, *Avew4 , *Avew6;
	double L[3];
	FILE *FpR, *FpW1, *FpW2;
	if(argc!=5){
		printf("argv should be 5");
		exit (1);
	}
	FpR = fopen(argv[1],"r");  //../bcc.xyz
//argv[2] //bcc fcc hcp
	FpW1 = fopen(argv[3],"w"); //BAD.dat
	FpW2 = fopen(argv[4],"w"); //BAD.dat
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
	printf("%d %f\n",Nparticles,L[0]);
	ArrR = Array2nd(Nparticles,3);
	Nbdist = Array2nd(Nparticles,12);
	Nblist = (int **)calloc(Nparticles,sizeof(int *));
	for(i=0;i<Nparticles;i++) Nblist[i] = (int *)calloc(12,sizeof(int));
	F4 = Array3rd(9, 9, 9);
	F6 =  Array3rd(13, 13, 13);
	Rq4 = Array2nd(Nparticles,9);
	Iq4 = Array2nd(Nparticles,9);
	Rq6 = Array2nd(Nparticles,13);
	Iq6 = Array2nd(Nparticles,13);
	Locq4sq = Array1st(Nparticles);
	Locq6sq = Array1st(Nparticles);
	w4top = Array1st(Nparticles);
	w6top = Array1st(Nparticles);
	Locq4 = Array1st(Nparticles);
	Locq6 = Array1st(Nparticles);
	Locw4 = Array1st(Nparticles);
	Locw6 = Array1st(Nparticles);
	Si = Array1st(Nparticles);
	Solid = (int *)calloc(Nparticles,sizeof(int ));
	Connect = (int *)calloc(Nparticles,sizeof(int ));
	Aveq4 = Array1st(Nparticles);
	Aveq6 = Array1st(Nparticles);
	Avew4 = Array1st(Nparticles);
	Avew6 = Array1st(Nparticles);
	Winger3j(F4,F6);
	for(m=0;m<Conf;m++){
		for(i=0;i<Nparticles;i++)fscanf(FpR,"%lf %lf %lf",&*(*(ArrR+i)+0),&*(*(ArrR+i)+1),&*(*(ArrR+i)+2));
		Reset(Nparticles,Solid,Nblist,Nbdist,Rq4,Iq4,Rq6,Iq6,w4top,w6top,Locq4sq,Locq6sq);
		CalNb(Nparticles,Nblist,ArrR,Nbdist,L);
		CalSHP(Nparticles,Nblist,ArrR,Rq4,Iq4,Rq6,Iq6,L);
///////////////////////////////Local Bond Orientational Order Parameter/////////////////////////////////////////////
		CalLocQW(Nparticles,Rq4,Iq4,Rq6,Iq6,w4top,w6top,F6,F4,Locq4sq,Locq6sq,Locq4,Locq6,Locw4,Locw6);
		for(i=0;i<Nparticles;i++)fprintf(FpW1,"%lf %lf %lf %lf\n",Locq4[i],Locq6[i],Locw4[i],Locw6[i]);
////////////////////////////cal vec//////////////////////////////////////////////////////////////////////////////////
//		CalSPBOP(Nparticles,Nblist,Rq4,Iq4,Rq6,Iq6,Locq4sq,Locq6sq,Si);
//		for(i=0;i<Nparticles;i++)fprintf(FpW,"%d %d %lf\n",m,i,Si[i]);
////////////////////////Average Bond Orientational Order Parameter/////////////////////////////////////////////////////////////
		CalAveQW(Nparticles,Connect,Solid,Nblist,Rq4,Iq4,Rq6,Iq6,F4,F6,Locq4sq,Locq6sq,Aveq4,Aveq6,Avew4,Avew6);
		for(i=0;i<Nparticles;i++) \
			fprintf(FpW2,"%d %d %d %d %lf %lf %lf %lf\n",m,i,Connect[i],Solid[i],Aveq4[i],Aveq6[i],Avew4[i],Avew6[i]);	
////////////////////////Category by BOOPs/////////////////////////////////////////////////////////////
//		Crystalcate(Nparticles,Nblist,LocVecq6R,LocVecq6I,Avew4,Avew6,Crystal);
//		for(i=0;i<Nparticles;i++) fprintf(fpwqc,"%d %d %.1f\n",n,i,Crystal[i]);
		if(m%(Conf/5)==0)printf("%d conf ok",m);
	}// m tail
	return 0;
}



