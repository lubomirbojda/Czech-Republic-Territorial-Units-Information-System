#include "Gui.h"
#include <iostream>

void Gui::spustiAplikaciu()
{
	bool vypnutie = false;
	int volba;
	std::string typ;
	std::string nazov;

	while (!vypnutie)
	{
		std::cout << "Preh¾adáva ÈR [1]" << std::endl;
		std::cout << "Nájs informácie o ÚJ s daným typom a názvom (tabu¾ky) [2]" << std::endl;
		std::cout << "Uroven 1 [3]" << std::endl;
		std::cout << "Ukonèi aplikáciu [4]" << std::endl;
		std::cin >> volba;
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		switch (volba)
		{
		case 1:
			system("cls");
			koniec = false;
			this->prehladavanie();
			break;
		case 2:
			std::cout << "Zadajte typ jednotky: ";
			std::getline(std::cin, typ);
			typ = algoritmus.zmenNaMalePismena(typ);
			if (typ == "kraj" || typ == "soorp" || typ == "obec")
			{
				std::cout << "Zadajte názov jednotky: ";
				std::getline(std::cin, nazov);
				nazov = algoritmus.zmenNaMalePismena(nazov);
			}
			else
			{
				std::cout << "Taký typ neexistuje.";
				_getch();
				system("cls");
				break;
			}
			this->aplikacia.vyhladajUJVTabulke(typ, nazov);
			_getch();
			system("cls");
			break;
		case 3:
			this->uroven1();
			break;
		case 4:
			vypnutie = true;
			break;
		default:
			std::cout << "Nesprávna vo¾ba" << std::endl;
			_getch();
			system("cls");
			break;
		}
	}
}

void Gui::uroven1()
{
	int v;
	std::cout << "Obsahuju [1]" << std::endl;
	std::cout << "Zacinaju [2]" << std::endl;
	std::cin >> v;
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	auto predikat = this->algoritmus.obsahujeText;
	//auto zacinaju = this->algoritmus.zacinajuNaText;
	switch (v)
	{
	case 1:
		this->zadajText();
		break;
	case 2:
		this->zadajText();
		predikat = this->algoritmus.zacinajuNaText;
		break;
	}

	std::cout << "Kraje [1]" << std::endl;
	std::cout << "Soorpy [2]" << std::endl;
	std::cout << "Obce [3]" << std::endl;
	std::cout << "Menu [4]" << std::endl;
	
	std::cin >> v;
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	auto krajeCR = this->aplikacia.getKraje();
	auto soorpCR = this->aplikacia.getSoorp();
	auto obceCR = this->aplikacia.getObce();
	switch (v)
	{
	case 1:
		
		this->algoritmus.vyfiltrujAlgoritmom(krajeCR.begin(), krajeCR.end(), hladanyText, predikat);
		this->algoritmus.vypisVyfiltrovaneJednotky(false);
		_getch();
		system("cls");
		break;
	case 2:
		this->algoritmus.vyfiltrujAlgoritmom(soorpCR.begin(), soorpCR.end(), hladanyText, predikat);
		this->algoritmus.vypisVyfiltrovaneJednotky(false);
		_getch();
		system("cls");
		break;
	case 3:
		this->algoritmus.vyfiltrujAlgoritmom(obceCR.begin(), obceCR.end(), hladanyText, predikat);
		this->algoritmus.vypisVyfiltrovaneJednotky(false);
		_getch();
		system("cls");
		break;
	case 4:
		system("cls");
		break;
	}
}

void Gui::zadajText()
{
	std::cout << "H¾adaný text:  ";
	std::getline(std::cin, hladanyText);
}

void Gui::prehladavanie()
{
	while (!koniec)
	{
		switch (_uroven)
		{
		case 0:
			std::cout << "Aktuálne vybrané: Èeská Republika" << std::endl;
			std::cout << "Èo si prajete vykona?" << std::endl;
			this->vypisMoznosti(_uroven);
			this->vykonajMoznost(_uroven, _input);
			break;
		case 1: case 2:
			std::cout << "Aktuálne vybrané: " << aplikacia.getAktualneVybrany()->data_->getNazov() << std::endl;
			std::cout << "Èo si prajete vykona?" << std::endl;
			this->vypisMoznosti(_uroven);
			this->vykonajMoznost(_uroven, _input);
			break;
		default:
			std::cout << "Nesprávna úroveò" << std::endl;
			break;
		}
	}
}

