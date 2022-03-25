#include<locale.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include<ctype.h> 
struct musteri {
	char isim[15];
	char soyisim[20];
	char adres[50];
	int musno,bakiye;
	unsigned long long int telno;
	
};
struct urun {
	char isim[20];
	int urunkodu,stok,fiyat;
};
main(){
	struct musteri *must;
	struct urun *ur;
	int mussayi=0,cvp=40,musno,urunsayi=0,urunno;
	must=(musteri*)calloc(mussayi,sizeof(musteri));
	ur=(urun*)calloc(urunsayi,sizeof(urun));
	bool kontrol2=false;
	short i,k,j,l;
	char isim[32];
	char *ptr;
	int cevap=0;
	setlocale(LC_ALL, "turkish");
	FILE *urunler;
	if((urunler=fopen("urunler.txt","r"))==NULL){printf("Bir �r�n kay�t dosyas� bulunamad��� i�in dosya olu�turuldu.\n");
		urunler=fopen("urunler.txt","w+");
	}
	else{
		urunler=fopen("urunler.txt","r+");
		fseek(urunler,0,SEEK_END);
		int sz=ftell(urunler)/sizeof(urun);
		ur=(urun*)realloc(ur,sz*sizeof(urun));
		urunsayi=0;
		fseek(urunler,0,SEEK_SET);
		while(urunsayi<sz){fread(&ur[urunsayi],sizeof(urun),1,urunler);
		urunsayi++;}
	}
	FILE *musteriler;
	if((musteriler=fopen("musteriler.txt","r"))==NULL){printf("Bir m��teri kay�t dosyas� bulunamad��� i�in dosya olu�turuldu.\n");
		musteriler=fopen("musteriler.txt","w+");
	}
	else{
		musteriler=fopen("musteriler.txt","r+");
		fseek(musteriler,0,SEEK_END);
		int sz=ftell(musteriler)/sizeof(musteri);
		must=(musteri*)realloc(must,sz*sizeof(musteri));
		mussayi=0;
		fseek(musteriler,0,SEEK_SET);
		while(mussayi<sz){fread(&must[mussayi],sizeof(musteri),1,musteriler);
		mussayi++;}
	}
	fclose(urunler);
	fclose(musteriler);
	while(cvp!=0){
	printf("Yapmak istedi�iniz i�lemi tu�lay�n�z.\n");
	printf("M��teri i�lemleri (d�zenleme,bakiye ekleme,listeleme,yeni kay�t,sipari�,arama) i�in 1\n");
	printf("�r�n i�lemleri (yeni kay�t, arama, g�ncelleme) i�in 2\n");
	printf("��k�� i�in 0\n");
	scanf("%d",&cvp);
	while(cvp==1 || cevap==1){
		printf("M��teri arama i�in 1\n");
		printf("T�m�n� listelemek i�in 2\n");
		printf("Yeni m��teri kayd� i�in 3\n");
		printf("M��teri kayd� g�ncellemek i�in 4\n");
		printf("M��teriye bakiye eklemek i�in 5\ngiriniz.\n");
		printf("Sipari� girmek i�in 6\ngiriniz.\n");
		scanf("%d",&j);
		getchar();
		if(j==1 && mussayi>0){
			int ara;
			printf("�simle arama yapmak i�in 1\n M��teri no ile arama yapmak i�in 2\tu�lay�n�z.\n");
			scanf("%d",&ara);
			getchar();
			if(ara==1){
				printf("M��teri ad� giriniz.\n");
				gets(isim);
				printf("\n");
				for(i=0;i<mussayi;i++){
					if(strstr(must[i].isim,isim)!=NULL){
						kontrol2=true;
						printf("%s %s %d %d %llu bu m��teriyi se�mek i�in %d ye bas�n\n",must[i].isim,must[i].adres,must[i].musno,must[i].bakiye,must[i].telno,i);
					}
				}
			}
			if(ara==2){
				printf("M��teri no giriniz.\n");
				scanf("%d",&musno);
				printf("\n");
				for(i=0;i<mussayi;i++){
					if(musno==must[i].musno){
						printf("%s %s %d %d %llu bu m��teriyi se�mek i�in %d ye bas�n\n",must[i].isim,must[i].adres,must[i].musno,must[i].bakiye,must[i].telno,i);
						kontrol2=true;
					}
				}
			}
			if(!kontrol2) printf("�stenen kriterlerde sonu� bulunamam��t�r.\n");
			kontrol2=false;
		}
		if(j==2 && mussayi>0){
			int i = 0;
			for (i = 0; i< mussayi; i++){
				printf ("�sim\t|Soyisim\t|Adres\t|Bakiye\t|No\t|Telefon\n");
				printf("%s %s %s %d %d %I64u\n",must[i].isim,must[i].soyisim,must[i].adres,must[i].bakiye,must[i].musno,must[i].telno);
		}
		}
		if(j==3){
			mussayi+=1;
			must=(musteri*)realloc(must,mussayi*sizeof(musteri));
			printf("M��teri ismi giriniz: ");
			gets(must[mussayi-1].isim);
			printf("M��teri soyismi giriniz: ");
			gets(must[mussayi-1].soyisim);
			printf("M��teri adres giriniz: ");
			gets(must[mussayi-1].adres);
			printf("M��teri bakiye giriniz: ");
			scanf("%d",&must[mussayi-1].bakiye);
			printf("M��teri no giriniz: ");
			scanf("%d",&must[mussayi-1].musno);
			printf("M��teri telefon no giriniz: ");
			scanf("%lld",&must[mussayi-1].telno);
			
		}
		
		if(j==4){
			printf("G�ncellemek istedi�iniz m��teri no'yu giriniz : ");
			char kelime[2];
			gets(kelime);
			musno=atoi(kelime);
			for (i = 0; i< mussayi; i++){
				if(must[i].musno==musno){
					printf("Yeni telefon numaras� giriniz : ");
					scanf("%lld",&must[i].telno);getchar();printf("\n");
					printf("Yeni adres giriniz : ");
					gets(must[i].adres);printf("\n");
					printf("%d nolu m��teri i�in\nYeni Adres : %s\nYeni Telefon no : %I64u\n",must[i].musno,must[i].adres,must[i].telno);
				}
			}	
		}
		if(j==5){
			printf("Bakiye eklemek istedi�iniz m��teri no'yu giriniz : ");
			char kelime[2];
			gets(kelime);
			musno=atoi(kelime);
			for (i = 0; i< mussayi; i++){
				if(must[i].musno==musno){
					printf("Bakiye giriniz: ");
					scanf("%d",&must[i].bakiye);
					printf("\n");
					printf("%d nolu m��teri i�in yeni bakiye : %d olarak de�i�tirilmi�tir.\n",must[i].musno,must[i].bakiye);
				}
			}
		}
		if(j==6){
			printf("Sipari� verilecek �r�n kodunu tu�lay�n�z : ");
			scanf("%d",&urunno);getchar();printf("\n");
			int arabalar=0;
			for(arabalar=0;arabalar<urunsayi;arabalar++){
				if(ur[arabalar].urunkodu==urunno){
					break;
				}
			}
			printf("Sipari� veren m��teri no tu�lay�n�z : ");
			scanf("%d",&musno);getchar();printf("\n");
			int arabalar2=0;
			for(arabalar2=0;arabalar2<urunsayi;arabalar2++){
				if(must[arabalar2].musno==musno){
					break;
				}
			}
			printf("�r�nden ka� tane sipari� edilecek : ");
			int urunmiktari;scanf("%d",&urunmiktari);getchar();printf("\n");
			if(must[arabalar2].bakiye>=(ur[arabalar].fiyat*urunmiktari) && (ur[arabalar].stok>=urunmiktari)){
				must[arabalar2].bakiye-=ur[arabalar].fiyat*urunmiktari;
				ur[arabalar].stok-=urunmiktari;
				printf("Sat�� tamamland�.\n");
				FILE *fatura;
				fatura=fopen("fatura.txt","w+");
				fprintf(fatura, "%s %s %s %d adet %d tl",must[arabalar2].isim,must[arabalar2].soyisim,ur[arabalar].isim,urunmiktari,ur[arabalar].fiyat);
				fclose(fatura);
				printf("Fatura dosyaya yaz�ld�.");
				
			}
			if(must[arabalar2].bakiye<(ur[arabalar].fiyat*urunmiktari))
			{
				printf("Yetersiz bakiye. ��leme devam edilemiyor.\n");
			}
			if(ur[arabalar].stok<urunmiktari){
				printf("Stokta bu �r�nden istenen miktarda yok.");		
			}
			
			
		}
		printf("Anamen�ye d�nmek i�in 0\nM��teri men�s�nde yeni i�lem yapmak i�in 1\ntu�lay�n�z.");
		scanf("%d",&cevap);
		printf("\n");
		cvp=-1;
	}
	while(cvp==2 || cevap==2){
		printf("�r�n ekleme i�in 1\n");
		printf("�r�n bilgileri g�ncelleme i�in 2\n");
		printf("�r�n arama i�in 3\ntu�lay�n�z.\n");
		scanf("%d",&l);
		getchar();
		if(l==1){
			urunsayi+=1;
			ur=(urun*)realloc(ur,urunsayi*sizeof(urun));
			printf("�r�m ismi giriniz: ");
			gets(ur[urunsayi-1].isim);
			printf("�r�n kodu giriniz: ");
			scanf("%d",&ur[urunsayi-1].urunkodu);
			printf("�r�n stok miktar� giriniz: ");
			scanf("%d",&ur[urunsayi-1].stok);
			printf("�r�n fiyat�n� giriniz: ");
			scanf("%d",&ur[urunsayi-1].fiyat);
		}
		if(l==2 && urunsayi>0){
			printf("G�ncellemek istedi�iniz �r�n kodunu giriniz : ");
			char kelime[2];
			gets(kelime);
			urunno=atoi(kelime);
			for (i = 0; i< urunsayi; i++){
				if(ur[i].urunkodu==urunno){
					printf("Yeni stok miktar� giriniz : ");
					scanf("%d",&ur[i].stok);getchar();printf("\n");
					printf("Yeni fiyat giriniz : ");
					scanf("%d",&ur[i].fiyat);getchar();printf("\n");
					printf("%d kodlu �r�n i�in\nYeni Stok : %d\nYeni Fiyat : %d\n",ur[i].urunkodu,ur[i].stok,ur[i].fiyat);
				}
			}
		}
		if(l==3 && urunsayi>0){
			int ara;
			printf("�simle arama yapmak i�in 1\n �r�n kodu ile arama yapmak i�in 2\ntu�lay�n�z.\n");
			scanf("%d",&ara);
			getchar();
			if(ara==1){
				printf("�r�n ad� giriniz.\n");
				gets(isim);
				printf("\n");
				for(i=0;i<urunsayi;i++){
					if(strstr(ur[i].isim,isim)!=NULL){
						kontrol2=true;
						printf("%s %d %d %d\n",ur[i].isim,ur[i].fiyat,ur[i].stok,ur[i].urunkodu);
					}
				}
			}
			if(ara==2){
				printf("Urun kodu giriniz.\n");
				scanf("%d",&urunno);
				printf("\n");
				for(i=0;i<urunsayi;i++){
					if(urunno==ur[i].urunkodu){
						printf("%s %d %d %d\n",ur[i].isim,ur[i].fiyat,ur[i].stok,ur[i].urunkodu);
						kontrol2=true;
					}
				}
			}
			if(!kontrol2) printf("�stenen kriterlerde sonu� bulunamam��t�r.\n");
			kontrol2=false;
		}
		printf("Anamen�ye d�nmek i�in 0\n�r�n men�s�nde yeni i�lem yapmak i�in 2\ntu�lay�n�z.");
		scanf("%d",&cevap);
		printf("\n");
		cvp=-1;
	}
	if(cvp==0){
		urunler=fopen("urunler.txt","r+");fseek(urunler,0,SEEK_SET);
		musteriler=fopen("musteriler.txt","r+");fseek(musteriler,0,SEEK_SET);
		for(int aney=0;aney<mussayi;aney++){
			fwrite(&must[aney],sizeof(musteri),1,musteriler);
		}
		for(int aney=0;aney<urunsayi;aney++){
			fwrite(&ur[aney],sizeof(urun),1,urunler);
		}
		printf("\nBizi tercih etti�iniz i�in te�ekk�rler.");
	}
}
}
