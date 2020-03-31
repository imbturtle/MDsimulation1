void RDF(int, double**, double *, double *);
double *Array1st(int);
double **Array2nd(int, int);
double ***Array3rd(int, int, int);
#define Pi M_PI

/***********************************************************************************************************
***********************************************************************************************************/
void RDF(int N, double **ArrR, double *L, double *g){
	int i, j, k, n;
	double Lij,Dij[3];
	extern double dr;
	for(i=0;i<N;i++){	
		for(j=i+1;j<N;j++){
			for(k=0;k<3;k++){
				Dij[k] = *(*(ArrR+j)+k) - *(*(ArrR+i)+k);
				while(Dij[k] >  L[k]) Dij[k] -= L[k]*2.0;
				while(Dij[k] < -L[k]) Dij[k] += L[k]*2.0;
			}
			Lij=sqrt(Dij[0]*Dij[0]+Dij[1]*Dij[1]+Dij[2]*Dij[2]);
/*			if(Lij<1.0){
				printf("%d %d %lf \n",i,j,Lij);
				printf("%lf %lf %lf \n",ArrR[i][0],ArrR[i][1],ArrR[i][2]);	
				printf("%lf %lf %lf \n",ArrR[j][0],ArrR[j][1],ArrR[j][2]);
			}	*/
			n = (int)(sqrt(Dij[0]*Dij[0]+Dij[1]*Dij[1]+Dij[2]*Dij[2])/dr);  
			g[n]++;
}}}
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