void Gui::vypisMoznosti(int aktUroven)
{
	switch (aktUroven)
	{
	case 0:
		std::cout << "Vybra kraj [1]" << std::endl;
		std::cout << "Vypíš všetky podradené územné jednotky, ktoré obsahujú zadaný text [2]" << std::endl;
		std::cout << "Vypíš všetky podradené územné jednotky, ktoré zaèínajú na zadaný text [3]" << std::endl;
		std::cout << "Vypíš všetky podradené územné jednotky daného typu [4]" << std::endl;
		std::cout << "Vráti sa do menu [5]" << std::endl;
		std::cin >> _input;
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		break;
	case 1:
		std::cout << "Vybra soorp [1]" << std::endl;
		std::cout << "Ís spä na úroveò ÈR [2]" << std::endl;
		std::cout << "Vypíš všetky podradené územné jednotky, ktoré obsahujú zadaný text [3]" << std::endl;
		std::cout << "Vypíš všetky podradené územné jednotky, ktoré zaèínajú na zadaný text [4]" << std::endl;
		std::cout << "Vypíš všetky podradené územné jednotky daného typu [5]" << std::endl;
		std::cout << "Vráti sa do menu [6]" << std::endl;
		std::cin >> _input;
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		break;
	case 2:
		std::cout << "Ís spä na nadradený kraj [1]" << std::endl;
		std::cout << "Vypíš všetky podradené územné jednotky, ktoré obsahujú zadaný text [2]" << std::endl;
		std::cout << "Vypíš všetky podradené územné jednotky, ktoré zaèínajú na zadaný text [3]" << std::endl;
		std::cout << "Vypíš všetky podradené územné jednotky daného typu [4]" << std::endl;
		std::cout << "Vráti sa do menu [5]" << std::endl;
		std::cin >> _input;
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		break;
	default:
		std::cout << "Nesprávna úroveò" << std::endl;
		break;
	}
}

void Gui::vykonajMoznost(int aktUroven, int input)
{
	auto aktVybraty = this->aplikacia.getAktualneVybrany();
	auto _CR = this->aplikacia.getCR();
	
	switch (aktUroven)
	{
	case 0:
		switch (input)
		{
		case 1:
		{
			this->vybrat();
			break;
		}
		case 2:
		{
			this->zadajText();
			this->algoritmus.vyfiltrujAlgoritmom(iteratorEH(&_CR, aktVybraty), iteratorEH(&_CR, nullptr), this->hladanyText, this->algoritmus.obsahujeText);
			this->moznostVypisuKomparator();
			_getch();
			system("cls");
			break;
		}
		case 3:
		{
			this->zadajText();
			this->algoritmus.vyfiltrujAlgoritmom(iteratorEH(&_CR, aktVybraty), iteratorEH(&_CR, nullptr), this->hladanyText, this->algoritmus.zacinajuNaText);
			this->moznostVypisuKomparator();
			_getch();
			system("cls");
			break;
		}
		case 4:
		{
			this->vypisTypu();
			break;
		}
		case 5:
			koniec = true;
			system("cls");
			break;
		default:
		{
			std::cout << "Nesprávna vo¾ba!";
			_getch();
			system("cls");
			break;
		}
		}
		break;
	case 1:
		switch (input)
		{
		case 1:
		{
			this->vybrat();
			break;
		}
		case 2:
		{
			this->aplikacia.setAktualneVybrany(_CR.accessParent(*aktVybraty));
			system("cls");
			_uroven--;
			break;
		}
		case 3:
		{
			this->zadajText();
			this->algoritmus.vyfiltrujAlgoritmom(iteratorEH(&_CR, aktVybraty), iteratorEH(&_CR, nullptr), this->hladanyText, this->algoritmus.obsahujeText);
			this->moznostVypisuKomparator();
			_getch();
			system("cls");
			break;
		}
		case 4:
		{
			this->zadajText();
			this->algoritmus.vyfiltrujAlgoritmom(iteratorEH(&_CR, aktVybraty), iteratorEH(&_CR, nullptr), this->hladanyText, this->algoritmus.zacinajuNaText);
			this->moznostVypisuKomparator();
			_getch();
			system("cls");
			break;
		}
		case 5:
		{
			this->vypisTypu();
			break;
		}
		case 6:
			koniec = true;
			system("cls");
			break;
		default:
		{
			std::cout << "Nesprávna vo¾ba!";
			_getch();
			system("cls");
			break;
		}
		}
		break;
	case 2:
		switch (input)
		{
		case 1:
		{
			this->aplikacia.setAktualneVybrany(_CR.accessParent(*aktVybraty));
			system("cls");
			_uroven--;
			break;
		}
		case 2:
		{
			this->zadajText();
			this->algoritmus.vyfiltrujAlgoritmom(iteratorEH(&_CR, aktVybraty), iteratorEH(&_CR, nullptr), this->hladanyText, this->algoritmus.obsahujeText);
			this->moznostVypisuKomparator();
			_getch();
			system("cls");
			break;
		}
		case 3:
		{
			this->zadajText();
			this->algoritmus.vyfiltrujAlgoritmom(iteratorEH(&_CR, aktVybraty), iteratorEH(&_CR, nullptr), this->hladanyText, this->algoritmus.zacinajuNaText);
			this->moznostVypisuKomparator();
			_getch();
			system("cls");
			break;
		}
		case 4:
		{
			this->vypisTypu();
			break;
		}
		case 5:
			koniec = true;
			system("cls");
			break;
		default:
		{
			std::cout << "Nesprávna vo¾ba!";
			_getch();
			system("cls");
			break;
		}
		}
		break;
	default:
		std::cout << "Nesprávna úroveò" << std::endl;
		break;
	}
}

