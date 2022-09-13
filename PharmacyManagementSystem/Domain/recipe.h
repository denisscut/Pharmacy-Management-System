#pragma once
#include <vector>
#include "../Domain/medicament.h"
#include <random>
#include <fstream>
#include "observer.h"
#include "../Repository/repoAbstract.h"
using std::vector;

class Recipe : public Observable{
private:
	vector<Medicament> medicamente;
	RepoAbstract& repo;
public:
	Recipe(RepoAbstract& repo) : repo{ repo }{};
	void eraseRecipe();
	void addToRecipe(Medicament med);
	vector <Medicament>& getRecipe();
	void generateRecipe(int number, vector <Medicament> v);
	void generateRecipeWithoutVec(int number);
	void exportCSV(string nameOfFile);
	void exportHTML(string nameOfFile);
};