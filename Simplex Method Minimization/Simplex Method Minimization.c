#include<stdio.h>
/*  Zmin = c1x1 + c2x2 + c3x3
  	a11x1 + a12x2 + a13x3 <= b1
  	a21x1 + a22x2 + a23x3 <= b2
  	a31x1 + a31x2 + a32x3 <= b3
	  
    Primal Simplex
*/
int findKey(float b[3], float key_column[3], float *pivot, int *key_row_no){
	int i,j,key_row_no1;
	int count=0;
	float ratio[2];
	float enkr;
	for( i=0; i<=2; i++ ){
			ratio[i] = b[i]/key_column[i];
			if (ratio[i] > 0){
				count++;
				if (count<=1){
					
					enkr = ratio[i]; 
					*pivot = key_column[i];
					*key_row_no = i;
					}
				
				if (ratio[i]<enkr){
					enkr = ratio[i];
					*pivot = key_column[i];
					*key_row_no = i;
				} 
			}
	}
}//pivot bulundu
	

//Z degerleri hesabi ve C-Z hesabi
int CalculateCZ(float tablo[3][6],int s1[3],int c[6],float key_column[3],int *key_column_no,float CZ1[6],float b[3])
{
	int i,j;
	int key_column_no1 = *key_column_no;
	float Z[6];
	float enk;
	for( i=0 ;i<=5 ;i++ ){
		Z[i]=0;
		for( j=0; j<=2; j++ ){
			
			Z[i] = Z[i] + s1[j] * tablo[j][i];
			
			}
	}
	for ( i=0; i<=5; i++ ){//C-Z degerleri ekrana yazildi, en kucuk deger bulundu
			CZ1[i] = c[i] - Z[i];
			//printf("\nC[%d]-Z[%d] degeri = %f\n", i+1, i+1, CZ1[i]);
		 	if( i == 0 ){
					enk = CZ1[0]; key_column_no1=0;
				}
			if ( CZ1[i] < enk ) {
					enk = CZ1[i];
					key_column_no1 = i;
			   }
	}
	s1[key_column_no1]= c[key_column_no1];
	
	if (enk < 0){//C-Zlerin en kucuk degerinin negatif olma durumu 
			printf("\nAnahtar sutun\n");
			for ( j=0; j<=2; j++ ){
			key_column[j] = tablo[j][key_column_no1];
			printf("%f\n", key_column[j]);
			 }	
		}
	
}
//Tablonun yeni elemanlarinin olusturulmasi
int NewTable(float New_key_row[6],float tablo[3][6],float b[3],float key_column[2],int *key_row_no){
	int i,j;
	int key_row_no1 = *key_row_no;
	
	switch(key_row_no1){//yeni satir sutün elemanlari hesabi
			
				case 0: 
						for( i=1; i<=2; i++ ){
							for ( j=0; j<=5; j++ ){
								tablo[i][j] = tablo[i][j]-( key_column[i] * New_key_row[j] );
						
							}
						b[i] = b[i] - ( b[key_row_no1] * key_column[i] );
						printf("\nb[%d]= %f\n", i+1, b[i]);
						}
						break;
						
						
				case 1:
						for( j=0; j<=5; j++){
							tablo[0][j] = tablo[0][j]-( key_column[0] * New_key_row[j] );
							tablo[2][j] = tablo[2][j]-( key_column[2] * New_key_row[j] );
					
						}	
						b[0] = b[0]-( b[key_row_no1] * key_column[0] );
						b[2] = b[2]-( b[key_row_no1] * key_column[2] );
						printf("\nb[%d]= %f\n", i, b[i]);
						break;
				
				case 2:
						for( i=0; i<=1; i++ ){
							for  ( j=0; j<=5; j++ ){
							tablo[i][j] = tablo[i][j] - ( key_column[i] * New_key_row[j] );
						
							}
						b[i] = b[i] - ( b[key_row_no1] * key_column[i] );
						printf("\nb[%d]= %f\n", i+1, b[i]);
						}
						break;
						
				
				
		}
	
}


