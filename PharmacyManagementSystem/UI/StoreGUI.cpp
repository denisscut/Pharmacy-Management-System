#include "StoreGUI.h"
#include <QtWidgets/qboxlayout.h>
#include <QtWidgets/qformlayout.h>
#include <Qt>
#include <set>
void StoreGUI::initializeGUIComponents() {

	//impartim fereastra in 2: in stanga, butoane+labels+qlineedits
	//iar in dreapta: tabelul cu melodii

	//"stanga" si "dreapta" pentru ca este QHBoxLayout
	//se adauga componente incepand din stanga, pe orizontala
	//aici: "left" component, then "right" component
	//care la randul lor contin alte componente

	//main layout
	QHBoxLayout* lyMain;
	lyMain = new QHBoxLayout;
	this->setLayout(lyMain);


	//left part of the window
	//pentru aceasta parte setam layout vertical
	left = new QWidget;
	QVBoxLayout* lyLeft = new QVBoxLayout;
	left->setLayout(lyLeft);

	//componente pentru functionalitatea de adaugare a unui medicament
	//folosim un QFormLayout pentru detaliile de adaugare a unui medicament


	model = new TableModel(srv.getAllMedicamente());

	tableViewMedicaments = new QTableView();
	tableViewMedicaments->setModel(model);
	//tableMedicaments = new QTableWidget{ noLines, noColumns };

	QVBoxLayout* lyTableMedicaments = new QVBoxLayout;
	QWidget* tableMedicamentsW = new QWidget;
	tableMedicamentsW->setLayout(lyTableMedicaments);
	lyTableMedicaments->addWidget(tableViewMedicaments);

	//setam header-ul tabelului
	QStringList tableHeaderList;
	tableHeaderList << "Nume" << "Producator" << "Substanta" << "Pret";
	//tableMedicaments->setHorizontalHeaderLabels(tableHeaderList);

	//optiune pentru a se redimensiona celulele din tabel in functie de continut
	//this->tableMedicaments->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
	//tableMedicaments->setMaximumWidth(tableMedicaments->verticalHeader()->width() + tableMedicaments->horizontalHeader()->length() + tableMedicaments->frameWidth() * 2);
	//tableMedicaments->setMaximumHeight(tableMedicaments->horizontalHeader()->height() + tableMedicaments->verticalHeader()->length() + tableMedicaments->frameWidth() * 2);



	sortByNameBtn = new QPushButton("Sorteaza dupa nume");
	sortByProducerBtn = new QPushButton("Sorteaza dupa producator");
	sortBySubstanceAndPriceBtn = new QPushButton("Sorteaza dupa substanta si pret");
	sortByNameBtn->setStyleSheet(styleBtns);
	sortByProducerBtn->setStyleSheet(styleBtns);
	sortBySubstanceAndPriceBtn->setStyleSheet(styleBtns);

	//QWidget* sortingBtns = new QWidget;
	//QHBoxLayout* lySortingBtns = new QHBoxLayout;
	//sortingBtns->setLayout(lySortingBtns);

	//lySortingBtns->addWidget(sortByNameBtn);
	//lySortingBtns->addWidget(sortByProducerBtn);
	//lySortingBtns->addWidget(sortBySubstanceAndPriceBtn);

	lyLeft->addWidget(tableMedicamentsW);
	//lyLeft->addWidget(sortingBtns);

	//Right SIDE

	newRight = new QWidget;
	QHBoxLayout* lyNewRight = new QHBoxLayout;
	newRight->setLayout(lyNewRight);

	right = new QWidget;
	QVBoxLayout* lyRight = new QVBoxLayout;
	right->setLayout(lyRight);

	//
	//Table of the Recipe
	//
	//tableRecipe = new QTableWidget{10, 4};
	//tableRecipeW = new QWidget;
	//QVBoxLayout* lyTableRecipe = new QVBoxLayout;
	//tableRecipeW->setLayout(lyTableRecipe);
	//lyTableRecipe->addWidget(tableRecipe);

	//setam header-ul tabelului
	//QStringList tableHeaderRecipe;
	//tableHeaderRecipe << "Nume" << "Producator" << "Substanta" << "Pret";
	//tableRecipe->setHorizontalHeaderLabels(tableHeaderRecipe);

	//lyRight->addWidget(tableRecipeW);


	//
	// Buttons for options
	//

	optBtns = new QWidget;
	QGridLayout* lyOptBtns = new QGridLayout;
	optBtns->setLayout(lyOptBtns);

	addBtnGUI = new QPushButton("Adauga medicament");
	deleteBtnGUI = new QPushButton("Sterge medicament");
	modifyBtnGUI = new QPushButton("Modifica medicament");
	findBtnGUI = new QPushButton("Cauta medicament");
	addToRecipeBtnGUI = new QPushButton("Adauga medicament pe reteta");
	genRecipeBtnGUI = new QPushButton("Genereaza medicamente pe reteta");
	exportRecipeBtnGUI = new QPushButton("Exporteaza reteta");
	nrOfMedWithPriceGTBtnGUI = new QPushButton("Numarul de medicamente cu pret > pret dat");
	filterBtnGUI = new QPushButton("Filtrare medicamente");
	clearRecipeBtn = new QPushButton("Goleste reteta");
	undoBtn = new QPushButton("Undo");
	recipeBtnGUI = new QPushButton("Deschide reteta");
	recipeReadOnlyBtnGUI = new QPushButton("Deschide reteta desenata");

	//sortBySubstanceAndPrice = new QPushButton("Sorteaza dupa substanta si pret");
	//sortByName->setStyleSheet(styleBtns);
	//sortByProducer->setStyleSheet(styleBtns);
	//sortBySubstanceAndPrice->setStyleSheet(styleBtns);

	addBtnGUI->setStyleSheet(styleBtns);
	deleteBtnGUI->setStyleSheet(styleBtns);
	modifyBtnGUI->setStyleSheet(styleBtns);
	findBtnGUI->setStyleSheet(styleBtns);
	addToRecipeBtnGUI->setStyleSheet(styleBtns);
	genRecipeBtnGUI->setStyleSheet(styleBtns);
	exportRecipeBtnGUI->setStyleSheet(styleBtns);
	filterBtnGUI->setStyleSheet(styleBtns);
	undoBtn->setStyleSheet(styleBtns);
	clearRecipeBtn->setStyleSheet(styleBtns);
	nrOfMedWithPriceGTBtnGUI->setStyleSheet(styleBtns);
	recipeBtnGUI->setStyleSheet(styleBtns);
	recipeReadOnlyBtnGUI->setStyleSheet(styleBtns);
	//TODO: Nu pot micsora fereastra din cauza butoanelor, de rezolvat.

	lyOptBtns->addWidget(sortByNameBtn, 0, 0);
	lyOptBtns->addWidget(sortByProducerBtn, 0, 1);
	lyOptBtns->addWidget(sortBySubstanceAndPriceBtn, 0, 2);
	lyOptBtns->addWidget(addBtnGUI, 3, 2);
	lyOptBtns->addWidget(deleteBtnGUI, 4, 0);
	lyOptBtns->addWidget(modifyBtnGUI, 4, 1);
	lyOptBtns->addWidget(findBtnGUI, 1, 0);
	lyOptBtns->addWidget(addToRecipeBtnGUI, 1, 1);
	lyOptBtns->addWidget(genRecipeBtnGUI, 1, 2);
	lyOptBtns->addWidget(exportRecipeBtnGUI, 2, 0);
	lyOptBtns->addWidget(filterBtnGUI, 2, 1);
	lyOptBtns->addWidget(undoBtn, 2, 2);
	lyOptBtns->addWidget(nrOfMedWithPriceGTBtnGUI, 3, 0);
	lyOptBtns->addWidget(clearRecipeBtn, 3, 1);
	lyOptBtns->addWidget(recipeBtnGUI, 4, 2);
	lyOptBtns->addWidget(recipeReadOnlyBtnGUI, 5, 0);


	lyLeft->addWidget(optBtns);

	newBtns = new QWidget;
	lyNewBtns = new QVBoxLayout;
	newBtns->setLayout(lyNewBtns);

	/*QPushButton* newButton = new QPushButton("DASdas");
	lyNewBtns->addWidget(newButton);*/

	reloadButtons();

	lyNewRight->addWidget(right);
	lyNewRight->addWidget(newBtns);

	lyMain->addWidget(left);
	lyMain->addWidget(newRight);
}

