#pragma once
#include "../Repository/repository.h"
#include "../Repository/repoProbabilitati.h"
#include "../Validators/validators.h"
#include <memory>
#include "../Domain/undo.h"
#include "../Domain/recipe.h"
class Service {
private:
	RepoAbstract& repo;
	MedicamentValidator& val;
	vector <std::unique_ptr < undoAction>> undoActions;

	Recipe recipe;

public:
	Service(RepoAbstract& medRepo, MedicamentValidator& val) :repo{ medRepo }, val{ val }, recipe{ medRepo }{};
	/// constructor de copiere
	Service(const Service& ot) = delete;

	/// @brief Adauga un medicament cu numele nume, pretul pret, producatorul producator si substanta substanta
	/// @param nume - numele medicamentului care se adauga (string)
	/// @param pret - pretul medicamentului care se adauga (double)
	/// @param producator - producatorul medicamentului care se adauga (string)
	/// @param substanta - substanta medicamentului care se adauga (string)
	void addMedicament(string nume, double pret, string producator, string substanta);

	/// Returneaza un vector cu toate medicamentele disponibile
	/// @return: lista cu toate medicamentele disponibile (vector cu obiecte de tip Medicament)
	vector<Medicament>& getAllMedicamente() {
		return this->repo.getAllMedicamente();
	}

	void undo();

	int getNumberOfMedicamentsByPrice(double price);

	/// @brief Sterge un medicament cu numele nume si producatorul producator, daca exista
	/// @param nume - numele medicamentului care se sterge (string)
	/// @param producator - producatorul medicamentului care se sterge (string)
	void deleteMedicament(string nume, string producator);


	/// @brief Modifica un medicament cu numele nume si producatorul producator, daca exista, daca nu 
	/// arunca exceptie.
	/// @param nume - numele medicamentului (string)
	/// @param producator - producatorul medicamentului (string)
	/// @param numeNou - numele nou al medicamentului (string)
	/// @param pretNou - pretul nou al medicamentului (double)
	/// @param producatorNou - producatorul nou al medicamentului (string)
	/// @param substantaNoua - substanta noua a medicamentului (string)
	void modifyMedicament(string nume, string producator, string numeNou, double pretNou, string producatorNou, string substantaNoua);


	/// @brief Verifica daca exista un medicament cu numele nume si producatorul producator
	/// @param nume - numele medicamentului (string)
	/// @param producator - producatorul medicamentului (producator)
	/// @return true daca exista, false altfel
	bool exists(string nume, string producator);


	/// @brief Cauta un medicament dupa numele nume si producatorul producator
	/// @param nume - numele medicamentului (string)
	/// @param producator - producatorul medicamentului (string)
	/// @return daca il gaseste il returneaza (Medicament), arunca exceptie altfel
	const Medicament& findMedicament(string nume, string producator);

	vector<Medicament> filtrarePret(double pret);

	vector<Medicament> filtrareSubstanta(string substanta);

	vector <Medicament> sortareSubstSiPret();
	vector <Medicament> sortareProducator();
	vector <Medicament> sortareNume();


	void eraseRecipe();
	void addToRecipe(Medicament med);
	vector <Medicament>& getRecipe();
	Recipe& getRecipeClass() {
		return recipe;
	}
	void generateRecipe(int number, vector <Medicament> v);
	void exportRecipe(string nameOfFile);
};
