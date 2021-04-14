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

/** Funkcja do obs³ugi prze³¹czników. Sprawdza liczbê argumentów (typu string) wprowadzonych z linii poleceñ. Jeœli jest ich 7 to sprawdza, czy prze³¹czniki s¹ prawid³owe, 
czyli czy jest to -g -w i -o. Nastêpnie sprawdzane jest rozszerzenie plików (wywo³ana zostaje funkcja sprawdz_pliki) oraz poprawnoœæ 
otwierania siê plików (funkcja szukaj_drogi, która jeœli warunki zostan¹ spe³nione, wykona ca³y program i zwróci true). W przypadku niespe³nienia warunków, funkcja zwraca false.
@param argc liczba argumentów
@param argv wskaŸnik na tablicê ³añcuchów znakowych
@return true albo false, w zale¿noœci czy warunki zosta³y spe³nione.
*/
bool przelaczniki(int argc, char* argv[]);

/** Funkcja sprawdzaj¹ca czy pliki s¹ tekstowe (czy maj¹ rozszerzenie .txt).
@param plik1 nazwa typu string pierwszego pliku
@param plik2 nazwa typu string drugiego pliku
@param plik3 nazwa typu string trzeciego pliku
@return jeœli wszystkie pliki maj¹ rozszerzenie .txt, funkcja zwraca true, w przeciwnym wypadku zwraca false.
*/
bool sprawdz_pliki(string plik1, string plik2, string plik3);

/** Funkcja tworz¹ca nowy wêze³ listy jednokierunkowej (sciezka). Lista ta przechowuje drogê (kolejne wierzcho³ki na drodze oraz odleg³oœæ
miêdzy pierwszym a ostatnim wierzcho³kiem) miêdzy danym wierzcho³kiem pocz¹tkowym, a kolejnymi wierzcho³kami grafu.
@param wartosc wartoœæ, która ma zostaæ przypisana do p->wierzcholek
@param waga wartoœæ, która ma zostaæ przypisana p->waga
@return wskaŸnik na nowo dodany wêze³ listy.
*/
sciezka* dodaj_wezel(int wartosc, double waga);

/** Funkcja dodaj¹ca na pocz¹tek nowy wêze³ listy jednokierunkowej (sciezka). Nowo powsta³y wêze³, staje siê g³ow¹ listy.
@param glowa wskaŸnik przekazany przez referancjê na pierwszy element listy
@param wartosc wartoœæ typu int, która zostaje przekazana do funkcji dodaj_wezel
@param waga wartoœæ typu double, która zostaje przekazana do funkcji dodaj_wezel
*/
void dodaj_wierzcholek(sciezka*& glowa, int wartosc, double waga);

/** Funkcja usuwaj¹ca kolejno wszystkie elementy listy (œcie¿ki).
@param glowa wskaŸnik przekazany przez referencjê na pierwszy element listy.
*/
void usun_liste_wierzcholkow(sciezka*& glowa);

/** Funkcja tworz¹ca pierwszy wêze³ listy jednokierunkowej LZ (lista zewnêtrzna listy list). Lista ta przechowuje numery wszystkich wierzcho³ków w grafie
(bez powtórzeñ), zmienn¹ odwiedzone, informuj¹c¹ czy dany wierzcho³ek zosta³ ju¿ odwiedzony podczas wykonywania algorytmu (pocz¹tkowo false), zmienn¹ droga
przechowuj¹c¹ najmniejsz¹ wartoœæ drogi do danego wierzcho³ka (pocz¹tkowo ma wartoœæ nieskoñczonoœæ, czyli najwiêksz¹ wartoœæ typu int) oraz wskaŸniki na nastêpny i poprzedni wêze³ listy,
poprzedni wierzcho³ek przy wyszukiwaniu œcie¿ki oraz wskaŸnik na pierwszy element listy wewnêtrznej LW. Do wszystkich wskaŸników zostaje przypisany nullptr.
@param wartosc (wierzcholek grafu) wartoœæ, która ma zostaæ przypisana do p->pierwszy_wierzcholek
@return funkcja zwraca wskaŸnik na nowo dodany wêze³ listy.
*/
element_LZ* dodaj_elementLZ(int wartosc);

/** Funkcja dodaj¹ca na koniec listy LZ nowy wêze³.
@param glowa wskaŸnik przekazany przez referancjê na pierwszy element listy
@param wartosc liczba typu int (wierzcholek grafu), która ma zostaæ przypisana do p->pierwszy_wierzcholek
*/
void dodaj_wezelLZ(element_LZ*& glowa, int wartosc);

/** Funkcja szukaj¹ca w LZ (liœcie zewnêtrznej listy list bêd¹cej reprezentacj¹ grafu) podanego wierzcho³ka.
@param wartosc poszukiwany wierzcholek w liœcie
@param p wskaŸnik na pierwszy element listy
@return wskaŸnik na element listy, w której znajduje siê dany wierzcho³ek. Jeœli w liœcie nie ma takiego wierzcho³ka, funkcja zwraca nullptr.
*/
element_LZ* znajdzLZ(int wartosc, element_LZ* p);