void clearLayout(QLayout* layout) {
	if (layout == NULL)
		return;
	QLayoutItem* item;
	while ((item = layout->takeAt(0))) {
		if (item->layout()) {
			clearLayout(item->layout());
			delete item->layout();
		}
		if (item->widget()) {
			delete item->widget();
		}
		delete item;
	}
}

void StoreGUI::reloadButtons() {
	clearLayout(lyNewBtns);
	std::set <string> uniqueSubstance;
	vector<Medicament> vec = srv.getAllMedicamente();
	for (size_t i = 0; i < vec.size(); i++)
		uniqueSubstance.insert(vec[i].getSubstanta());

	std::set<string>::iterator it;
	buttonsOfSubstance.clear();
	for (it = uniqueSubstance.begin(); it != uniqueSubstance.end(); ++it) {
		QPushButton* ctr = new QPushButton(QString::fromStdString(*it));
		buttonsOfSubstance.push_back(ctr);
	}

	for (auto button : buttonsOfSubstance) {
		lyNewBtns->addWidget(button);
	}
	for (auto button : buttonsOfSubstance) {
		QObject::connect(button, &QPushButton::clicked, this, &StoreGUI::option);
	}
}

void StoreGUI::initializeButtons() {
	addBtn = new QPushButton("Adauga");
	addBtn->setStyleSheet(styleBtns);
	deleteBtn = new QPushButton("Sterge");
	deleteBtn->setStyleSheet(styleBtns);
	modifyBtn = new QPushButton("Modifica");
	modifyBtn->setStyleSheet(styleBtns);
	findBtn = new QPushButton("Cauta");
	findBtn->setStyleSheet(styleBtns);
	filterBtn = new QPushButton("Filtrare");
	filterBtn->setStyleSheet(styleBtns);
	addToRecipeBtn = new QPushButton("Adauga pe reteta");
	addToRecipeBtn->setStyleSheet(styleBtns); 
	genRecipeBtn = new QPushButton("Generare");
	genRecipeBtn->setStyleSheet(styleBtns);
	exportRecipeBtn = new QPushButton("Generare");
	exportRecipeBtn->setStyleSheet(styleBtns);
	nrOfMedWithPriceGTBtn= new QPushButton("Afiseaza");
	nrOfMedWithPriceGTBtn->setStyleSheet(styleBtns);
}

