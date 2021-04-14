/** @file */

#pragma once

/*!
\mainpage Dijkstra
\author Paulina Czapla [SSI] [INF] [SEM1] [GR4]
\date 14.01.2020
*/

#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include <iostream> 
#include <fstream>
#include "struktury.h"

using namespace std;

/** Funkcja do obs�ugi prze��cznik�w. Sprawdza liczb� argument�w (typu string) wprowadzonych z linii polece�. Je�li jest ich 7 to sprawdza, czy prze��czniki s� prawid�owe, 
czyli czy jest to -g -w i -o. Nast�pnie sprawdzane jest rozszerzenie plik�w (wywo�ana zostaje funkcja sprawdz_pliki) oraz poprawno�� 
otwierania si� plik�w (funkcja szukaj_drogi, kt�ra je�li warunki zostan� spe�nione, wykona ca�y program i zwr�ci true). W przypadku niespe�nienia warunk�w, funkcja zwraca false.
@param argc liczba argument�w
@param argv wska�nik na tablic� �a�cuch�w znakowych
@return true albo false, w zale�no�ci czy warunki zosta�y spe�nione.
*/
bool przelaczniki(int argc, char* argv[]);

/** Funkcja sprawdzaj�ca czy pliki s� tekstowe (czy maj� rozszerzenie .txt).
@param plik1 nazwa typu string pierwszego pliku
@param plik2 nazwa typu string drugiego pliku
@param plik3 nazwa typu string trzeciego pliku
@return je�li wszystkie pliki maj� rozszerzenie .txt, funkcja zwraca true, w przeciwnym wypadku zwraca false.
*/
bool sprawdz_pliki(string plik1, string plik2, string plik3);

/** Funkcja tworz�ca nowy w�ze� listy jednokierunkowej (sciezka). Lista ta przechowuje drog� (kolejne wierzcho�ki na drodze oraz odleg�o��
mi�dzy pierwszym a ostatnim wierzcho�kiem) mi�dzy danym wierzcho�kiem pocz�tkowym, a kolejnymi wierzcho�kami grafu.
@param wartosc warto��, kt�ra ma zosta� przypisana do p->wierzcholek
@param waga warto��, kt�ra ma zosta� przypisana p->waga
@return wska�nik na nowo dodany w�ze� listy.
*/
sciezka* dodaj_wezel(int wartosc, double waga);

/** Funkcja dodaj�ca na pocz�tek nowy w�ze� listy jednokierunkowej (sciezka). Nowo powsta�y w�ze�, staje si� g�ow� listy.
@param glowa wska�nik przekazany przez referancj� na pierwszy element listy
@param wartosc warto�� typu int, kt�ra zostaje przekazana do funkcji dodaj_wezel
@param waga warto�� typu double, kt�ra zostaje przekazana do funkcji dodaj_wezel
*/
void dodaj_wierzcholek(sciezka*& glowa, int wartosc, double waga);

/** Funkcja usuwaj�ca kolejno wszystkie elementy listy (�cie�ki).
@param glowa wska�nik przekazany przez referencj� na pierwszy element listy.
*/
void usun_liste_wierzcholkow(sciezka*& glowa);

/** Funkcja tworz�ca pierwszy w�ze� listy jednokierunkowej LZ (lista zewn�trzna listy list). Lista ta przechowuje numery wszystkich wierzcho�k�w w grafie
(bez powt�rze�), zmienn� odwiedzone, informuj�c� czy dany wierzcho�ek zosta� ju� odwiedzony podczas wykonywania algorytmu (pocz�tkowo false), zmienn� droga
przechowuj�c� najmniejsz� warto�� drogi do danego wierzcho�ka (pocz�tkowo ma warto�� niesko�czono��, czyli najwi�ksz� warto�� typu int) oraz wska�niki na nast�pny i poprzedni w�ze� listy,
poprzedni wierzcho�ek przy wyszukiwaniu �cie�ki oraz wska�nik na pierwszy element listy wewn�trznej LW. Do wszystkich wska�nik�w zostaje przypisany nullptr.
@param wartosc (wierzcholek grafu) warto��, kt�ra ma zosta� przypisana do p->pierwszy_wierzcholek
@return funkcja zwraca wska�nik na nowo dodany w�ze� listy.
*/
element_LZ* dodaj_elementLZ(int wartosc);

/** Funkcja dodaj�ca na koniec listy LZ nowy w�ze�.
@param glowa wska�nik przekazany przez referancj� na pierwszy element listy
@param wartosc liczba typu int (wierzcholek grafu), kt�ra ma zosta� przypisana do p->pierwszy_wierzcholek
*/
void dodaj_wezelLZ(element_LZ*& glowa, int wartosc);

