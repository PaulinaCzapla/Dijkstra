/** @file */
#pragma once

#ifndef STRUKTURY_H
#define STRUKTURY_H

/** W�ze� listy wierzcho�k�w najkr�tszej �cie�ki. */
struct sciezka
{
	int wierzcholek;						///< numer wierzcho�ka
	double waga;							///< d�ugo�� �cie�ki od pocz�tkowego do danego wierzcho�ka
	sciezka* nastepny;						///< adres nast�pnego elementu w li�cie
};

/** W�ze� listy wewn�trznej listy list. */
struct element_LW
{
	int wierzcholek;						///< numer wierzcho�ka s�siedniego
	double wartosc;							///< warto�� drogi do danego wierzcho�ka
	element_LW* nastepny;					///< adres nast�pnego elementu listy
};

/** W�ze� listy zewn�trznej listy list. */
struct element_LZ
{
	int pierwszy_wierzcholek;				///< numer wierzcho�ka w grafie
	bool odwiedzone;						///< flaga odwiedzenia wierzcho�ka
	double droga;							///< najkr�tsza droga do danego wierzcho�ka z wierzcho�ka pocz�tkowego
	element_LZ* poprzedni_wierzcholek;		///< adres na poprzedni wierzcho�ek w �cie�ce
	element_LZ* nastepny;					///< adres na nast�pny element listy
	element_LW* polaczenie;					///< adres na pierwszy element listy wewn�trznej
};


#endif