/*---------------------------------------------------------------------------
					Disk Kopyalama Program� Versiyon 1.00.0
  Tarih : 04/10/1999                            Program Yazar� : Hasan �zgan
---------------------------------------------------------------------------*/
#include "ozgan.c"

void ekran(void)
{
	int i, k;

	tampon = malloc(512 * 18);
	if (!tampon) {
		clrscr();
		printf("Yetersiz bellek\n");
		exit(1);
	}

	if ((fp = fopen("HATA.RPR", "w+")) == NULL) {
		clrscr();
		printf("Diskinizi Kontrol Edin\n");
		exit(1);
	}
	rewind(fp);
	fprintf(fp, "/*---------------------------------------------------------------------\n"
				"    Disk Kopyalama Program� v.1.00.0   Program Yazar� : Hasan �ZGAN    \n"
				"---------------------------------------------------------------------*/\n" );

	if ((TempFile = fopen("TempFile.$01", "w+b")) == NULL) {
		clrscr();
		printf("Diskinizi Kontrol Edin\n");
		exit(1);
	} // Burada bir sefere mahsus a��lm�� t�m globallar explorer();
	 // fonksiyonunda free hale getirilmi�tir.

	win_menu(sat, kol, 14, 44, MAVI_ | A_BEYAZ);
	win_menu(sat, (kol+44), 14, 35, MAVI_ | A_BEYAZ);
	for (i = 0; i < 14; i++)
		fillc((sat+1) + i, (kol+1), ' ', 43, BEYAZ_);
	for (i = 0; i < 13; i++)
		fillc((sat+2) + i, (kol+45), ' ', 34, BEYAZ_);
	tablo(0); // ��lemi kutucuklar� rengini ayarlar
	writens((sat-1), kol, " \x3d 1.44 D�SKET KOPYALAMA PROGRAMI (c) 1999         Program Yazar� : Hasan �ZGAN ", YESIL_ | A_BEYAZ);
	writens((sat+1), (kol+45),  "            M  E  N  �            ", KIRMIZI_ | A_BEYAZ);
	writens((sat+9), (kol+45), "        B   �   L   G   �         ", KIRMIZI_ | A_BEYAZ);
	fillc((sat+13), (kol+1), '�', 43, MAVI_ | A_BEYAZ);
	fillc((sat+8), (kol+45), '�', 34, MAVI_ | A_BEYAZ);
	writec(sat, (kol+44), '\xc2', MAVI_ | A_BEYAZ);
	writec((sat+15), (kol+44), '\xc1', MAVI_ | A_BEYAZ);
	writec((sat+13), kol, '\xc3', MAVI_ | A_BEYAZ);
	writec((sat+13), (kol+44), '\xb4', MAVI_ | A_BEYAZ);
	writec((sat+8), (kol+44), '\xc3', MAVI_ | A_BEYAZ);
	writec((sat+8), (kol+79), '\xb4', MAVI_ | A_BEYAZ);
	writens((sat+12), (kol+3), "[\xfe] -> Okuma", BEYAZ_ | A_KIRMIZI);
	writens((sat+12), (kol+17), "[\xfe] -> Yazma", BEYAZ_ | A_YESIL);
	writens((sat+12), (kol+31), "[\xfe] -> Hata", BEYAZ_ | A_MAVI);
	writens((sat+14), (kol+2), "Y�z:  0  �z:  00  ", BEYAZ_ | SIYAH);
	writens((sat+14), (kol+20), " Rapor_Dosyas�_HATA.RPR ", MAVI_ | SARI);
	bilgi(0);
	explorer();
}
void explorer(void)
{
	char tus;
	int sayac;
	char *menu[4] = { " O K U M A    � � L E M � ",
					  "  D � S K E    Y A Z M A  ",
					  "         B � L G �        ",
					  "       K  A  P  A  T      " };

	for (;;) {
		for (sayac = 0; sayac < 4; sayac++)
			writens((sat+3)+sayac, (kol+49), menu[sayac], BEYAZ_ | A_BEYAZ);
		switch (deger) {
			case 4 : deger = 0; break;
			case (-1) : deger = 3; break;
		}
		writens((sat+3)+deger, (kol+49), menu[deger], YESIL_ | A_BEYAZ);
		switch (tus = ok_tuslari()) {
			case '\x48' : deger--; break;
			case '\x50' : deger++; break;
			case '\x1b' : deger = 3; break;
		}
		if (tus == '\x0d')
			switch (deger) {
				case 0 : baslat(0); break; /* Okuma */
				case 1 : baslat(1); break; /* YAZMA */
				case 2 : bilgi(1); break; /* Yard�m alabilirsiniz. */
				case 3 : pos((sat+17), kol); fclose(TempFile); 	fclose(fp);
						 unlink("TempFile.$01"); free(tampon); exit(1);
			}
	}
}

