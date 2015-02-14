#include <allegro.h>
#include "znak.h"
#include "tablica.h"

void init();
void deinit();
//definiowanie sta³ych dotycz¹cych planszy tak aby mo¿na by³o je póŸniej ³atwo zmieniæ
#define POCZ_X 33
#define POCZ_Y 33
#define SZER_POLA 32
#define WYS_POLA 32

int main() {
    init();
//deklaracja wskaŸników do odpowiednich bitmap Allegro    
	BITMAP *plansza = NULL;
	BITMAP *kolko = NULL;
	BITMAP *krzyzyk = NULL;
	BITMAP *gracz_gracz = NULL;
	BITMAP *gracz_gracz_wci = NULL;
	BITMAP *gracz_cpu = NULL;
	BITMAP *gracz_cpu_wci = NULL;
	BITMAP *nowa = NULL;
	BITMAP *nowa_wci = NULL;
	BITMAP *koniec = NULL;
	BITMAP *koniec_wci = NULL;
	BITMAP *p_10 = NULL;
	BITMAP *p_12 = NULL;
	BITMAP *p_14 = NULL;
	BITMAP *kot = NULL;
	BITMAP *tlo = NULL;
	BITMAP *tlo1 = NULL;
	BITMAP *wygralx = NULL;
	BITMAP *wygralo = NULL;
	BITMAP *remis = NULL;
	BITMAP *bufor = NULL;
	
    //za³adowanie bitmap do pamiêci
    gracz_gracz = load_bmp("graczgracz.bmp",default_palette);
	gracz_gracz_wci = load_bmp("graczgracz_wci.bmp",default_palette);
	nowa = load_bmp("nowagra.bmp",default_palette);
	nowa_wci = load_bmp("nowagra_wci.bmp",default_palette);
	koniec = load_bmp("koniec.bmp",default_palette);
	koniec_wci = load_bmp("koniec_wci.bmp",default_palette);
	gracz_cpu = load_bmp("graczcpu.bmp",default_palette);
	gracz_cpu_wci = load_bmp("graczcpu_wci.bmp",default_palette);
    kolko = load_bmp("kolko.bmp",default_palette); 
    krzyzyk = load_bmp("krzyzyk.bmp",default_palette);
    kot = load_bmp("kot.bmp",default_palette);
    wygralx = load_bmp("wygralx.bmp",default_palette);
    wygralo = load_bmp("wygralo.bmp",default_palette);
    tlo =  load_bmp("tlo.bmp",default_palette);
    tlo1 =  load_bmp("tlo1.bmp",default_palette);
    p_10 = load_bmp("10.bmp",default_palette);
	p_12 = load_bmp("12.bmp",default_palette);
	p_14 = load_bmp("14.bmp",default_palette);
	remis = load_bmp("remis.bmp",default_palette);
	//stworzenie okna gry o rozmiarach 800x600
    bufor = create_bitmap(800,600);
    //wyœwietlenie bitmap jako screeny
    masked_blit(tlo1, screen, 0,0,0,0, tlo1->w, tlo1->h);
    masked_blit(p_10, screen, 0, 0, 360, 270, p_10->w, p_10->h);
    masked_blit(p_12, screen, 0, 0, 360, 300, p_12->w, p_12->h);
    masked_blit(p_14, screen, 0, 0, 360, 330, p_14->w, p_14->h);
    
    int rozmiar_planszy;
    
    while (true) {// pêtla odpowiedzialna za za³adowanie odpowiedniej planszy
        if (mouse_x >= 360 && mouse_x <= 360+p_10->w && mouse_y >= 270 && mouse_y <= 270+p_10->h && mouse_b != 0) {
            plansza = load_bmp("plansza10.bmp",default_palette);
            rozmiar_planszy = 10;
            break;
        }
        if (mouse_x >= 360&& mouse_x <= 360+p_10->w && mouse_y >= 300 && mouse_y <= 300+p_10->h && mouse_b != 0) {
            plansza = load_bmp("plansza12.bmp",default_palette);
            rozmiar_planszy = 12;
            break;
        }
        if (mouse_x >= 360&& mouse_x <= 360+p_10->w && mouse_y >= 330 && mouse_y <= 330+p_10->h && mouse_b != 0) {
            plansza = load_bmp("plansza14.bmp",default_palette);
            rozmiar_planszy = 14;
            break;
        }  
    }
    
    rest(100);
    
    Tablica tab;            //wywo³anie obiektu tab(naszej tablicy) typu Tablica
	int index_x, index_y;
    
    const int x_przycisku_nowa = plansza->w + 30,
	          y_przycisku_nowa = 20,
	          x_przycisku_g_g = plansza->w + 30,
	          y_przycisku_g_g = 50,
              x_przycisku_g_c = plansza->w + 30,
	          y_przycisku_g_c = 80,
              x_przycisku_koniec = plansza->w + 30,
	          y_przycisku_koniec = 110;
	          
    int ile_ruchow = 0;
    
	bool przycisk_g_g = true; //ustawienie przycisku gracz vs gracz na wciœniêty
    bool gracz_kolko = true;  //ustawienie gracza O jako rozpoczynaj¹cego
    bool cpu = false;         //CPU czeka na swój ruch
    bool blokuj = false;      //blokowanie wy³¹czone
  //wyœwietlenie bitmap za³adowanych do bufora pomocniczego  
    masked_blit(tlo, bufor, 0,0,0,0, tlo->w, tlo->h);
    masked_blit(plansza, bufor, 0,0,0,0, plansza->w, plansza->h);

	while (!key[KEY_ESC]) {// pêtla obs³uguj¹ca wyœwietlanie dzia³añ na przyciskach wciœniêcie wyciœniêcie itp.
        
        if (przycisk_g_g == true) {
            masked_blit(gracz_gracz_wci, bufor, 0, 0, x_przycisku_g_g, y_przycisku_g_g, gracz_gracz_wci->w, gracz_gracz_wci->h);
            masked_blit(gracz_cpu, bufor, 0, 0, x_przycisku_g_c, y_przycisku_g_c, gracz_cpu->w, gracz_cpu->h);
        }
        else {
            masked_blit(gracz_gracz, bufor, 0, 0, x_przycisku_g_g, y_przycisku_g_g, gracz_gracz->w, gracz_gracz->h);
            masked_blit(gracz_cpu_wci, bufor, 0, 0, x_przycisku_g_c, y_przycisku_g_c, gracz_cpu_wci->w, gracz_cpu_wci->h);
        }
        
        masked_blit(nowa, bufor, 0, 0, x_przycisku_nowa, y_przycisku_nowa, nowa->w, nowa->h);
        masked_blit(koniec, bufor, 0, 0, x_przycisku_koniec, y_przycisku_koniec, koniec->w, koniec->h);
        
/***************************** BLOK STEROWANIA MYSZK¥ NA PLANSZY ******************************/        
        if (mouse_b != 0) {         //instrukcja która zadba o to ¿e po klikniêciu w dowolnym miejscu jakiegoœ pola zostanie ustawiony w nim odpowiedni znak
            if (mouse_x < rozmiar_planszy * SZER_POLA + POCZ_X &&
                mouse_x > POCZ_X &&
                mouse_y < rozmiar_planszy * WYS_POLA + POCZ_Y &&
                mouse_y > POCZ_Y) {
                        
                index_x = (mouse_x - POCZ_X) / SZER_POLA;
                index_y = (mouse_y - POCZ_Y) / WYS_POLA;
                
                if (gracz_kolko == true) {   //ustawienie kó³ka
                    if (tab.sprawdz_znak(index_x, index_y) != 'O' && tab.sprawdz_znak(index_x, index_y) != 'X' && blokuj == false) { 
                        tab.postaw_znak(index_x, index_y, 'O');
                        ile_ruchow++;
                        if (tab.sprawdz_kto_wygral('O', 'X', rozmiar_planszy)) { //sprawdzenie czy gracz O wygra³
                            masked_blit(wygralo, bufor, 0,0,100,plansza->h+10, wygralo->w, wygralo->h);
                            
                            blokuj = true; //w³¹czenie blokowania 
                        }
                        masked_blit(kolko, bufor, 0,0, index_x * SZER_POLA + POCZ_X, index_y * WYS_POLA + POCZ_Y, kolko->w, kolko->h); //wyœwietlenie znaku na planszy
                        gracz_kolko = !gracz_kolko;            //zmiana graczy
                    }
                }
                else {
                    if (cpu == false) {  //ustawienie krzy¿yka   
                        if (tab.sprawdz_znak(index_x, index_y) != 'O' && tab.sprawdz_znak(index_x, index_y) != 'X' && blokuj == false) { 
                            tab.postaw_znak(index_x, index_y, 'X');
                            ile_ruchow++;
                            if (tab.sprawdz_kto_wygral('X', 'O', rozmiar_planszy)) { //sprawdzenie czy gracz X wygra³
                            masked_blit(wygralx, bufor, 0,0,100,plansza->h+10, wygralx->w, wygralx->h);
                               
                               blokuj = true;
                            }
                            masked_blit(krzyzyk, bufor, 0,0, index_x * SZER_POLA + POCZ_X, index_y * WYS_POLA + POCZ_Y, krzyzyk->w, krzyzyk->h);// wyœwietlenie X na planszy
                            gracz_kolko = !gracz_kolko;      //zmiana graczy
                        }               
                    }
       
                }
            }
            else {
/****************************** OBS£UGA PRZYCISKÓW ****************************/
                if ((mouse_x > x_przycisku_g_g) &&
                    (mouse_x < x_przycisku_g_g + gracz_gracz->w) &&
                    (mouse_y > y_przycisku_g_g) &&
                    (mouse_y < y_przycisku_g_g + gracz_gracz->h) &&   
                    (przycisk_g_g != true)) {
                        cpu = false;
                        przycisk_g_g = true;
                }
                if ((mouse_x > x_przycisku_g_c) &&
                    (mouse_x < x_przycisku_g_c + gracz_cpu->w) &&
                    (mouse_y > y_przycisku_g_c) &&
                    (mouse_y < y_przycisku_g_c + gracz_cpu->h) &&   
                    (przycisk_g_g == true)) {
                        cpu = true;
                        przycisk_g_g = false;
                }
                if ((mouse_x > x_przycisku_nowa) &&
                    (mouse_x < x_przycisku_nowa + nowa->w) &&
                    (mouse_y > y_przycisku_nowa) &&
                    (mouse_y < y_przycisku_nowa + nowa->h)) {
                        if (mouse_b != 0) {
                            while (mouse_b != 0) {
                                masked_blit(nowa_wci, bufor, 0, 0, x_przycisku_nowa, y_przycisku_nowa, nowa_wci->w, nowa_wci->h);
                                blit(bufor,screen,0,0,0,0,800,600);
                            }
                            bufor = create_bitmap(800,600);
                            masked_blit(tlo, bufor, 0,0,0,0, tlo->w, tlo->h);
                            masked_blit(plansza, bufor, 0,0,0,0, plansza->w, plansza->h);
                            gracz_kolko = true;
                            blokuj = false;
                            ile_ruchow = 0;
                            tab.wyczysc();   
                        }
                              
                        
                }
                if ((mouse_x > x_przycisku_koniec) &&
                    (mouse_x < x_przycisku_koniec + koniec->w) &&
                    (mouse_y > y_przycisku_koniec) &&
                    (mouse_y < y_przycisku_koniec + koniec->h)) {
                   
                        break;
                }               
            }          
        }
/*************************INSTRUKCJE INICJU¥CE RUCH KOMPUTERA*****************************************************/        
        if (cpu == true && gracz_kolko == false && blokuj == false) {
                        int x, y;
                        tab.zeruj_pri();           //zerowanie tablicy priorytetów
                        tab.ustaw_priorytet('X', 'O', rozmiar_planszy, 2.1); //ustawienie priorytetu jeœli s¹ dwa X
                        tab.ustaw_priorytet('O', 'X', rozmiar_planszy, 1.0); //ustawienie priorytetu jeœli mamy XOX
                        tab.szukaj_max(x, y, rozmiar_planszy);
                        tab.postaw_znak(x, y, 'X');
                        ile_ruchow++;
                        masked_blit(krzyzyk, bufor, 0,0, x * SZER_POLA + POCZ_X, y * WYS_POLA + POCZ_Y, krzyzyk->w, krzyzyk->h);
                        if (tab.sprawdz_kto_wygral('X', 'O', rozmiar_planszy)) {//sprawdzenie czy komputer wygra³
                            masked_blit(wygralx, bufor, 0,0,100,plansza->h+10, wygralx->w, wygralx->h);
                            masked_blit(kot, bufor, 0,0,(plansza->w - kot->w)/2,(plansza->h - kot->h)/2, kot->w, kot->h);
                            
                            blokuj = true;
                        }
                        gracz_kolko = !gracz_kolko;     
        }
        
        while (mouse_b) {
              rest(1);
        }
/**********************************************************************************************/        
        if (ile_ruchow == (rozmiar_planszy*rozmiar_planszy)) { //sprawdzenie czy zape³niono ca³¹ planszê znakami i nie ma wygranej (czy mamy remis)
               masked_blit(remis, bufor, 0,0,100,plansza->h+10, remis->w, remis->h);
        }
        blit(bufor,screen,0,0,0,0,800,600);
        clear_keybuf(); 
        rest(10);
}

	deinit();
	return 0;
}
END_OF_MAIN()

void init() {
	int depth, res;
	allegro_init();
	depth = desktop_color_depth();
	if (depth == 0) depth = 32;
	set_color_depth(depth);
	res = set_gfx_mode(GFX_AUTODETECT_WINDOWED, 800, 600, 0, 0);
	if (res != 0) {
		allegro_message(allegro_error);
		exit(-1);
	}

	install_timer();
	install_keyboard();
	install_mouse();
	enable_hardware_cursor();
    select_mouse_cursor(MOUSE_CURSOR_ALLEGRO);

    show_mouse(screen);
    unscare_mouse();
	/* add other initializations here */
}

void deinit() {
	clear_keybuf();
	/* add other deinitializations here */
}