void StoreGUI::reloadTableMedicaments(vector <Medicament>& medicaments) {

	model->setMedicaments(medicaments);

	//this->tableMedicaments->clearContents();
	//this->tableMedicaments->setRowCount((int)medicaments.size());

	//int lineNumber = 0;
	//for (auto& medicament : medicaments) {
	//	this->tableMedicaments->setItem(lineNumber, 0, new QTableWidgetItem(QString::fromStdString(medicament.getNume())));
	//	this->tableMedicaments->setItem(lineNumber, 1, new QTableWidgetItem(QString::fromStdString(medicament.getProducator())));
	//	this->tableMedicaments->setItem(lineNumber, 2, new QTableWidgetItem(QString::fromStdString(medicament.getSubstanta())));
	//	this->tableMedicaments->setItem(lineNumber, 3, new QTableWidgetItem(QString::number(medicament.getPret())));
	//	lineNumber++;
	//}
	reloadButtons();
}


//void StoreGUI::reloadTableRecipe(vector <Medicament>& medicaments) {
//	this->tableRecipe->clearContents();
//	this->tableRecipe->setRowCount((int)medicaments.size());
//
//	int lineNumber = 0;
//	for (auto& medicament : medicaments) {
//		this->tableRecipe->setItem(lineNumber, 0, new QTableWidgetItem(QString::fromStdString(medicament.getNume())));
//		this->tableRecipe->setItem(lineNumber, 1, new QTableWidgetItem(QString::fromStdString(medicament.getProducator())));
//		this->tableRecipe->setItem(lineNumber, 2, new QTableWidgetItem(QString::fromStdString(medicament.getSubstanta())));
//		this->tableRecipe->setItem(lineNumber, 3, new QTableWidgetItem(QString::number(medicament.getPret())));
//		lineNumber++;
//	}
//}