void bilgi(int kontrol)
{
	int i, k = 0;
	char *yardim[19] = { "    Kullan�c�' n�n Dikkatine !    ",
						 " C ve Sistem Programc�lar� Derne�i",
						 "��rencisi oldu�um s�re i�inde �dev",
						 "olarak yapt���m bu program a�a��da",
						 "anlat�ld��� gibi �al���r.         ",
						 "                                  ",
						 " Program diski okuma ve yazma �ek-",
						 "linde �al���r. �sterseniz bir kere",
						 "okuyup istedi�iniz kadar diske    ",
						 " yazma yapabilirsiniz.            ",
						 "Program o kadar ak�ll� ki bozuk   ",
						 "disketi kopyalad���n�zda sa�lam   ",
						 "disketiniz de bozuk disket olur.  ",
						 " Program mailware versiyondur.    ",
						 "kullanan arkada�lardan sadece bana",
						 "bir te��ekk�r maili g�ndermesini  ",
						 "istiyorum.                        ",
						 "                 Hasan �ZGAN      ",
						 "           hasanozgan@hotmail.com " };
	if (kontrol == 0) {
		for (i = 0; i < 5; i++)
			writens((sat+10)+i, (kol+45), yardim[i], BEYAZ_ | GRI);
		return;
	}
	else
		for (;;) {
			switch (ok_tuslari()) {
				case '\x48' : k--; break;
				case '\x50' : k++; break;
				case '\x1b' : return;
			}
			switch (k) {
				case -1 : k = 0; break;
				case 15 : k = 14; break;
			}
			for (i = 0; i < 5; i++, k++)
				writens((sat+10)+i, (kol+45), yardim[k], BEYAZ_ | GRI);
			k -= 5;
		}
}

void tablo(int kontrol)
{
	int i, k;

	if (kontrol != 0)
		kontrol = 0x0c;

	for (i = 0, k = 0; i < 9; k+=2) {
		writec((sat+2) + i, (kol+4) + k, '\xfe', BEYAZ_ | (SIYAH + kontrol));
		if (k == 36) {
			k = -2; i++;
		}
	}
	fillc((sat+10), (kol+20), ' ', 21, BEYAZ_);
}
void baslat(int kontrol)
{
	int sayac, bakis;

	kafa = 0; iz = 0;

	if (kontrol == 0) { // O K U M A
		sayi = 0; tablo(0);
		for (iz = 0; iz < 80; ++iz)
			for (kafa = 0; kafa < 2; ++kafa) {
				for (sayac = 0; sayac < 3; sayac++) {
					bakis = biosdisk(2, 0, kafa, iz, 1, 18, tampon);
					if (!bakis)
						break;
				}
				if (bakis) {
					// printf("%02x", bakis); /* Hata kontrol */
					hata_gor(bakis);
				}
				else {
					fseek(TempFile, 512*18*sayi, SEEK_SET);
					fwrite(tampon, 512*18, 1, TempFile);
					hareket(0);
				}
			}
			test = 1;
		}
	else {   // Y A Z M A
		if (test == 0)
			hata_gor(1000);
		sayi = 0; tablo(1);
		for (iz = 0; iz < 80; iz++)
			for (kafa = 0; kafa < 2; kafa++) {
				fseek(TempFile, (512*18) * sayi, SEEK_SET);
				fread(tampon, 512*18, 1, TempFile);
				for (sayac = 0; sayac < 3; sayac++) {
					bakis = biosdisk(3, 0, kafa, iz, 1, 18, tampon);
					if (!bakis)
						break;
				}
				if (bakis) {
					// printf("%02x ", bakis); /* Hata kontrol */
					hata_gor(bakis);
				}
				else
					hareket(1);
			}
	}
	hata_gor(0);
}

