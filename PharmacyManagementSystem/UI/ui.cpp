#include <iostream>
#include "ui.h"
#include "../Utils/utils.h"
using namespace std;


void ConsoleUI::printMenu() {
	cout << "Comenzi disponibile:" << endl;
	cout << "0. Exit" << endl;
	cout << "1. Adauga medicament" << endl;
	cout << "2. Sterge medicament" << endl;
	cout << "3. Modifica medicament" << endl;
	cout << "4. Cauta medicament" << endl;
	cout << "5. Filtrare medicamente" << endl;
	cout << "6. Sortare medicamente" << endl;
	cout << "7. Goleste reteta" << endl;
	cout << "8. Adauga pe reteta" << endl;
	cout << "9. Genereaza reteta" << endl;
	cout << "10. Export(cu extensia CSV sau HTML)" << endl;
	cout << "11. Afisati numarul de medicamente care au pretul mai mare decat un pret dat" << endl;
	cout << "12. Undo" << endl;
}


void ConsoleUI::uiAdd() {
	string nume, producator, substanta;
	double pret;
	cout << "Numele medicamentului este:";
	getline(cin >> ws, nume);

	cout << "Producatorul medicamentului este:";
	getline(cin >> ws, producator);
	cout << "Substanta medicamentului este:";
	getline(cin >> ws, substanta);

	cout << "Pretul medicamentului (numar real, >0) este:";
	cin >> pret;
	try {
		srv.addMedicament(nume, pret, producator, substanta);
	}
	catch (RepoException& re) {
		cout << re.getErrorMessage() << '\n';
	}
	catch (ValidationException& ve) {
		cout << "Medicamentul nu este valid!" << endl;
		cout << ve.getErrorMessages();
	}
}


void ConsoleUI::uiDelete() {
	string nume, producator;

	cout << "Numele medicamentului este:";
	getline(cin >> ws, nume);

	cout << "Producatorul medicamentului este:";
	getline(cin >> ws, producator);

	try {
		srv.deleteMedicament(nume, producator);
	}
	catch (RepoException& re) {
		cout << re.getErrorMessage() << endl;
	}
	catch (ValidationException& ve) {
		cout << ve.getErrorMessages();
	}
}


void ConsoleUI::uiModify() {
	string nume, producator;
	string numeNou, producatorNou, substantaNoua;
	double pretNou;

	cout << "Numele medicamentului este:";
	getline(cin >> ws, nume);

	cout << "Producatorul medicamentului este:";
	getline(cin >> ws, producator);

	try {
		srv.exists(nume, producator);
		cout << "Numele nou al medicamentului este:";
		getline(cin >> ws, numeNou);

		cout << "Producatorul nou al medicamentului este:";
		getline(cin >> ws, producatorNou);
		cout << "Substanta noua a medicamentului este:";
		getline(cin >> ws, substantaNoua);

		cout << "Pretul nou al medicamentului (numar real, >0) este:";
		cin >> pretNou;
		try {

			srv.modifyMedicament(nume, producator, numeNou, pretNou, producatorNou, substantaNoua);
		}
		catch (RepoException& re) {
			cout << re.getErrorMessage() << endl;
		}
		catch (ValidationException& ve) {
			cout << ve.getErrorMessages();
		}
	}
	catch (ValidationException& ve) {
		cout << ve.getErrorMessages();
	}
	catch (RepoException& re) {
		cout << re.getErrorMessage() << endl;
	}
}


void ConsoleUI::uiFiltrare() {
	string cmdStr, substanta, pretStr;
	int cmd, pret;
	cout << "1. Filtrare dupa pret" << endl;
	cout << "2. Filtrare dupa substanta activa" << endl;
	cout << "Comanda este:";
	getline(cin >> ws, cmdStr);
	cmd = strtoint(cmdStr);
	if (cmd == 1) {
		cout << "Pretul medicamentului (numar real, >0) este:";
		getline(cin >> ws, pretStr);
		pret = strtoint(pretStr);
		if (pret == INT_MAX) {
			cout << "Pretul introdus este invalida.\n";
		}
		else {
			try {
				auto newVec = srv.filtrarePret(pret);
				for (auto med : newVec)
					cout << med << '\n';
			}
			catch (RepoException& re) {
				cout << re.getErrorMessage() << endl;
			}
			catch (ValidationException& ve) {
				cout << ve.getErrorMessages();
			}
		}
	}
	else if (cmd == 2) {
		cout << "Substanta medicamentului este:	";
		getline(cin >> ws, substanta);
		try {
			auto newVec = srv.filtrareSubstanta(substanta);
			for (auto med : newVec)
				cout << med << '\n';
		}
		catch (RepoException& re) {
			cout << re.getErrorMessage() << endl;
		}
		catch (ValidationException& ve) {
			cout << ve.getErrorMessages();
		}
	}
	else if (cmd == INT_MAX) {
		cout << "Comanda introdusa este invalida.\n";
	}
}


void ConsoleUI::uiFind() {
	string nume, producator;
	cout << "Numele medicamentului este:";
	getline(cin >> ws, nume);
	cout << "Producatorul medicamentului este:";
	getline(cin >> ws, producator);
	try {
		const Medicament& med = srv.findMedicament(nume, producator);
		cout << med << '\n';
	}
	catch (RepoException& re) {
		cout << re.getErrorMessage() << endl;
	}
	catch (ValidationException& ve) {
		cout << ve.getErrorMessages();
	}
}


