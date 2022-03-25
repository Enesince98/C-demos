#include <stdio.h>  
#include<locale.h>   
static int b[11]; //girilen öðrenci numarasý 11 basamaklý olduðu için böyle kabul edilmiþtir.  
/////////Doðrusal sýralama algoritmasý////////////  
siralama(){  
    int temp;  
    for(int i=0;i<10;i++){  
        for(int k=i+1;k<11;k++){  
            if(b[i]<b[k]){  
                temp=b[k];   
                b[k]=b[i];  
                b[i]=temp;  
}}}}   
///////sayýnýn tekliðini kontrol ediyor/////////  
bool teklik(){  
    int top;  
    for(int i=0;i<11;i++)   
        top+=b[i];  
    if (top%2)   
        return true;  
    else   
        return false;  
}  
//////havel hakimi algoritmasý/////////////  
havelhakimi(){ int a=0; 
	if (teklik()) {
		printf("G grafý oluþturulamaz.");  // 3. adým
		return 0;
	}
	for (int p=0;p<11;p++){
		if(b[p]<0){
			printf("G grafý oluþturulamaz.");  //4. adým
			return 0;}
		if((b[p]==0) or (b[p]==1))             //5. adým
			a++;
	}
	if (a==11) {
		printf("G grafý oluþturulabilir");     //5. adým
		return 0;
	}
	siralama();				//6. adým
	int i=b[0];				//7. adým
	b[0]=0;  				//8. adým
	for (int k=1;k<=i;k++){  
        b[k]-=1;             //9. adým
	}	
	havelhakimi();  		//10. adým
}

main(){  
    setlocale(LC_ALL, "Turkish"); //türkçe karakter sorunu için  
    int sayac=0;  
    printf("Bir tamsayý giriniz.\n\n");  
    long long int k;  
    scanf("%I64u",&k);  
	if (k==1) {printf("G grafý oluþturulamaz."); return 0;}
	if (k==0) {printf("G grafý oluþturulabilir."); return 0;}
    printf("\n");  
    //sayýnýn rakamlarýnýn diziye aktarýlmasý  //  
    while(k>0){                                //  
        b[sayac]=k%10;                         //  
        k/=10;                                 //  
        sayac++;                               //  
    }                                          //  
    //sayýnýn rakamlarýnýn diziye aktarýlmasý  
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
        printf("G grafý oluþturulamaz.");  
    else   
        printf("G grafý oluþturulabilir.");  
} */ 
