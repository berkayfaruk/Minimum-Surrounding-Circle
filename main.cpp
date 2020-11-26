#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<graphics.h>
#include<string.h>

struct nokta                                       //STRUCT TANIMLAMALARIMIZ
{
    int X;
    int Y;
};

struct daire                                        //STRUCT TANIMLAMALARIMIZ
{
    struct nokta merkez;
};

int NoktaSayisiBulma()                              //  .TXT DE KI TOPLAM KAÇ KOORDINAT OLDUGUNU BULAN FONKSIYON
{
    FILE *dosya = fopen("noktalar.txt","r");        //  DOSYA OKUMA FORMATI
    if(dosya == NULL)
    {
        printf("Dosya Acilamadi");                  //  EGER DOSYADA HIC KOORDINAT YOK ISE HATA MESAJI VERIR.
        return -1;
    }

    char karakter[10];
    int satirSayisi=0;
    while((fgets(karakter,10,dosya)) != NULL)       //  .TXT 'NIN ILK SATIRINDAN - + , KARAKTERLERIYLE TOPLAMDA 10 KARAKTER OKUR.
    {
        satirSayisi++;                               //  BIR ALT SATIRA GECTIKCE SATIR SAYISINI ARTTIRIP TOPLAMDA KI KOORDINAT SAYISINI BULURUZ.
    }

    fclose(dosya);                                  //  DOSYA KAPATMA FONKSIYONU
    return satirSayisi;
}