void StoreGUI::connectSignalsSlots() {
	QObject::connect(addBtn, &QPushButton::clicked, this, &StoreGUI::addMedicament);
	QObject::connect(addBtnGUI, &QPushButton::clicked, this, &StoreGUI::guiAddMedicament);
	QObject::connect(deleteBtn, &QPushButton::clicked, this, &StoreGUI::deleteMedicament);
	QObject::connect(deleteBtnGUI, &QPushButton::clicked, this, &StoreGUI::guiDeleteMedicament);
	QObject::connect(modifyBtn, &QPushButton::clicked, this, &StoreGUI::modifyMedicament);
	QObject::connect(modifyBtnGUI, &QPushButton::clicked, this, &StoreGUI::guiModifyMedicament);
	QObject::connect(findBtn, &QPushButton::clicked, this, &StoreGUI::findMedicament);
	QObject::connect(findBtnGUI, &QPushButton::clicked, this, &StoreGUI::guiFindMedicament);
	QObject::connect(sortByNameBtn, &QPushButton::clicked, this, &StoreGUI::sortByName);
	QObject::connect(sortByProducerBtn, &QPushButton::clicked, this, &StoreGUI::sortByProducer);
	QObject::connect(sortBySubstanceAndPriceBtn, &QPushButton::clicked, this, &StoreGUI::sortBySubstanceAndPrice);
	QObject::connect(addToRecipeBtn, &QPushButton::clicked, this, &StoreGUI::addToRecipe);
	QObject::connect(addToRecipeBtnGUI, &QPushButton::clicked, this, &StoreGUI::guiAddToRecipe);
	QObject::connect(filterBtnGUI, &QPushButton::clicked, this, &StoreGUI::guiFilterMedicament);
	QObject::connect(filterBtn, &QPushButton::clicked, this, &StoreGUI::filterMedicament); 
	QObject::connect(genRecipeBtnGUI, &QPushButton::clicked, this, &StoreGUI::guiGenerateRecipe);
	QObject::connect(genRecipeBtn, &QPushButton::clicked, this, &StoreGUI::generateRecipe);
	QObject::connect(exportRecipeBtnGUI, &QPushButton::clicked, this, &StoreGUI::guiExportRecipe);
	QObject::connect(exportRecipeBtn, &QPushButton::clicked, this, &StoreGUI::exportRecipe);
	QObject::connect(undoBtn, &QPushButton::clicked, this, &StoreGUI::undo); 
	QObject::connect(nrOfMedWithPriceGTBtnGUI, &QPushButton::clicked, this, &StoreGUI::guiNrOfMedWithPriceGT);
	QObject::connect(nrOfMedWithPriceGTBtn, &QPushButton::clicked, this, &StoreGUI::nrOfMedWithPriceGT);
	QObject::connect(clearRecipeBtn, &QPushButton::clicked, this, &StoreGUI::clearRecipe);
	QObject::connect(recipeBtnGUI, &QPushButton::clicked, this, &StoreGUI::recipeGUI);
	QObject::connect(recipeReadOnlyBtnGUI, &QPushButton::clicked, this, &StoreGUI::recipeReadOnlyGUI);
}

void StoreGUI::recipeGUI() {
	RecipeGUI* recipeGUI = new RecipeGUI(srv.getRecipeClass());
	recipeGUI->show();
}

