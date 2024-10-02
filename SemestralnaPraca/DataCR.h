#pragma once
#include <vector>
#include <fstream>
#include "Obec.h"
#include <libds/amt/explicit_hierarchy.h>
#include <libds/adt/table.h>
#include <libds/adt/list.h>
#include "Algoritmus.h"

using ListUJ = ds::adt::SinglyLinkedList<UzemnaJednotka*>*;
using ListObec = ds::adt::SinglyLinkedList<Obec*>*;
class DataCR
{
private:
	std::ifstream subor;
	std::vector<UzemnaJednotka*> kraje;
	std::vector<UzemnaJednotka*> soorp;
	std::vector<Obec*> obce;
	bool jeUzSoorpZahrnuty(std::vector<UzemnaJednotka*> soorp, std::string kod);
	template<typename T>
	void pridajDoTabulky(T* uzemnaJednotka, ds::adt::HashTable<std::string, ds::adt::SinglyLinkedList<T*>*>* tabulka);

	ds::amt::MultiWayEH<UzemnaJednotka*> _CR;

	
	ds::adt::HashTable<std::string, ListUJ>* tabulkaKraje;
	ds::adt::HashTable<std::string, ListUJ>* tabulkaSoorp;
	ds::adt::HashTable<std::string, ListObec>* tabulkaObce;

	void vycistiTabulky();

public:
	DataCR(std::string cestaSuboru);
	~DataCR();
	void nacitanieDat();
	std::vector<UzemnaJednotka*> getKraje();
	std::vector<UzemnaJednotka*> getSoorp();
	std::vector<Obec*> getObce();
	ds::amt::MultiWayEH<UzemnaJednotka*>* getCR();
	ds::adt::HashTable<std::string, ListUJ>* getTabulkaKraje();
	ds::adt::HashTable<std::string, ListUJ>* getTabulkaSoorp();
	ds::adt::HashTable<std::string, ListObec>* getTabulkaObce();
};

template<typename T>
inline void DataCR::pridajDoTabulky(T* uzemnaJednotka, ds::adt::HashTable<std::string, ds::adt::SinglyLinkedList<T*>*>* tabulka)
{
	auto nazov = Algoritmus::zmenNaMalePismena(uzemnaJednotka->getNazov());
	
	if (!tabulka->contains(nazov))
	{
		auto k = new ds::adt::SinglyLinkedList<T*>;
		k->insertLast(uzemnaJednotka);
		tabulka->insert(nazov, k);
	}
	else
	{
		auto x = tabulka->find(nazov);
		x->insertLast(uzemnaJednotka);
	}
}