int main() {
	int i,j,k,key_column_no,key_row_no,m;
	float enk,enkr,pivot;
	int count=0;// Ratiolarin pozitif degerleri
	int c[6];// Amac fonksiyonu degiskenleri kat sayisi
	int a[3][3];// Kisit fonksiyonlari degisken katsayilari
	float b[3];// Solution degerleri
	int s[3][3]={{1,0,0},{0,1,0},{0,0,1}};// Kisit fonksiyonlarina giren atik degiskenlerin katsayilari
	int s1[3]={0,0,0};// Amac fonksiyonundaki atik degisenlerin katsayilari
	float Z[6];//Z degerleri
	float CZ1[6]={-1,-1,-1,-1,-1,-1};// C-Z degerleri
	float ratio[3];// Solution degerlerinin pivot sutununa bolunmus degerleri
	float key_column[3];// Anahtar sutun
	float tablo[3][6];// Kisit fonksiyonlarinin katsayilari tek matriste
	float New_key_row[6];// Pivota bölünmüþ pivot sutunu
	
	printf("\nZmin = c1x1 + c2x2 + c3x3\n");
  	printf("\na11x1 + a12x2 + a13x3 <= b1\n");
  	printf("\na21x1 + a22x2 + a23x3 <= b2\n");
  	printf("\na31x1 + a31x2 + a32x3 <= b3\n");
  	printf("\n--Primal Simplex Method--\n");
	
  	printf("\nci degerlerini giriniz.\n");
	for( i=0; i<=5; i++ )
	  {
	  printf ("\nc[%d] degeri = ",i+1);
	  scanf("%d",&c[i]);
	  }
	  
	printf("\naij degerlerini giriniz.\n");  
	for( i=0; i<=2; i++ ){
		
			for(j=0; j<=2; j++ )
			{
				printf("\n a[%d][%d] degeri = ",i+1,j+1);
				scanf("%d",&a[i][j]);
			}
	}
	
	printf("\nbi degerlerini giriniz.\n");
	for( i=0; i<=2; i++ ){
		printf("\nb[%d] degeri = ",i+1);
		scanf("%f",&b[i]);
	}
	
	
	printf("\tx1\tx2\tx3\tS1\tS2\tS3\t\n\t");// kisit fonksiyonlari katsayilarinin tumu yeni matrise yerlestirildi
	for( k==0; k<=2; k++ ){
		for( m=0; m <=5; m++ ){
				for(j = 0; j <= 2; j++ ) {
        				for(i = 0; i <= 2; i++ ) { 
            					tablo[i][j] = a[i][j];
								tablo[i][j+3] = s[i][j];
								
						}
				}
		printf("%.f\t", tablo[k][m]);
		}
		printf("\n\t");
	}
	
	
	/*int countCZ=-1;  // islemlerin tekrari icin loop denemesi
		while( countCZ == -1 ){
		for(k=0;k<=5;k++){	
			printf("CZ[%d]=%f",i,CZ1[k]);
			if(CZ1[k] >= 0) countCZ++;
			if(countCZ == 5) {
				int Sol=0;
				printf("Optimal solution sartina ulasildi.");
				for(i=0;i<=2;i++){
				Sol = Sol+ b[i]*s1[i];
				}
			}
		}*/	
	CalculateCZ(tablo, s1, c, key_column,&key_column_no, CZ1,b);
			
	for(i=0;i<=2;i++){
		printf("\ns1[%d]=%d\n", i, s1[i]);
	}
	
	findKey(b, key_column, &pivot, &key_row_no);
	
	printf("\npivot=%f\n ", pivot);
	
	for ( i=0; i<=5; i++){// Anahtar sutun pivoya bolunup diziye aktarildi
		New_key_row[i] = tablo[key_row_no][i]/pivot;
		
	}
	b[key_row_no] = b[key_row_no]/pivot;
	
	printf("\nb[%d]=%f\n", key_row_no+1,b[key_row_no]);
	
	NewTable( New_key_row, tablo, b, key_column, &key_row_no);
	
	for (i=0;i<=2;i++){// Anahtar eleman bulunduktan sonra ikinci tablodaki elemanlar yerlestirildi
		for(j=0;j<=5;j++){
			tablo[key_row_no][j] = New_key_row[j];
			printf(" \ntablo[%d][%d]= %f\n",i+1,j+1,tablo[i][j]);
		}
		
	}
	
	
	return 0;
}

