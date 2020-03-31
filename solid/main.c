#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include"solid.c"
#define pi M_PI

int main(int argc, char* argv[]){
	int i, j, k, m, n, m1, m2, m3, **Nblist, Nparticles, Conf=50;//parameter
	double ***F4, ***F6, **Nbdist, **ArrR, **Rq4, **Iq4, **Rq6, **Iq6, *Locq4sq, *Locq6sq, *w4top, *w6top\
		, *Locq4, *Locq6, *Locw4, *Locw6,*Si;
	double L[3];
/*	**AveVecq4R, **AveVecq4I\
		 *Aveq4mR, *Aveq4mI, *Aveq4sq, *Aveq6mR, *Aveq6mI, *Aveq6sq,\
		*Aveq4, *Aveq6, *Avew4 , *Avew6, *Locdq4, *Locdq6, *Locdw4, *Locdw6, *Avedq4, *Avedq6, *Avedw4, *Avedw6,
		**AveVecq6R, **AveVecq6I, *Crystal;*/
		

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
	printf("%d %f",Nparticles,L[0]);
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
//	Aveq4mR = Array1st(9);
//	Aveq4mI = Array1st(9);
//	Aveq6mR = Array1st(13);
//	Aveq6mI = Array1st(13);
//	Aveq4sq = Array1st(1);
//	Aveq6sq = Array1st(1);
//	Aveq4 = Array1st(Nparticles);
//	Aveq6 = Array1st(Nparticles);
//	Avew4 = Array1st(Nparticles);
//	Avew6 = Array1st(Nparticles);
//	Crystal = Array1st(Nparticles);
	Winger3j(F4,F6);
	for(n=0;n<Conf;n++){
		for(i=0;i<Nparticles;i++)fscanf(FpR,"%lf %lf %lf",&*(*(ArrR+i)+0),&*(*(ArrR+i)+1),&*(*(ArrR+i)+2));
		Reset(Nparticles,Nblist,Nbdist,Rq4,Iq4,Rq6,Iq6,w4top,w6top,Locq4sq,Locq6sq);
		CalNb(Nparticles,Nblist,ArrR,Nbdist,L);
		CalSHP(Nparticles,Nblist,ArrR,Rq4,Iq4,Rq6,Iq6,L);
///////////////////////////////Local Bond Orientational Order Parameter/////////////////////////////////////////////
		CalLocQW(Nparticles,Rq4,Iq4,Rq6,Iq6,w4top,w6top,F6,F4,Locq4sq,Locq6sq,Locq4,Locq6,Locw4,Locw6);
//		for(i=0;i<Nparticles;i++)fprintf(FpW,"%lf %lf %lf %lf\n",Locq4[i],Locq6[i],Locw4[i],Locw6[i]);
////////////////////////////cal vec//////////////////////////////////////////////////////////////////////////////////
		CalSPBOP(Nparticles,Nblist,Rq4,Iq4,Rq6,Iq6,Locq4sq,Locq6sq,Si);
		for(i=0;i<Nparticles;i++)fprintf(FpW,"%d %d %lf\n",m,i,Si[i]);
////////////////////////Average Bond Orientational Order Parameter/////////////////////////////////////////////////////////////
/*		for(i=0;i<Nparticles;i++){
			CalAveQW(i,w4top,w6top,F6,F4,Aveq4mR,Aveq4mI,Aveq4sq,Aveq6mR,Aveq6mI,Aveq6sq,Rq4,Iq4,Rq6,Iq6,LocNb,Nblist);
			Aveq4[i] = sqrt(4.0*pi/9.0*Aveq4sq[0])/(LocNb[i]+1.0);
			Aveq6[i] = sqrt(4.0*pi/13.0*Aveq6sq[0])/(LocNb[i]+1.0);
			Avew4[i] = w4top[0]/pow(Aveq4sq[0],1.5);
			Avew6[i] = w6top[0]/pow(Aveq6sq[0],1.5);
		}*/
//		for(i=0;i<Nparticles;i++) fprintf(fpwqc,"%d %d %lf %lf %lf %lf\n",n,i,Aveq4[i],Aveq6[i],Avew4[i],Avew6[i]);	
////////////////////////Category by BOOPs/////////////////////////////////////////////////////////////
//		Crystalcate(Nparticles,Nblist,LocVecq6R,LocVecq6I,Avew4,Avew6,Crystal);
//		for(i=0;i<Nparticles;i++) fprintf(fpwqc,"%d %d %.1f\n",n,i,Crystal[i]);
		if(n%(Conf/5)==0)printf("%d step ok\n",n);
	}// n tail
	return 0;
}



