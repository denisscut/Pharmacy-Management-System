#pragma once
#include "repoAbstract.h"
#include <unordered_map>
using std::unordered_map;
class RepoProbabilitati : public RepoAbstract {
private:
	vector <Medicament> medicamenteVect;
	unordered_map < int, Medicament> medicamente;
	int nr;
	int prob;
public:
	RepoProbabilitati() {
		this->nr = 0;
		this->prob = 5;
	};
	RepoProbabilitati(const RepoProbabilitati& ot) = delete;

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
	void pass();
	void setProb10() {
		this->prob = 10;
	}
};