void StoreGUI::recipeReadOnlyGUI() {
	RecipeReadOnlyGUI* recipeGUI = new RecipeReadOnlyGUI(srv.getRecipeClass());
	recipeGUI->show();
}

void StoreGUI::guiAddMedicament() {
	addMedicamentGUI = new QWidget;
	QFormLayout* lyAddMedicamentGUI = new QFormLayout;
	addMedicamentGUI->setLayout(lyAddMedicamentGUI);

	editName = new QLineEdit;
	editProducer = new QLineEdit;
	editSubstance = new QLineEdit;
	editPrice = new QLineEdit;

	lyAddMedicamentGUI->addRow(lblName, editName);
	lyAddMedicamentGUI->addRow(lblProducer, editProducer);
	lyAddMedicamentGUI->addRow(lblSubstance, editSubstance);
	lyAddMedicamentGUI->addRow(lblPrice, editPrice);

	lyAddMedicamentGUI->addWidget(addBtn);

	addMedicamentGUI->show();
}

void StoreGUI::addMedicament() {
	try {
		string name = editName->text().toStdString();
		string producer = editProducer->text().toStdString();
		string substance = editSubstance->text().toStdString();
		double price = editPrice->text().toDouble();

		editName->clear();
		editProducer->clear();
		editSubstance->clear();
		editPrice->clear();

		this->srv.addMedicament(name, price, producer, substance);
		this->reloadTableMedicaments(this->srv.getAllMedicamente());
		QMessageBox::information(this, "Info", QString::fromStdString("Medicament adaugat cu succes."));
	}
	catch (RepoException& re) {
		QMessageBox::information(this, "Warning", QString::fromStdString(re.getErrorMessage()));
	}
	catch (ValidationException& ve) {
		QMessageBox::information(this, "Warning", QString::fromStdString(ve.getErrorMessages()));
	}
	addMedicamentGUI->close();
}

void StoreGUI::guiDeleteMedicament() {
	deleteMedicamentGUI = new QWidget;
	QFormLayout* lyDeleteMedicamentGUI = new QFormLayout;
	deleteMedicamentGUI->setLayout(lyDeleteMedicamentGUI);

	editName = new QLineEdit;
	editProducer = new QLineEdit;

	lyDeleteMedicamentGUI->addRow(lblName, editName);
	lyDeleteMedicamentGUI->addRow(lblProducer, editProducer);

	lyDeleteMedicamentGUI->addWidget(deleteBtn);

	deleteMedicamentGUI->show();
}

void StoreGUI::deleteMedicament() {
	try {
		string name = editName->text().toStdString();
		string producer = editProducer->text().toStdString();

		editName->clear();
		editProducer->clear();

		this->srv.deleteMedicament(name, producer);
		this->reloadTableMedicaments(this->srv.getAllMedicamente());
		QMessageBox::information(this, "Info", QString::fromStdString("Medicament sters cu succes."));
	}
	catch (RepoException& re) {
		QMessageBox::information(this, "Warning", QString::fromStdString(re.getErrorMessage()));
	}
	catch (ValidationException& ve) {
		QMessageBox::information(this, "Warning", QString::fromStdString(ve.getErrorMessages()));
	}
	deleteMedicamentGUI->close();
}


void StoreGUI::guiModifyMedicament() {
	modifyMedicamentGUI = new QWidget;
	QFormLayout* lyModifyMedicamentGUI = new QFormLayout;
	modifyMedicamentGUI->setLayout(lyModifyMedicamentGUI);

	editName = new QLineEdit;
	editProducer = new QLineEdit;
	editNewName = new QLineEdit;
	editNewProducer = new QLineEdit;
	editNewSubstance = new QLineEdit;
	editNewPrice = new QLineEdit;


	lyModifyMedicamentGUI->addRow(lblName, editName);
	lyModifyMedicamentGUI->addRow(lblProducer, editProducer);
	lyModifyMedicamentGUI->addRow(lblNewName, editNewName);
	lyModifyMedicamentGUI->addRow(lblNewProducer, editNewProducer);
	lyModifyMedicamentGUI->addRow(lblNewSubstance, editNewSubstance);
	lyModifyMedicamentGUI->addRow(lblNewPrice, editNewPrice);

	lyModifyMedicamentGUI->addWidget(modifyBtn);

	modifyMedicamentGUI->show();
}

