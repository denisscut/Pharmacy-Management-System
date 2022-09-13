#pragma once
#include <QtWidgets/QApplication>
#include <QLabel>
#include "../Service/service.h"
#include <QLineEdit>
#include <QPushButton>
#include <QTableWidget>
#include <QHeaderView>
#include <QMessageBox>
#include <QComboBox>
#include <QListWidget>
#include <string>
#include <set>
#include "recipeGUI.h"
#include "recipeReadOnlyGUI.h"
#include "../Domain/tableModel.h"

class StoreGUI : public QWidget {
private:

	QTableView* tableViewMedicaments;
	TableModel* model;
	QListView* listViewMedicaments;

	QWidget* left;
	QWidget* newRight;
	QWidget* right;
	//QWidget* tableRecipeW;
	QWidget* optBtns;
	QWidget* newBtns;
	QLayout* lyNewBtns;

	Service& srv;

	QWidget* addToRecipeGUI;
	QWidget* filterMedicamentGUI;
	QWidget* addMedicamentGUI;
	QWidget* deleteMedicamentGUI;
	QWidget* modifyMedicamentGUI;
	QWidget* findMedicamentGUI;
	QWidget* generateRecipeGUI;
	QWidget* exportRecipeGUI;
	QWidget* nrOfMedWithPriceGTGUI;
	vector <QPushButton*> buttonsOfSubstance;

	QLabel* lblName = new QLabel{ "Numele: " };
	QLabel* lblProducer = new QLabel{ "Producatorul: " };
	QLabel* lblSubstance = new QLabel{ "Substanta: " };
	QLabel* lblPrice = new QLabel{ "Pretul: " };
	QLabel* lblNewName = new QLabel{ "Numele nou: " };
	QLabel* lblNewProducer = new QLabel{ "Producatorul nou: " };
	QLabel* lblNewSubstance = new QLabel{ "Substanta noua: " };
	QLabel* lblNewPrice = new QLabel{ "Pretul nou: " };

	QString styleBtns{ "QPushButton{padding:0.35em 1.2em;border:0.1em solid #282828;margin:0 0.3em 0.3em 0;border-radius:0.12em;box-sizing: border-box;text-decoration:none;font-family:'Roboto', sans-serif;font-weight:300;color:#282828;text-align:center;transition: all 0.2s;}QPushButton:hover{color:#FFFFFF;background-color:#282828;}" };
	
	QLineEdit* editString;
	QLineEdit* editName;
	QLineEdit* editProducer;
	QLineEdit* editSubstance;
	QLineEdit* editPrice;
	QLineEdit* editNewName;
	QLineEdit* editNewProducer;
	QLineEdit* editNewSubstance;
	QLineEdit* editNewPrice;
	QLineEdit* editNumber;
	QLineEdit* editNameOfFile;

	QComboBox* optionsFilter;
	//QPushButton* btnAddMedicament;
	QPushButton* sortByNameBtn;
	QPushButton* sortByProducerBtn;
	QPushButton* sortBySubstanceAndPriceBtn;
	QTableWidget* tableMedicaments;
	QTableWidget* tableRecipe;

	QPushButton* filterBtnGUI;
	QPushButton* addBtnGUI;
	QPushButton* deleteBtnGUI;
	QPushButton* modifyBtnGUI;
	QPushButton* findBtnGUI;
	QPushButton* addToRecipeBtnGUI;
	QPushButton* genRecipeBtnGUI;
	QPushButton* exportRecipeBtnGUI;
	QPushButton* printOptionBtnGUI;
	QPushButton* nrOfMedWithPriceGTBtnGUI;
	QPushButton* recipeBtnGUI;
	QPushButton* recipeReadOnlyBtnGUI;

	QPushButton* filterBtn;
	QPushButton* addBtn;
	QPushButton* deleteBtn;
	QPushButton* modifyBtn;
	QPushButton* findBtn;
	QPushButton* addToRecipeBtn;
	QPushButton* genRecipeBtn;
	QPushButton* exportRecipeBtn;
	QPushButton* printOptionBtn;
	QPushButton* undoBtn;
	QPushButton* clearRecipeBtn;
	QPushButton* nrOfMedWithPriceGTBtn;

	void initializeGUIComponents();
	void initializeButtons();
	void connectSignalsSlots();
	void reloadTableMedicaments(vector <Medicament>& lst);
	//void reloadTableRecipe(vector <Medicament>& lst);
	void reloadButtons();
public:
	StoreGUI(Service& srv) : srv{ srv } {
		initializeGUIComponents();
		initializeButtons();
		connectSignalsSlots();
		reloadTableMedicaments(srv.getAllMedicamente());
		//reloadTableRecipe(srv.getRecipe());
	};

	void guiAddMedicament();
	void addMedicament();
	void guiDeleteMedicament();
	void deleteMedicament();
	void guiModifyMedicament();
	void modifyMedicament();
	void guiFilterMedicament();
	void filterMedicament();
	void guiFindMedicament();
	void findMedicament();
	void sortByName();
	void sortByProducer();
	void sortBySubstanceAndPrice();
	void guiAddToRecipe();
	void addToRecipe();
	void guiGenerateRecipe();
	void generateRecipe();
	void exportRecipe();
	void guiExportRecipe();
	void guiNrOfMedWithPriceGT();
	void nrOfMedWithPriceGT();
	void clearRecipe();
	void option();
	void undo();
	void recipeGUI();
	void recipeReadOnlyGUI();
};