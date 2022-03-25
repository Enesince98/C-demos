#include <stdio.h>
#include <string.h>
#include<locale.h>
#include<ctype.h> 
#include <stdlib.h>
struct musteri {
	char isim[11];
	char soyisim[21];
	short hesapno;
	unsigned long long int telno;
	int bakiye;
};
static struct musteri mus;
bool sayimikontrol(char sayi[20],char a){
	bool kontrol=false;
	if (a=='c'){
	for(int i=0;i<strlen(sayi);i++){
		if(isdigit(sayi[i])) kontrol=true;
	}return kontrol;}
	else{
		for(int i=0;i<strlen(sayi);i++){
		if(!isdigit(sayi[i])) kontrol=true;
	}return kontrol;}
}
musterikayit(short hesno){
	mus.hesapno=hesno;
	printf("�smi giriniz : ");
	scanf("%s",mus.isim);
	bool kontrol=sayimikontrol(mus.isim,'c');
	while(strlen(mus.isim)>10 || kontrol){
		printf("�sim en fazla 10 karakter olmal�d�r. Do�ru isim girdi�inizden emin olun.\n");
		printf("�sim giriniz : ");
		scanf("%s",&mus.isim);
		kontrol=sayimikontrol(mus.isim,'c');
	}
	printf("Soyad�n� giriniz : ");
	scanf("%s",mus.soyisim);
	kontrol=sayimikontrol(mus.soyisim,'c');
	while(strlen(mus.soyisim)>20 || kontrol){
		printf("Soyad� en fazla 20 karakter olmal�d�r.Do�ru soyad� girdi�inizden emin olun.\n");
		printf("Soyad� giriniz : ");
		scanf("%s",mus.soyisim);
		kontrol = sayimikontrol(mus.soyisim,'c');
	}
	printf("Telefon no giriniz : ");
	if(scanf("%llu",&mus.telno)!=1){printf("Rakam yerine harf girdiniz i�lem iptal edildi.\n");mus.telno=0;return 0;}
	while(mus.telno < 1000000000 || mus.telno >=10000000000){
		printf("Telefon numaras�n� do�ru girdi�inizden emin olun.");
		printf("Telefon no giriniz : ");
		if(scanf("%llu",&mus.telno)!=1){printf("Rakam yerine harf girdiniz i�lem iptal edildi.\n");mus.telno=0;return 0;}	
	}
	printf("Bakiyeyi giriniz : ");
	if(scanf("%d",&mus.bakiye)!=1){printf("Rakam yerine harf girdiniz i�lem iptal edildi.\n");mus.bakiye=50001;return 0;}
	while(mus.bakiye < -50000 || mus.bakiye > 50000 || kontrol){
		printf("Bakiye -50000 ile 50000 aras�nda olmal�d�r.\n");
		printf("Bakiyeyi giriniz : ");
		if(scanf("%d",&mus.bakiye)!=1){printf("Rakam yerine harf girdiniz i�lem iptal edildi.\n");mus.bakiye=50001;return 0;}
	}
}
short hesapnokontrol(){
	printf("Hesap numaras�n� tu�lay�n�z : ");
	short hesno;
	char tel[4];
	scanf("%3s",tel);
	bool kontrol;
	if (strlen(tel)<=3){
		kontrol = sayimikontrol(tel,'s');
		if(!kontrol)
			hesno=atoi(tel);}
	else kontrol=true;
	tel[0]='\0';
	while(hesno < 1 || hesno > 100 || kontrol){
		printf("Hesap numaras� 1 ile 100 aras�nda olmal�d�r.\n");
		printf("Hesap numaras�n� tu�lay�n�z : ");
		scanf("%3s",tel);
		kontrol = sayimikontrol(tel,'s');
		if (strlen(tel)<=3){
			kontrol = sayimikontrol(tel,'s');
			if(!kontrol)
				hesno=atoi(tel);}
		else kontrol=true;
		tel[0]='\0';
	}
	return hesno;
}
main(){
	setlocale(LC_ALL, "turkish");

	char cvp='e';
	FILE *dosyam;
	if((dosyam=fopen("dosyam.dat","r"))==NULL){printf("Bir kay�t dosyas� bulunamad��� i�in dosya olu�turuldu.\n\n");
		dosyam=fopen("dosyam.dat","w");
		mus.hesapno = -1;
		for (short i=1;i<=100;i++)
			fwrite(&mus,sizeof(musteri),1,dosyam);
	}
	fclose(dosyam);
	printf("Yapmak istedi�iniz i�lemi tu�lay�n�z.\n");
	while(cvp=='e'||cvp=='E'){
	char k[1];
	printf("Yeni m��teri giri�i i�in 1\n");
	printf("M��teri bilgilerinde de�i�iklik i�in 2\n");
	printf("M��teriyi silmek i�in 3\n");
	printf("M��teri bilgilerini g�r�nt�lemek i�in 4\n");
	printf("M��teri bilgilerini dosyaya kaydetmek i�in 5\n");
	printf("Bor�/Kazan� bilgilerini dosyaya kaydetmek i�in 6\n");
	printf("\n��lem Se�iminizi yap�n : ");
	scanf(" %s",&k);
	if(strlen(k)>1 || (k[0] != '1' && k[0] != '2' && k[0] != '3' && k[0] != '4' && k[0] != '5' && k[0] != '6')){printf("Se�iminizi 1 ile 6 aras�nda bir say�y� tu�layarak yap�n�z.\n");cvp='e';continue;}
	
	if(k[0]=='1'){
		printf("\n---Yeni M��teri Kayd�---\n");
		dosyam = fopen("dosyam.dat","r+");
		short hesno = hesapnokontrol();
		fseek(dosyam,sizeof(musteri)*(hesno-1),SEEK_SET);
		fread(&mus,sizeof(musteri),1,dosyam);
		fseek(dosyam,sizeof(musteri)*(hesno-1),SEEK_SET);
		if (mus.hesapno == hesno) {printf("�stenen hesap numaras�nda zaten bir m��teri bulunmaktad�r.\n"); fclose(dosyam);cvp='e';continue;}
		musterikayit(hesno);
		fwrite(&mus,sizeof(musteri),1,dosyam);
		fclose(dosyam);
		printf("\n M��teri ba�ar�yla kaydedilmi�tir.\n");
	}
	
	if(k[0]=='2'){
		printf("\n---M��teri Bilgilerinde De�i�iklik---\n");
		dosyam = fopen("dosyam.dat","r+");
		short hesno = hesapnokontrol();
		fseek(dosyam,sizeof(musteri)*(hesno-1),SEEK_SET);
		fread(&mus,sizeof(musteri),1,dosyam);
		if (mus.hesapno == -1) {printf("�stenen hesap numaras�nda bir m��teri bulunmamaktad�r.\n"); fclose(dosyam);cvp='e';continue;}
		fseek(dosyam,sizeof(musteri)*(hesno-1),SEEK_SET);
		char tel[5];
		printf("Bakiyeyi giriniz : ");
		scanf("%s",&tel);
		bool negatif=false;
		if(tel[0]=='-') {negatif=true;tel[0]='0';}
		else negatif=false;
		bool kontrol = sayimikontrol(tel,'s');
		if (!kontrol && strlen(tel)<=5){if(negatif )mus.bakiye=-(atoi(tel));else mus.bakiye=atoi(tel); }
		else kontrol=true;
		while(mus.bakiye < -50000 || mus.bakiye > 50000 || kontrol){
			printf("Bakiye -50000 ile 50000 aras�nda olmal�d�r.\n");
			printf("Bakiyeyi giriniz : ");
			scanf("%s",&tel);
			if(tel[0]=='-') {negatif=true;tel[0]='0';}
			else negatif=false;
			kontrol = sayimikontrol(tel,'s');
			if (!kontrol && strlen(tel)<=5){if(negatif )mus.bakiye=-(atoi(tel));else mus.bakiye=atoi(tel); }
			else kontrol=true;
		}
		printf("\nBilgiler : %d - %d - %llu- %s - %s Olarak de�i�tirilmi�tir.\n",mus.hesapno,mus.bakiye,mus.telno,mus.isim,mus.soyisim);
		fwrite(&mus,sizeof(musteri),1,dosyam);
		fclose(dosyam);
	}
	if(k[0]=='3'){
	printf("\n---M��teri Silme---\n");
	dosyam = fopen("dosyam.dat","r+");
	short hesno = hesapnokontrol();
	fseek(dosyam,sizeof(musteri)*(hesno-1),SEEK_SET);
	fread(&mus,sizeof(musteri),1,dosyam);
	fseek(dosyam,sizeof(musteri)*(hesno-1),SEEK_SET);
	if (mus.hesapno == -1) {printf("�stenen hesap numaras�nda bir m��teri zaten bulunmamaktad�r.\n"); fclose(dosyam);cvp='e';continue;}
	struct musteri mussil;
	mussil.hesapno=-1;
	fwrite(&mussil,sizeof(musteri),1,dosyam);
	fclose(dosyam);
	printf("M��teri silme i�lemi ba�ar�yla ger�ekle�tirilmi�tir.\n");
}
	if(k[0]=='4'){
		printf("\n---M��teri Bilgileri G�rme---\n");
		dosyam = fopen("dosyam.dat","r");
		short hesno = hesapnokontrol();
		fseek(dosyam,sizeof(musteri)*(hesno-1),SEEK_SET);
		fread(&mus,sizeof(musteri),1,dosyam);
		if (mus.hesapno == -1) printf("�stenen hesap numaras�nda bir m��teri bulunmamaktad�r.\n");
		else printf("%d - %d - %llu- %s - %s\n",mus.hesapno,mus.bakiye,mus.telno,mus.isim,mus.soyisim);
		fclose(dosyam);
		printf("\n M��teri g�r�nt�lenmi�tir.\n");
	}
	if(k[0]=='5'){
		FILE *kayitdosyasi=fopen("kayitlar.txt","w");
		dosyam = fopen("dosyam.dat","r");
		fseek(dosyam,0,SEEK_SET);
		for(short i=0;i<100;i++){
			fread(&mus,sizeof(musteri),1,dosyam);
			if(mus.hesapno!=-1)
			fprintf(kayitdosyasi,"%d	%s	%s	%llu	%d\n",mus.hesapno,mus.isim,mus.soyisim,mus.telno,mus.bakiye);
		}
		fclose(dosyam);
		fclose(kayitdosyasi);
		printf("\n M��teri kay�tlar� ba�ar�yla dosyaya yaz�lm��t�r.");
	}
	if(k[0]=='6'){
		FILE *kayitdosyasi=fopen("gelirgider.txt","w");
		dosyam = fopen("dosyam.dat","r");
		fseek(dosyam,0,SEEK_SET);
		for(short i=0;i<100;i++){
			fread(&mus,sizeof(musteri),1,dosyam);
			if(mus.hesapno!=-1){
				if(mus.bakiye<0)
				fprintf(kayitdosyasi,"%d	%s	%s	%llu	BOR�LU\n",mus.hesapno,mus.isim,mus.soyisim,mus.telno);
				else
				fprintf(kayitdosyasi,"%d	%s	%s	%llu	ALACAKLI\n",mus.hesapno,mus.isim,mus.soyisim,mus.telno);
			}
		}
		fclose(dosyam);
		fclose(kayitdosyasi);
		printf("\n Ki�iler bor�lu ve alacakl� olarak dosyaya kaydedilmi�tir.\n");
	}
	printf("Devam etmek istiyorsan�z e'yi tu�lay�n�z : ");
	scanf("%*c",&cvp);

}
printf("Bizi tercih etti�iniz i�in te�ekk�r ederiz.");
}
