#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>


struct ogrenci {
    int ogrenciNo;
    char ogrenciAdi[20];
    char ogrenciSoyadi[20];
    int dersler[10];
};

struct ders {
    int dersNo;
    char dersAdi[20];
};

void dersEkle();  // ders ekleme fonksiyonu
void dersListesi();  // dersleri listeleme fonksiyonu
int dersKontrol(int dersNmbr); // dersin olup olmadiginin kontrolu

void ogrenciListesi(); // dersleri listeleme fonksiyonu
void ogrenciEkle();  // ogrenci ekleme fonksiyonu

void ogrenciyiDerseKaydet(int ogrenciNo); // ogrenciye ders ekleme fonksiyonu
void ogrenciDersleri(int ogrenciNo); // ogrenciye ait dersleri listeleme fonksiyonu
void dersiAlanOgrenciler(int dersKodu);  // dersi alan ogrencileri listeleme fonksiyonu

int main(){
    int islem;
    do{
        printf("\n####### \tMENU\t   #######\n\n");
        printf("1- Ogrenci ekle\n");
        printf("2- Ders ekle\n");
        printf("3- Ogrenciyi derse kaydet\n");
        printf("4- Ogrenci derslerini listele\n");
        printf("5- Dersi alan ogrencileri listele\n");
        printf("6- Cikis\n");
        printf("7- Ogrenci Listesi\n");
        printf("8- Ders Listesi\n\n");
        printf("Islem seciniz: ");
        scanf("%d",&islem);
        int ogrNmbr;
        switch(islem){
        case 1:
            ogrenciEkle();
            printf("\nMenuyu gitmek icin bir tusa basiniz.\n");
            getch();
            break;
        case 2:
            dersEkle();
            printf("\nMenuyu gitmek icin bir tusa basiniz.\n");
            getch();
            break;
        case 3:

            printf("Ogrenci Numarasi Giriniz :");
            scanf("%d",&ogrNmbr);
            ogrenciyiDerseKaydet(ogrNmbr);
            printf("\nMenuyu gitmek icin bir tusa basiniz.\n");
            getch();
            break;
        case 4:
            printf("Ogrenci Numarasi Giriniz :");
            scanf("%d",&ogrNmbr);
            ogrenciDersleri(ogrNmbr);
            printf("\nMenuyu gitmek icin bir tusa basiniz.\n");
            getch();
            break;
        case 5:
            printf("Ders Kodunu Giriniz :");
            scanf("%d",&ogrNmbr);
            dersiAlanOgrenciler(ogrNmbr);
            printf("\nMenuyu gitmek icin bir tusa basiniz.\n");
            getch();
            break;
        case 7:
            ogrenciListesi();
            printf("\nMenuyu gitmek icin bir tusa basiniz.\n");
            getch();
            break;
        case 8:
            dersListesi();
            printf("\nMenuyu gitmek icin bir tusa basiniz.\n");
            getch();
            break;
        case 6:
            printf("cikis basarili \n");
            break;
        default:
            printf("hatali kod tekrar deneyin. \n");
            break;
        }
    }
    while(islem!=6);
    return 1;
}


void ogrenciEkle(){
    FILE *ogrenciPtr;
    ogrenciPtr= fopen("ogrenci.bin","ab+"); // ekleme ve okuma yapýldý
    if(ogrenciPtr==NULL)
        printf("ogrenci.bin acilamadi. \n");

    int dersler[10] = {0};
    struct ogrenci ogrenciObj = {0, "", "",dersler};


    fseek(ogrenciPtr,(-1)*sizeof(struct ogrenci),SEEK_END); // kayýttaki son elemana ulasildi
    fread(&ogrenciObj,sizeof(struct ogrenci),1,ogrenciPtr);

    if(ogrenciObj.ogrenciNo==100) // ogrenci sayisi max 100 olarak belirlendi
        printf("Ogrenci sayisi maximuma ulasti. Daha fazla ogrenci ekleyemezsiniz.\n");
    else{
        printf( "ogrenci adi: " );
        scanf( "%s", &ogrenciObj.ogrenciAdi);
        printf( "ogrenci soyadi: " );
        scanf( "%s", &ogrenciObj.ogrenciSoyadi);
        ogrenciObj.ogrenciNo=ogrenciObj.ogrenciNo+1;
        int i=0;
        for(i=0;i<10;i++){
            ogrenciObj.dersler[i] = 0;   //dersler  default olarak 0 degeri aldi
         }

        fseek(ogrenciPtr,sizeof(struct ogrenci),SEEK_END);
        fwrite(&ogrenciObj,sizeof( struct ogrenci ), 1, ogrenciPtr );// yeni ogrenci sona eklendi
    }
    fclose(ogrenciPtr);
}

