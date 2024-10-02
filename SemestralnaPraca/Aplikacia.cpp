#include "Aplikacia.h"
#include "Algoritmus.h"
#include <string>


Aplikacia::Aplikacia()
{
	dataCR_.nacitanieDat();
	_CR = dataCR_.getCR();
	_CR->accessRoot()->data_ = new UzemnaJednotka("CR", "", "", TypUJ::TypCR);
	aktVybraty = _CR->accessRoot();

	tabulkaKraje = dataCR_.getTabulkaKraje();
	tabulkaSoorp = dataCR_.getTabulkaSoorp();
	tabulkaObce = dataCR_.getTabulkaObce();
}

Aplikacia::~Aplikacia()
{
	delete _CR->accessRoot()->data_;
}

void Aplikacia::setAktualneVybrany(ds::amt::MultiWayExplicitHierarchyBlock<UzemnaJednotka*>* aktualny)
{
	this->aktVybraty = aktualny;
}

ds::amt::MultiWayExplicitHierarchyBlock<UzemnaJednotka*>* Aplikacia::getAktualneVybrany()
{
	return aktVybraty;
}

ds::amt::MultiWayEH<UzemnaJednotka*> Aplikacia::getCR()
{
	return *_CR;
}

void Aplikacia::vyhladajUJVTabulke(std::string typUJ, std::string nazovUJ)
{
	if (typUJ == "kraj")
	{
		this->najdiVTabulkeAVypis(nazovUJ, tabulkaKraje);
	}
	else if (typUJ == "soorp")
	{
		this->najdiVTabulkeAVypis(nazovUJ, tabulkaSoorp);
	}
	else if (typUJ == "obec")
	{
		this->najdiVTabulkeAVypis(nazovUJ, tabulkaObce);
	}
}

std::vector<UzemnaJednotka*> Aplikacia::getKraje()
{
	return dataCR_.getKraje();
}

std::vector<UzemnaJednotka*> Aplikacia::getSoorp()
{
	return dataCR_.getSoorp();
}

std::vector<Obec*> Aplikacia::getObce()
{
	return dataCR_.getObce();
}

