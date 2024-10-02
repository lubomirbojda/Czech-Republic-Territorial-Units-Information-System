#include "UzemnaJednotka.h"
#include <iostream>
#include "Algoritmus.h"

UzemnaJednotka::UzemnaJednotka(std::string nazovUzemnejJednotky, std::string kodUzemnejJednotky, std::string kodNadradenejUzemnejJednotky, TypUJ typ)
{
	nazov = nazovUzemnejJednotky;
	kod = kodUzemnejJednotky;
	kodNadradenejUJ = kodNadradenejUzemnejJednotky;
	typUJ = typ;
	this->vypocitajPocetSpoluhlasok();
}

std::string UzemnaJednotka::getKod()
{
	return kod;
}

std::string UzemnaJednotka::getNazov()
{
	return nazov;
}

std::string UzemnaJednotka::getKodNadradenejUJ()
{
	return kodNadradenejUJ;
}

TypUJ UzemnaJednotka::getTyp()
{
	return typUJ;
}

void UzemnaJednotka::vypisInformacie()
{
	std::cout << "\n" << nazov + ":" << "\n";
	std::cout << "\t" << "kód: " << kod << "\n";
}

int UzemnaJednotka::getPocetSpoluhlasok()
{
	return this->pocetSpoluhlasok;
}

bool UzemnaJednotka::jeSpoluhlaska(char znak)
{
	if (samohlasky.find(znak) == std::string::npos)
		return true;

	return false;
}

void UzemnaJednotka::vypocitajPocetSpoluhlasok()
{
	auto naz = Algoritmus::zmenNaMalePismena(nazov);
	for (auto znak : naz)
	{
		if (this->jeSpoluhlaska(znak))
		{
			pocetSpoluhlasok++;
		}
	}

	int pozicia = naz.find("ch");

	while (pozicia != std::string::npos) {
		pocetSpoluhlasok--;
		pozicia = naz.find("ch", pozicia + naz.length());
	}
}
