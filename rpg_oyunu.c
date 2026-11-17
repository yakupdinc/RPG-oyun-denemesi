#include <stdio.h>   
#include <stdlib.h>  
#include <time.h>    
#include <string.h>  
#include <windows.h>
struct yetenek {
    char ad[30];
    int hasar;
    int manaBedeli;
};  
struct karakter {
    char ad[30];
    int can;
    int maxCan;
    int maxMana;
    int mana;
    struct yetenek yetenekler[3];
    int iksirSayisi;
};

void durumGoster (const struct karakter *k){
printf("Karakter Adi: %s\n", k->ad);
    printf("Can: %d/%d\n", k->can, k->maxCan);
    printf("Mana: %d/%d\n", k->mana, k->maxMana);
    printf("İksir Sayisi: %d\n", k->iksirSayisi);
    printf("Yetenekler:\n");
    for (int i = 0; i < 3; i++) {
        printf("  %s - Hasar: %d, Mana Bedeli: %d\n", k->yetenekler[i].ad, k->yetenekler[i].hasar, k->yetenekler[i].manaBedeli);
    }
}

void saldir (struct karakter *saldiran, struct karakter *hedef, int yetenekIndex){
if (yetenekIndex < 0 || yetenekIndex >= 3) {
        printf("Gecersiz yetenek indeksi!\n");
        return;
    }
    struct yetenek *yetenek = &saldiran->yetenekler[yetenekIndex];
    if (saldiran->mana < yetenek->manaBedeli) {
        printf("%s yeterli manaya sahip degil!\n", saldiran->ad);
        return;
    }
    saldiran->mana -= yetenek->manaBedeli;
    int bonusHasar = rand() % 6; // 0 ile 5 arasında rastgele bonus hasar
    yetenek->hasar += bonusHasar;
    hedef->can -= yetenek->hasar;
    if (hedef->can < 0) {
        hedef->can = 0;
    }
    printf("%s %s'ya %d hasar verdi! Kalan can: %d\n", saldiran->ad, hedef->ad, yetenek->hasar, hedef->can);
}

void iksirKullan (struct karakter *k){
    if (k->iksirSayisi > 0) {
        k->can += 20; // Örnek: İksir ile 20 can kazan
        if (k->can > k->maxCan) {
            k->can = k->maxCan;
        }
        k->iksirSayisi--;
        printf(">> %s iksir içti ve canını yeniledi!\n", k->ad);
    } else {
        printf(">> %s'in iksiri yok!\n", k->ad);
    }
}

int main() {
    srand(time(NULL));
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    struct karakter k1 = {"Kahraman", 100, 100, 50, 50, {{"Ateş Topu", 30, 10}, {"Buz Mızrağı", 20, 5}, {"Yıldırım", 25, 8}}, 3};
    struct karakter k2 = {"Düşman", 80, 80, 30, 30, {{"Kara Büyü", 15, 5}, {"Zehirli Ok", 10, 3}, {"Kılıç Darbesi", 20, 7}}, 2};
    int secim; 
    int tur = 1;

while (k1.can > 0 && k2.can > 0) {
   printf("\n================ TUR %d ================\n", tur);

    // 1. KAHRAMANIN SEÇİMİ
    for (int i = 0; i < 3; i++) {
        printf("%d. %s (Hasar: %d, Mana: %d)\n", 
               i + 1, k1.yetenekler[i].ad, 
               k1.yetenekler[i].hasar, 
               k1.yetenekler[i].manaBedeli);
    }
    printf("4. İksir İç (+30 Can) [Kalan: %d]\n", k1.iksirSayisi);
    printf("Hamleni seç: ");
    scanf("%d", &secim);

    printf("\n--- TUR OZETI ---\n");

    // 2. KAHRAMANIN HAMLESİ (saldir ve iksirKullan kendi mesajlarını basar)
    if (secim >= 1 && secim <= 3) {
        saldir(&k1, &k2, secim - 1);
    } else if (secim == 4) {
        iksirKullan(&k1);
    } else {
        printf(">> %s geçersiz bir hamle yaptı ve turunu boşa harcadı!\n", k1.ad);
    }

    // 3. DÜŞMANIN HAMLESİ (Eğer kahramanın darbesiyle ölmediyse)
    if (k2.can > 0) {
        if (k2.can < 35 && k2.iksirSayisi > 0) {
            iksirKullan(&k2);
        } else {
            int k2Secim = rand() % 3;
            saldir(&k2, &k1, k2Secim);
        }
    }

    // 4. HAMLELER SONRASI GÜNCEL DURUM (CURRENT STATUS)
    printf("\n--- GUNCEL DURUM ---\n");
    durumGoster(&k1);
    durumGoster(&k2);

    tur++;

}
printf("\n================ SAVAS BITTI ================\n");
if (k1.can > 0) {
    printf("TEBRIKLER! %s savasi kazandi!\n", k1.ad);
} else {
    printf("KAYBETTIN! %s yenildi...\n", k1.ad);
}
}