#pragma once
#include <string>
#include "Aplikacia.h"
class Gui
{
public:
	void spustiAplikaciu();

private:
	using iteratorEH = ds::amt::MultiWayExplicitHierarchy<UzemnaJednotka*>::PreOrderHierarchyIterator;
	Aplikacia aplikacia;
	Algoritmus algoritmus;

	void uroven1();
	bool koniec = true;
	int _input = 0;
	int _uroven = 0;
	std::string hladanyText;
	void zadajText();
	void prehladavanie();
	void vypisMoznosti(int aktUroven);
	void vykonajMoznost(int aktUroven, int input);
	void vybrat();
	void vypisTypu();
	void moznostVypisuKomparator();
};