void ConsoleUI::uiSort() {
	string cmdStr, substanta, nume, producator;
	int cmd;
	cout << "1. Sortare dupa denumire" << endl;
	cout << "2. Sortare dupa producator" << endl;
	cout << "3. Sortare dupa substanta activa + pret" << endl;
	cout << "Comanda este:";
	getline(cin >> ws, cmdStr);
	cmd = strtoint(cmdStr);
	if (cmd == 1) {
		try {
			auto newVec = srv.sortareNume();
			for (auto med : newVec)
				cout << med << '\n';
		}
		catch (RepoException& re) {
			cout << re.getErrorMessage() << '\n';
		}
	}
	else if (cmd == 2) {
		try {
			auto newVec = srv.sortareProducator();
			for (auto med : newVec)
				cout << med << '\n';
		}
		catch (RepoException& re) {
			cout << re.getErrorMessage() << '\n';
		}
	}
	else if (cmd == 3) {
		try {
			auto newVec = srv.sortareSubstSiPret();
			for (auto med : newVec)
				cout << med << '\n';
		}
		catch (RepoException& re) {
			cout << re.getErrorMessage() << '\n';
		}
	}
	else if (cmd == INT_MAX) {
		cout << "Comanda introdusa este invalida.\n";
	}
}


void ConsoleUI::uiEraseRecipe() {
	srv.eraseRecipe();
}


void ConsoleUI::uiAddToRecipe() {
	string nume, producator;

	cout << "Numele medicamentului este:";
	getline(cin >> ws, nume);

	cout << "Producatorul medicamentului este:";
	getline(cin >> ws, producator);

	try {
		auto& med = srv.findMedicament(nume, producator);
		Medicament copyMed(med);
		try {

			srv.addToRecipe(copyMed);
		}
		catch (RepoException& re) {
			cout << re.getErrorMessage() << endl;
		}
		catch (ValidationException& ve) {
			cout << ve.getErrorMessages();
		}
	}
	catch (ValidationException& ve) {
		cout << ve.getErrorMessages();
	}
	catch (RepoException& re) {
		cout << re.getErrorMessage() << endl;
	}
}


void ConsoleUI::uiGenerateRecipe() {
	string numberStr;
	int number;
	cout << "Numarul de medicamente din reteta: ";
	getline(cin >> ws, numberStr);
	number = strtoint(numberStr);
	if (number == INT_MAX)
		cout << "Numarul introdus este invalid\n";
	else
		srv.generateRecipe(number, srv.getAllMedicamente());
}


void ConsoleUI::uiExport() {
	string nameOfFile;
	cout << "Numele fisierului (cu extensia .csv sau .html): ";
	getline(cin >> ws, nameOfFile);
	try {
		srv.exportRecipe(nameOfFile);
	}
	catch (ValidationException& ve) {
		cout << ve.getErrorMessages();
	}
}

void ConsoleUI::uiUndo() {
	try {
		srv.undo();
	}
	catch (UndoException ue) {
		cout << ue.getErrorMessage() << '\n';
	}
}

void ConsoleUI::uiGetMedicamenteByPrice() {
	string priceStr;
	double price;
	cout << "Introduceti pretul: ";
	getline(cin >> ws, priceStr);
	price = strtoint(priceStr);
	if (price != INT_MAX)
		cout << srv.getNumberOfMedicamentsByPrice(price) << '\n';
	else
		cout << "Pretul introdus este invalida.\n";
}


void ConsoleUI::printAllMedicamente() {
	cout << "Lista medicamentelor: \n";
	auto allMedicamente = srv.getAllMedicamente();
	if (allMedicamente.size() == 0)
		cout << "Nu exista medicamente." << endl;
	else
		for (const auto& med : allMedicamente) {
			cout << med << endl;
		}
}


void ConsoleUI::printAllRecipes() {
	auto allRecipes = srv.getRecipe();
	if (allRecipes.size() == 0)
		cout << "Nu exista medicamente in reteta." << endl;
	else
		for (const auto& med : allRecipes) {
			cout << med << endl;
		}
}


int ConsoleUI::quitUI() {
	int read, cmd = 0;
	string stay;
	read = 1;
	while (read) {
		printf("Vrei sa continui(y/n): ");
		getline(cin >> ws, stay);
		if (stay == "n" || stay == "N" || stay == "y" || stay == "Y") {
			if (stay == "n" || stay == "N")
				cmd = 0;
			else if (stay == "y" || stay == "Y")
				cmd = 1;
			read = 0;
		}
		else
			cout << "Comanda introdusa este invalida.\n";
	}
	return cmd;
}


void ConsoleUI::run() {
	int running = 1, cmd;
	string cmdStr, stay;
	while (running) {
		system("CLS");
		printMenu();
		printAllMedicamente();
		cout << "Sunt " << srv.getRecipe().size() << " medicamente in reteta.\n";
		printAllRecipes();
		cout << "Comanda este:";
		getline(cin >> ws, cmdStr);
		cmd = strtoint(cmdStr);
		switch (cmd)
		{
		case 1:
			uiAdd();
			break;
		case 2:
			uiDelete();
			break;
		case 3:
			uiModify();
			break;
		case 4:
			uiFind();
			break;
		case 5:
			uiFiltrare();
			break;
		case 6:
			uiSort();
			break;
		case 7:
			uiEraseRecipe();
			break;
		case 8:
			uiAddToRecipe();
			break;
		case 9:
			uiGenerateRecipe();
			break;
		case 10:
			uiExport();
			break;
		case 11:
			uiGetMedicamenteByPrice();
			break;
		case 12:
			uiUndo();
			break;
		case 0:
			running = 0;
			break;
		default:
			cout << "Comanda introdusa este invalida.\n";
			break;
		}

		if (running)
			running = quitUI();
	}
}