void hareket(int hal)
{
	int bolum, kalan;
	char tampon[20];

	bolum = sayi / 19;
	kalan = sayi % 19;
	sayi++;

	sprintf(tampon, " Y�z:  %d  �z:  %02d  ", kafa, iz);
	writens((sat+14), (kol+1), tampon, BEYAZ_ | A_BEYAZ);

	switch(hal) {
		case 0 : /* OKUMA */
				  writec((sat+2)+bolum, (kol+4)+(2*kalan), '\xfe', BEYAZ_ | A_KIRMIZI); return;
		case 1 : /* YAZMA */ ;
				  writec((sat+2)+bolum, (kol+4)+(2*kalan), '\xfe', BEYAZ_ | A_YESIL); return;
		case 2 : /* HATA */ ;
				  writec((sat+2)+bolum, (kol+4)+(2*kalan), '\xfe', BEYAZ_ | A_MAVI); return;
	}
}

void hata_gor(int kontrol)
{
	int i;
	void *tampn = malloc(5 * 36 * 2);
	if (tampn == 0) {
		clrscr();
		printf("Yetersiz Bellek\n");
		exit(1);
	}

	switch (kontrol) {
		case 0x00 : gettext((kol+21), (sat+4), (kol+60), (sat+11), tampn);
					win_menu((sat+4), (kol+21), 5, 36, MAVI_ | A_BEYAZ);
					for (i = 0; i < 5; i++)
						fillc((sat+5)+i, (kol+22), ' ', 35, MAVI_);
					writens((sat+6), (kol+25), "! ��leminiz tamamlanm��t�r !", BEYAZ_ | A_BEYAZ);
					writens((sat+8), (kol+34), " T A M A M ", KIRMIZI_ | A_BEYAZ);
					getch(); puttext((kol+21), (sat+4), (kol+60), (sat+11), tampn);
					free(tampn); explorer();

		case 0x03 : gettext((kol+21), (sat+4), (kol+60), (sat+11), tampn);
					win_menu((sat+4), (kol+21), 5, 36, MAVI_ | A_BEYAZ);
					for (i = 0; i < 5; i++)
						fillc((sat+5)+i, (kol+22), ' ', 35, MAVI_);
					writens((sat+6), (kol+27), "Yazma korumas�n� kald�r�n", BEYAZ_ | A_BEYAZ);
					writens((sat+8), (kol+34), " T A M A M ", KIRMIZI_ | A_BEYAZ);
					getch(); puttext((kol+21), (sat+4), (kol+60), (sat+11), tampn);
					free(tampn); explorer();

		case 0x80 : gettext((kol+21), (sat+4), (kol+60), (sat+11), tampn);
					win_menu((sat+4), (kol+21), 5, 36, MAVI_ | A_BEYAZ);
					for (i = 0; i < 5; i++)
						fillc((sat+5)+i, (kol+22), ' ', 35, MAVI_);
					writens((sat+6), (kol+29), "S�r�c�ye disket tak�n", BEYAZ_ | A_BEYAZ);
					writens((sat+8), (kol+34), " T A M A M ", KIRMIZI_ | A_BEYAZ);
					getch(); puttext((kol+21), (sat+4), (kol+60), (sat+11), tampn);
					free(tampn); explorer();
		case 1000 : gettext((kol+21), (sat+4), (kol+60), (sat+11), tampn);
					win_menu((sat+4), (kol+21), 5, 36, MAVI_ | A_BEYAZ);
					for (i = 0; i < 5; i++)
						fillc((sat+5)+i, (kol+22), ' ', 35, MAVI_);
					writens((sat+6), (kol+27), "�nce okuma i�lemini yap�n", BEYAZ_ | A_BEYAZ);
					writens((sat+8), (kol+34), " T A M A M ", KIRMIZI_ | A_BEYAZ);
					getch(); puttext((kol+21), (sat+4), (kol+60), (sat+11), tampn);
					free(tampn); explorer();

		case 0x10 : // okunamayan kay�t
		case 0x02 : // ss i�areti bulunam�yor
		case 0x0a : // bozuk sekt�r
		case 0x0b : feof(fp); fprintf(fp, "Hata : Diskte %d. y�z, %02d. iz okunamad�\n", kafa, iz);
					free(tampn);
					hareket(2);   // bozuk iz
					fseek(TempFile, 512*18*sayi, SEEK_SET);
					memset(tampon, 0, (512*18));
					fwrite(tampon, (512*18), 1, TempFile);
					break;

		case 0x04 : // sekt�r bulunamad�
		case 0xcc : feof(fp); fprintf(fp, "Hata : Diske %d. y�z�n, %02d. izine yaz�lamad�\n", kafa, iz);
					free(tampn); hareket(2); break; // yazma hatas�
	}
}

void main(void)
{
	clrscr();
	ekran();
	getch();
}


