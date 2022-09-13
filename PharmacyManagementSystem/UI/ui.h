#pragma once
#include "../Service/service.h"
#include "../Domain/medicament.h"

class ConsoleUI {
private:
	Service& srv;

public:
	ConsoleUI(Service& srv) :srv{ srv } {};
	ConsoleUI(const ConsoleUI& ot) = delete;

	void printMenu();
	void uiAdd();
	void printAllMedicamente();
	void run();
	int quitUI();
	void uiDelete();
	void uiModify();
	void uiFind();
	void uiFiltrare();
	void uiSort();
	void uiEraseRecipe();
	void uiAddToRecipe();
	void printAllRecipes();
	void uiGenerateRecipe();
	void uiExport();
	void uiGetMedicamenteByPrice();
	void uiUndo();
};