/** Funkcja szukaj�ca w LZ (li�cie zewn�trznej listy list b�d�cej reprezentacj� grafu) podanego wierzcho�ka.
@param wartosc poszukiwany wierzcholek w li�cie
@param p wska�nik na pierwszy element listy
@return wska�nik na element listy, w kt�rej znajduje si� dany wierzcho�ek. Je�li w li�cie nie ma takiego wierzcho�ka, funkcja zwraca nullptr.
*/
element_LZ* znajdzLZ(int wartosc, element_LZ* p);

/** Funkcja tworz�ca nowy w�ze� listy jednokierunkowej (lista wewn�trzna listy list). Wpisuje do struktury podane warto�ci i zwraca wska�nik na nowo powsta�y w�ze� LW.
@param wartosc d�ugo�� kraw�dzi do danego wierzcho�ka
@param wezel numer wierzcho�ka
@return wska�nik na nowy w�ze� listy.
*/
element_LW* dodaj_elementLW(double wartosc, int wezel);

/** Funkcja dodaj�ca na koniec listy wewn�trznej nowy weze�. Sprawdza, czy wska�nik na element listy, podany jako parametr, wskazuje na ostatni element. Je�li nie,
to przesuwa wska�nik na nast�pny element listy, a� nie trafi na LW->nastepny==nullptr. Wtedy zostaje wywo�ana funkcja dodaj_elementLW z parametrami wartosc i wezel przekazanymi do funkcji.
@param LW wska�nik na w�ze� listy wewn�trznej podany przez referencj�
@param wierzcholek numer wierzcho�ka
@param wartosc d�ugo�� kraw�dzi do danego wierzcho�ka.
*/
void dodaj_wezelLW(element_LW*& LW, int wierzcholek, double wartosc);

/** Funkcja tworz�ca list� wewn�trzn� dla danego elementu listy zewn�trznej. Przypisuje adres na pierwszy element nowej listy wewn�trznej do LZ->polaczenie,
tworz�c tym samym po��czenie mi�dzy tymi dwoma listami. Je�li dla danego w�z�a listy zewn�trznej nie ma jeszcze listy wewn�trznej, wywo�ana zostaje funkcja dodaj_elementLW z parametrami waga i wierzcho�ek.
Je�li dla danego w�z�a istniej� ju� elementy listy, zostaje wywo�ana funkacja dodaj_wezelLW z parametrami el_LW, wierzcholek i waga.
@param LZ wska�nik na podany element listy zewn�trznej listy list (b�d�cej reprezentacj� grafu) przekazany przez referencj�
@param waga d�ugo�� kraw�dzi z wierzcho�ka, kt�rego numer przechowywany jest w LZ do podanego jako parametr wierzcho�ka
@param wierzcholek numer wierzcholka, do kt�rego prowadzi kraw�d�
@param skierowana true je�li kraw�d� mi�dzy wierzcho�kami jest skierowana (prowadzi tylko w jedn� stron�), false je�li jest nieskierowana (prowadzi w obie strony)
*/
void dodaj_polaczenie(element_LZ*& LZ, double waga, int wierzcholek, bool skierowana);

/** Funkcja usuwaj�ca graf, przedstawiony za pomoc� struktury listy listy. Dla ka�dego elementu listy zewn�trznej LZ, funkcja usuwa elementy po��czonej z ni� listy wewn�trznej LW (o ile istnieje), po czym po
przypisaniu do zmiennej tymczasowej wska�nika na nast�pny w�ze� LZ, zostaje usuni�ty dany w�ze� LZ, tak d�ugo a� lista zewn�trzna ma elementy.
@param poczatek wska�nik przekazany przez referancj� na pocz�tek listy zewn�trznej.
*/
void usun_graf(element_LZ*& poczatek);

/** Funkcja wczytuj�ca z podanego pliku graf do listy list (lista zewn�trzna (jej elementami jest struktura element_LZ), kt�rej ka�dy w�ze� wskazuje na list� wewn�trzn�
(jej elementami jest struktura element_LW). Je�li dane w pliku s� nieprawid�owe, funkcja zwraca nullptr. Je�li oczytany wierzcho�ek nie znajduje si� jeszcze w grafie, wywo�ana zostaje dla niego funkcja dodaj_elementLZ, 
w przeciwnym przypadku, wierzcho�ek jest wczytywany do istniej�cej listy LZ za pomoc� funkcji dodaj_wezelLZ. W zale�no�ci od tego, czy kraw�d� jest skierowana, wierzcho�ki s�siednie zostaj� wpisane do
listy wewn�trznej LW. Po��czenie mi�dzy list� zewn�trzn� a wewn�trzn� jest dodawane za pomoc� funkcji dodaj_polaczenie.
@param plik referencja na plik z grafem
@return wska�nik na pierwszy element listy zewn�trznej LZ. Je�li dane s� nieprawid�owe, zwraca nullptr.
*/
element_LZ* wczytaj_graf(ifstream& plik);