void Gui::vybrat()
{
	auto aktVybraty = this->aplikacia.getAktualneVybrany();
	int i = 1;
	for (auto uj : *aktVybraty->sons_)
	{
		std::cout << uj->data_->getNazov() << " [" << i << "]" << std::endl;
		i++;
	}
	if (i == 1)
	{
		std::cout << "Tento kraj nemá žiadne soorp.";
		_getch();
		system("cls");
		return;
	}
	int vyber;
	std::cin >> vyber;
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	if (vyber <= aktVybraty->sons_->size() && vyber >= 1)
	{
		_uroven++;
		this->aplikacia.setAktualneVybrany(aktVybraty->sons_->access(vyber - 1)->data_);
	}
	else
	{
		std::cout << "Nespravna zadaná vo¾ba." << std::endl;
		_getch();
	}
	system("cls");
}

void Gui::vypisTypu()
{
	auto _CR = this->aplikacia.getCR();
	auto aktVybraty = this->aplikacia.getAktualneVybrany();
	std::cout << "Zadajte typ: ";
	std::string zadanyTyp;
	std::cin >> zadanyTyp;
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	zadanyTyp = algoritmus.zmenNaMalePismena(zadanyTyp);
	TypUJ typ;
	if (zadanyTyp == "kraj")
	{
		typ = TypKraj;
	}
	if (zadanyTyp == "soorp")
	{
		typ = TypSoorp;
	}
	if (zadanyTyp == "obec")
	{
		typ = TypObec;
	}

	this->algoritmus.vyfiltrujAlgoritmom(iteratorEH(&_CR, aktVybraty), iteratorEH(&_CR, nullptr), "", [&](UzemnaJednotka* uj, std::string s)->bool {
		if (uj->getTyp() == typ)
		{
			return true;
		}
		return false;
	});


	this->algoritmus.vypisVyfiltrovaneJednotky(false);

	_getch();
	system("cls");
}

void Gui::moznostVypisuKomparator()
{
	int volba;
	std::cout << "Vypísa územné jednotky [1]" << std::endl;
	std::cout << "Vypísa územné jednotky v abecednom poradí [2]" << std::endl;
	std::cout << "Vypísa územné jednotky pod¾a poètu spoluhlások v názve [3]" << std::endl;

	std::cin >> volba;
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	switch (volba)
	{
	case 1:
		this->algoritmus.vypisVyfiltrovaneJednotky(false);
		break;
	case 2:
		this->algoritmus.vytriedKomparatorom(this->algoritmus.porovnajAbecedne);
		this->algoritmus.vypisVyfiltrovaneJednotky(false);
		break;
	case 3:
		this->algoritmus.vytriedKomparatorom(this->algoritmus.porovnajPodlaPoctuSpoluhlasok);
		this->algoritmus.vypisVyfiltrovaneJednotky(true);
		break;
	default:
		std::cout << "Nesprávna vo¾ba" << std::endl;
		_getch();
		system("cls");
		break;
	}
}
