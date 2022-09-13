#include <QtWidgets/QApplication>

#include <iostream>
#include <vector>
#include "Repository/repository.h"
#include "Validators/validators.h"
#include "Service/service.h"
#include "Repository/repoProbabilitati.h"
#include "UI/ui.h"
#include <crtdbg.h>
#include "Tests/tests.h"
#include "UI/StoreGUI.h"
#include <qdebug.h>

int main(int argc, char *argv[])
{
	Test::testAll();
    QApplication a(argc, argv);
	
	Repository repo;
	MedicamentValidator val;
	Service srv = { repo, val };

	try {
		srv.addMedicament("M1", 1, "P1", "S1");
		srv.addMedicament("M2", 5, "P2", "S2");
		srv.addMedicament("M3", 3, "P3", "S3");
		srv.addMedicament("M4", 3, "P4", "S4");
		srv.addMedicament("M5", 2, "P5", "S5");
		srv.addMedicament("M6", 6, "P6", "S6");
	}
	catch (RepoException& re) {
		std::cout << re.getErrorMessage() << '\n';
	}

	StoreGUI gui{ srv };
	gui.setWindowTitle("Pharmacy Management System");
	gui.resize(1280, 720);
	//gui.setWindowState(Qt::WindowMaximized);
	gui.show();
    //w.show();
    return a.exec();
}