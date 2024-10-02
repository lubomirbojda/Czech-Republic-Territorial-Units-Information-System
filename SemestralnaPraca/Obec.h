#pragma once
#include "UzemnaJednotka.h"
#include <iostream>
class Obec : public UzemnaJednotka
{
public:
	Obec(std::string nazov, std::string kod, std::string kodNadradenejUJ, std::string typObce, std::string katastralnaVymera, std::string celkovyPocetObyvatelov,
		std::string pocetObyvatelovOd0do14, std::string pocetObyvatelovOd65Vyssie, std::string vodovod, std::string plyn, std::string kanalizacia, TypUJ typ) : UzemnaJednotka(nazov, kod, kodNadradenejUJ, typ) {


		_typObce = typObce;
		_katastralnaVymera = zmenStringNaInt(katastralnaVymera);
		_celkovyPocetObyvatelov = zmenStringNaInt(celkovyPocetObyvatelov);
		_pocetObyvatelovOd0do14 = zmenStringNaInt(pocetObyvatelovOd0do14);
		_pocetObyvatelovOd65Vyssie = zmenStringNaInt(pocetObyvatelovOd65Vyssie);

		switch (zmenStringNaInt(vodovod)) {
		case 0:
			_vodovod = false;
			break;
		case 1:
			_vodovod = true;
			break;
		default:
			_vodovod = false;
		}

		switch (zmenStringNaInt(plyn)) {
		case 0:
			_plyn = false;
			break;
		case 1:
			_plyn = true;
			break;
		default:
			_plyn = false;
		}

		switch (zmenStringNaInt(kanalizacia)) {
		case 0:
			_kanalizacia = false;
			_kanalizaciaCOV = false;
			break;
		case 1:
			_kanalizacia = true;
			_kanalizaciaCOV = false;
			break;
		case 2:
			_kanalizacia = true;
			_kanalizaciaCOV = true;
			break;
		default:
			_kanalizacia = false;
		}
	}

	static int zmenStringNaInt(std::string retazec) {
		retazec.erase(std::remove_if(retazec.begin(), retazec.end(), std::isspace), retazec.end());
		return std::stoi(retazec);
	}

	void vypisInformacie() override {
		std::cout << "\n" << nazov + ":" << "\n";
		std::cout << "\t" << "kód: " << kod << "\n";
		std::cout << "\t" << "katastrálna výmera: " << _katastralnaVymera << "\n";
		std::cout << "\t" << "poèet obyvate¾ov: " << _celkovyPocetObyvatelov << "\n";
		std::cout << "\t" << "vodovod: " << (_vodovod ? "Áno" : "Nie") << "\n";
		std::cout << "\t" << "plyn: " << (_plyn ? "Áno" : "Nie") << "\n";
		std::cout << "\t" << "kanalizácia: " << (_kanalizacia ? "Áno" : "Nie") << "\n";
		std::cout << "\t" << "kanalizácia(ÈOV): " << (_kanalizaciaCOV ? "Áno" : "Nie") << "\n";
	};

private:
	std::string _typObce;
	int _katastralnaVymera;
	int _celkovyPocetObyvatelov;
	int _pocetObyvatelovOd0do14;
	int _pocetObyvatelovOd65Vyssie;
	bool _vodovod;
	bool _plyn;
	bool _kanalizacia;
	bool _kanalizaciaCOV;

};

