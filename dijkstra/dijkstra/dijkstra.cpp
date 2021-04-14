/** @file */
#include "dijkstra.h"
#include "struktury.h"

bool przelaczniki(int argc, char* argv[])
{
	string graf_wejsciowy, wierzch_wejsciowy, wyniki_wyjsciowy;

	if (argc == 7)
	{
		int sprawdzenie = 0;
		bool g = 0, w = 0, o = 0;

		parsuj_przelaczniki(argc, argv, g, graf_wejsciowy, sprawdzenie, w, wierzch_wejsciowy, o, wyniki_wyjsciowy);

		if (sprawdzenie != 3)
		{
			cout << " \n Podano nieprawidlowe argumenty. \n";
			cout << "    dijkstra.exe -  nazwa pliku \n - g <nazwa.txt> -  plik wejsciowy z grafem \n - w <nazwa.txt> -  plik wejsciowy z wierzcholkami \n - o <nazwa.txt> -  plik wyjsciowy z wynikami \n";
			return false;
		}

		if (sprawdz_pliki(graf_wejsciowy, wierzch_wejsciowy, wyniki_wyjsciowy) == true)
		{
			if (szukaj_drogi(wierzch_wejsciowy, graf_wejsciowy, wyniki_wyjsciowy))
				return true;
			else
				return false;
		}
		else
		{
			cout << "\n Nieprawidlowy format pliku. Pliki musza byc plikami tekstowymi. \n";
			return false;
		}
	}
	else
	{
		cout << " \n Podano nieprawidlowe argumenty. \n";
		cout << "    dijkstra.exe -  nazwa pliku \n - g <nazwa.txt> -  plik wejsciowy z grafem \n - w <nazwa.txt> -  plik wejsciowy z wierzcholkami \n - o <nazwa.txt> -  plik wyjsciowy z wynikami \n";
		return false;
	}
}

void parsuj_przelaczniki(int argc, char* argv[], bool& g, std::string& graf_wejsciowy, int& sprawdzenie, bool& w, std::string& wierzch_wejsciowy, bool& o, std::string& wyniki_wyjsciowy)
{
	for (int i = 1; i < argc; i += 2)
	{
		if (string(argv[i]) == "-g" && g == 0)
		{
			graf_wejsciowy = argv[i + 1];
			sprawdzenie++;
			g = 1;
			continue;
		}
		if (string(argv[i]) == "-w" && w == 0)
		{
			wierzch_wejsciowy = argv[i + 1];
			sprawdzenie++;
			w = 1;
			continue;
		}
		if (string(argv[i]) == "-o" && o == 0)
		{
			wyniki_wyjsciowy = argv[i + 1];
			sprawdzenie++;
			o = 1;
			continue;
		}
	}
}

bool sprawdz_pliki(string plik1, string plik2, string plik3)
{
	string tablica_nazw[3] = { plik1, plik2, plik3 };

	unsigned int sprawdzenie = 0;
	for (int i = 0; i < 3; i++)
	{
		int dlugosc = tablica_nazw[i].length();
		if (dlugosc > 3)
		{
			if (tablica_nazw[i][dlugosc - 1] == 't' && tablica_nazw[i][dlugosc - 2] == 'x' && tablica_nazw[i][dlugosc - 3] == 't' && tablica_nazw[i][dlugosc - 4] == '.')
				sprawdzenie++;
		}
	}

	if (sprawdzenie == 3)
		return true;
	else
		return false;
}

sciezka* dodaj_wezel(int wartosc, double waga)
{
	sciezka* p;
	p = new sciezka;

	p->wierzcholek = wartosc;
	p->waga = waga;
	p->nastepny = nullptr;

	return p;
}

void dodaj_wierzcholek(sciezka*& glowa, int wartosc, double waga)
{
	if (glowa == nullptr)
		return;
	sciezka* wezel = nullptr;

	wezel = dodaj_wezel(wartosc, waga);
	wezel->nastepny = glowa;
	glowa = wezel;
}

void usun_liste_wierzcholkow(sciezka*& glowa)
{
	while (glowa)
	{
		auto tmp = glowa->nastepny;
		delete glowa;
		glowa = tmp;
	}
}


