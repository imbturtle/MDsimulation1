void CalNb(int, int **, double **, double **, double *);
void CalSHP(int, int **, double **, double **, double **, double **, double **, double *);
void CalLocQW(int, double **, double **, double **, double **, double *, double *, double ***, double ***\
	, double *, double *, double *, double *, double *, double *);
void CalSPBOP(int, int **, double **, double **, double **, double **, double *, double *, double *);
void CalAveQW(int, int *, int *, int **, double **, double **, double **, double **\
	, double ***, double ***, double *, double *, double *, double *, double *, double *);
void Reset(int, int *, int **, double **, double **, double **, double **, double **, double *, double *\
	, double *,double *);
void Winger3j(double***, double***);
void SumYml(double**, double**, double**, double**, double*, double, int);
double SumPi(double);
double *Array1st(int);
double **Array2nd(int, int);
double ***Array3rd(int, int, int);

#define pi M_PI
/***********************************************************************************************************
***********************************************************************************************************/
void CalNb(int N, int **Nblist, double **ArrR, double **Nbdist, double *L){
	int i, j, k, l;
	double Dij[3],Lij;
	for(i=0;i<N;i++)for(j=0;j<N;j++){	//j top
		if(i==j) continue;
		for(l=0;l<3;l++){
			Dij[l] =  *(*(ArrR+j)+l) - *(*(ArrR+i)+l);
			while(Dij[l] > L[l]) Dij[l] -= L[l]*2.0;
			while(Dij[l] <-L[l]) Dij[l] += L[l]*2.0;
		}
		Lij = sqrt(Dij[0] * Dij[0] + Dij[1] * Dij[1] + Dij[2] * Dij[2]);
		for(k=0;k<12;k++){
			if(Lij < Nbdist[i][k]){
				for(l=11;l>k;l--){
					Nbdist[i][l] = Nbdist[i][l-1];
					Nblist[i][l] = Nblist[i][l-1];
				}
				Nbdist[i][k] = Lij;
				Nblist[i][k] = j;
				break;
}}}}
/***********************************************************************************************************
***********************************************************************************************************/
void CalSHP(int N, int **Nblist, double **ArrR, double **Rq4, double **Iq4, double **Rq6, double **Iq6, double *L){
	int i,j,l;
	double Lij, Dij[3], costheta, sintheta, phi;
	for(i=0;i<N;i++){	
		for(j=0;j<12;j++){
			for(l=0;l<3;l++){
				Dij[l] =  ArrR[Nblist[i][j]][l] - ArrR[i][l];
				while(Dij[l] > L[l]) Dij[l] -= L[l]*2.0;
				while(Dij[l] <-L[l]) Dij[l] += L[l]*2.0;
			}
			Lij = sqrt(Dij[0] * Dij[0] + Dij[1] * Dij[1] + Dij[2] * Dij[2]);
			costheta = Dij[2]/Lij;
			sintheta = pow(1.0-costheta*costheta,0.5);
			phi = atan(Dij[1]/Dij[0]);
			if(Dij[0]==0.0 && Dij[1]==0.0) phi = 0.0;
			if(Dij[0]==0.0 && Dij[1]>0.0)  phi = pi/2.0;
			if(Dij[0]==0.0 && Dij[1]<0.0)  phi =-pi/2.0;
			if(phi < 0.0) phi += 2.0*pi;
			if(Dij[0] < 0.0) phi += pi;
			Rq4[i][0] += (3.0/16.0)*sqrt(35.0/2.0/pi)*pow(sintheta,4.0)*cos(4.0*phi);//here qlm=summation(Ylm)
			Iq4[i][0] += (3.0/16.0)*sqrt(35.0/2.0/pi)*pow(sintheta,4.0)*-sin(4.0*phi);
			Rq4[i][1] += (3.0/8.0)*sqrt(35.0/pi)*pow(sintheta,3.0)*costheta*cos(3.0*phi);
			Iq4[i][1] += (3.0/8.0)*sqrt(35.0/pi)*pow(sintheta,3.0)*costheta*-sin(3.0*phi);
			Rq4[i][2] += (3.0/8.0)*sqrt(5.0/2.0/pi)*pow(sintheta,2.0)*(7.0*pow(costheta,2.0)-1)*cos(2.0*phi);
			Iq4[i][2] += (3.0/8.0)*sqrt(5.0/2.0/pi)*pow(sintheta,2.0)*(7.0*pow(costheta,2.0)-1)*-sin(2.0*phi);
			Rq4[i][3] += (3.0/8.0)*sqrt(5.0/pi)*sintheta*(7.0*pow(costheta,3.0)-3.0*costheta)*cos(phi);
			Iq4[i][3] += (3.0/8.0)*sqrt(5.0/pi)*sintheta*(7.0*pow(costheta,3.0)-3.0*costheta)*-sin(phi);
			Rq4[i][4] += (3.0/16.0)*sqrt(1.0/pi)*(35.0*pow(costheta,4.0)-30.0*pow(costheta,2.0)+3.0);
			Rq4[i][5] += (-3.0/8.0)*sqrt(5.0/pi)*sintheta*(7.0*pow(costheta,3.0)-3.0*costheta)*cos(phi);
			Iq4[i][5] += (-3.0/8.0)*sqrt(5.0/pi)*sintheta*(7.0*pow(costheta,3.0)-3.0*costheta)*sin(phi);
			Rq4[i][6] += (3.0/8.0)*sqrt(5.0/2.0/pi)*pow(sintheta,2.0)*(7.0*pow(costheta,2.0)-1)*cos(2.0*phi);
			Iq4[i][6] += (3.0/8.0)*sqrt(5.0/2.0/pi)*pow(sintheta,2.0)*(7.0*pow(costheta,2.0)-1)*sin(2.0*phi);
			Rq4[i][7] += (-3.0/8.0)*sqrt(35.0/pi)*pow(sintheta,3.0)*costheta*cos(3.0*phi);
			Iq4[i][7] += (-3.0/8.0)*sqrt(35.0/pi)*pow(sintheta,3.0)*costheta*sin(3.0*phi);
			Rq4[i][8] += (3.0/16.0)*sqrt(35.0/2.0/pi)*pow(sintheta,4.0)*cos(4.0*phi);
			Iq4[i][8] += (3.0/16.0)*sqrt(35.0/2.0/pi)*pow(sintheta,4.0)*sin(4.0*phi);
			Rq6[i][0] += (1.0/64.0)*sqrt(3003.0/pi)*pow(sintheta,6.0)*cos(6.0*phi);
			Iq6[i][0] += (1.0/64.0)*sqrt(3003.0/pi)*pow(sintheta,6.0)*-sin(6.0*phi);
			Rq6[i][1] += (3.0/32.0)*sqrt(1001.0/pi)*pow(sintheta,5.0)*costheta*cos(5.0*phi);
			Iq6[i][1] += (3.0/32.0)*sqrt(1001.0/pi)*pow(sintheta,5.0)*costheta*-sin(5.0*phi);
			Rq6[i][2] += (3.0/32.0)*sqrt(91.0/2.0/pi)*pow(sintheta,4.0)*(11.0*pow(costheta,2.0)-1.0)*cos(4.0*phi);
			Iq6[i][2] += (3.0/32.0)*sqrt(91.0/2.0/pi)*pow(sintheta,4.0)*(11.0*pow(costheta,2.0)-1.0)*-sin(4.0*phi);
			Rq6[i][3] += (1.0/32.0)*sqrt(1365.0/pi)*pow(sintheta,3.0)*(11.0*pow(costheta,3.0)-3.0*costheta)*cos(3.0*phi);
			Iq6[i][3] += (1.0/32.0)*sqrt(1365.0/pi)*pow(sintheta,3.0)*(11.0*pow(costheta,3.0)-3.0*costheta)*-sin(3.0*phi);
			Rq6[i][4] += (1.0/64.0)*sqrt(1365.0/pi)*pow(sintheta,2.0)*\
				(33.0*pow(costheta,4.0)-18.0*pow(costheta,2.0)+1.0)*cos(2.0*phi);
			Iq6[i][4] += (1.0/64.0)*sqrt(1365.0/pi)*pow(sintheta,2.0)*\
				(33.0*pow(costheta,4.0)-18.0*pow(costheta,2.0)+1.0)*-sin(2.0*phi);
			Rq6[i][5] += (1.0/16.0)*sqrt(273.0/2.0/pi)*sintheta*\
				(33.0*pow(costheta,5.0)-30.0*pow(costheta,3.0)+5.0*costheta)*cos(phi);
			Iq6[i][5] += (1.0/16.0)*sqrt(273.0/2.0/pi)*sintheta*\
				(33.0*pow(costheta,5.0)-30.0*pow(costheta,3.0)+5.0*costheta)*-sin(phi);
			Rq6[i][6] += (1.0/32.0)*sqrt(13.0/pi)*(231.0*pow(costheta,6.0)-315.0*pow(costheta,4.0)+\
				105.0*pow(costheta,2.0)-5);
			Rq6[i][7] += (-1.0/16.0)*sqrt(273.0/2.0/pi)*sintheta*\
				(33.0*pow(costheta,5.0)-30.0*pow(costheta,3.0)+5.0*costheta)*cos(phi);
			Iq6[i][7] += (-1.0/16.0)*sqrt(273.0/2.0/pi)*sintheta*\
				(33.0*pow(costheta,5.0)-30.0*pow(costheta,3.0)+5.0*costheta)*sin(phi);
			Rq6[i][8] += (1.0/64.0)*sqrt(1365.0/pi)*pow(sintheta,2.0)*\
				(33.0*pow(costheta,4.0)-18.0*pow(costheta,2.0)+1.0)*cos(2.0*phi);
			Iq6[i][8] += (1.0/64.0)*sqrt(1365.0/pi)*pow(sintheta,2.0)*\
				(33.0*pow(costheta,4.0)-18.0*pow(costheta,2.0)+1.0)*sin(2.0*phi);
			Rq6[i][9] += (-1.0/32.0)*sqrt(1365.0/pi)*pow(sintheta,3.0)*(11.0*pow(costheta,3.0)-3.0*costheta)*cos(3.0*phi);
			Iq6[i][9] += (-1.0/32.0)*sqrt(1365.0/pi)*pow(sintheta,3.0)*(11.0*pow(costheta,3.0)-3.0*costheta)*sin(3.0*phi);
			Rq6[i][10] += (3.0/32.0)*sqrt(91.0/2.0/pi)*pow(sintheta,4.0)*(11.0*pow(costheta,2.0)-1.0)*cos(4.0*phi);
			Iq6[i][10] += (3.0/32.0)*sqrt(91.0/2.0/pi)*pow(sintheta,4.0)*(11.0*pow(costheta,2.0)-1.0)*sin(4.0*phi);
			Rq6[i][11] += (-3.0/32.0)*sqrt(1001.0/pi)*pow(sintheta,5.0)*costheta*cos(5.0*phi);
			Iq6[i][11] += (-3.0/32.0)*sqrt(1001.0/pi)*pow(sintheta,5.0)*costheta*sin(5.0*phi);
			Rq6[i][12] += (1.0/64.0)*sqrt(3003.0/pi)*pow(sintheta,6.0)*cos(6.0*phi);
			Iq6[i][12] += (1.0/64.0)*sqrt(3003.0/pi)*pow(sintheta,6.0)*sin(6.0*phi); 						
}}}
/***********************************************************************************************************
***********************************************************************************************************/
void CalLocQW(int N,double **Rq4,double **Iq4,double **Rq6,double **Iq6,double *w4top,double *w6top,double ***F6,double ***F4,double *Locq4sq,double *Locq6sq,double *Locq4,double *Locq6,double *Locw4,double *Locw6){
	int i,m,m1,m2,m3;
	for(i=0;i<N;i++){
		for(m=0;m<9;m++)Locq4sq[i] += Rq4[i][m]*Rq4[i][m]+Iq4[i][m]*Iq4[i][m];//here ql = square (summation of qlm)*Nb^2
		for(m=0;m<13;m++)Locq6sq[i] += Rq6[i][m]*Rq6[i][m]+Iq6[i][m]*Iq6[i][m];
		w4top[i] = 0.0;
		w6top[i] = 0.0;
		for(m1=0;m1<13;m1++)for(m2=0;m2<13;m2++)for(m3=0;m3<13;m3++){
			if(m1+m2+m3==12 && m1<9 && m2<9 && m3<9){
				w4top[i] += F4[m1][m2][m3] * (Rq4[i][m1]*Rq4[i][m2]*Rq4[i][m3] - Iq4[i][m1]*Iq4[i][m2]*Rq4[i][m3] -\
					Rq4[i][m1]*Iq4[i][m2]*Iq4[i][m3] - Iq4[i][m1]*Rq4[i][m2]*Iq4[i][m3]);//Real part
//				w4topi += F4[m1][m2][m3] * (-Rq4[i][m1]*Rq4[i][m2]*Iq4[i][m3] + Iq4[i][m1]*Iq4[i][m2]*Iq4[i][m3] +\
					Rq4[i][m1]*Iq4[i][m2]*Rq4[i][m3] + Iq4[i][m1]*Rq4[i][m2]*Rq4[i][m3]);//image part
			}
			if(m1+m2+m3==18){
				w6top[i] += F6[m1][m2][m3] * (Rq6[i][m1]*Rq6[i][m2]*Rq6[i][m3] - Iq6[i][m1]*Iq6[i][m2]*Rq6[i][m3] -\
					Rq6[i][m1]*Iq6[i][m2]*Iq6[i][m3] - Iq6[i][m1]*Rq6[i][m2]*Iq6[i][m3]);//Real part
//				w6topi += F6[m1][m2][m3] * (-Rq6[i][m1]*Rq6[i][m2]*Iq6[i][m3] + Iq6[i][m1]*Iq6[i][m2]*Iq6[i][m3] +\
					Rq6[i][m1]*Iq6[i][m2]*Rq6[i][m3] + Iq6[i][m1]*Rq6[i][m2]*Rq6[i][m3]);//image part
		}}
		Locq4[i] = sqrt((4.0*pi)/(9.0)*Locq4sq[i])/12.0;
		Locq6[i] = sqrt((4.0*pi)/(13.0)*Locq6sq[i])/12.0;
		Locw4[i] = w4top[i]/pow(Locq4sq[i],1.5);
		Locw6[i] = w6top[i]/pow(Locq6sq[i],1.5);
}}
/***********************************************************************************************************
***********************************************************************************************************/
void CalSPBOP(int N, int **Nblist, double **Rq4, double **Iq4, double **Rq6, double **Iq6\
	, double *Locq4sq, double *Locq6sq, double *Si){
	int i,j,m;
	double LocVecq4R[N][9],LocVecq4I[N][9],LocVecq6R[N][13],LocVecq6I[N][13];
	for(i=0;i<N;i++)for(m=0;m<13;m++){
		if(m<9){
			LocVecq4R[i][m] = Rq4[i][m]/sqrt(Locq4sq[i]);
			LocVecq4I[i][m] = Iq4[i][m]/sqrt(Locq4sq[i]);
		}
		LocVecq6R[i][m] = Rq6[i][m]/sqrt(Locq6sq[i]);
		LocVecq6I[i][m] = Iq6[i][m]/sqrt(Locq6sq[i]);
	}
	for(i=0;i<N;i++){
		Si[i] = 0.0;
		for(j=0;j<12;j++){
			for(m=0;m<13;m++) Si[i] += LocVecq6R[i][m]*LocVecq6R[Nblist[i][j]][m] + LocVecq6I[i][m]*LocVecq6I[Nblist[i][j]][m];
		}
		Si[i] /= 12.0;
}}
/***********************************************************************************************************
***********************************************************************************************************/
void CalAveQW(int N,int *Connect,int *Solid, int **Nblist, double **Rq4, double **Iq4, double **Rq6, double **Iq6\
	, double ***F4, double ***F6, double *Locq4sq, double *Locq6sq\
	, double *Aveq4, double *Aveq6, double *Avew4, double *Avew6){
	int i,j,k,m,m1,m2,m3,PhaseNb[N][12];
	double LocVecq4R[N][9],LocVecq4I[N][9],LocVecq6R[N][13],LocVecq6I[N][13],\
		Aveq4mR[9],Aveq4mI[9],Aveq6mR[13],Aveq6mI[13],Aveq4sq[N],Aveq6sq[N],\
		w4top[N],w6top[N],Nb[N],\
		Sij,qc=0.6;
	memset(PhaseNb,-1, sizeof(int)*N*12);
	memset(Connect,0, sizeof(int)*N);
	memset(Aveq4sq,0, sizeof(double)*N);
	memset(Aveq6sq,0, sizeof(double)*N);
	memset(w4top,0, sizeof(double)*N);
	memset(w6top,0, sizeof(double)*N);
	memset(Nb,0, sizeof(double)*N);
	for(i=0;i<N;i++)for(m=0;m<13;m++){
		if(m<9){
			LocVecq4R[i][m] = Rq4[i][m]/sqrt(Locq4sq[i]);
			LocVecq4I[i][m] = Iq4[i][m]/sqrt(Locq4sq[i]);
		}
		LocVecq6R[i][m] = Rq6[i][m]/sqrt(Locq6sq[i]);
		LocVecq6I[i][m] = Iq6[i][m]/sqrt(Locq6sq[i]);
	}
	for(i=0;i<N;i++){
		for(j=0;j<12;j++){
			Sij = 0.0;
			for(m=0;m<13;m++) Sij += LocVecq6R[i][m]*LocVecq6R[Nblist[i][j]][m] + LocVecq6I[i][m]*LocVecq6I[Nblist[i][j]][m];
			if(Sij>qc) Connect[i]++;
		}
		if(Connect[i]>8)Solid[i]=1;//Solid 1,Liquid 0
	}
	for(i=0;i<N;i++){//i top //list same phase
		k=1;
		if(Solid[i]==1){
			for(j=0;j<12;j++){
				if(Solid[Nblist[i][j]]==1){
					PhaseNb[i][k]=Nblist[i][j];
					k++;
		}}}
		if(Solid[i]==0){
			for(j=0;j<12;j++){
				if(Solid[Nblist[i][j]]!=1){
					PhaseNb[i][k]=Nblist[i][j];
					k++;
		}}}
		Nb[i]=k;
	}//i bot
	for(i=0;i<N;i++){
		for(m=0;m<13;m++){
			if(m<9){
				Aveq4mR[m] = Rq4[i][m]/12.0;//itself
				Aveq4mI[m] = Iq4[i][m]/12.0;
				for(j=0;j<12;j++){
					if(PhaseNb[i][j]<0) break;		
					Aveq4mR[m] += Rq4[PhaseNb[i][j]][m]/12.0;
					Aveq4mI[m] += Iq4[PhaseNb[i][j]][m]/12.0;
	
			}}
			Aveq6mR[m] = Rq6[i][m]/12.0;
			Aveq6mI[m] = Iq6[i][m]/12.0;
			for(j=0;j<12;j++){
				if(PhaseNb[i][j]<0) break;		
				Aveq6mR[m] += Rq6[PhaseNb[i][j]][m]/12.0;
				Aveq6mI[m] += Iq6[PhaseNb[i][j]][m]/12.0;
		}}
		for(m=0;m<13;m++){
			if(m<9)Aveq4sq[i] += Aveq4mR[m]*Aveq4mR[m]+Aveq4mI[m]*Aveq4mI[m];
			Aveq6sq[i] += Aveq6mR[m]*Aveq6mR[m]+Aveq6mI[m]*Aveq6mI[m];
		}	
		for(m1=0;m1<13;m1++)for(m2=0;m2<13;m2++)for(m3=0;m3<13;m3++){
			if(m1+m2+m3==12 && m1<9 && m2<9 && m3<9){
				w4top[i] += F4[m1][m2][m3] * (Aveq4mR[m1]*Aveq4mR[m2]*Aveq4mR[m3] -\
					Aveq4mI[m1]*Aveq4mI[m2]*Aveq4mR[m3]- Aveq4mR[m1]*Aveq4mI[m2]*Aveq4mI[m3] -\
					Aveq4mI[m1]*Aveq4mR[m2]*Aveq4mI[m3]);//Real part
//				w4topi += F4[m1][m2][m3] * (-Aveq4mR[m1]*Aveq4mR[m2]*Aveq4mI[m3] + \
					Aveq4mI[m1]*Aveq4mI[m2]*Aveq4mI[m3] + Aveq4mR[m1]*Aveq4mI[m2]*Aveq4mR[m3] +\
					Aveq4mI[m1]*Aveq4mR[m2]*Aveq4mR[m3]);//image part
			}
			if(m1+m2+m3==18){
				w6top[i] += F6[m1][m2][m3] * (Aveq6mR[m1]*Aveq6mR[m2]*Aveq6mR[m3] - \
					Aveq6mI[m1]*Aveq6mI[m2]*Aveq6mR[m3] - Aveq6mR[m1]*Aveq6mI[m2]*Aveq6mI[m3] - \
					Aveq6mI[m1]*Aveq6mR[m2]*Aveq6mI[m3]);//Real part
//				w6topi += F6[m1][m2][m3] * (-Aveq6mR[m1]*Aveq6mR[m2]*Aveq6mI[m3] + \
					Aveq6mI[m1]*Aveq6mI[m2]*Aveq6mI[m3] + Aveq6mR[m1]*Aveq6mI[m2]*Aveq6mR[m3] + \
					Aveq6mI[m1]*Aveq6mR[m2]*Aveq6mR[m3]);//image part
	}}}
	for(i=0;i<N;i++){
		Aveq4[i] = sqrt(4.0*pi/9.0*Aveq4sq[i])/Nb[i];
		Aveq6[i] = sqrt(4.0*pi/13.0*Aveq6sq[i])/Nb[i];
		Avew4[i] = w4top[i]/pow(Aveq4sq[i],1.5);
		Avew6[i] = w6top[i]/pow(Aveq6sq[i],1.5);
}}	

