#include "DataCR.h"
#include <sstream>
#include <iostream>
#include <algorithm>
#include "Algoritmus.h"


DataCR::DataCR(std::string cestaSuboru)
{
	tabulkaKraje = new ds::adt::HashTable<std::string, ListUJ>;
	tabulkaSoorp = new ds::adt::HashTable<std::string, ListUJ>;
	tabulkaObce = new ds::adt::HashTable<std::string, ListObec>;

	if (!cestaSuboru.empty())
	{
		subor.open(cestaSuboru);
	}
	else
	{
		std::cout << "Nie je zadany subor.";
	}
}

DataCR::~DataCR()
{
	if (subor.is_open())
	{
		subor.close();
	}

	for (auto uj : this->kraje)
	{
		delete uj;
	}
	for (auto uj : this->soorp)
	{
		delete uj;
	}
	for (auto uj : this->obce)
	{
		delete uj;
	}

	this->vycistiTabulky();
}

void DataCR::nacitanieDat()
{
	_CR.emplaceRoot();
	auto koren = _CR.accessRoot();
	int indexKraj = 0;
	int indexSoorp = 0;
	int indexObec = 0;
	std::string riadok;
	std::vector<std::string> data;

	if (subor.is_open())
	{
		while (std::getline(subor, riadok))
		{
			std::stringstream ss(riadok);
			std::string stlpec;
			while (std::getline(ss, stlpec, ';'))
			{
				data.push_back(stlpec);
			}
			if (data[1].empty())
			{
				indexSoorp = 0;
				indexObec = 0;
				kraje.push_back(new UzemnaJednotka(data[2], data[0], "CR", TypUJ::TypKraj));
				_CR.emplaceSon(*koren, indexKraj).data_ = kraje.back();
				this->pridajDoTabulky(kraje.back(), this->tabulkaKraje);
				indexKraj++;
			}
			else
			{
				if (!jeUzSoorpZahrnuty(soorp, data[1]))
				{
					indexObec = 0;
					soorp.push_back(new UzemnaJednotka(data[2], data[1], data[0], TypUJ::TypSoorp));
					_CR.emplaceSon(*koren->sons_->access(indexKraj - 1)->data_, indexSoorp).data_ = soorp.back();
					this->pridajDoTabulky(soorp.back(), this->tabulkaSoorp);
					indexSoorp++;
				}
				if (data[13] != "2" && data[13] != "1")
				{
					data[13] = "0";
				}
				if (data[14] != "1")
				{
					data[14] = "0";
				}
				if (data[15] != "1")
				{
					data[15] = "0";
				}
				obce.push_back(new Obec(data[4], data[5], data[1], data[6], data[9], data[10], data[11], data[12], data[14], data[15], data[13], TypUJ::TypObec));
				_CR.emplaceSon(*koren->sons_->access(indexKraj - 1)->data_->sons_->access(indexSoorp - 1)->data_, indexObec).data_ = obce.back();
				this->pridajDoTabulky(obce.back(), this->tabulkaObce);
				indexObec++;
			}

			data.clear();
		}
	}
}

bool DataCR::jeUzSoorpZahrnuty(std::vector<UzemnaJednotka*> soorp, std::string kod)
{
	bool zahrnuty = false;
	for (auto s : soorp)
	{
		if (s->getKod() == kod)
		{
			zahrnuty = true;
			break;
		}
	}

	return zahrnuty;
}

std::vector<UzemnaJednotka*> DataCR::getKraje()
{
	return kraje;
}

std::vector<UzemnaJednotka*> DataCR::getSoorp()
{
	return soorp;
}

std::vector<Obec*> DataCR::getObce()
{
	return obce;
}

ds::amt::MultiWayEH<UzemnaJednotka*>* DataCR::getCR()
{
	return &_CR;
}

ds::adt::HashTable<std::string, ListUJ>* DataCR::getTabulkaKraje()
{
	return tabulkaKraje;
}

ds::adt::HashTable<std::string, ListUJ>* DataCR::getTabulkaSoorp()
{
	return tabulkaSoorp;
}

ds::adt::HashTable<std::string, ListObec>* DataCR::getTabulkaObce()
{
	return tabulkaObce;
}

void DataCR::vycistiTabulky()
{
	for (auto i = tabulkaKraje->begin(); i != tabulkaKraje->end(); ++i)
	{
		delete (*i).data_;
	}
	for (auto i = tabulkaSoorp->begin(); i != tabulkaSoorp->end(); ++i)
	{
		delete (*i).data_;
	}
	for (auto i = tabulkaObce->begin(); i != tabulkaObce->end(); ++i)
	{
		delete (*i).data_;
	}

	delete tabulkaKraje;
	delete tabulkaSoorp;
	delete tabulkaObce;
}

