#pragma once
#include "../Domain/medicament.h"
#include <vector>
#include <functional>
using std::vector;
using std::function;
class RepoAbstract {
public:
	RepoAbstract() {};

	virtual void store(const Medicament& med) = 0;

	virtual const Medicament& find(string nume, string producator) = 0;


	virtual int getNumberOfMedicamentsByPrice(double price) = 0;

	virtual bool exists(const Medicament& med) = 0;

	virtual vector<Medicament>& getAllMedicamente() = 0;

	virtual void deleteMedicament(string nume, string producator) = 0;

	virtual void modifyMedicament(const Medicament& med, const Medicament& medNou) = 0;


	virtual vector<Medicament> filtrare(function <bool(Medicament)> comp) = 0;
	virtual vector<Medicament> sortare(function <bool(Medicament, Medicament)> comp) = 0;
};