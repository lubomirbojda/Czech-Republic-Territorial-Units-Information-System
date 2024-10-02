#pragma once
#include <string>

enum TypUJ {
	TypKraj,
	TypSoorp,
	TypObec,
	TypCR
};

class UzemnaJednotka
{
private:
	const std::string samohlasky = "aeiouyáéíóúùýì-\"\ ";
	bool jeSpoluhlaska(char znak);
	void vypocitajPocetSpoluhlasok();
protected:
	std::string nazov;
	std::string kod;
	std::string kodNadradenejUJ;
	TypUJ typUJ;
	int pocetSpoluhlasok = 0;
public:
	UzemnaJednotka(std::string nazovUzemnejJednotky, std::string kodUzemnejJednotky, std::string kodNadradenejUzemnejJednotky, TypUJ typ);
	std::string getKod();
	std::string getNazov();
	std::string getKodNadradenejUJ();
	TypUJ getTyp();
	virtual void vypisInformacie();
	int getPocetSpoluhlasok();
};