element_LZ* dodaj_elementLZ(int wartosc)
{
	constexpr int nieskonczonosc = numeric_limits<int>::max();
	element_LZ* p;
	p = new element_LZ;

	p->pierwszy_wierzcholek = wartosc;
	p->nastepny = nullptr;
	p->droga = nieskonczonosc;
	p->poprzedni_wierzcholek = nullptr;
	p->odwiedzone = false;
	p->polaczenie = nullptr;

	return p;
}

void dodaj_wezelLZ(element_LZ*& glowa, int wartosc)
{
	constexpr int nieskonczonosc = numeric_limits<int>::max();
	if (glowa == nullptr)
		return;
	while (glowa)
	{
		if (glowa->nastepny == nullptr)
		{
			element_LZ* p = dodaj_elementLZ(wartosc);

			glowa->nastepny = p;
			glowa = p;
			return;
		}
		glowa = glowa->nastepny;
	}
}

element_LZ* znajdzLZ(int wartosc, element_LZ* p)
{
	while (p != nullptr)
	{
		if (p->pierwszy_wierzcholek == wartosc)
		{
			return p;
		}
		p = p->nastepny;
	}
	return nullptr;
}


element_LW* dodaj_elementLW(double wartosc, int wezel)
{
	element_LW* q;
	q = new element_LW;

	q->wierzcholek = wezel;
	q->wartosc = wartosc;
	q->nastepny = nullptr;

	return q;
}

void dodaj_wezelLW(element_LW*& LW, int wierzcholek, double wartosc)
{
	if (LW == nullptr)
		return;

	while (LW)
	{
		if (LW->nastepny == nullptr)
		{
			LW->nastepny = dodaj_elementLW(wartosc, wierzcholek);

			return;
		}
		LW = LW->nastepny;
	}
}

void dodaj_polaczenie(element_LZ*& LZ, double waga, int wierzcholek, bool skierowana)
{
	element_LW* el_LW = LZ->polaczenie;

	if (el_LW == nullptr)
	{
		LZ->polaczenie = dodaj_elementLW(waga, wierzcholek);
		return;
	}
	else
	{
		while (el_LW)
		{
			if (el_LW->wierzcholek == wierzcholek && skierowana == true)
				return;

			if (el_LW->nastepny == nullptr)
			{
				dodaj_wezelLW(el_LW, wierzcholek, waga);
				return;
			}
			el_LW = el_LW->nastepny;
		}
	}
}

void usun_graf(element_LZ*& poczatek)
{
	if (poczatek != nullptr)
	{
		element_LW*& LW = poczatek->polaczenie;
		element_LZ* tmpLZ = nullptr;
		element_LW* tmpLW = nullptr;
		int i = 0, j = 0;
		while (poczatek)
		{
			LW = poczatek->polaczenie;

			while (LW)
			{
				tmpLW = LW->nastepny;
				delete LW;
				LW = tmpLW;
			}
			tmpLZ = poczatek->nastepny;
			delete poczatek;
			poczatek = tmpLZ;
		}
	}

}


element_LZ* wczytaj_graf(ifstream& plik)
{
	int wierzch1, wierzch2;
	char dwukropek;
	string skierowana;
	double waga;
	bool sprawdzenie = false, skier;

	element_LZ* p = nullptr;
	element_LZ* pomoc = nullptr;
	element_LZ* poczatek = nullptr;

	while (!plik.eof())
	{
		if (!(plik >> wierzch1 >> skierowana >> wierzch2 >> dwukropek >> waga)) //sprawdzenie, czy dane się prawidłowo wczytują
		{
			cout << "\n Bledny plik! \n";

			if (poczatek != nullptr)
			{
				usun_graf(poczatek);
			}
			return nullptr;
		}
		if (waga < 0) //sprawdzenie, czy waga krawędzi nie jest ujemna
		{
			cout << "\nWagi krawedzi nie moga byc ujemne. Popraw wartosci w pliku z grafem. \n";

			if (poczatek != nullptr)
			{
				usun_graf(poczatek);
			}
			return nullptr;
		}

		if (skierowana == "->")
			skier = true;
		else
			skier = false;

		buduj_graf(wierzch1, poczatek, sprawdzenie, p, waga, wierzch2, skier, pomoc);

		sprawdzenie = true;
	}
	return poczatek;
}

