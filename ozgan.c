/*-----------------------------------------------------------------
				ozgan.net Yazçlçm Sistemleri Ltd. ûti.
  -----------------------------------------------------------------*/
#include "ozgan.h";

char far *vp = (char far*) 0xb8000000;

char *virgul(const char *adres)
{
	int i, k;
	char temp[80];
	char ters[80];

	memset(temp, 0, 80);
	strcpy(ters, adres);
	strrev(ters);
	for (i = 0, k = 0; i < strlen(adres); i++, k++) {
		temp[k] = ters[i];
		if (i == 2 || i == 5 || i == 8) {
			if (ters[i+1] != NULL) {
				k++; temp[k] = ',';
			}
			else
				k++;
		}
	}
	strrev(temp);
	return temp;
}

char *sifrele(char *string)
{
	int i;
	for (i = 0; i < strlen(string); i++)
		string[i] += 12;
	return string;
}

char *sifreac(char *string)
{
	int i;
	for (i = 0; i < strlen(string); i++)
		string[i] -= 12;
	return string;
}

char *turksay(int sat, int kol, int uzunluk, int renk1, int renk2,
	char sonlandirici, char *adress)
{
	int i = 0;
	char temp[80], ch, *p;

    pos(sat, kol);
	fillc(sat, kol - uzunluk, ' ', uzunluk, renk1);
	memset(temp, 0, 80);
	if (adress != NULL) {
        strcpy(temp, adress);
		p = virgul(temp);
		writens(sat, kol-strlen(p), p, renk1);
	}
	for (i = strlen(temp);;) {
		tarih();
		ch = getch();
		if (ch >= '0' && ch <= '9') {
			temp[i] = ch; i++;
		}
		if (temp[0] == '0') {
			temp[0] = NULL; i--;
		}
		switch (ch) {
			case '\x08' : if (i == -1)
							 i++;
						  i--; temp[i] = NULL;
						  break;
			case '\x0d' :  goto SON;
		}
		if (i == uzunluk-3)
			i--;
		if (i == (-1))
			i = 0;
		p = virgul(temp);
		fillc(sat, kol - uzunluk, ' ', uzunluk, renk1);
		writens(sat, kol-strlen(p), p, renk1);
		writec(sat, kol, sonlandirici, renk2);
	}
SON:
	p = virgul(temp);
	temp[uzunluk] = NULL;
	fillc(sat, kol - uzunluk, ' ', uzunluk, renk2);
	writens(sat, kol-strlen(p), p, renk2);
	return temp;
}


char *turkyaz(int sat, int kol, int uzunluk, int renk1, int renk2,
			char sonlandirici, char *adres)
{
	int i = 0;
	char ch, temp[80];

	memset(temp, 0, 78);
	fillc(sat, kol, ' ', uzunluk, renk1);
	if (adres != NULL) {
		writens(sat, kol, adres, renk1);
		strcpy(temp, adres);
	}
	for (;;) {
		tarih();
		ch = getch();
		if (ch == NULL)
			switch (ch = getch()) {
				case '\x4b' : i--;
                              if (i == -1)
								  i = 0;
							  pos(sat, kol + i);break;
				case '\x4d' : i++; pos(sat, kol + i); break;
			}
		else {
			switch (ch) {
				case '\t' : break;
				case '\x1b' : fillc(sat, kol, ' ', uzunluk, renk1);
							  i = 0; pos(sat, kol + i); break; /* ESC Tuüu */
				case '\x0d' : goto SON; 		          	/* ENTER tuüu */
				case '\x08' : i--;                      /*BACKSPACE Tuüu */
							  if (i == (-1))
								  i = 0;
							  temp[i] = NULL;
                              pos(sat, kol + i);
							  writens(sat, kol + i, "  ", renk1); break;
				default : pos(sat, kol + i);
						  writec(sat, kol + i, ch, renk1);
						  writec(sat, kol + uzunluk, sonlandirici, renk2);
						  temp[i] = ch; i++; break;
			}
		}
		if (i == uzunluk)
			i--;
		if (i == (-1))
			i = 0;
	}
SON:
	fillc(sat, kol, ' ', uzunluk, renk2);
	writens(sat, kol, temp, renk2);
	pos(24, 80);
	return temp;
}
void writens(int kolon, int satir, char *str, int renk)
{
	char far *scrp = vp;
	int k;

	scrp += kolon * 160 + satir * 2;
	for (k = 0; str[k] != '\0'; str++) {
		*scrp++ = str[k];
		*scrp++ = renk;
	}
}

void tarih(void)
{
}

