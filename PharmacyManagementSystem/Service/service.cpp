#include "service.h"
#include <iostream>

void Service::undo() {
	if (undoActions.empty()) {
		throw UndoException("Nu mai exista operatii");
	}
	std::unique_ptr<undoAction> action = std::move(undoActions.back());
	undoActions.pop_back();
	action->doUndo();
}


void Service::addMedicament(string nume, double pret, string producator, string substanta) {
	Medicament m1{ nume, pret, producator, substanta };
	val.valideaza(m1);
	repo.store(m1);
	undoActions.push_back(std::make_unique<undoAdd>(m1, repo));
}


void Service::deleteMedicament(string nume, string producator) {
	val.valideazaNumeSiProd(nume, producator);
	Medicament med = repo.find(nume, producator);
	repo.deleteMedicament(nume, producator);
	undoActions.push_back(std::make_unique<undoDelete>(med, repo));
}


bool Service::exists(string nume, string producator) {
	val.valideazaNumeSiProd(nume, producator);
	auto m = repo.find(nume, producator);
	return true;
}


int Service::getNumberOfMedicamentsByPrice(double price) {
	return repo.getNumberOfMedicamentsByPrice(price);
}


void Service::modifyMedicament(string nume, string producator, string numeNou, double pretNou, string producatorNou, string substantaNoua) {
	Medicament medNou{ numeNou, pretNou, producatorNou, substantaNoua };
	val.valideaza(medNou);
	const Medicament& med = repo.find(nume, producator);
	Medicament medTmp = med;
	if (repo.exists(medNou) == true)
		throw RepoException("Medicament cu numele " + numeNou + " si producatorul " + producatorNou + " exista deja in lista");
	repo.modifyMedicament(med, medNou);
	undoActions.push_back(std::make_unique<undoModify>(medNou, medTmp, repo));
}


const Medicament& Service::findMedicament(string nume, string producator) {
	const Medicament& m1{ nume, 3, producator, "test" };
	val.valideaza(m1);
	const Medicament& med = repo.find(nume, producator);
	return med;
}



vector <Medicament> Service::filtrarePret(double pret) {
	const Medicament& m1{ "test", pret, "test", "test" };
	val.valideaza(m1);
	return repo.filtrare([pret](Medicament el) {return el.getPret() == pret; });
}

vector <Medicament> Service::filtrareSubstanta(string substanta) {
	const Medicament& m1{ "test", 3, "test", substanta };
	val.valideaza(m1);
	return repo.filtrare([substanta](Medicament el) {return el.getSubstanta() == substanta; });
}


vector <Medicament> Service::sortareNume() {
	return repo.sortare([](Medicament el, Medicament el2) {return el.getNume() < el2.getNume(); });
}


vector <Medicament> Service::sortareProducator() {
	return repo.sortare([](Medicament el, Medicament el2) {return el.getProducator() < el2.getProducator(); });
}


vector <Medicament> Service::sortareSubstSiPret() {
	return repo.sortare([](Medicament el, Medicament el2) {
		if (el.getSubstanta() < el2.getSubstanta())
			return true;
		else if (el.getSubstanta() == el2.getSubstanta() && el.getPret() < el2.getPret())
			return true;
		return false;
		});
}


void Service::eraseRecipe() {
	this->recipe.eraseRecipe();
}


void Service::addToRecipe(Medicament med) {
	recipe.addToRecipe(med);
}


vector <Medicament>& Service::getRecipe() {
	return recipe.getRecipe();
}


void Service::generateRecipe(int number, vector <Medicament> v) {
	recipe.generateRecipe(number, v);
}

void Service::exportRecipe(string nameOfFile) {
	int option = FileValidator::valideaza(nameOfFile);
	if (option == 1) {
		//It's a CSV file.
		recipe.exportCSV(nameOfFile);
	}
	else if (option == 2) {
		//It's an HTML file.
		recipe.exportHTML(nameOfFile);
	}
}