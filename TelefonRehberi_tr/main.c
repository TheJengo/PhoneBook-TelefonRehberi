#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <conio.h>
#include <string.h>
typedef struct{
    char isim[100];
    long int kod;
    long long int numara;
}Telephone;

char* DosyaOku(char*);
int KayitSay(char*);
int KayitKontrol(Telephone*);
void KayitEkle(char*,Telephone,int);
void KayitGuncelle(char*,Telephone[],int);
int KayitBul(char*,char[],int);
int KayitSil(char*,long int);
int NumaraBul(char*,long long int);

int MAX = 100;   // Telefon Rehberinizdeki Maximum kişi sayısını bu değişkeni değiştirerek değiştirebilirsiniz.
int main()
{
    setlocale(LC_ALL,"Turkish");
    Telephone Telephone,*pArr;
    pArr = &Telephone;

    printf("  TELEFON REHBERI v1.0\n************************\n");

    /* Kayit Sayisi Kontrolü*/
    int restriction = 0, kayitSayisi;
    kayitSayisi = KayitSay("TelefonRehber.txt");
    if(kayitSayisi >= MAX)
    {
        printf("Rehberiniz Doludur! Bu yüzden bazi islemleri kullaniminiz kisitlanmistir.\n");
        restriction = 1;
    }

    /* Menu */
    char sec;
    char isim[100];
    int countTry = 0, secim, duzenle = 0, sonuc;

    do{
        printf("\n1. Kayit Ekle\n2. Telefonlari Listele\n3. Kaydi Duzenle\n4. Numara ile Kayit Bul\n5. isim ile Kayit Bul\n6. Kayit Sil\n0. Cikis\n");
        printf("Secim : "); scanf("%d",&secim);
        switch(secim){

            /* Cikis Bolumu */
            case 0:
                exit(1);
                break;

            /* Kayit Ekleme */
            case 1:
                if(restriction == 0) //  Kisitlama Kontrolu
                {
                    system("CLS");
                    char isim[100];
                    printf("Kayit Ekleme Bolumune Hosgeldiniz!\n");
                    printf("Isim:"); scanf(" %s",isim);
                    strcpy(pArr->isim,isim);
                    printf("Alan Kodu:"); scanf("%d",&pArr->kod);
                    printf("Telefon:"); scanf("%lld",&pArr->numara);
                    /* Girdi Kontrol ve Ekleme */
                    if(KayitKontrol(pArr))
                    {
                        duzenle = 0;
                        KayitEkle("TelefonRehber.txt",*pArr,duzenle);
                    }
                    else{
                        printf("Kayit Ekleme Basarisiz!\n");
                    }
                }
                else{
                    system("CLS");
                    printf("\nRehberiniz dolu oldugunda bu bolume erisiminiz kisitlanmistir!\n");
                    countTry = 0;
                }
                break;

                /* Tum Kayitlari Listeleme */
            case 2:
                system("CLS");
                printf("Tum Kayitlar:\n\n");
                char *list;
                list = DosyaOku("TelefonRehber.txt");
                printf("%s",list);
                countTry = 0;
                break;

                /* Kayit Duzenleme */
            case 3:
                system("CLS");
                duzenle = 1;
                do{
                    printf("Kayit Duzenleme Bolumune Hosgeldiniz!\n");
                    printf("Kaydi Duzenlenecek kisi: "); scanf("%s",isim);
                    sonuc = KayitBul("TelefonRehber.txt",isim, duzenle);
                    if(!sonuc)
                    {
                        printf("Tekrar Arama Yapmak ister misiniz? (E / H)\n");
                        scanf(" %c",&sec);
                    }
                }while(sec == 'E');
                break;

                /* Numara ile Kayit Bulma */
            case 4:
                system("CLS");
                long long int numara;
                do{
                    printf("Numara ile Kayit Bulma Bolumune Hosgeldiniz!\n");
                    printf("Numara :"); scanf("%lld",&numara);
                    sonuc = NumaraBul("TelefonRehber.txt",numara);
                    if(!sonuc)
                    {
                        printf("Tekrar Arama Yapmak ister misiniz? (E / H)\n");
                        scanf(" %c",&sec);
                    }
                }while(sec == 'E');
                break;

                /* Isim ile Kayit Bulma */
            case 5:
                system("CLS");
                int sonuc;
                duzenle = 0;
                do{
                    printf("Isim ile Kayit Bulma Bolumune Hosgeldiniz!\n");
                    printf("Isim: "); scanf("%s",isim);
                    sonuc = KayitBul("TelefonRehber.txt",isim,duzenle);
                    if(!sonuc)
                    {
                        printf("Tekrar Arama Yapmak ister misiniz? (E / H)\n");
                        scanf(" %c",&sec);
                    }
                }while(sec == 'E');
                break;

                /* Kayit Silme */
            case 6:
                system("CLS");
                long int kod;
                do{
                    printf("Kayit Silme Bolumune Hosgeldiniz!\n");
                    printf("Alan Kodu:"); scanf("%ld",&kod);
                    sonuc = KayitSil("TelefonRehber.txt",kod);
                if(!sonuc)
                {
                    printf("Tekrar Arama Yapmak Ister misiniz? (E / H)\n");
                    scanf(" %c",&sec);
                }
                }while(sec == 'E');
                break;
            default:
                printf("Gecersiz secim islemi lutfen tekrar deneyiniz!\n");
                countTry++;
                break;
        }
    }while(countTry != 3);
}
char* DosyaOku(char *DosyaAdi)
{
    char *text = NULL;
    int i;
    FILE *fp = fopen(DosyaAdi,"r");
    if(fp != NULL)
    {
        /* imleci en sona götür. */
        fseek(fp,0,SEEK_END);

        /* imlecin bulundugu byte degerini al */
        text_size = ftell(fp);
        /* imleci en basa geri gönder */
        rewind(fp);

        /* imlecin bulundugu noktaya kadar boyut yarat */
        text = (char *) malloc(sizeof(char) * (text_size + 1));

        // For döngüsüyle ayni islemi döngü kullanmadan stdio.h kutuphanesinin kendi fonksiyonu ile yapar.
        fread(text,sizeof(char),text_size,fp);
    /* En Sevdigimiz "Actigin dosyayi kapat!" */
    fclose(fp);
    }
    else{
        printf("Dosya isleminde bir sorun yasandi!");
        exit(1);
    }
    return text;
}
void KayitEkle(char *DosyaAdi,Telephone Telefon,int duzenle)
{
    FILE *fp;
    Telephone *pArr;
    pArr = &Telefon;
    fp = fopen(DosyaAdi,"a");
    if(fp != NULL)
    {
        fprintf(fp,"Isim: %s\n",pArr->isim);
        fprintf(fp,"Kodu: %d\n",pArr->kod);
        fprintf(fp,"Telefon: %lld\n",pArr->numara);
        fclose(fp);
        if(duzenle == 0)
        {
            printf("Kayit Eklendi!\n\n");
        }
    }
    else{
        printf("Yazma islemi Basarisiz oldu!\n");
        exit(1);
    }
    fclose(fp);
}
int KayitBul(char *DosyaAdi,char isim[],int duzenle)
{
    /*
        Duzenle Parametresi isim ile kayit bulma ve kayit duzenleme bolumunde ayni fonksiyon kullanildigi icin cagirildigi yere gore tepki vermesi icindir.
    */
    FILE *fp;
    Telephone *pArr,Kisi[MAX];
    pArr = &Kisi;
    char nameTag[20],kodTag[20],noTag[20];
    fp = fopen(DosyaAdi,"r+");
    int kayitBulunan[MAX];
    int isEqual = 0,FlagOne = 0,i = 0,c = 0,kayitNo;
    if(fp != NULL)
    {
        while(!feof(fp))
        {
            fscanf(fp," %s %s ",nameTag,&(pArr+i)->isim);
            fscanf(fp," %s %ld ",kodTag,&(pArr+i)->kod);
            fscanf(fp," %s %lld ",noTag,&(pArr+i)->numara);
            isEqual = strncmp((pArr+i)->isim,isim,sizeof(isim));
            if(!isEqual)
             {
                 printf("\n%d. Kayit:\n%s %s\n%s %d\n%s %lld\n",i+1,nameTag,(pArr+i)->isim,kodTag,(pArr+i)->kod,noTag,(pArr+i)->numara);
                 kayitBulunan[c]=i;
                 c++;
                 FlagOne++;
             }
            i++;
        }
        if(FlagOne != 0)
        {
            fclose(fp);
            printf("\n%d Kayit bulundu.\n",FlagOne);
            if(duzenle == 1) // Eger Duzenleme Bolumunde Cagirilmissa fonksiyon duzenleme degeri 1 olarak gonderildigi icin bu blok calisir
            {
            int FlagTwo = 0;
            do{
                printf("Duzenlemek istediginiz kayit numarasi:");
                scanf("%d",&kayitNo);
                for(c=0;c<i;c++)
                {
                    // kayitNo ile listelenen kayitlar uyusuyorsa Kayit Duzenleme Fonksiyonu Cagiriliyor
                    if(kayitBulunan[c] == (kayitNo-1))
                    {
                        KayitGuncelle("TelefonRehber.txt",(pArr+kayitNo-1),kayitNo-1);
                        FlagTwo = 1;
                        break;
                    }
                }
                if(c==i)
                {
                    printf("\nGecersiz Kayit Numarasi!\n");
                }
            }while(FlagTwo == 0);

                return 1; // 1 dondurulurse Kayit Bulundugunda yapilacak islem sirasini takip etmesi icin Main fonksiyonuna yansitilir
            }
        }
        else{
            fclose(fp);
            printf("\nKayit Bulunamadi.\n");
            return 0; // 0 dondurulurse Kayit Bulundugunda yapilacak islem sirasini takip etmesi icin Main fonksiyonuna yansitilir
        }
    }
    else{
        printf("Okuma islemi basarisiz oldu!\n");
        exit(1);
    }
}
void KayitGuncelle(char *DosyaAdi,Telephone Telefon[],int kayitNo) //  kayitNo parametresi KayitBul fonksiyonunda gonderilen degerdir
{
    Telephone *pArr,updated;
    pArr = &Telefon[0];
    char isim[100];
    char nameTag[20],kodTag[20],noTag[20];
    printf("Isim:"); scanf(" %s",isim);
    strcpy(updated.isim,isim);
    printf("Alan Kodu:"); scanf("%ld",&updated.kod);
    printf("Telefon:"); scanf("%lld",&updated.numara);
    int i=0,guncelle = 1;
    if(KayitKontrol(pArr))  // Girilen girdilerin uygunlugu KayitKontrol Fonksiyonu ile kontrol ediliyor
    {
        FILE *fp_new;
        FILE *fp_old;
        if((fp_old = fopen(DosyaAdi,"r+")) == NULL)
        {
            printf("Dosya Acilamadi ! \n");
            exit(1);
        }
        if((fp_new = fopen("Yeni_Dosya.txt","wt")) == NULL)
        {
            printf("Dosya Acilamadi ! \n");
            exit(1);
        }
        while(!feof(fp_old)) // Tum Kayitlar diziye aliniyor
        {
                fscanf(fp_old," %s %s ",nameTag,&(pArr+i)->isim);
                fscanf(fp_old," %s %ld ",kodTag,&(pArr+i)->kod);
                fscanf(fp_old," %s %lld ",noTag,&(pArr+i)->numara);
                i++;
        }
        int c;
        for(c=0;c<i;c++) // Tum kayitlar duzenlenecek kayit disinda yeni klasore aktariliyor
        {
            if(c==kayitNo)
                continue;
            else{
                fprintf(fp_new,"Isim: %s\n",(pArr+c)->isim);
                fprintf(fp_new,"Kodu: %d\n",(pArr+c)->kod);
                fprintf(fp_new,"Telefon: %lld\n",(pArr+c)->numara);
            }
        }
        fclose(fp_new);
        fclose(fp_old);
        KayitEkle("Yeni_Dosya.txt",updated,guncelle); // guncellenecek deger yeni klasore yeni kayit gibi ekleniyor
        remove(DosyaAdi);
        rename("Yeni_Dosya.txt",DosyaAdi); // Yeni dosyamiza asil dosyamizin adini veriyoruz
        printf("Kayit Guncellendi!\n");
    }
    else{
        printf("Kayit Guncellenemedi!\n");
    }
}
int KayitKontrol(Telephone *pArr) // Girdi kontrol fonksiyonu
{
        int FlagOne = 0,FlagTwo = 0,FlagThree = 0;
        if(pArr->kod <= 200 || pArr->kod >= 500)
        {
            if(pArr->kod == 90)
            {
                FlagThree = 1;
                FlagOne = 0;
            }
            else{
                printf("Gecersiz Alan Kodu!\n");
                FlagOne = 1;
            }
        }
        if(FlagThree)
        {
            if(pArr->numara <= 5000000000 || pArr->numara >= 6000000000)
            {
                printf("Gecersiz Telefon Numarasi!\n");
                FlagTwo = 1;
            }
        }
        if(!FlagOne && !FlagTwo && FlagThree == 0)
        {
            if((pArr->numara <= 1000000 || pArr->numara >= 9999999) )
            {
                printf("Gecersiz Telefon Numarasi!\n");
                FlagTwo = 1;
            }
        }
        if(!FlagOne && !FlagTwo)
        {
            return 1;
        }
        else{
            return 0;
        }
}
int NumaraBul(char *DosyaAdi,long long numara) // Numara ile Kayit Bulma fonksiyonu
{
    FILE *fp;
    Telephone *pArr,Kisi[MAX];
    pArr = &Kisi;
    char nameTag[20],kodTag[20],noTag[20];
    fp = fopen(DosyaAdi,"r+");
    int FlagOne = 0,i = 0;
    if(fp != NULL)
    {
        while(!feof(fp))
        {
            fscanf(fp," %s %s ",nameTag,&(pArr+i)->isim);
            fscanf(fp," %s %ld ",kodTag,&(pArr+i)->kod);
            fscanf(fp," %s %lld ",noTag,&(pArr+i)->numara);
            if((pArr+i)->numara == numara)
            {
                printf("\n%d. Kayit:\n%s %s\n%s %d\n%s %lld\n",i+1,nameTag,(pArr+i)->isim,kodTag,(pArr+i)->kod,noTag,(pArr+i)->numara);
                FlagOne++;
            }
            i++;
            if(FlagOne != 0)
            {
                fclose(fp);
                printf("\n%d Kayit bulundu.\n",FlagOne);
                return 1;
            }
            else{
                fclose(fp);
                printf("\nKayit Bulunamadi.\n");
                return 0;
            }
        }
    }
    else{
        printf("Okuma islemi basarisiz oldu!\n");
        exit(1);
    }
}
int KayitSil(char *DosyaAdi,long int kod) //Kayit Sil Fonksiyonu
{
    FILE *fp_old;
    FILE *fp_new;
    Telephone *pArr,Kisi[MAX];
    pArr = &Kisi[0];
    char nameTag[20],kodTag[20],noTag[20];
    int i=0, FlagOne = 0,kayitNo,c=0;
    int kayitBulunan[MAX];
    if((fp_old = fopen(DosyaAdi,"r")) == NULL)
    {
        printf("Dosya Acilamadi ! \n");
    }
    if((fp_new = fopen("Yeni_Dosya.txt","wt")) == NULL)
    {
        printf("Dosya Acilamadi ! \n");
    }
    while(!feof(fp_old)) //Eski dosyadaki tüm veriler Struct dizimize alınıyor
    {
            fscanf(fp_old," %s %s ",nameTag,&(pArr+i)->isim);
            fscanf(fp_old," %s %ld ",kodTag,&(pArr+i)->kod);
            fscanf(fp_old," %s %lld ",noTag,&(pArr+i)->numara);
            if((pArr+i)->kod == kod)
            {
                printf("\n%d. Kayit:\n%s %s\n%s %ld\n%s %lld\n",i+1,nameTag,(pArr+i)->isim,kodTag,(pArr+i)->kod,noTag,(pArr+i)->numara);
                kayitBulunan[c]=i;
                FlagOne++;
                c++;
            }
            i++;
   }
   if(FlagOne != 0)
   {    int c;
        printf("\n%d Kayit bulundu.\n",FlagOne);
        int FlagTwo = 0;
        do{
            printf("Silmek istediginiz kayit numarasi:");
            scanf("%d",&kayitNo);
            for(c=0;c<i;c++)
            {
                // kayitNo ile listelenen kayitlar uyusuyorsa Kayit Duzenleme Fonksiyonu Cagiriliyor
                if(kayitBulunan[c] == (kayitNo-1))
                {
                    FlagTwo = 1;
                    break;
                }
            }
            if(c==i)
            {
                printf("\nGecersiz Kayit Numarasi!\n");
            }
        }while(FlagTwo == 0);
        for(c=0;c<i;c++) //Silenecek Kayit haric diger tum kayitlar yeni dosyaya aktariliyor
        {
            if(c != (kayitNo-1))
            {
                fprintf(fp_new,"Isim: %s\n",(pArr+c)->isim);
                fprintf(fp_new,"Kodu: %ld\n",(pArr+c)->kod);
                fprintf(fp_new,"Telefon: %lld\n",(pArr+c)->numara);
            }else{
                continue;
            }
        }
        printf("Kayit Silindi!\n");
        fclose(fp_new);
        fclose(fp_old);
        /* Dosya degisim islemleri */
        remove(DosyaAdi);
        rename("Yeni_Dosya.txt",DosyaAdi);
        return 1;
   }
   else{
        fclose(fp_new);
        fclose(fp_old);

        remove(DosyaAdi);
        rename("Yeni_Dosya.txt",DosyaAdi);
        printf("\nKayit Bulunamadi.\n");
        return 0;
   }
}
int KayitSay(char *DosyaAdi)// Dosyadaki Tum kayitlari sayan Fonksiyon ve sayisini donduren fonksiyon
{
    FILE *fp;
    fp = fopen(DosyaAdi,"r+");
    Telephone *pArr,Telephone;
    pArr = &Telephone;
    char nameTag[20],kodTag[20],noTag[20];
    int i=0;
    if(fp != NULL)
    {
        while(!feof(fp))
        {
            fscanf(fp," %s %s ",nameTag,&pArr->isim);
            fscanf(fp," %s %ld ",kodTag,&pArr->kod);
            fscanf(fp," %s %lld ",noTag,&pArr->numara);
            i++;
        }
        fclose(fp);
        return i;
    }
    else{
        printf("Dosya Bulunamadi!\n");
        exit(1);
    }
}
