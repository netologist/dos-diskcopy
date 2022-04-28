/*----------------------------------------------------
	   ozgan.net Yazçlçm Sistemleri Ltd. ûti.
  --------------------------------------------------*/
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <dos.h>
#include <bios.h>
/* Karakter Renkleri */
#define SIYAH 0
#define MAVI 0x01
#define YESIL 0x02
#define CYAN 0x03
#define KIRMIZI 0x04
#define MAGENTA 0x05
#define KAHVE 0x06
#define BEYAZ 0x07
#define GRI 0x08
#define A_MAVI 0x09
#define A_YESIL 0x0a
#define A_CYAN 0x0b
#define A_KIRMIZI 0x0c
#define A_MAGENTA 0x0d
#define SARI 0x0e
#define A_BEYAZ 0x0f
/* Zemin Renkleri */
#define SIYAH_ 0x00
#define MAVI_ 0x10
#define YESIL_ 0x20
#define CYAN_ 0x30
#define KIRMIZI_ 0x40
#define MAGENTA_ 0x50
#define KAHVE_ 0x60
#define BEYAZ_ 0x70
#define BLINK_ 0x80

/* Fonksiyon Prototipleri */
void set_cursor_size(int min, int max);
void writec(int kolon, int satir, char karakter, int renk);
void fillc(int kolon, int satir, char karakter, int kac_tane, int renk);
void writens(int kolon, int satir, char *str, int renk);
void kayit(int sat, int kol, int uzunluk, int renk1, int renk2, char ch);
void pos(int row, int col);
void win_menu(int satir, int kolon, int menu_boyu, int menu_eni, int renk);
void set_cursor_size(int min, int max);
char ok_tuslari(void);
void tarih(void);
void ekran(void);
void explorer(void);
void hareket(int hal);
void tablo(int kontrol);
void bilgi(int kontrol);
void baslat(int kontrol);
void hata_gor(int kontrol);
/*------------------------*/

/* Global Tançmlamalar */
int sat = 5, kol = 0;
int kafa, iz;
int test = 0; // Okuma iüleminin yapçlçp yapçlmadçßçnç anlamak iáindir.
long sayi = 0; // hareket fonksiyonun iáindir
void *tampon;
int deger = 0; //MenÅ hareketlerini globalleütirmek iáindir.
FILE *TempFile, *fp;