void StoreGUI::modifyMedicament() {
	try {
		string name = editName->text().toStdString();
		string producer = editProducer->text().toStdString();
		string newName = editNewName->text().toStdString();
		string newProducer = editNewProducer->text().toStdString();
		string newSubstance = editNewSubstance->text().toStdString();
		double newPrice = editNewPrice->text().toDouble();
		editName->clear();
		editProducer->clear();
		editNewName->clear();
		editNewProducer->clear();
		editNewSubstance->clear();
		editNewPrice->clear();

		this->srv.modifyMedicament(name, producer, newName, newPrice, newProducer, newSubstance);
		this->reloadTableMedicaments(this->srv.getAllMedicamente());
		QMessageBox::information(this, "Info", QString::fromStdString("Medicament modificat cu succes."));
	}
	catch (RepoException& re) {
		QMessageBox::information(this, "Warning", QString::fromStdString(re.getErrorMessage()));
	}
	catch (ValidationException& ve) {
		QMessageBox::information(this, "Warning", QString::fromStdString(ve.getErrorMessages()));
	}
	modifyMedicamentGUI->close();
}


void StoreGUI::guiFindMedicament() {
	findMedicamentGUI = new QWidget;
	QFormLayout* lyFindMedicamentGUI = new QFormLayout;
	findMedicamentGUI->setLayout(lyFindMedicamentGUI);

	editName = new QLineEdit;
	editProducer = new QLineEdit;

	lyFindMedicamentGUI->addRow(lblName, editName);
	lyFindMedicamentGUI->addRow(lblProducer, editProducer);

	lyFindMedicamentGUI->addWidget(findBtn);

	findMedicamentGUI->show();
}

void StoreGUI::findMedicament() {
	try {
		string name = editName->text().toStdString();
		string producer = editProducer->text().toStdString();

		editName->clear();
		editProducer->clear();

		auto med = this->srv.findMedicament(name, producer);
		QMessageBox::information(this, "Info", QString::fromStdString(med.toString()));
	}
	catch (RepoException& re) {
		QMessageBox::information(this, "Warning", QString::fromStdString(re.getErrorMessage()));
	}
	catch (ValidationException& ve) {
		QMessageBox::information(this, "Warning", QString::fromStdString(ve.getErrorMessages()));
	}
	findMedicamentGUI->close();
}

void StoreGUI::sortByName() {
	try {
		auto vec = this->srv.sortareNume();
		this->reloadTableMedicaments(vec);
	}
	catch (RepoException& re) {
		QMessageBox::information(this, "Warning", QString::fromStdString(re.getErrorMessage()));
	}
	catch (ValidationException& ve) {
		QMessageBox::information(this, "Warning", QString::fromStdString(ve.getErrorMessages()));
	}
}


void StoreGUI::sortByProducer() {
	try {
		auto vec = this->srv.sortareProducator();
		this->reloadTableMedicaments(vec);
	}
	catch (RepoException& re) {
		QMessageBox::information(this, "Warning", QString::fromStdString(re.getErrorMessage()));
	}
	catch (ValidationException& ve) {
		QMessageBox::information(this, "Warning", QString::fromStdString(ve.getErrorMessages()));
	}
}


void StoreGUI::sortBySubstanceAndPrice() {
	try {
		auto vec = this->srv.sortareSubstSiPret();
		this->reloadTableMedicaments(vec);
	}
	catch (RepoException& re) {
		QMessageBox::information(this, "Warning", QString::fromStdString(re.getErrorMessage()));
	}
	catch (ValidationException& ve) {
		QMessageBox::information(this, "Warning", QString::fromStdString(ve.getErrorMessages()));
	}
}


