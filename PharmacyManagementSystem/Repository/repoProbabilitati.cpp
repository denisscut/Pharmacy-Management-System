#pragma once
#include "repoProbabilitati.h"
#include "repository.h"
bool RepoProbabilitati::exists(const Medicament& s) {
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

void RepoProbabilitati::store(const Medicament& med) {
	pass();
	if (exists(med)) {
		throw RepoException("Medicamentul cu numele " + med.getNume() + " si producatorul " + med.getProducator() + " exista deja in lista\n");
	}
	auto it = medicamente.find(nr);
	medicamente.insert(it, { nr, med });
	nr++;
}

const Medicament& RepoProbabilitati::find(string nume, string producator) {
	pass();
	auto it = std::find_if(this->medicamente.begin(), this->medicamente.end(), [nume, producator](auto item) {
		Medicament med = item.second;
		if (med.getNume() == nume && med.getProducator() == producator)
			return true;
		return false;
		});
	if (it == this->medicamente.end())
		throw RepoException("Medicamentul cu numele " + nume + " si producatorul " + producator + " nu exista in lista");
	return it->second;
}


void RepoProbabilitati::deleteMedicament(string nume, string producator) {
	//auto it = std::remove_if(this->medicamente.begin(), this->medicamente.end(), [nume, producator](auto item) {
	//	Medicament med = item.second;
	//	if (med.getNume() == nume && med.getProducator() == producator)
	//		return true;
	//	return false;
	//	});
	pass();
	auto it = medicamente.begin();
	for (; it != medicamente.end(); ++it) {
		if (it->second.getNume() == nume && it->second.getProducator() == producator)
			break;
	}

	if (it == this->medicamente.end())
		throw RepoException("Medicamentul cu numele " + nume + " si producatorul " + producator + " nu exista.\n");
	this->medicamente.erase(it);
}


void RepoProbabilitati::modifyMedicament(const Medicament& med, const Medicament& newMed) {
	//std::replace_if(this->medicamente.begin(), this->medicamente.end(), [med](auto item) {Medicament md = item.second;  return md == med; }, newMed);
	pass();
	bool stop = 0;
	for (auto it = medicamente.begin(); it != medicamente.end() && !stop; ++it) {
		if (it->second == med) {
			it->second = newMed;
			stop = 1;
		}
	}
}


int RepoProbabilitati::getNumberOfMedicamentsByPrice(double price) {
	pass();
	return static_cast<int>(std::count_if(this->medicamente.begin(), this->medicamente.end(), [price](auto item) {Medicament med = item.second;  return med.getPret() > price; }));
}

vector<Medicament>& RepoProbabilitati::getAllMedicamente() {
	medicamenteVect.erase(medicamenteVect.begin(), medicamenteVect.end());
	for (auto it = medicamente.begin(); it != medicamente.end(); ++it) {
		medicamenteVect.push_back(it->second);
	}
	return medicamenteVect;
}


vector<Medicament> RepoProbabilitati::filtrare(function <bool(Medicament)> comp) {
	vector<Medicament> newVect;
	pass();
	for (auto it = medicamente.begin(); it != medicamente.end(); ++it) {
		newVect.push_back(it->second);
	}
	auto it = std::copy_if(newVect.begin(), newVect.end(), newVect.begin(), comp);
	newVect.resize(std::distance(newVect.begin(), it));
	return newVect;
}


vector<Medicament> RepoProbabilitati::sortare(function <bool(Medicament, Medicament)> comp) {
	//pass();
	vector<Medicament> newVect;
	for (auto it = medicamente.begin(); it != medicamente.end(); ++it) {
		newVect.push_back(it->second);
	}
	std::sort(newVect.begin(), newVect.end(), comp);
	return newVect;
}

void RepoProbabilitati::pass() {
	std::mt19937 mt{ std::random_device{}() };
	std::uniform_int_distribution<> dist(0, static_cast<int>(11) - 1);
	int rndNr = dist(mt);// numar aleator intre [0,size-1]
	if (rndNr > this->prob)
		throw(RepoException("Nu se poate executa functia. Mai incearca o data!"));
}