/** Funkcja czy�ci/resetuje dane na li�cie zewn�trznej po zastosowaniu algorytmu dijkstry.
@param p wska�nik na pocz�tek listy zewn�trznej LZ
*/
void wyczysc_dane(element_LZ* p);

/** Funkcja wykonuj�ca algorytm dijkstry, wyszukuje najkr�tsz� drog� z podanego wierzcho�ka do reszty wierzcho�k�w. Zostaje wywo�ana dla danego wierzcho�ka pocz�tkowego, kt�ry zostaje wyszukany w li�cie LZ.
Pocz�tkowo w li�cie LZ warto�� drogi do wierzcho�ka pocz�tkowego jest r�wna zero, natomiast do reszty wierzcho�k�w jest r�wna maksymalnej warto�ci zmiennej typu int ("nieskonczonosc"). 
Nast�pnie sprawdzany jest pierwszy element listy LW, wierzcho�ek zostaje wyszukany w li�cie LZ i odleg�o�� z wierzcho�ka pocz�tkowego zostaje przypisana do element_LZ->droga, a wska�nik na wierzcho�ek poprzedni
(czyli wierzcho�ek pocz�tkowy) zostaje przypisany do element_LZ->poprzedni_wierzcho�ek. Element_LZ-> odwiedzone zostaje zmieniony na true. W nast�pnej kolejno�ci, wywo�ana
zostaje dla tego wierzcho�ka rekurencyjnie funkcja dijkstra. Przed przypisaniem warto�ci do element_LZ->droga zostaje sprawdzone, czy warto�� ju� tam zapisana nie jest niesko�czono�ci�, b�d� czy nie jest wi�ksza 
od nowej. Je�li tak, warto�� zostaje przypisana. Funkcja dijkstra jest wywo�ywana rekurencyjnie tylko dla wierzcho�k�w, kt�re nie zosta�y jeszcze odwiedzone, b�d� kt�rych droga zosta�a zmieniona.
Algorytm wykonuje si�, a� najkr�tsze �cie�ki z danego wierzcho�ka pocz�tkowego do reszty wierzcho�k�w zostan� odnalezione.
@param tmp_wierzcholek wska�nik na wierzcho�ek pocz�tkowy przekazany przez referencj�
@param numer numer wierzcho�ka pocz�tkowego
@param glowa wska�nik na w�ze� pocz�tkowy listy zewn�trznej LZ
*/
void dijkstra(element_LZ*& tmp_wierzcholek, int numer, element_LZ* glowa);

/** Funkcja otwiera plik z grafem i wywo�uje funkcj� wczytaj_graf oraz otwiera plik z wierzcho�kami pocz�tkowymi, odczytuje ka�dy wierzcho�ek i je�li istnieje on w grafie to wywo�uje funkcje dijkstra i wczytaj_sciezke.
Na koniec zamyka pliki i wywoluje funkcje usun_graf. Je�li pliki otwieraj� si� nieprawid�owo, funkcja zwraca warto�� false i zwalnia zaalokowan� pami��.
@param wierzcholki nazwa pliku z wierzcho�kami
@param graf nazwa pliku z grafem
@param wyniki nazwa pliku na wyniki
@return true je�li wszystkie pliki otwar�y si� poprawnie
*/
bool szukaj_drogi(string wierzcholki, string graf, string wyniki);

/** Funkcja wczytuj�ca najpierw �cie�k� z wierzcho�ka pocz�tkowego do pierwszego wierzcho�ka grafu do listy �cie�ka, a nast�pnie wpisuj�ca t� �cie�k� do pliku wyj�ciowego.
@param numer numer wierzcho�ka pocz�tkowego
@param glowa wska�nik na w�ze� pocz�tkowy listy zewn�trznej LZ
@param czy_wystepuje zmienna typu bool informuj�ca o tym czy wierzcho�ek wyst�puje w grafie
@param wyniki referencja na plik wyj�ciowy na wyniki.
*/
void wczytaj_sciezke(int numer, element_LZ*& glowa, bool czy_wystepuje, ofstream& wyniki);

void zapisz_liste_do_pliku(sciezka*& tmp_sciezka, double& waga, const int& nieskonczonosc, std::ofstream& plik);

void dodaj_wezel_do_sciezki(element_LZ* wierzcholek, int numer, element_LZ*& tmp, bool& spr, sciezka*& glowa_sciezki, sciezka*& sciezka_tmp);

void parsuj_przelaczniki(int argc, char* argv[], bool& g, std::string& graf_wejsciowy, int& sprawdzenie, bool& w, std::string& wierzch_wejsciowy, bool& o, std::string& wyniki_wyjsciowy);

void buduj_graf(int wierzch1, element_LZ*& poczatek, bool sprawdzenie, element_LZ*& p, double waga, int wierzch2, bool skier, element_LZ*& pomoc);


#endif