void StoreGUI::guiFilterMedicament() {
	filterMedicamentGUI = new QWidget;
	QFormLayout* lyFilterMedicamentGUI = new QFormLayout;
	filterMedicamentGUI->setLayout(lyFilterMedicamentGUI);

	editString = new QLineEdit;
	optionsFilter = new QComboBox;
	optionsFilter->addItem("Pret");
	optionsFilter->addItem("Substanta");

	lyFilterMedicamentGUI->addRow(optionsFilter, editString);

	lyFilterMedicamentGUI->addWidget(filterBtn);

	filterMedicamentGUI->show();
}


void StoreGUI::filterMedicament() {
	try {
		vector<Medicament> vec;
		if (optionsFilter->currentText() == "Pret") {
			vec = this->srv.filtrarePret(editString->text().toDouble());
		}
		else if (optionsFilter->currentText() == "Substanta") {
			vec = this->srv.filtrareSubstanta(editString->text().toStdString());
		}
		editString->clear();

		QWidget* listMedicamentsGUI = new QWidget;
		QVBoxLayout* lyListMedicamentsGUI = new QVBoxLayout;
		listMedicamentsGUI->setLayout(lyListMedicamentsGUI);
		QListWidget* listOfMedicaments = new QListWidget;
		for (auto medicament : vec) {
			QListWidgetItem* item = new QListWidgetItem;
			item->setText(QString::fromStdString(medicament.toString()));
			listOfMedicaments->addItem(item);
		}
		lyListMedicamentsGUI->addWidget(listOfMedicaments);
		listMedicamentsGUI->show();
	}
	catch (RepoException& re) {
		QMessageBox::information(this, "Warning", QString::fromStdString(re.getErrorMessage()));
	}
	catch (ValidationException& ve) {
		QMessageBox::information(this, "Warning", QString::fromStdString(ve.getErrorMessages()));
	}
	filterMedicamentGUI->close();
}


void StoreGUI::guiAddToRecipe() {
	addToRecipeGUI = new QWidget;
	QFormLayout* lyAddToRecipeGUI = new QFormLayout;
	addToRecipeGUI->setLayout(lyAddToRecipeGUI);

	editName = new QLineEdit;
	editProducer = new QLineEdit;

	lyAddToRecipeGUI->addRow(lblName, editName);
	lyAddToRecipeGUI->addRow(lblProducer, editProducer);

	lyAddToRecipeGUI->addWidget(addToRecipeBtn);

	addToRecipeGUI->show();
}


void StoreGUI::addToRecipe() {
	try {
		string name = editName->text().toStdString();
		string producer = editProducer->text().toStdString();
	
		editName->clear();
		editProducer->clear();
		auto med = srv.findMedicament(name, producer);
		this->srv.addToRecipe(med);
		//this->reloadTableRecipe(this->srv.getRecipe());
		QMessageBox::information(this, "Info", QString::fromStdString("Medicament adaugat cu succes."));
	}
	catch (RepoException& re) {
		QMessageBox::information(this, "Warning", QString::fromStdString(re.getErrorMessage()));
	}
	catch (ValidationException& ve) {
		QMessageBox::information(this, "Warning", QString::fromStdString(ve.getErrorMessages()));
	}
	addToRecipeGUI->close();
}


void StoreGUI::guiGenerateRecipe() {
	generateRecipeGUI = new QWidget;
	QFormLayout* lyGenerateToRecipeGUI = new QFormLayout;
	generateRecipeGUI->setLayout(lyGenerateToRecipeGUI);

	editNumber = new QLineEdit;

	lyGenerateToRecipeGUI->addRow("Numarul de medicamente generate pe lista: ", editNumber);
	lyGenerateToRecipeGUI->addWidget(genRecipeBtn);

	generateRecipeGUI->show();
}


