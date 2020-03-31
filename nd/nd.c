void CalNb(int, int**, double**, double**, double*);
void CalNd(int, int **, double **, double **, double ***, double *);
void Reset(int, int **, double **);
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
void CalNd(int N, int **Nblist, double **ArrR, double **Nbdist, double ***Nd, double *L){
	int i, j, k, l,Nearest=12;
	double Djk[3],d0;
	for(i=0;i<N;i++){
		d0 = (Nbdist[i][0]+Nbdist[i][1]+Nbdist[i][2]+Nbdist[i][3]+Nbdist[i][4]+Nbdist[i][5])/6.0;
		for(j=0;j<Nearest;j++)for(k=j+1;k<Nearest;k++){
			for(l=0;l<3;l++){
				Djk[l]=ArrR[Nblist[i][k]][l]-ArrR[Nblist[i][j]][l];
				while(Djk[l] > L[l]) Djk[l] -= L[l]*2.0;
				while(Djk[l] <-L[l]) Djk[l] += L[l]*2.0;
			}
			Nd[i][j][k] = sqrt(Djk[0] * Djk[0] + Djk[1] * Djk[1] + Djk[2] * Djk[2])/d0 ;
}}}
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

