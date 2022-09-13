#pragma once
#include "repository.h"

bool Repository::exists(const Medicament& s) {
	bool exista = false;
	try {
		find(s.getNume(), s.getProducator());
		exista = true;
	}
	catch (RepoException) {
		exista = false;
	}
	return exista;
}

void Repository::store(const Medicament& med) {
	if (exists(med)) {
		throw RepoException("Medicamentul cu numele " + med.getNume() + " si producatorul " + med.getProducator() + " exista deja in lista\n");
	}
	this->medicamente.push_back(med);
}

const Medicament& Repository::find(string nume, string producator) {
	auto it = std::find_if(this->medicamente.begin(), this->medicamente.end(), [nume, producator](Medicament med) {
		if (med.getNume() == nume && med.getProducator() == producator)
			return true;
		return false;
		});
	if (it == this->medicamente.end())
		throw RepoException("Medicamentul cu numele " + nume + " si producatorul " + producator + " nu exista in lista");
	return *it;
}


void Repository::deleteMedicament(string nume, string producator) {
	auto it = std::remove_if(this->medicamente.begin(), this->medicamente.end(), [nume, producator](Medicament med) {
		if (med.getNume() == nume && med.getProducator() == producator)
			return true;
		return false;
		});
	if (it == this->medicamente.end())
		throw RepoException("Medicamentul cu numele " + nume + " si producatorul " + producator + " nu exista.\n");
	this->medicamente.erase(it, this->medicamente.end());
}


void Repository::modifyMedicament(const Medicament& med, const Medicament& newMed) {
	std::replace_if(this->medicamente.begin(), this->medicamente.end(), [med](Medicament md) {return md == med; }, newMed);
}


int Repository::getNumberOfMedicamentsByPrice(double price) {
	return static_cast<int>(std::count_if(this->medicamente.begin(), this->medicamente.end(), [price](Medicament med) {return med.getPret() > price; }));
}

vector<Medicament>& Repository::getAllMedicamente() {
	return this->medicamente;
}


vector<Medicament> Repository::filtrare(function <bool(Medicament)> comp) {
	vector<Medicament> newVect(this->medicamente.size());
	auto it = std::copy_if(this->medicamente.begin(), this->medicamente.end(), newVect.begin(), comp);
	newVect.resize(std::distance(newVect.begin(), it));
	return newVect;
}


vector<Medicament> Repository::sortare(function <bool(Medicament, Medicament)> comp) {
	vector<Medicament> newVect(this->medicamente);
	std::sort(newVect.begin(), newVect.end(), comp);
	return newVect;
}