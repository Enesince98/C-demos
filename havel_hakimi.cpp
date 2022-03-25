#include <stdio.h>  
#include<locale.h>   
static int b[11]; //girilen ��renci numaras� 11 basamakl� oldu�u i�in b�yle kabul edilmi�tir.  
/////////Do�rusal s�ralama algoritmas�////////////  
siralama(){  
    int temp;  
    for(int i=0;i<10;i++){  
        for(int k=i+1;k<11;k++){  
            if(b[i]<b[k]){  
                temp=b[k];   
                b[k]=b[i];  
                b[i]=temp;  
}}}}   
///////say�n�n tekli�ini kontrol ediyor/////////  
bool teklik(){  
    int top;  
    for(int i=0;i<11;i++)   
        top+=b[i];  
    if (top%2)   
        return true;  
    else   
        return false;  
}  
//////havel hakimi algoritmas�/////////////  
havelhakimi(){ int a=0; 
	if (teklik()) {
		printf("G graf� olu�turulamaz.");  // 3. ad�m
		return 0;
	}
	for (int p=0;p<11;p++){
		if(b[p]<0){
			printf("G graf� olu�turulamaz.");  //4. ad�m
			return 0;}
		if((b[p]==0) or (b[p]==1))             //5. ad�m
			a++;
	}
	if (a==11) {
		printf("G graf� olu�turulabilir");     //5. ad�m
		return 0;
	}
	siralama();				//6. ad�m
	int i=b[0];				//7. ad�m
	b[0]=0;  				//8. ad�m
	for (int k=1;k<=i;k++){  
        b[k]-=1;             //9. ad�m
	}	
	havelhakimi();  		//10. ad�m
}

main(){  
    setlocale(LC_ALL, "Turkish"); //t�rk�e karakter sorunu i�in  
    int sayac=0;  
    printf("Bir tamsay� giriniz.\n\n");  
    long long int k;  
    scanf("%I64u",&k);  
	if (k==1) {printf("G graf� olu�turulamaz."); return 0;}
	if (k==0) {printf("G graf� olu�turulabilir."); return 0;}
    printf("\n");  
    //say�n�n rakamlar�n�n diziye aktar�lmas�  //  
    while(k>0){                                //  
        b[sayac]=k%10;                         //  
        k/=10;                                 //  
        sayac++;                               //  
    }                                          //  
    //say�n�n rakamlar�n�n diziye aktar�lmas�  
    havelhakimi();  
}  
/*havelhakimi(){  
    int i=b[0];  
    bool c=false,d=true,e=true;  
    while(i>1){  
        b[0]=0;  
        for (int k=1;k<=i;k++){  
            b[k]-=1;  
            if(b[k]<0) {  
                c=true;break;  
            }  
        }  
        d=teklik();  
        if(d or c)   
            break;  
        siralama();  
        for (int k=0;k<11;k++) {  
            printf("%d  ",b[k]);          
            }         
        printf("\n-------\n");  
        i=b[0];  
    }  
    d=teklik();  
    if(c or d)   
        printf("G graf� olu�turulamaz.");  
    else   
        printf("G graf� olu�turulabilir.");  
} */ 