/** Funkcja tworz¹ca nowy wêze³ listy jednokierunkowej (lista wewnêtrzna listy list). Wpisuje do struktury podane wartoœci i zwraca wskaŸnik na nowo powsta³y wêze³ LW.
@param wartosc d³ugoœæ krawêdzi do danego wierzcho³ka
@param wezel numer wierzcho³ka
@return wskaŸnik na nowy wêze³ listy.
*/
element_LW* dodaj_elementLW(double wartosc, int wezel);

/** Funkcja dodaj¹ca na koniec listy wewnêtrznej nowy weze³. Sprawdza, czy wskaŸnik na element listy, podany jako parametr, wskazuje na ostatni element. Jeœli nie,
to przesuwa wskaŸnik na nastêpny element listy, a¿ nie trafi na LW->nastepny==nullptr. Wtedy zostaje wywo³ana funkcja dodaj_elementLW z parametrami wartosc i wezel przekazanymi do funkcji.
@param LW wskaŸnik na wêze³ listy wewnêtrznej podany przez referencjê
@param wierzcholek numer wierzcho³ka
@param wartosc d³ugoœæ krawêdzi do danego wierzcho³ka.
*/
void dodaj_wezelLW(element_LW*& LW, int wierzcholek, double wartosc);

/** Funkcja tworz¹ca listê wewnêtrzn¹ dla danego elementu listy zewnêtrznej. Przypisuje adres na pierwszy element nowej listy wewnêtrznej do LZ->polaczenie,
tworz¹c tym samym po³¹czenie miêdzy tymi dwoma listami. Jeœli dla danego wêz³a listy zewnêtrznej nie ma jeszcze listy wewnêtrznej, wywo³ana zostaje funkcja dodaj_elementLW z parametrami waga i wierzcho³ek.
Jeœli dla danego wêz³a istniej¹ ju¿ elementy listy, zostaje wywo³ana funkacja dodaj_wezelLW z parametrami el_LW, wierzcholek i waga.
@param LZ wskaŸnik na podany element listy zewnêtrznej listy list (bêd¹cej reprezentacj¹ grafu) przekazany przez referencjê
@param waga d³ugoœæ krawêdzi z wierzcho³ka, którego numer przechowywany jest w LZ do podanego jako parametr wierzcho³ka
@param wierzcholek numer wierzcholka, do którego prowadzi krawêdŸ
@param skierowana true jeœli krawêdŸ miêdzy wierzcho³kami jest skierowana (prowadzi tylko w jedn¹ stronê), false jeœli jest nieskierowana (prowadzi w obie strony)
*/
void dodaj_polaczenie(element_LZ*& LZ, double waga, int wierzcholek, bool skierowana);

/** Funkcja usuwaj¹ca graf, przedstawiony za pomoc¹ struktury listy listy. Dla ka¿dego elementu listy zewnêtrznej LZ, funkcja usuwa elementy po³¹czonej z ni¹ listy wewnêtrznej LW (o ile istnieje), po czym po
przypisaniu do zmiennej tymczasowej wskaŸnika na nastêpny wêze³ LZ, zostaje usuniêty dany wêze³ LZ, tak d³ugo a¿ lista zewnêtrzna ma elementy.
@param poczatek wskaŸnik przekazany przez referancjê na pocz¹tek listy zewnêtrznej.
*/
void usun_graf(element_LZ*& poczatek);

/** Funkcja wczytuj¹ca z podanego pliku graf do listy list (lista zewnêtrzna (jej elementami jest struktura element_LZ), której ka¿dy wêze³ wskazuje na listê wewnêtrzn¹
(jej elementami jest struktura element_LW). Jeœli dane w pliku s¹ nieprawid³owe, funkcja zwraca nullptr. Jeœli oczytany wierzcho³ek nie znajduje siê jeszcze w grafie, wywo³ana zostaje dla niego funkcja dodaj_elementLZ, 
w przeciwnym przypadku, wierzcho³ek jest wczytywany do istniej¹cej listy LZ za pomoc¹ funkcji dodaj_wezelLZ. W zale¿noœci od tego, czy krawêdŸ jest skierowana, wierzcho³ki s¹siednie zostaj¹ wpisane do
listy wewnêtrznej LW. Po³¹czenie miêdzy list¹ zewnêtrzn¹ a wewnêtrzn¹ jest dodawane za pomoc¹ funkcji dodaj_polaczenie.
@param plik referencja na plik z grafem
@return wskaŸnik na pierwszy element listy zewnêtrznej LZ. Jeœli dane s¹ nieprawid³owe, zwraca nullptr.
*/
element_LZ* wczytaj_graf(ifstream& plik);

