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
	printf("Ýsmi giriniz : ");
	scanf("%s",mus.isim);
	bool kontrol=sayimikontrol(mus.isim,'c');
	while(strlen(mus.isim)>10 || kontrol){
		printf("Ýsim en fazla 10 karakter olmalýdýr. Doðru isim girdiðinizden emin olun.\n");
		printf("Ýsim giriniz : ");
		scanf("%s",&mus.isim);
		kontrol=sayimikontrol(mus.isim,'c');
	}
	printf("Soyadýný giriniz : ");
	scanf("%s",mus.soyisim);
	kontrol=sayimikontrol(mus.soyisim,'c');
	while(strlen(mus.soyisim)>20 || kontrol){
		printf("Soyadý en fazla 20 karakter olmalýdýr.Doðru soyadý girdiðinizden emin olun.\n");
		printf("Soyadý giriniz : ");
		scanf("%s",mus.soyisim);
		kontrol = sayimikontrol(mus.soyisim,'c');
	}
	printf("Telefon no giriniz : ");
	if(scanf("%llu",&mus.telno)!=1){printf("Rakam yerine harf girdiniz iþlem iptal edildi.\n");mus.telno=0;return 0;}
	while(mus.telno < 1000000000 || mus.telno >=10000000000){
		printf("Telefon numarasýný doðru girdiðinizden emin olun.");
		printf("Telefon no giriniz : ");
		if(scanf("%llu",&mus.telno)!=1){printf("Rakam yerine harf girdiniz iþlem iptal edildi.\n");mus.telno=0;return 0;}	
	}
	printf("Bakiyeyi giriniz : ");
	if(scanf("%d",&mus.bakiye)!=1){printf("Rakam yerine harf girdiniz iþlem iptal edildi.\n");mus.bakiye=50001;return 0;}
	while(mus.bakiye < -50000 || mus.bakiye > 50000 || kontrol){
		printf("Bakiye -50000 ile 50000 arasýnda olmalýdýr.\n");
		printf("Bakiyeyi giriniz : ");
		if(scanf("%d",&mus.bakiye)!=1){printf("Rakam yerine harf girdiniz iþlem iptal edildi.\n");mus.bakiye=50001;return 0;}
	}
}
short hesapnokontrol(){
	printf("Hesap numarasýný tuþlayýnýz : ");
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
		printf("Hesap numarasý 1 ile 100 arasýnda olmalýdýr.\n");
		printf("Hesap numarasýný tuþlayýnýz : ");
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
	if((dosyam=fopen("dosyam.dat","r"))==NULL){printf("Bir kayýt dosyasý bulunamadýðý için dosya oluþturuldu.\n\n");
		dosyam=fopen("dosyam.dat","w");
		mus.hesapno = -1;
		for (short i=1;i<=100;i++)
			fwrite(&mus,sizeof(musteri),1,dosyam);
	}
	fclose(dosyam);
	printf("Yapmak istediðiniz iþlemi tuþlayýnýz.\n");
	while(cvp=='e'||cvp=='E'){
	char k[1];
	printf("Yeni müþteri giriþi için 1\n");
	printf("Müþteri bilgilerinde deðiþiklik için 2\n");
	printf("Müþteriyi silmek için 3\n");
	printf("Müþteri bilgilerini görüntülemek için 4\n");
	printf("Müþteri bilgilerini dosyaya kaydetmek için 5\n");
	printf("Borç/Kazanç bilgilerini dosyaya kaydetmek için 6\n");
	printf("\nÝþlem Seçiminizi yapýn : ");
	scanf(" %s",&k);
	if(strlen(k)>1 || (k[0] != '1' && k[0] != '2' && k[0] != '3' && k[0] != '4' && k[0] != '5' && k[0] != '6')){printf("Seçiminizi 1 ile 6 arasýnda bir sayýyý tuþlayarak yapýnýz.\n");cvp='e';continue;}
	
	if(k[0]=='1'){
		printf("\n---Yeni Müþteri Kaydý---\n");
		dosyam = fopen("dosyam.dat","r+");
		short hesno = hesapnokontrol();
		fseek(dosyam,sizeof(musteri)*(hesno-1),SEEK_SET);
		fread(&mus,sizeof(musteri),1,dosyam);
		fseek(dosyam,sizeof(musteri)*(hesno-1),SEEK_SET);
		if (mus.hesapno == hesno) {printf("Ýstenen hesap numarasýnda zaten bir müþteri bulunmaktadýr.\n"); fclose(dosyam);cvp='e';continue;}
		musterikayit(hesno);
		fwrite(&mus,sizeof(musteri),1,dosyam);
		fclose(dosyam);
		printf("\n Müþteri baþarýyla kaydedilmiþtir.\n");
	}
	
	if(k[0]=='2'){
		printf("\n---Müþteri Bilgilerinde Deðiþiklik---\n");
		dosyam = fopen("dosyam.dat","r+");
		short hesno = hesapnokontrol();
		fseek(dosyam,sizeof(musteri)*(hesno-1),SEEK_SET);
		fread(&mus,sizeof(musteri),1,dosyam);
		if (mus.hesapno == -1) {printf("Ýstenen hesap numarasýnda bir müþteri bulunmamaktadýr.\n"); fclose(dosyam);cvp='e';continue;}
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
			printf("Bakiye -50000 ile 50000 arasýnda olmalýdýr.\n");
			printf("Bakiyeyi giriniz : ");
			scanf("%s",&tel);
			if(tel[0]=='-') {negatif=true;tel[0]='0';}
			else negatif=false;
			kontrol = sayimikontrol(tel,'s');
			if (!kontrol && strlen(tel)<=5){if(negatif )mus.bakiye=-(atoi(tel));else mus.bakiye=atoi(tel); }
			else kontrol=true;
		}
		printf("\nBilgiler : %d - %d - %llu- %s - %s Olarak deðiþtirilmiþtir.\n",mus.hesapno,mus.bakiye,mus.telno,mus.isim,mus.soyisim);
		fwrite(&mus,sizeof(musteri),1,dosyam);
		fclose(dosyam);
	}
	if(k[0]=='3'){
	printf("\n---Müþteri Silme---\n");
	dosyam = fopen("dosyam.dat","r+");
	short hesno = hesapnokontrol();
	fseek(dosyam,sizeof(musteri)*(hesno-1),SEEK_SET);
	fread(&mus,sizeof(musteri),1,dosyam);
	fseek(dosyam,sizeof(musteri)*(hesno-1),SEEK_SET);
	if (mus.hesapno == -1) {printf("Ýstenen hesap numarasýnda bir müþteri zaten bulunmamaktadýr.\n"); fclose(dosyam);cvp='e';continue;}
	struct musteri mussil;
	mussil.hesapno=-1;
	fwrite(&mussil,sizeof(musteri),1,dosyam);
	fclose(dosyam);
	printf("Müþteri silme iþlemi baþarýyla gerçekleþtirilmiþtir.\n");
}
	if(k[0]=='4'){
		printf("\n---Müþteri Bilgileri Görme---\n");
		dosyam = fopen("dosyam.dat","r");
		short hesno = hesapnokontrol();
		fseek(dosyam,sizeof(musteri)*(hesno-1),SEEK_SET);
		fread(&mus,sizeof(musteri),1,dosyam);
		if (mus.hesapno == -1) printf("Ýstenen hesap numarasýnda bir müþteri bulunmamaktadýr.\n");
		else printf("%d - %d - %llu- %s - %s\n",mus.hesapno,mus.bakiye,mus.telno,mus.isim,mus.soyisim);
		fclose(dosyam);
		printf("\n Müþteri görüntülenmiþtir.\n");
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
		printf("\n Müþteri kayýtlarý baþarýyla dosyaya yazýlmýþtýr.");
	}
	if(k[0]=='6'){
		FILE *kayitdosyasi=fopen("gelirgider.txt","w");
		dosyam = fopen("dosyam.dat","r");
		fseek(dosyam,0,SEEK_SET);
		for(short i=0;i<100;i++){
			fread(&mus,sizeof(musteri),1,dosyam);
			if(mus.hesapno!=-1){
				if(mus.bakiye<0)
				fprintf(kayitdosyasi,"%d	%s	%s	%llu	BORÇLU\n",mus.hesapno,mus.isim,mus.soyisim,mus.telno);
				else
				fprintf(kayitdosyasi,"%d	%s	%s	%llu	ALACAKLI\n",mus.hesapno,mus.isim,mus.soyisim,mus.telno);
			}
		}
		fclose(dosyam);
		fclose(kayitdosyasi);
		printf("\n Kiþiler borçlu ve alacaklý olarak dosyaya kaydedilmiþtir.\n");
	}
	printf("Devam etmek istiyorsanýz e'yi tuþlayýnýz : ");
	scanf("%*c",&cvp);

}
printf("Bizi tercih ettiðiniz için teþekkür ederiz.");
}
