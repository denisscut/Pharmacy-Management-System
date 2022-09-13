#pragma once
#include <vector>
#include <string>
#include "../Domain/medicament.h"
#include <functional>
#include <algorithm>
#include <random>
#include <iostream>
#include <fstream>
#include "repoAbstract.h"

using std::string;
using std::function;
using std::vector;

/// @brief Clasa de exceptii specifica pentru repository
class RepoException {
private:
	string errorMsg;
public:
	RepoException(string errorMsg) :errorMsg{ errorMsg } {};
	string getErrorMessage() {
		return this->errorMsg;
	}
};

class Repository : public RepoAbstract {
private:
	vector <Medicament> medicamente;
public:
	Repository() {};
	Repository(const Repository& ot) = delete;

	/// Adauga un medicament in lista
	/// @param med: medicamentul care se adauga (Medicament)
	/// @return -
	/// post: medicamentul va fi adaugat in lista
	///
	/// @throws: RepoException daca un medicament cu acelasi nume si acelasi producator
	///		 exista deja
	void store(const Medicament& med) override;

	/// Cauta un medicament cu numele si producatorul dat
	/// @param nume: numele dupa care se cauta
	/// @param producator: producatorul dupa care se cauta
	/// @returns: entitatea Medicament cu numele si producatorul dat (daca aceasta exista)
	/// @throws: RepoException daca nu exista medicament cu numele si producatorul dat
	const Medicament& find(string nume, string producator) override;


	int getNumberOfMedicamentsByPrice(double price) override;

	/// Verifica daca un medicament dat exista in lista
	/// @param med : medicamentul care se cauta in lista
	/// @return: true daca medicamentul exista, false altfel
	bool exists(const Medicament& med) override;


	/// Returneaza o lista cu toate medicamentele
	/// @return: lista cu medicamente (vector of Medicament objects)
	vector<Medicament>& getAllMedicamente() override;


	/// @brief Sterge un medicament cu numele nume si producatorul producator, daca exista
	/// @param nume - numele medicamentului care se sterge (string)
	/// @param producator - producatorul medicamentului care se sterge (string)
	void deleteMedicament(string nume, string producator) override;

	/// @brief Modifica un medicament
	/// @param med - medicamentul care va fi modificat (Medicament)
	void modifyMedicament(const Medicament& med, const Medicament& medNou) override;


	vector<Medicament> filtrare(function <bool(Medicament)> comp) override;
	vector<Medicament> sortare(function <bool(Medicament, Medicament)> comp) override;
};