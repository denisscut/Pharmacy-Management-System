#pragma once
#include <string>
using std::string;
using std::ostream;
class Medicament {
private:
	std::string nume, producator, substanta;
	double pret;
public:
	//Constructor default sters
	Medicament() {
		this->pret = 0;
	};
	//Constructor
	Medicament(string nume, double pret, string producator, string substanta) : nume{ nume }, pret{ pret }, producator{ producator },
		substanta{ substanta }{}
	////Constructor de copiere
	Medicament(const Medicament& ot) : nume{ ot.nume }, pret{ ot.pret }, producator{ ot.producator }, substanta{ ot.substanta }{}

	string getNume() const;
	string getProducator() const;
	string getSubstanta() const;
	double getPret() const;
	void setNume(string numeNou);
	void setProducator(string producatorNou);
	void setSubstanta(string substantaNoua);
	void setPret(double pret);
	bool operator==(const Medicament& ot);
	string toString();
	friend ostream& operator<<(ostream& os, const Medicament& ob);
};