int main()
{
    int gd=DETECT,gm;
    initgraph(&gd,&gm,(char*)"");                    //   GRAPHICS.H KÜTÜPHANESI YARDIMI ILE MASAÜSTÜNDE ARAYÜZÜN AÇILMASI
    initwindow(800,800," PROLAB ");                  //   800*800 PIKSEL ARAYÜZÜN AÇILMASI VE UYGULAMA ADININ VERILMESI

    int boyutu = getmaxx();                     //   KOORDINAT DÜZLEMINI ÇIZMEK IÇIN GEREKLI ARAYÜZ BOYUTUNUN ALINMASI
    int koordinatBoyutu = boyutu/2;             //   KOORDINAT DÜZLEMININ ARAYÜZÜN TAM ORTA NOKTASINDAN GEÇMESI
    int noktaSayisi = 0;

    noktaSayisi = NoktaSayisiBulma();                //  FONKSIYONDAN DÖNEN DEGERI ALMA

    struct nokta noktalar[noktaSayisi];              //  TANIMLANAN STRUCTAN DEGISKEN ÜRETME
    char karakter[10];
    int x = 0;

    FILE *dosya = fopen("noktalar.txt","r");         //  DOSYANIN AÇILIP OKUNMASI

    while((fgets(karakter,10,dosya)) != NULL)        //  DOSYANIN SONUNA KADAR GELIP NULL DEGERI DÖNENE KADAR OKUMA ISLEMI
    {
        noktalar[x].X = atoi(strtok(karakter,","));  //  ATOI VE STRTOK FONKSIYONLARI YARDIMI ILE X VE Y KOORDINATLARININ ALINMASI
        noktalar[x].Y = atoi(strtok(NULL,","));
        x++;
    }

    setcolor(GREEN);                                  // KOORDINAT DÜZLEMININ RENGINI YESIL YAPAN FONKSIYON
    line(getmaxx()/2, 0, getmaxx()/2, getmaxy());     // LINE FONKSIYONU YARDIMI ILE X DÜZLEMININ ÇIZILMESI
    line(0,getmaxy()/2,getmaxx(),getmaxy()/2);        // LINE FONKSIYONU YARDIMI ILE Y DÜZLEMININ ÇIZILMESI

    setcolor(YELLOW);                                 // DÜZLEMDE GÖSTERILECEK NOKTALARIN RENGININ SARI YAPILMASI

    for(int i=0; i<noktaSayisi; i++)                  // X VE Y DÜZLEMINDE DOSYADAN OKUNAN NOKTALARIN 5 PIKSEL YARIÇAPLI ÇEMBER OLARAK GÖSTERILMESI
    {
        circle(noktalar[i].X+koordinatBoyutu,koordinatBoyutu-noktalar[i].Y,5);
    }


    float toplamXkoordinati = 0,toplamYkoordinati = 0,merkezX = 0,merkezY = 0;  // EN DAR ÇEMBERI ÇIZMEMIZ IÇIN SART OLAN GEREKLI TANIMLAMALAR

    for(int i=0; i<noktaSayisi; i++)    // TÜM X VE Y KOORDINATLARININ TOPLANMASI
    {
        toplamXkoordinati = toplamXkoordinati + noktalar[i].X;
        toplamYkoordinati = toplamYkoordinati + noktalar[i].Y;
    }

    merkezX = toplamXkoordinati / noktaSayisi;      // MERKEZ X VE Y NOKTALARININ BULUNMASI IÇIN YAPILAN ISLEMLER
    merkezY = toplamYkoordinati / noktaSayisi;

    setcolor(GREEN);                                // MERKEZ NOKTAMIZIN RENGININ YESIL YAPILMASI
    circle(koordinatBoyutu+merkezX,koordinatBoyutu-merkezY,5);      //MERKEZ NOKTAMIZIN DÜZLEMDE GÖSTERILMESI

    //  ILK NOKTAMIZIN MERKEZ NOKTAMIZA OLAN UZAKLIGININ REFERANS OLARAK ALINMASI

    float noktalarArasiUzaklik = sqrt(pow(merkezX - noktalar[0].X,2) + pow(merkezY - noktalar[0].Y,2));


    int i=1;

    while(i<noktaSayisi)    // EN DAR ÇEMBERIMIZ MERKEZE EN UZAK ÇEMBERIMIZ OLACAÐI ICIN GEREKLI NOKTAYI ELDE ETMEMIZE YARAYAN ALGORITMA
    {
        float noktalarArasiUzaklik2 = sqrt(pow(merkezX - noktalar[i].X,2) + pow(merkezY - noktalar[i].Y,2));

        if(noktalarArasiUzaklik2 > noktalarArasiUzaklik)    // EGER ILK ALDIGIMIZ NOKTADAN DAHA UZAK BIR MESAFE GELIRSE GEREKLI ATAMANIN YAPILMASI
        {
            noktalarArasiUzaklik = noktalarArasiUzaklik2;
        }
        i++;
    }

    int tempX=0;
    int tempY=0;        // KOORDINAT DÜZLEMINE CIZDIRDIGIMIZ ÇEMBERLERIN ÜSTÜNDE DEGERLERININ GÖSTERILMESI ICIN OUTTEXTXY FONKSIYONUNU KULLANDIK -->
    char diziX[10];
    char diziY[10];     // --> ANCAK BU FONKSIYON CHAR TÜRÜNDE BIR DEGER ALDIGI ICIN ; INT TIPININ CHAR TIPINE DONUSTURULMESI GEREKIYOR

    setcolor(6);

    for(int i=0; i<noktaSayisi; i++)
    {
        tempX=noktalar[i].X;    // ILK X NOKTASININ GEREKLI DEGISKENE ATAMASININ YAPILMASI
        tempY=noktalar[i].Y;    // ILK Y NOKTASININ GEREKLI DEGISKENE ATAMASININ YAPILMASI
        itoa(tempX,diziX,10);   // ITOA FONKSIYONU YARDIMIYLA ILK X NOKTASININ CHAR TÜRÜNE ÇEVRILMESI
        itoa(tempY,diziY,10);   // ITOA FONKSIYONU YARDIMIYLA ILK Y NOKTASININ CHAR TÜRÜNE ÇEVRILMESI
        settextstyle(2,HORIZ_DIR,5);    // NOKTALARIN ÜZERINDE YAZI TIPININ DEGISTIRILMESINI SAGLAYAN FONKSIYON
        outtextxy(noktalar[i].X+koordinatBoyutu-15,koordinatBoyutu-noktalar[i].Y-15,diziX); // CHAR TIPINE ÇEVRILEN INT DEGERLERININ EKRANDA GÖSTERILMESI
        outtextxy(noktalar[i].X+koordinatBoyutu+5,koordinatBoyutu-noktalar[i].Y-15,diziY);  // CHAR TIPINE CEVRILEN INT DEGERLERININ EKRANDA GOSTERILMESI
        tempX=0;    // TANIMLANAN DEGISKENLERIN AYNI DEGERI GÖSTERMEMESI ICIN YAPILAN ATAMA
        tempY=0;    // TANIMLANAN DEGISKENLERIN AYNI DEGERI GÖSTERMEMESI ICIN YAPILAN ATAMA
    }

    char cmerkezX[10];      // ARAYÜZÜMÜZÜN SOL ÜST KÖSEDE MERKEZ VE YARIÇAP DEGERININ GOSTERILMESI ICIN GEREKEN INT TIPININ CHAR TIPINE DONUSTURULMESI
    char cmerkezY[10];
    char yaricap[10];

    settextstyle(6,HORIZ_DIR,2);    // YAZI TIPININ DEGISTIRILMESI
    itoa(merkezX,cmerkezX,10);
    itoa(merkezY,cmerkezY,10);
    outtextxy(20,20,"MERKEZ :");
    outtextxy(170,20,"(");
    outtextxy(190,20,cmerkezX);
    outtextxy(220,20,",");
    outtextxy(230,20,cmerkezY);
    outtextxy(270,20,")");
    itoa(noktalarArasiUzaklik,yaricap,10);
    outtextxy(20,50,"YARICAP :");
    outtextxy(200,50,yaricap);

    setcolor(RED);      // EN DAR CEMBERIMIZIN RENGININ KIRMIZI OLARAK YAPILMASI

    circle(koordinatBoyutu+merkezX,koordinatBoyutu-merkezY,noktalarArasiUzaklik);   // KOORDINAT DUZLEMINDE DIGER NOKTALARI KAPSAYAN EN DAR CEMBERIMIZIN CIZILMESI

    printf("Merkez : ( %.2f , %.2f )\n",merkezX,merkezY);   // ARAYÜZDE INT OLARAK GÖZÜKEN DEGERLERIN CONSOLE EKRANINDA KI NET FLOAT DEGERLERI
    printf("Yaricap : ( %.2f )\n",noktalarArasiUzaklik);

    setcolor(5);                        //  SPLINE RENGININ MOR OLARAK DEGISTIRILMESI
    for(int i=0; i<noktaSayisi; i++)    //  ILK KOORDINAT NOKTASINDAN BASLANARAK UCUCA EKLEME YONTEMIYLE SPLİNE'NIN CIZILMESI
    {
        if(i+1==noktaSayisi)            // DOSYANIN SONUNA GELINDIGI ZAMAN DONGUDEN CIKILMASI
            break;
        line(koordinatBoyutu+noktalar[i].X,koordinatBoyutu-noktalar[i].Y,koordinatBoyutu+noktalar[i+1].X,koordinatBoyutu-noktalar[i+1].Y); // SPLINE LARIN CIZDIRILMESI
    }

    getch();
    closegraph();

    system("pause");
}

