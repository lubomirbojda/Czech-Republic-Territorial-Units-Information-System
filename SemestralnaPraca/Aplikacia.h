#pragma once
#include "DataCR.h"
#include <libds/amt/explicit_hierarchy.h>
#include "Algoritmus.h"
#include <conio.h>
#include <libds/adt/table.h>
#include <libds/adt/list.h>
#include "Algoritmus.h"
class Aplikacia
{
private:
	DataCR dataCR_ = DataCR("CR.csv");
	ds::amt::MultiWayEH<UzemnaJednotka*>* _CR;
	ds::amt::MultiWayExplicitHierarchyBlock<UzemnaJednotka*>* aktVybraty;
	ds::adt::HashTable<std::string, ListUJ>* tabulkaKraje;
	ds::adt::HashTable<std::string, ListUJ>* tabulkaSoorp;
	ds::adt::HashTable<std::string, ListObec>* tabulkaObce;

	template<typename T>
	void najdiVTabulkeAVypis(std::string kod, ds::adt::HashTable<std::string, ds::adt::SinglyLinkedList<T*>*>* tabulka);


public:
	Aplikacia();
	~Aplikacia();
	void setAktualneVybrany(ds::amt::MultiWayExplicitHierarchyBlock<UzemnaJednotka*>* aktualny);
	ds::amt::MultiWayExplicitHierarchyBlock<UzemnaJednotka*>* getAktualneVybrany();
	ds::amt::MultiWayEH<UzemnaJednotka*> getCR();
	void vyhladajUJVTabulke(std::string typUJ, std::string nazovUJ);
	std::vector<UzemnaJednotka*> getKraje();
	std::vector<UzemnaJednotka*> getSoorp();
	std::vector<Obec*> getObce();
};

template<typename T>
inline void Aplikacia::najdiVTabulkeAVypis(std::string kod, ds::adt::HashTable<std::string, ds::adt::SinglyLinkedList<T*>*>* tabulka)
{
	if (tabulka->contains(kod))
	{
		auto ujList = tabulka->find(kod);
		for (auto uj : *ujList)
		{
			uj->vypisInformacie();
		}
	}
}