/***********************************************************************************************************
***********************************************************************************************************/
void Crystalcate(int N, int **Nblist,double **LocVecq6R,double **LocVecq6I,double *Avew4,double *Avew6,double *Crystal){
	int i,j,m,Connect;
	double Sij,qc=0.6;
	for(i=0;i<N;i++){
		Connect=0;
		for(j=0;j<20;j++){
			Sij = 0.0;
			if(Nblist[i][j] < 0) break;	
			for(m=0;m<13;m++) Sij += LocVecq6R[i][m]*LocVecq6R[Nblist[i][j]][m] \
				+ LocVecq6I[i][m]*LocVecq6I[Nblist[i][j]][m];
			if(Sij>qc) Connect++;
		}
		if(Connect>8) Crystal[i]++;//Crystal 0=>liquid, 1=>bcc
		if(Crystal[i]==1 && Avew6[i]<0 && Avew4[i]<0) Crystal[i]+=1;
		if(Crystal[i]==1 && Avew6[i]<0 && Avew4[i]>0) Crystal[i]+=2;//Crystal 2=>fcc, 3=>hcp	
}}
/***********************************************************************************************************
***********************************************************************************************************/
void Reset(int N,int *Solid,int **Nblist,double **Nbdist,double **Rq4 ,double **Iq4 ,double **Rq6,double **Iq6\
	,double *w4top,double *w6top,double *Locq4sq,double *Locq6sq){
	int i,j,k,m;
	
	for(i=0;i<N;i++)for(j=0;j<12;j++){
		Nbdist[i][j] = 99.0;
		Nblist[i][j] = 0;
		for(m=0;m<13;m++){
			if(m<9){
				Rq4[i][m] = 0.0;
				Iq4[i][m] = 0.0;
			}
			Rq6[i][m] = 0.0;
			Iq6[i][m] = 0.0;
	}}
	memset(Solid,0, sizeof(int)*N);
	memset(w4top,0, sizeof(double)*N);
	memset(w6top,0, sizeof(double)*N);
	memset(Locq4sq,0, sizeof(double)*N);
	memset(Locq6sq,0, sizeof(double)*N);

//	memset(Crystal,0, sizeof(double)*N);
}
/***********************************************************************************************************
***********************************************************************************************************/
void Winger3j(double ***F4, double ***F6){
	double diagonal, summation, m1, m2, m3, l1, l2, l3, t;
	l1=l2=l3=4.0;
	for(m1=-l1;m1<l1+1.0;m1++){
		for(m2=-l2;m2<l2+1.0;m2++){
			for(m3=-l3;m3<l3+1.0;m3++){
				if(m1+m2+m3 == 0.0){
					summation = 0.0;
					for(t=0.0;t<=20.0;t+=1.0){
						if(l3-l2+t+m1<0.0 || l3-l1+t-m2<0.0 || l1+l2-l3-t<0.0 || l1-t-m1<0.0 || l2-t+m2 <0.0) continue;
						summation += pow(-1.0,t)/(SumPi(t)*SumPi(l3-l2+t+m1)*SumPi(l3-l1+t-m2)*SumPi(l1+l2-l3-t)*\
						SumPi(l1-t-m1)*SumPi(l2-t+m2));
						}
					diagonal = pow(-1.0,(double)(l1-l2-m3)) *\
					sqrt(SumPi(l1+l2-l3)*SumPi(l1-l2+l3)*SumPi(-l1+l2+l3)/SumPi(l1+l2+l3+1.0)) *\
					sqrt(SumPi(l1+m1)*SumPi(l1-m1)*SumPi(l2+m2)*SumPi(l2-m2)*SumPi(l3+m3)*SumPi(l3-m3)) *\
					summation;
					F4[(int)(m1+l1)][(int)(m2+l2)][(int)(m3+l3)] = diagonal;
				}
			}
		}
	}
	l1=l2=l3=6.0;
	for(m1=-l1;m1<l1+1.0;m1++){
		for(m2=-l2;m2<l2+1.0;m2++){
			for(m3=-l3;m3<l3+1.0;m3++){
				if(m1+m2+m3 == 0.0){
					summation = 0.0;
					for(t=0.0;t<=20.0;t+=1.0){
						if(l3-l2+t+m1<0.0 || l3-l1+t-m2<0.0 || l1+l2-l3-t<0.0 || l1-t-m1<0.0 || l2-t+m2 <0.0) continue;
						summation += pow(-1.0,t)/(SumPi(t)*SumPi(l3-l2+t+m1)*SumPi(l3-l1+t-m2)*SumPi(l1+l2-l3-t)*\
						SumPi(l1-t-m1)*SumPi(l2-t+m2));
					}
					diagonal = pow(-1.0,(double)(l1-l2-m3)) *\
					sqrt(SumPi(l1+l2-l3)*SumPi(l1-l2+l3)*SumPi(-l1+l2+l3)/SumPi(l1+l2+l3+1.0)) *\
					sqrt(SumPi(l1+m1)*SumPi(l1-m1)*SumPi(l2+m2)*SumPi(l2-m2)*SumPi(l3+m3)*SumPi(l3-m3)) *\
					summation;
					F6[(int)(m1+l1)][(int)(m2+l2)][(int)(m3+l3)] = diagonal;
				}
			}
		}
	}
}
/***********************************************************************************************************
***********************************************************************************************************/
double SumPi(double x){
	int i,j;
	if(x == 0.0){
		return 1.0;
	}
	j = (int)x;
	x = 1.0;
	for(i=1;i<=j;i++) x *= i;
	return x;
}
/***********************************************************************************************************
***********************************************************************************************************/
double *Array1st(int col){
	double *Name;
	Name = (double *)calloc(col,sizeof(double));
	return Name;
}
/***********************************************************************************************************
***********************************************************************************************************/
double **Array2nd(int col, int row){
	int i;
	double **Name;
	Name = (double **)calloc(col,sizeof(double *));
	for(i=0;i<col;i++)Name[i] = (double *)calloc(row,sizeof(double));
	return Name;
}
/***********************************************************************************************************
***********************************************************************************************************/
double ***Array3rd(int col, int row,int hight){
	int i,j;
	double ***Name;
	Name = (double ***)calloc(col,sizeof(double **));
	for(i=0;i<col;i++){
		Name[i] = (double **)calloc(row,sizeof(double *));
		for(j=0;j<row;j++) Name[i][j] = (double *)calloc(hight,sizeof(double));
	}
	return Name;
}
/***********************************************************************************************************
***********************************************************************************************************/

