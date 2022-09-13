#pragma once
#include <QtWidgets/QApplication>
#include <QLabel>
#include "../Domain/observer.h"
#include "../Domain/recipe.h"
#include <qlistwidget.h>
#include <qpushbutton.h>
#include <QVBoxLayout>
#include <QInputDialog>
#include "../Domain/tableModel.h"
class RecipeGUI : public QWidget, public Observer {
	Recipe& recipe;
	QListWidget* listOfMedicaments;
	QPushButton* eraseRecipeBtn;
	QPushButton* generateRecipeBtn;



	void initGUI() {
		QVBoxLayout* lyMain = new QVBoxLayout();
		this->setLayout(lyMain);

		listOfMedicaments = new QListWidget();
		lyMain->addWidget(listOfMedicaments);
		eraseRecipeBtn = new QPushButton("Goleste reteta");
		lyMain->addWidget(eraseRecipeBtn);

		generateRecipeBtn = new QPushButton("Genereaza reteta");
		lyMain->addWidget(generateRecipeBtn);
	}
	void connectSignals() {
		recipe.addObserver(this);
		QObject::connect(eraseRecipeBtn, &QPushButton::clicked, [&]() {
			recipe.eraseRecipe();
			reloadList(recipe.getRecipe());
		});
		QObject::connect(generateRecipeBtn, &QPushButton::clicked, [&]() {
			QInputDialog* inputDialog = new QInputDialog(this);
			//inputDialog->setOptions(QInputDialog::NoButtons);

			bool ok = false;

			int result = inputDialog->getInt(nullptr,"","Numarul de medicamente generate pe lista: ", 0, 0, 2147483647, 1, &ok);

			//recipe.eraseRecipe();
			recipe.generateRecipeWithoutVec(result);
			reloadList(recipe.getRecipe());
		});
	}

	void reloadList(const vector<Medicament>& medicaments) {
		listOfMedicaments->clear();
		for (auto med : medicaments) {
			QListWidgetItem* item = new QListWidgetItem();
			item->setText(QString::fromStdString(med.toString()));
			listOfMedicaments->addItem(item);
		}
	}

	void update() override{
		reloadList(recipe.getRecipe());
	}

public:
	RecipeGUI(Recipe& recipe) : recipe{ recipe } {
		initGUI();
		connectSignals();
		reloadList(recipe.getRecipe());
	}

	~RecipeGUI() {
		recipe.removeObserver(this);
	}
};