void StoreGUI::generateRecipe() {
	try {
		srv.generateRecipe(editNumber->text().toInt(), srv.getAllMedicamente());
		//reloadTableRecipe(srv.getRecipe());
	}
	catch (RepoException& re) {
		QMessageBox::information(this, "Warning", QString::fromStdString(re.getErrorMessage()));
	}
	catch (ValidationException& ve) {
		QMessageBox::information(this, "Warning", QString::fromStdString(ve.getErrorMessages()));
	}
	generateRecipeGUI->close();
}


void StoreGUI::guiExportRecipe() {
	exportRecipeGUI = new QWidget;
	QFormLayout* lyExportRecipeGUI = new QFormLayout;
	exportRecipeGUI->setLayout(lyExportRecipeGUI);

	editNameOfFile = new QLineEdit;

	lyExportRecipeGUI->addRow("Numele fisierului: ", editNameOfFile);
	lyExportRecipeGUI->addWidget(exportRecipeBtn);

	exportRecipeGUI->show();
}


void StoreGUI::exportRecipe() {
	try {
		srv.exportRecipe(editNameOfFile->text().toStdString());
	}
	catch (RepoException& re) {
		QMessageBox::information(this, "Warning", QString::fromStdString(re.getErrorMessage()));
	}
	catch (ValidationException& ve) {
		QMessageBox::information(this, "Warning", QString::fromStdString(ve.getErrorMessages()));
	}
	exportRecipeGUI->close();
}


void StoreGUI::undo() {
	try {
		srv.undo();
		reloadButtons();
		reloadTableMedicaments(srv.getAllMedicamente());
		//reloadTableRecipe(srv.getRecipe());
	}
	catch (UndoException& ue) {
		QMessageBox::information(this, "Warning", QString::fromStdString(ue.getErrorMessage()));
	}
}


void StoreGUI::guiNrOfMedWithPriceGT() {
	nrOfMedWithPriceGTGUI = new QWidget;
	QFormLayout* lyNrOfMedWithPriceGTGUI = new QFormLayout;
	nrOfMedWithPriceGTGUI->setLayout(lyNrOfMedWithPriceGTGUI);

	editPrice = new QLineEdit;

	lyNrOfMedWithPriceGTGUI->addRow("Pret: ", editPrice);
	lyNrOfMedWithPriceGTGUI->addWidget(nrOfMedWithPriceGTBtn);

	nrOfMedWithPriceGTGUI->show();
}


void StoreGUI::nrOfMedWithPriceGT() {
	try {
		int number = srv.getNumberOfMedicamentsByPrice(editPrice->text().toInt());
		string strNumber = std::to_string(number);
		QMessageBox::information(this, "Warning", QString::fromStdString(strNumber));
	}
	catch (RepoException& re) {
		QMessageBox::information(this, "Warning", QString::fromStdString(re.getErrorMessage()));
	}
	catch (ValidationException& ve) {
		QMessageBox::information(this, "Warning", QString::fromStdString(ve.getErrorMessages()));
	}
	nrOfMedWithPriceGTGUI->close();
}


void StoreGUI::clearRecipe() {
	try {
		srv.eraseRecipe();
		//reloadTableRecipe(srv.getRecipe());
	}
	catch (RepoException& re) {
		QMessageBox::information(this, "Warning", QString::fromStdString(re.getErrorMessage()));
	}
	catch (ValidationException& ve) {
		QMessageBox::information(this, "Warning", QString::fromStdString(ve.getErrorMessages()));
	}
}


void StoreGUI::option() {
	try {
		QPushButton* buttonSender = qobject_cast<QPushButton*>(sender()); // retrieve the button you have clicked
		QString buttonText = buttonSender->text(); // retrive the text from the button clicked
		auto newVec = srv.filtrareSubstanta(buttonText.toStdString());
		string message = std::to_string(newVec.size());
		QMessageBox::information(this, "Info", QString::fromStdString(message));
	}
	catch (RepoException& re) {
		QMessageBox::information(this, "Warning", QString::fromStdString(re.getErrorMessage()));
	}
	catch (ValidationException& ve) {
		QMessageBox::information(this, "Warning", QString::fromStdString(ve.getErrorMessages()));
	}
}