void dersEkle(){
    FILE *dersPtr;
    dersPtr= fopen("ders.bin","ab+");
    if(dersPtr==NULL)
        printf("ders.bin acilamadi. \n");

    struct ders dersObj = {0, ""};

    fseek(dersPtr,(-1)*sizeof(struct ders),SEEK_END);
    fread(&dersObj,sizeof(struct ders),1,dersPtr);

    if(dersObj.dersNo==20)  // ders sayýsý max 20 olarak ayarlandý
        printf("Ders sayisi maximuma ulasti. Daha fazla ders ekleyemezsiniz.\n");
    else{
        printf( "ders adi: " );
        scanf( "%s", &dersObj.dersAdi);
        dersObj.dersNo=dersObj.dersNo+1;
        fseek(dersPtr,sizeof(struct ders),SEEK_END); //imlec sona getirildi
        fwrite(&dersObj,sizeof( struct ders ), 1, dersPtr );// yeni ders sona eklendi
    }
    fclose(dersPtr);
}


void ogrenciListesi(){
    FILE *ogrenciPtr;
    ogrenciPtr= fopen("ogrenci.bin","ab+");
    if(ogrenciPtr==NULL)
        printf("ogrenci.bin acilamadi. \n");

    int dersler[10],i,j;
    struct ogrenci ogrenciObj = {0, "", "",dersler};
    ogrenciPtr= fopen("ogrenci.bin","ab+");
    fseek(ogrenciPtr,(-1)*sizeof(struct ogrenci),SEEK_END);
    fread(&ogrenciObj,sizeof(struct ogrenci),1,ogrenciPtr);
    int limit =ogrenciObj.ogrenciNo; // son ogrenciden alýnan numara sayac olarak kullanýldý
    for(i=0;i<limit;i++){
        fseek(ogrenciPtr,i*sizeof(struct ogrenci),SEEK_SET);
        fread(&ogrenciObj,sizeof(struct ogrenci),1,ogrenciPtr);
        printf("%d\t%20s %20s ",ogrenciObj.ogrenciNo,ogrenciObj.ogrenciAdi,ogrenciObj.ogrenciSoyadi);
        for(j=0;j<10;j++){
            if(ogrenciObj.dersler[j]>0)
                printf("%d ",ogrenciObj.dersler[j]);
        }
        printf("\n");

    }
    fclose(ogrenciPtr);
}



void dersListesi(){
    FILE *dersPtr;
    dersPtr= fopen("ders.bin","ab+");
    if(dersPtr==NULL)
        printf("ders.bin acilamadi. \n");

    int i;
    struct ders dersObj = {0, ""};

    fseek(dersPtr,(-1)*sizeof(struct ders),SEEK_END);
    fread(&dersObj,sizeof(struct ders),1,dersPtr);
    int limit =dersObj.dersNo;
    for(i=0;i<limit;i++){
        fseek(dersPtr,i*sizeof(struct ders),SEEK_SET);
        fread(&dersObj,sizeof(struct ders),1,dersPtr);
        printf("%d\t%20s\n",dersObj.dersNo,dersObj.dersAdi);
    }
    fclose(dersPtr);
}



void ogrenciyiDerseKaydet(int no){
    FILE *ogrenciPtr;
    int dersler[10]={0};
    int i,sayac=0,dersKodu,dersVarmi;
    struct ogrenci ogrenciObj = {0, "","",dersler};

    ogrenciPtr= fopen("ogrenci.bin","rb+");
    if(ogrenciPtr==NULL)
        printf("ogrenci.bin acilamadi. \n");

    fseek(ogrenciPtr,(no-1)*sizeof(struct ogrenci),SEEK_SET);

    fread(&ogrenciObj,sizeof(struct ogrenci),1,ogrenciPtr);
    if(ogrenciObj.ogrenciNo==0){
        printf("\nOgrenci Bulunamadi.\n");
    }

    else{
        printf("\n---Bulunan Ogrenci---\n%d\t%20s %20s",ogrenciObj.ogrenciNo,ogrenciObj.ogrenciAdi,ogrenciObj.ogrenciSoyadi);
        printf("\t dersler: ");

        for(i=0;i<10;i++){
            if(ogrenciObj.dersler[i]>0){
                printf("%d ",ogrenciObj.dersler[i]);
                sayac++;
            }
        }
        if(sayac == 0)
            printf("kayitli ders yok");

        printf("\n\nDers Kodunu Giriniz: ");
        scanf("%d",&dersKodu);
        dersVarmi = dersKontrol(dersKodu);
        if(dersVarmi==0)
            printf("Ders Bulunamadi.");
        else{
            sayac=1;
            for(i=0;i<11;i++){
                if(i==10){
                    printf("Bir ogrenciye 10 dan fazla ders ekleyemesiniz");
                    break;
                }
                if(dersKodu == ogrenciObj.dersler[i]){
                    printf("Bu ders zaten ogrencide kayitli");
                    break;
                }
                if(ogrenciObj.dersler[i]==0){
                    ogrenciObj.dersler[i] = dersKodu;
                    fseek(ogrenciPtr,(no-1)*sizeof(struct ogrenci),SEEK_SET);
                    fwrite(&ogrenciObj,sizeof( struct ogrenci ), 1, ogrenciPtr );
                    printf("\n%d kodlu ders %d numarali ogrenciye eklendi.\n",ogrenciObj.dersler[i],ogrenciObj.ogrenciNo);
                    sayac =0;
                    break;
                }
            }
        }
    }
    fclose(ogrenciPtr);
}



