/** @file */
#pragma once

#ifndef STRUKTURY_H
#define STRUKTURY_H

/** Wêze³ listy wierzcho³ków najkrótszej œcie¿ki. */
struct sciezka
{
	int wierzcholek;						///< numer wierzcho³ka
	double waga;							///< d³ugoœæ œcie¿ki od pocz¹tkowego do danego wierzcho³ka
	sciezka* nastepny;						///< adres nastêpnego elementu w liœcie
};

/** Wêze³ listy wewnêtrznej listy list. */
struct element_LW
{
	int wierzcholek;						///< numer wierzcho³ka s¹siedniego
	double wartosc;							///< wartoœæ drogi do danego wierzcho³ka
	element_LW* nastepny;					///< adres nastêpnego elementu listy
};

/** Wêze³ listy zewnêtrznej listy list. */
struct element_LZ
{
	int pierwszy_wierzcholek;				///< numer wierzcho³ka w grafie
	bool odwiedzone;						///< flaga odwiedzenia wierzcho³ka
	double droga;							///< najkrótsza droga do danego wierzcho³ka z wierzcho³ka pocz¹tkowego
	element_LZ* poprzedni_wierzcholek;		///< adres na poprzedni wierzcho³ek w œcie¿ce
	element_LZ* nastepny;					///< adres na nastêpny element listy
	element_LW* polaczenie;					///< adres na pierwszy element listy wewnêtrznej
};


#endif