void buduj_graf(int wierzch1, element_LZ*& poczatek, bool sprawdzenie, element_LZ*& p, double waga, int wierzch2, bool skier, element_LZ*& pomoc)
{
	if (znajdzLZ(wierzch1, poczatek) == nullptr)
	{
		if (sprawdzenie == false)
		{
			p = dodaj_elementLZ(wierzch1);
			poczatek = p;

			dodaj_polaczenie(p, waga, wierzch2, skier);
		}
		else
		{
			dodaj_wezelLZ(p, wierzch1);
			dodaj_polaczenie(p, waga, wierzch2, skier);
		}
	}
	else
	{
		pomoc = znajdzLZ(wierzch1, poczatek); //zwraca wskaznik na LZ
		dodaj_polaczenie(pomoc, waga, wierzch2, skier);
	}

	if (znajdzLZ(wierzch2, poczatek) == nullptr)
	{
		dodaj_wezelLZ(p, wierzch2);

		if (skier == false)
		{
			dodaj_polaczenie(p, waga, wierzch1, skier);
		}
	}
	else
	{
		if (skier == false)
		{
			pomoc = znajdzLZ(wierzch2, poczatek); //zwraca wskaznik na LZ
			dodaj_polaczenie(pomoc, waga, wierzch1, skier);
		}
	}
}

void wyczysc_dane(element_LZ* p)
{
	constexpr int nieskonczonosc = numeric_limits<int>::max();
	const bool zero = 0;
	while (p != nullptr)
	{
		p->odwiedzone = zero;
		p->droga = nieskonczonosc;
		p->poprzedni_wierzcholek = nullptr;
		p = p->nastepny;
	}
}

void dijkstra(element_LZ*& tmp_wierzcholek, int numer, element_LZ* glowa)
{
	element_LZ* tmp_wierzch = nullptr;
	tmp_wierzch = tmp_wierzcholek;

	tmp_wierzcholek->odwiedzone = true;
	element_LW* tmp_LW = tmp_wierzch->polaczenie; //wskaźnik na pierwszy element LW dla danego wierzcholka początkowego

	constexpr int nieskonczonosc = numeric_limits<int>::max();
	bool sprawdzenie = 0;
	while (tmp_LW != nullptr)
	{
		sprawdzenie = 0;
		if (tmp_LW->wierzcholek != numer) //sprawdzenie czy wierzcholek sasiedni nie jest wierzcholkiem początkowym
		{
			tmp_wierzch = znajdzLZ(tmp_LW->wierzcholek, glowa); //znajduje wierzcholek sąsiedni w LZ

			if (tmp_wierzch->droga == nieskonczonosc || tmp_wierzch->droga > (tmp_LW->wartosc + tmp_wierzcholek->droga)) //sprawdza czy może podmienić wskaźniki i drogi
			{
				tmp_wierzch->droga = tmp_LW->wartosc + tmp_wierzcholek->droga;
				tmp_wierzch->poprzedni_wierzcholek = tmp_wierzcholek;
				sprawdzenie = 1;
			}
			if (tmp_wierzch->odwiedzone == 0 || (tmp_wierzch->odwiedzone == 1 && sprawdzenie == 1)) //wywołuje rekurencyjnie funkcję dla danego wierzchołka, jeśli 
				dijkstra(tmp_wierzch, numer, glowa);												//nie został on jeszcze odwiedzony lub jeśli zmieniła się wartość drogi do niego
		}
		tmp_LW = tmp_LW->nastepny; //nastepny element listy LW
	}
	return;
}