void ogrenciDersleri(int no){
    FILE *ogrenciPtr;
    FILE *dersPtr;
    int dersler[10]={0};
    int i,sayac,dersKodu,dersVarmi;
    struct ogrenci ogrenciObj = {0, "","",dersler};
    struct ders dersObj = {0, ""};

    ogrenciPtr= fopen("ogrenci.bin","rb+");
    if(ogrenciPtr==NULL)
        printf("ogrenci.bin acilamadi. \n");

    dersPtr= fopen("ders.bin","rb+");
    if(dersPtr==NULL)
        printf("ders.bin acilamadi. \n");

    fseek(ogrenciPtr,(no-1)*sizeof(struct ogrenci),SEEK_SET);
    fread(&ogrenciObj,sizeof(struct ogrenci),1,ogrenciPtr);
    if(ogrenciObj.ogrenciNo==0){
        printf("\nOgrenci Bulunamadi.\n");
    }
    else{
        printf("\n---Bulunan Ogrenci---\n%d\t%20s %20s\n",ogrenciObj.ogrenciNo,ogrenciObj.ogrenciAdi,ogrenciObj.ogrenciSoyadi);
        printf("## dersleri ## \n\n");

        for(i=0;i<10;i++){
            if(ogrenciObj.dersler[i]>0){
                sayac = ogrenciObj.dersler[i];
                fseek(dersPtr,(sayac-1)*sizeof(struct ders),SEEK_SET);
                fread(&dersObj,sizeof(struct ders),1,dersPtr);
                printf("Ders Kodu:\t%2d    |    Ders Adi:\t%s \n",dersObj.dersNo,dersObj.dersAdi);
            }
        }
    }
    fclose(ogrenciPtr);
}


void dersiAlanOgrenciler(int no){
    FILE *ogrenciPtr;
    FILE *dersPtr;
    int dersler[10]={0};
    int i,sayac,j,dersKodu,dersVarmi;
    struct ogrenci ogrenciObj = {0, "","",dersler};
    struct ders dersObj = {0, ""};

    ogrenciPtr= fopen("ogrenci.bin","rb+");
    if(ogrenciPtr==NULL)
        printf("ogrenci.bin acilamadi. \n");

    dersPtr= fopen("ders.bin","rb+");
    if(dersPtr==NULL)
        printf("ders.bin acilamadi. \n");

    fseek(dersPtr,(no-1)*sizeof(struct ders),SEEK_SET);
    fread(&dersObj,sizeof(struct ders),1,dersPtr);
    if(dersObj.dersNo==0){
        printf("\nDers Bulunamadi.\n");
    }
    else{
        printf("\n---Bulunan Ders---\n%d\t%20s \n",dersObj.dersNo,dersObj.dersAdi);
        printf("## dersi alan ogrenciler ## \n\n");

        fseek(ogrenciPtr,(-1)*sizeof(struct ogrenci),SEEK_END);
        fread(&ogrenciObj,sizeof(struct ogrenci),1,ogrenciPtr);
        int limit =ogrenciObj.ogrenciNo;
        for(i=0;i<limit;i++){
            fseek(ogrenciPtr,i*sizeof(struct ogrenci),SEEK_SET);
            fread(&ogrenciObj,sizeof(struct ogrenci),1,ogrenciPtr);

            for(j=0;j<10;j++){
                if(no==ogrenciObj.dersler[j]){
                     printf("%d\t%20s %20s \n",ogrenciObj.ogrenciNo,ogrenciObj.ogrenciAdi,ogrenciObj.ogrenciSoyadi);
                }
            }
        }
    }

    fclose(ogrenciPtr);
}


int dersKontrol(int dersNmbr){
    FILE *dersPtr2;
    struct ders dersObj = {0, ""};
    dersPtr2= fopen("ders.bin","ab+");
    if(dersPtr2==NULL)
        printf("ders.bin acilamadi. \n");
    fseek(dersPtr2,(dersNmbr-1)*sizeof(struct ders),SEEK_SET);

    fread(&dersObj,sizeof(struct ders),1,dersPtr2);
    int ders = dersObj.dersNo;
    fclose(dersPtr2);

    if(ders==0)
        return 0;
    return 10;
}
