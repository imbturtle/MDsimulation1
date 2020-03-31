double *Array1st(int);
double **Array2nd(int, int);
double ***Array3rd(int, int, int);
void CalNb(int, int**, double**, double**, double*);
void CalAD(int, int **, double ***, double **, double *, double *);
void Reset(int, int **, double **);
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
void CalAD(int N, int **Nblist, double ***Angle, double **ArrR, double *L, double *Totalpair){
	int i, j, k, l, Number, Nearest=12;
	double Dij[3], Dik[3], Lij, Lik, Phi, Rad=180.0/M_PI, AdotB, AipB, Theta, Dtheta=0.5;
	for(i=0;i<N;i++){
		for(j=0;j<Nearest;j++){	//j top
			for(l=0;l<3;l++){
				Dij[l] =  ArrR[Nblist[i][j]][l] - ArrR[i][l];
				while(Dij[l] > L[l]) Dij[l] -= L[l]*2.0;
				while(Dij[l] <-L[l]) Dij[l] += L[l]*2.0;
			}
			Lij = sqrt(Dij[0] * Dij[0] + Dij[1] * Dij[1] + Dij[2] * Dij[2]);
			for(k=j+1;k<Nearest;k++){	//k top
				for(l=0;l<3;l++){
					Dik[l] =  ArrR[Nblist[i][k]][l] - ArrR[i][l];
					while(Dik[l] > L[l]) Dik[l] -= L[l]*2.0;
					while(Dik[l] <-L[l]) Dik[l] += L[l]*2.0;
				}
				Lik = sqrt(Dik[0] * Dik[0] + Dik[1] * Dik[1] + Dik[2] * Dik[2]);   
				Totalpair[0] += 1.0;
				AdotB = Dij[0] * Dik[0] + Dij[1] * Dik[1] + Dij[2] * Dik[2]; 
				AipB = Lij * Lik;
				Angle[i][j][k] = acos(AdotB/AipB) * Rad; // arccos(theta)= AdotB/A*B
//				printf("%lf\n",Theta);
//				l = (int)(Theta/Dtheta);
//				Angle[l]++;
			}//k tail
		}//j tail		
}}
/***********************************************************************************************************
***********************************************************************************************************/
void Reset(int N,int **Nblist,double **Nbdist){
	int i,j,m;
	for(i=0;i<N;i++)for(j=0;j<12;j++){
		Nbdist[i][j] = 99.0;
		Nblist[i][j] = 0;
}}
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

