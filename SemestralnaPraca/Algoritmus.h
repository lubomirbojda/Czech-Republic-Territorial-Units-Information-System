#pragma once
#include <string>
#include <algorithm>
#include <vector>
#include <iostream>
#include <functional>
#include "UzemnaJednotka.h"
#include <libds/adt/sorts.h>
#include <locale>
#include <codecvt>

class Algoritmus {
public:
	template<typename T>
	void vyfiltrujAlgoritmom(T begin, T end, std::string hladanyText, std::function<bool(UzemnaJednotka*, std::string)> predikat);
	static std::string zmenNaMalePismena(std::string retazec);
	void vypisVyfiltrovaneJednotky(bool pocetSpoluhlasok);
	void vytriedKomparatorom(std::function<bool(UzemnaJednotka*, UzemnaJednotka*)> predikat);

	std::function<bool(UzemnaJednotka*, std::string)> obsahujeText = [&](UzemnaJednotka* uj, std::string zadanyText)-> bool {
		auto text = this->zmenNaMalePismena(zadanyText);
		if (zmenNaMalePismena(uj->getNazov()).find(text) != std::string::npos)
		{
			return true;
		}
		return false;
	};

	std::function<bool(UzemnaJednotka*, std::string)> zacinajuNaText = [&](UzemnaJednotka* uj, std::string zadanyText)-> bool {
		auto text = this->zmenNaMalePismena(zadanyText);
		if (zmenNaMalePismena(uj->getNazov()).rfind(text, 0) == 0)
		{
			return true;
		}
		return false;
	};

	std::function<bool(UzemnaJednotka*, UzemnaJednotka*)> porovnajAbecedne = [&](UzemnaJednotka* uj1, UzemnaJednotka* uj2)->bool {
		std::string slovo1 = zmenNaMalePismena(uj1->getNazov());
		std::string slovo2 = zmenNaMalePismena(uj2->getNazov());

		return std::use_facet<std::collate<char>>(std::locale()).compare(slovo1.data(), slovo1.data() + slovo1.length(),
			slovo2.data(), slovo2.data() + slovo2.length()) < 0;
	};

	std::function<bool(UzemnaJednotka*, UzemnaJednotka*)> porovnajPodlaPoctuSpoluhlasok = [&](UzemnaJednotka* uj1, UzemnaJednotka* uj2)->bool {
		return uj1->getPocetSpoluhlasok() > uj2->getPocetSpoluhlasok();
	};

private:
	ds::adt::HeapSort<UzemnaJednotka*> heapSort;
	ds::amt::ImplicitSequence<UzemnaJednotka*> sekvenciaVyfiltrovanychUJ;

};

 

inline std::string Algoritmus::zmenNaMalePismena(std::string retazec)
{
	std::transform(retazec.begin(), retazec.end(), retazec.begin(),
		[](unsigned char c) { return std::tolower(c); });
	return retazec;
}


template<typename T>
inline void Algoritmus::vyfiltrujAlgoritmom(T begin, T end, std::string hladanyText, std::function<bool(UzemnaJednotka*, std::string)> predikat)
{
	this->sekvenciaVyfiltrovanychUJ.clear();
	for (T i = begin; i != end; ++i)
	{
		UzemnaJednotka* uj = *i;
		if (uj->getTyp() != TypCR)
		{
			if (predikat(uj, hladanyText))
			{
				this->sekvenciaVyfiltrovanychUJ.insertLast().data_ = uj;
			}
		}
	}
}

inline void Algoritmus::vypisVyfiltrovaneJednotky(bool pocetSpoluhlasok)
{
	if (this->sekvenciaVyfiltrovanychUJ.size() != 0)
	{
		for (auto uj : this->sekvenciaVyfiltrovanychUJ)
		{
			std::cout << uj->getKod() << " " << uj->getNazov();
			if (pocetSpoluhlasok)
			{
				std::cout << "  - [" << uj->getPocetSpoluhlasok() << "]";
			}
			std::cout << std::endl;
		}
	}
	else
	{
		std::cout << "Žiadne územné jednotky sa nenašli." << std::endl;
	}
}

inline void Algoritmus::vytriedKomparatorom(std::function<bool(UzemnaJednotka*, UzemnaJednotka*)> predikat)
{
	if (this->sekvenciaVyfiltrovanychUJ.size() >= 2)
		this->heapSort.sort(this->sekvenciaVyfiltrovanychUJ, predikat);


}