void writec(int kolon, int satir, char karakter, int renk)
{
	char far *scrp = vp;
	int k;

	scrp += kolon * 160 + satir * 2;
	*scrp++ = karakter;
	*scrp = renk;
}

void fillc(int kolon, int satir, char karakter, int kac_tane, int renk)
{
	int k;
	char far *scrp = vp;

	scrp += kolon * 160 + satir * 2;
	for (k = 0; k < kac_tane; k++) {
		*scrp++ = karakter;
		*scrp++ = renk;
	}
}
void pos(int row, int col)
{
        union REGS regs;

        regs.h.ah = 2;
        regs.h.bh = 0;
        regs.h.dh = row;
        regs.h.dl = col;
        int86(0x10, &regs, &regs);
}

void win_menu(int satir, int kolon, int menu_boyu, int menu_eni, int renk)
{
        int j;

        writec(satir, kolon, '⁄',  renk);
        writec(satir, kolon + menu_eni, 'ø', renk);
        writec(satir + menu_boyu + 1, kolon, '¿', renk);
		writec(satir + menu_boyu + 1, kolon + menu_eni, 'Ÿ', renk);

        for (j = 1; j != menu_eni; j++) {
                writec(satir , kolon + j, 'ƒ', renk);
                writec(satir + menu_boyu + 1, kolon + j, 'ƒ', renk);
        }
        for (j = 1; j != menu_boyu + 1; j++) {
                writec(satir + j, kolon, '≥', renk);
                writec(satir + j, kolon + menu_eni, '≥', renk);
        }


}

char ok_tuslari(void)
{
        char ch = ' ';

        ch = getch();
		switch(ch) {
			case  0 : ch = getch();
				switch (ch) {
					case '\x48' : return ch;
					case '\x50' : return ch;
					case '\x4b' : return ch;
					case '\x4d' : return ch;
					case '\x23' : return ch; /* ALT + H */
					case '\x53' : return ch; /* DELETE */
				}
			case '\x1b' : return ch; /* ESC */
			case '\x13': return ch;
			case '\x0d': return ch;

	}
	return NULL;
}
void hata(int hata_kodu, char *dosya, char *yol)
{
	int i;
	char ch;
	char dizi[10];
	char *p;
	char *hatalar[] = { "             dosyasç bulunamadç",
						"Yetersiz Bellek                ",
						"Diske Yazma Hatasç             ",
						"Hatalç Yol                     ",
						"Bu kayçt Mevcut                ",
						"Bîyle bir kayçt bulunamadç     ",
						"Dosya Yaratçlamadç             ",
						"Aynç kartta bir áok kullançcç  " };
	char *onay[] = { "\x10Tamam\x11", "\x10Yardçm\x11"};

	p = malloc(100);
	if (p == NULL) {
		hata(1, 0, 0);
		exit(1);
	}
	gettext(20, 9, 63, 15, p);
	win_menu(9, 20, 4, 42, BEYAZ_ | A_BEYAZ);
	writens(9, 35, "=U Y A R I=", BEYAZ_ | A_BEYAZ);
	for (i = 0; i < 4; i++) {
		fillc(10 + i, 21, ' ', 41, BEYAZ_);
	}
	writens(10, 22, "K o d ->", BEYAZ_ | SIYAH);
	writens(11, 22, "Mesaj ->", BEYAZ_ | SIYAH);
	sprintf(dizi, "%02d", hata_kodu);
	writens(10, 31, dizi, BEYAZ_ | A_BEYAZ);
	writens(11, 31, hatalar[hata_kodu], BEYAZ_ | A_BEYAZ);
	writens(13, 30, " Tamam         Yardçm ", BEYAZ_ | SIYAH);
	switch (hata_kodu) {
		case 0 : writens(11, 31, dosya, BEYAZ_ | SARI); break;
		case 3 : writens(11, 42, yol, BEYAZ_ | SARI); break;
	}
	for (i = 0;;)  {
		switch (i) {
			case 2 : i = 0;
			case 0: writens(13, 30, " Tamam         Yardçm ", BEYAZ_ | SIYAH);
					writens(13, 30, onay[0], SIYAH_ | A_BEYAZ); break;
			case -1 : i = 1;
			case 1 : writens(13, 30, " Tamam         Yardçm ", BEYAZ_ | SIYAH);
					 writens(13, 44, onay[1], SIYAH_ | A_BEYAZ); break;
		}
		switch (ch = ok_tuslari()) {
			case '\x4b' : i--; break;
			case '\x4d' : i++; break;
		}

		if (ch == '\x0d') {
			puttext(20, 9, 63, 15, p); free(p);
			break;
		}
	}
}