bool szukaj_drogi(string wierzcholki, string graf, string wyniki)
{
	ifstream plik_wierzcholki;
	plik_wierzcholki.open(wierzcholki, ios::in);

	constexpr int minus_nieskonczonosc = numeric_limits<int>::min();
	int numer = minus_nieskonczonosc;
	element_LZ* glowa = nullptr;
	element_LZ* wierzcholek_poczatkowy = nullptr;
	element_LZ* koniec = nullptr;

	ofstream plik_wyniki;

	if (plik_wierzcholki.good())
	{
		ifstream plik_graf;
		plik_graf.open(graf, ios::in);

		if (plik_graf.good())
		{
			glowa = wczytaj_graf(plik_graf);
			plik_graf.close();
		}
		else
		{
			plik_graf.close();
			cout << "\n Nie udalo sie otworzyc pliku " << graf << ". Podaj dane jeszcze raz. \n";
			return false;
		}

		if (glowa != nullptr)
		{
			plik_wyniki.open(wyniki, ios::out);
			while (!plik_wierzcholki.eof())
			{
				wyczysc_dane(glowa);

				if (!(plik_wierzcholki >> numer))
				{
					cout << "\n Bledny plik! \n";
					break;
				}

				if (numer == minus_nieskonczonosc)
					return false;

				wierzcholek_poczatkowy = znajdzLZ(numer, glowa); //wskaźnik na wierzcholek poczatkowy w LZ

				if (wierzcholek_poczatkowy == nullptr)
				{
					wczytaj_sciezke(numer, glowa, false, plik_wyniki);
					continue;
				}
				wierzcholek_poczatkowy->odwiedzone = true;
				wierzcholek_poczatkowy->droga = false;
				wierzcholek_poczatkowy->poprzedni_wierzcholek = nullptr;

				dijkstra(wierzcholek_poczatkowy, numer, glowa);
				wczytaj_sciezke(numer, glowa, true, plik_wyniki);
			}
		}
		else
			return false;
	}
	else
	{
		plik_wierzcholki.close();
		cout << "\n Nie udalo sie otworzyc pliku " << wierzcholki << ". Podaj dane jeszcze raz. \n";
		return false;
	}

	plik_wierzcholki.close();
	plik_wyniki.close();

	usun_graf(glowa);
	return true;
}

void wczytaj_sciezke(int numer, element_LZ*& glowa, bool czy_wystepuje, ofstream& plik)
{
	sciezka* tmp_glowa = nullptr;

	if (!czy_wystepuje)
	{
		plik << "Wierzchołek " << numer << " nie występuje w grafie. \n";
	}
	else
	{
		plik << "Wierzchołek początkowy: " << numer << "\n";

		element_LZ* wierzcholek = glowa;
		element_LZ* tmp = wierzcholek;
		sciezka* glowa_sciezki = nullptr;
		sciezka* sciezka_tmp = nullptr;

		bool spr = 0;

		while (wierzcholek != nullptr)
		{
			tmp = wierzcholek;

			dodaj_wezel_do_sciezki(wierzcholek, numer, tmp, spr, glowa_sciezki, sciezka_tmp);

			spr = 0;									//zerowanie zmiennej spr, ponieważ w następnej pętli będzie rozpatrywana ścieżka do innego wierzchołka i lista zostanie usunięta

			sciezka* tmp_sciezka = glowa_sciezki;
			double waga = 0;
			constexpr int nieskonczonosc = numeric_limits<int>::max();

			zapisz_liste_do_pliku(tmp_sciezka, waga, nieskonczonosc, plik);

			if (waga != 0 && waga != nieskonczonosc)
			{
				plik << " : ";
				plik << waga << " \n";
			}
			if (glowa_sciezki != nullptr)
				usun_liste_wierzcholkow(glowa_sciezki);	//po wczytaniu ścieżki do pliku, lista jest usuwana

			wierzcholek = wierzcholek->nastepny;
		}
	}
	plik << "\n";
}

void zapisz_liste_do_pliku(sciezka*& tmp_sciezka, double& waga, const int& nieskonczonosc, std::ofstream& plik)
{
	while (tmp_sciezka != nullptr)				//wczytywanie listy ścieżka do pliku
	{
		waga = tmp_sciezka->waga;

		if (waga == nieskonczonosc)
			break;

		plik << tmp_sciezka->wierzcholek;
		tmp_sciezka = tmp_sciezka->nastepny;

		if (tmp_sciezka != nullptr)
			plik << " -> ";
	}
}

void dodaj_wezel_do_sciezki(element_LZ* wierzcholek, int numer, element_LZ*& tmp, bool& spr, sciezka*& glowa_sciezki, sciezka*& sciezka_tmp)
{
	if (wierzcholek->pierwszy_wierzcholek != numer)
	{
		if (tmp != nullptr)
		{
			while (tmp != nullptr)
			{
				if (spr == 0)
				{
					glowa_sciezki = dodaj_wezel(tmp->pierwszy_wierzcholek, tmp->droga);
					sciezka_tmp = glowa_sciezki;
					spr = 1;					//zmienna spr informuje o tym, czy w liście ścieżka już jest jakiś węzeł
				}
				else
				{
					dodaj_wierzcholek(glowa_sciezki, tmp->pierwszy_wierzcholek, tmp->droga);
				}
				tmp = tmp->poprzedni_wierzcholek;
			}
		}
	}
}