/** Funkcja czyœci/resetuje dane na liœcie zewnêtrznej po zastosowaniu algorytmu dijkstry.
@param p wskaŸnik na pocz¹tek listy zewnêtrznej LZ
*/
void wyczysc_dane(element_LZ* p);

/** Funkcja wykonuj¹ca algorytm dijkstry, wyszukuje najkrótsz¹ drogê z podanego wierzcho³ka do reszty wierzcho³ków. Zostaje wywo³ana dla danego wierzcho³ka pocz¹tkowego, który zostaje wyszukany w liœcie LZ.
Pocz¹tkowo w liœcie LZ wartoœæ drogi do wierzcho³ka pocz¹tkowego jest równa zero, natomiast do reszty wierzcho³ków jest równa maksymalnej wartoœci zmiennej typu int ("nieskonczonosc"). 
Nastêpnie sprawdzany jest pierwszy element listy LW, wierzcho³ek zostaje wyszukany w liœcie LZ i odleg³oœæ z wierzcho³ka pocz¹tkowego zostaje przypisana do element_LZ->droga, a wskaŸnik na wierzcho³ek poprzedni
(czyli wierzcho³ek pocz¹tkowy) zostaje przypisany do element_LZ->poprzedni_wierzcho³ek. Element_LZ-> odwiedzone zostaje zmieniony na true. W nastêpnej kolejnoœci, wywo³ana
zostaje dla tego wierzcho³ka rekurencyjnie funkcja dijkstra. Przed przypisaniem wartoœci do element_LZ->droga zostaje sprawdzone, czy wartoœæ ju¿ tam zapisana nie jest nieskoñczonoœci¹, b¹dŸ czy nie jest wiêksza 
od nowej. Jeœli tak, wartoœæ zostaje przypisana. Funkcja dijkstra jest wywo³ywana rekurencyjnie tylko dla wierzcho³ków, które nie zosta³y jeszcze odwiedzone, b¹dŸ których droga zosta³a zmieniona.
Algorytm wykonuje siê, a¿ najkrótsze œcie¿ki z danego wierzcho³ka pocz¹tkowego do reszty wierzcho³ków zostan¹ odnalezione.
@param tmp_wierzcholek wskaŸnik na wierzcho³ek pocz¹tkowy przekazany przez referencjê
@param numer numer wierzcho³ka pocz¹tkowego
@param glowa wskaŸnik na wêze³ pocz¹tkowy listy zewnêtrznej LZ
*/
void dijkstra(element_LZ*& tmp_wierzcholek, int numer, element_LZ* glowa);

/** Funkcja otwiera plik z grafem i wywo³uje funkcjê wczytaj_graf oraz otwiera plik z wierzcho³kami pocz¹tkowymi, odczytuje ka¿dy wierzcho³ek i jeœli istnieje on w grafie to wywo³uje funkcje dijkstra i wczytaj_sciezke.
Na koniec zamyka pliki i wywoluje funkcje usun_graf. Jeœli pliki otwieraj¹ siê nieprawid³owo, funkcja zwraca wartoœæ false i zwalnia zaalokowan¹ pamiêæ.
@param wierzcholki nazwa pliku z wierzcho³kami
@param graf nazwa pliku z grafem
@param wyniki nazwa pliku na wyniki
@return true jeœli wszystkie pliki otwar³y siê poprawnie
*/
bool szukaj_drogi(string wierzcholki, string graf, string wyniki);

/** Funkcja wczytuj¹ca najpierw œcie¿kê z wierzcho³ka pocz¹tkowego do pierwszego wierzcho³ka grafu do listy œcie¿ka, a nastêpnie wpisuj¹ca t¹ œcie¿kê do pliku wyjœciowego.
@param numer numer wierzcho³ka pocz¹tkowego
@param glowa wskaŸnik na wêze³ pocz¹tkowy listy zewnêtrznej LZ
@param czy_wystepuje zmienna typu bool informuj¹ca o tym czy wierzcho³ek wystêpuje w grafie
@param wyniki referencja na plik wyjœciowy na wyniki.
*/
void wczytaj_sciezke(int numer, element_LZ*& glowa, bool czy_wystepuje, ofstream& wyniki);

void zapisz_liste_do_pliku(sciezka*& tmp_sciezka, double& waga, const int& nieskonczonosc, std::ofstream& plik);

void dodaj_wezel_do_sciezki(element_LZ* wierzcholek, int numer, element_LZ*& tmp, bool& spr, sciezka*& glowa_sciezki, sciezka*& sciezka_tmp);

void parsuj_przelaczniki(int argc, char* argv[], bool& g, std::string& graf_wejsciowy, int& sprawdzenie, bool& w, std::string& wierzch_wejsciowy, bool& o, std::string& wyniki_wyjsciowy);

void buduj_graf(int wierzch1, element_LZ*& poczatek, bool sprawdzenie, element_LZ*& p, double waga, int wierzch2, bool skier, element_LZ*& pomoc);


#endif