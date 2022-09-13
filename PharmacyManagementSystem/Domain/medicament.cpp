#include "medicament.h"
#include <assert.h>
#include <iostream>
#include <typeinfo>

string Medicament::getNume() const {
	return this->nume;
}
string Medicament::getProducator() const {
	return this->producator;
}
string Medicament::getSubstanta() const {
	return this->substanta;
}
double Medicament::getPret() const {
	return this->pret;
}

void Medicament::setProducator(string producatorNou) {
	this->producator = producatorNou;
}
void Medicament::setNume(string numeNou) {
	this->nume = numeNou;
}
void Medicament::setSubstanta(string substantaNoua) {
	this->substanta = substantaNoua;
}
void Medicament::setPret(double PretNou) {
	this->pret = PretNou;
}

ostream& operator<<(ostream& os, const Medicament& ob) {
	os << "Nume: " << ob.getNume() << " | Producator: " << ob.getProducator() << " | Substanta: " << ob.getSubstanta() << " | Pret: " << ob.getPret();
	return os;
}

bool Medicament::operator==(const Medicament& ot) {
	return (this->getNume() == ot.getNume() && this->getProducator() == ot.getProducator());
}

string Medicament::toString() {		
	return "Medicamentul: " + this->getNume() + ", " + this->getProducator() + ", " + this->getSubstanta() + ", " + std::to_string(this->getPret()) + "\n";
}