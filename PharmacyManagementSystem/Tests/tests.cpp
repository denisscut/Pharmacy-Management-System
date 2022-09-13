#include "tests.h"
#include <vector>

using std::vector;

void Test::testGetSetMedicament() {
	Medicament song1{ "AA", 1.22, "AA2", "AA3" };
	assert(song1.getNume() == "AA");
	assert(song1.getProducator() == "AA2");
	assert(song1.getSubstanta() == "AA3");
	assert(song1.getPret() == 1.22);

	Medicament song2{ "BB", 3.44, "BB2", "BB3" };
	assert(song2.getNume() == "BB");
	assert(song2.getProducator() == "BB2");
	assert(song2.getSubstanta() == "BB3");
	assert(song2.getPret() == 3.44);

	song2.setNume("CC");
	song2.setProducator("CC2");
	song2.setSubstanta("CC3");
	song2.setPret(5.22);

	assert(song2.getNume() == "CC");
	assert(song2.getProducator() == "CC2");
	assert(song2.getSubstanta() == "CC3");
	assert(song2.getPret() == 5.22);
}


void Test::testOperatorPrintMedicament() {
	const Medicament& m1{ "A", 2, "A2", "A3" };
	std::stringstream out;
	out << m1;
	assert(out.str() == "Nume: A | Producator: A2 | Substanta: A3 | Pret: 2");
}


void Test::testToStringMedicament() {
	Medicament m1{ "A", 2, "A2", "A3" };
	string txt = m1.toString();

	assert(txt == "Medicamentul: A, A2, A3, 2.000000\n");
}

void Test::testDomain() {
	testGetSetMedicament();
	testOperatorPrintMedicament();
	testToStringMedicament();
}


void Test::testAddRepo() {
	Repository testRepo;
	Medicament med1{ "A", 3.45, "A2", "A3" };
	testRepo.store(med1);
	assert(testRepo.getAllMedicamente().size() == 1);

	Medicament med2{ "B", 3.42, "B2", "B3" };
	Medicament med3{ "A", 4.32, "A2", "A3" };
	try {
		testRepo.store(med3);
		assert(false);
	}
	catch (RepoException) {
		assert(true);
	}
}


void Test::testDeleteRepo() {
	Repository testRepo;
	Medicament med1{ "A1", 3.45, "A2", "A3" };
	testRepo.store(med1);
	assert(testRepo.getAllMedicamente().size() == 1);
	Medicament med2{ "B1", 3.42, "B2", "B3" };
	testRepo.store(med2);
	try {
		testRepo.deleteMedicament("A1", "A3");
		assert(false);
	}
	catch (RepoException) {
		assert(true);
	}
	testRepo.deleteMedicament("A1", "A2");
	assert(testRepo.getAllMedicamente().size() == 1);
	testRepo.deleteMedicament("B1", "B2");
	assert(testRepo.getAllMedicamente().size() == 0);
}


void Test::testFindRepo() {
	Repository testRepo;

	Medicament med1{ "AA", 3.24, "AA2", "AA3", };
	Medicament med2{ "BB", 2.44, "AA2", "AA3", };
	Medicament med3{ "CC", 4.45, "CC2", "AA3", };
	testRepo.store(med1);
	testRepo.store(med2);

	auto foundMed = testRepo.find("AA", "AA2");
	assert(foundMed.getProducator() == "AA2");
	assert(foundMed.getPret() == 3.24);
	assert(foundMed.getSubstanta() == "AA3");


	try {
		testRepo.find("DD", "DD2");
		assert(false);
	}
	catch (RepoException& ve) {
		assert(ve.getErrorMessage() == "Medicamentul cu numele DD si producatorul DD2 nu exista in lista");
	}
}


void Test::testModifyRepo() {
	Repository testRepo;
	Medicament med1{ "A1", 3.45, "A2", "A3" };
	testRepo.store(med1);
	assert(testRepo.getAllMedicamente().size() == 1);
	Medicament med2{ "B1", 3.42, "B2", "B3" };
	Medicament med3{ "C1", 3.41, "C2", "C3" };
	testRepo.store(med2);
	testRepo.modifyMedicament(med1, med3);

	//vector <Medicament>::const_iterator it = testRepo.getAllMedicamente().begin();
	//vector<Medicament>::const_iterator it = testRepo.getAllMedicamente().begin();
	/*assert(it->getNume() == "C1");
	assert(it->getPret() == 3.41);
	assert(it->getProducator() == "C2");
	assert(it->getSubstanta() == "C3");
	it++;
	assert(it->getNume() == "B1");
	assert(it->getPret() == 3.42);
	assert(it->getProducator() == "B2");
	assert(it->getSubstanta() == "B3");*/
}

void Test::testFiltrareRepo() {
	Repository testRepo;
	Medicament med1{ "A1", 3.89, "B2", "A3" };
	Medicament med2{ "B1", 3.45, "A2", "C3" };
	Medicament med3{ "D1", 3.46, "D2", "C3" };

	testRepo.store(med1);
	testRepo.store(med2);
	testRepo.store(med3);

	vector<Medicament> vec = testRepo.filtrare([](Medicament el) {return el.getPret() == 3.45; });
	assert(vec.size() == 1);
	assert(vec[0].getNume() == "B1");

	string substanta = "C3";
	vector<Medicament> vec2 = testRepo.filtrare([substanta](Medicament el) {return el.getSubstanta() == substanta; });
	assert(vec2.size() == 2);
	assert(vec2[0].getPret() == 3.45);
	assert(vec2[1].getPret() == 3.46);
}


void Test::testSortareRepo() {
	Repository testRepo;
	Medicament med1{ "D1", 3.89, "B2", "D3" };
	Medicament med2{ "B1", 3.45, "A2", "C3" };
	Medicament med3{ "A1", 3.40, "D2", "C3" };
	Medicament med4{ "F1", 3.40, "F2", "G3" };
	Medicament med5{ "G1", 3.40, "G2", "G3" };
	testRepo.store(med1);
	testRepo.store(med2);
	testRepo.store(med3);
	testRepo.store(med4);
	testRepo.store(med5);

	vector<Medicament> vec = testRepo.sortare([](Medicament el, Medicament el2) {return el.getNume() < el2.getNume(); });
	assert(vec[0].getNume() == "A1");
	assert(vec[1].getNume() == "B1");
	assert(vec[2].getNume() == "D1");

	assert(testRepo.getAllMedicamente()[0].getNume() == "D1");
	assert(testRepo.getAllMedicamente()[1].getNume() == "B1");
	assert(testRepo.getAllMedicamente()[2].getNume() == "A1");

	vector<Medicament> vec2 = testRepo.sortare([](Medicament el, Medicament el2) {return el.getProducator() < el2.getProducator(); });

	assert(vec2[0].getProducator() == "A2");
	assert(vec2[1].getProducator() == "B2");
	assert(vec2[2].getProducator() == "D2");


	assert(testRepo.getAllMedicamente()[0].getProducator() == "B2");
	assert(testRepo.getAllMedicamente()[1].getProducator() == "A2");
	assert(testRepo.getAllMedicamente()[2].getProducator() == "D2");


	vector<Medicament> vec3 = testRepo.sortare([](Medicament el, Medicament el2) {
		if (el.getSubstanta() < el2.getSubstanta())
			return true;
		else if (el.getSubstanta() == el2.getSubstanta() && el.getPret() < el2.getPret())
			return true;
		return false;
		});

	assert(vec3[0].getSubstanta() == "C3");
	assert(vec3[1].getSubstanta() == "C3");
	assert(vec3[2].getSubstanta() == "D3");

	assert(vec3[0].getPret() == 3.40);
	assert(vec3[1].getPret() == 3.45);
	assert(vec3[2].getPret() == 3.89);

	assert(testRepo.getAllMedicamente()[0].getProducator() == "B2");
	assert(testRepo.getAllMedicamente()[1].getProducator() == "A2");
	assert(testRepo.getAllMedicamente()[2].getProducator() == "D2");

}


void Test::testGetNumberOfMedicamentsByPriceRepo() {
	Repository testRepo;
	Medicament med1{ "D1", 5.89, "B2", "D3" };
	Medicament med2{ "B1", 4.45, "A2", "C3" };
	Medicament med3{ "A1", 3.40, "D2", "C3" };
	Medicament med4{ "F1", 2.40, "F2", "G3" };
	Medicament med5{ "G1", 3.40, "G2", "G3" };
	testRepo.store(med1);
	testRepo.store(med2);
	testRepo.store(med3);
	testRepo.store(med4);
	testRepo.store(med5);

	assert(testRepo.getNumberOfMedicamentsByPrice(2) == 5);
	assert(testRepo.getNumberOfMedicamentsByPrice(4) == 2);
	assert(testRepo.getNumberOfMedicamentsByPrice(5.90) == 0);
}


void Test::testRecipe() {

	RepoAbstract* repo = new Repository();
	Recipe repoTest{ *repo };
	Medicament med1{ "D1", 3.89, "B2", "D3" };
	Medicament med2{ "B1", 3.45, "A2", "C3" };
	Medicament med3{ "A1", 3.40, "D2", "C3" };

	vector <Medicament> v;
	v.push_back(med1);
	v.push_back(med2);
	v.push_back(med3);

	repoTest.addToRecipe(med1);
	repoTest.addToRecipe(med2);
	repoTest.addToRecipe(med3);

	assert(repoTest.getRecipe().size() == 3);
	repoTest.eraseRecipe();
	assert(repoTest.getRecipe().size() == 0);

	repoTest.generateRecipe(8, v);
	assert(repoTest.getRecipe()[0].getNume() == "D1" || repoTest.getRecipe()[0].getNume() == "B1" || repoTest.getRecipe()[0].getNume() == "A1");
}


void Test::testRepo() {
	testAddRepo();
	testDeleteRepo();
	testFindRepo();
	testModifyRepo();
	testFiltrareRepo();
	testSortareRepo();
	testRecipe();
	testGetNumberOfMedicamentsByPriceRepo();
}

void Test::testAddService() {
	Repository testRepo;
	MedicamentValidator testVal;
	Service testService{ testRepo,testVal };

	testService.addMedicament("AA", 3.42, "BB", "CC");
	testService.addMedicament("AA2", 3.42, "BB", "CC");
	testService.addMedicament("AA3", 3.42, "BB", "CC");

	assert(testService.getAllMedicamente().size() == 3);
	try {
		testService.addMedicament("AA", 3.42, "BB", "CC");
		assert(false);
	}
	catch (RepoException&) {
		assert(true);
	}

	try {
		testService.addMedicament("DD", 1.22, "DD1", "DD2");
		assert(true);
	}
	catch (ValidationException&) {
		assert(false);
	}

	try {
		testService.addMedicament("", 2.24, "DD1", "DD2");
		assert(false);
	}
	catch (ValidationException& ve) {
		assert(ve.getErrorMessages() == "Numele trebuie sa aiba cel putin 2 caractere.\n");
	}


	try {
		testService.addMedicament("EE", 2.24, "", "DD2");
		assert(false);
	}
	catch (ValidationException&) {
		assert(true);
	}

	try {
		testService.addMedicament("GG", -2, "DD1", "DD2");
		assert(false);
	}
	catch (ValidationException&) {
		assert(true);
	}
}


void Test::testDeleteService() {
	Repository testRepo;
	MedicamentValidator testVal;
	Service testSrv{ testRepo, testVal };
	testSrv.addMedicament("A1", 3.45, "A2", "A3");
	assert(testSrv.getAllMedicamente().size() == 1);
	testSrv.addMedicament("B1", 3.45, "B2", "B3");

	try {
		testSrv.deleteMedicament("A2", "A3");
		assert(false);
	}
	catch (RepoException) {
		assert(true);
	}
	testSrv.deleteMedicament("A1", "A2");
	assert(testSrv.getAllMedicamente().size() == 1);
	testSrv.deleteMedicament("B1", "B2");
	assert(testSrv.getAllMedicamente().size() == 0);
}


void Test::testModifyService() {
	Repository testRepo;
	MedicamentValidator testVal;
	Service testSrv{ testRepo, testVal };
	testSrv.addMedicament("A1", 3.45, "A2", "A3");
	assert(testSrv.getAllMedicamente().size() == 1);
	testSrv.addMedicament("B1", 3.45, "B2", "B3");

	try {
		testSrv.modifyMedicament("A1", "A3", "C1", 3.42, "C2", "C3");
		assert(false);
	}
	catch (RepoException) {
		assert(true);
	}

	try {
		testSrv.modifyMedicament("A1", "A2", "C", 3.42, "C2", "C3");
		assert(false);
	}
	catch (ValidationException) {
		assert(true);
	}

	try {
		testSrv.modifyMedicament("A1", "A2", "B1", 3.45, "B2", "B3");
		assert(false);
	}
	catch (RepoException) {
		assert(true);
	}

	testSrv.modifyMedicament("A1", "A2", "C1", 3.42, "C2", "C3");
	vector <Medicament>::const_iterator it = testSrv.getAllMedicamente().begin();
	assert(it->getNume() == "C1");
	assert(it->getPret() == 3.42);
	assert(it->getProducator() == "C2");
	assert(it->getSubstanta() == "C3");
}


void Test::testFindService() {
	Repository testRepo;
	MedicamentValidator testVal;
	Service testSrv{ testRepo, testVal };
	testSrv.addMedicament("A1", 3.45, "A2", "A3");
	assert(testSrv.getAllMedicamente().size() == 1);
	testSrv.addMedicament("B1", 3.45, "B2", "B3");

	try {
		testSrv.findMedicament("A2", "A3");
		assert(false);
	}
	catch (RepoException) {
		assert(true);
	}
	try {
		testSrv.findMedicament("A", "A3");
		assert(false);
	}
	catch (ValidationException) {
		assert(true);
	}
	try {
		const Medicament& med = testSrv.findMedicament("A1", "A2");
		assert(med.getNume() == "A1");
		assert(med.getPret() == 3.45);
		assert(med.getProducator() == "A2");
		assert(med.getSubstanta() == "A3");
	}
	catch (ValidationException) {
		assert(false);
	}
	catch (RepoException) {
		assert(false);
	}
}


void Test::testExistsService() {
	Repository testRepo;
	MedicamentValidator testVal;
	Service testSrv{ testRepo, testVal };

	testSrv.addMedicament("A1", 3.45, "A2", "A3");
	assert(testSrv.getAllMedicamente().size() == 1);
	testSrv.addMedicament("B1", 3.45, "B2", "B3");
	bool result;


	try {
		result = testSrv.exists("A1", "A3");
		assert(false);
	}
	catch (RepoException re) {
		assert(true);
	}

	try {
		result = testSrv.exists("A1", "A");
		assert(false);
	}
	catch (ValidationException ve) {
		assert(true);
	}

	try {
		result = testSrv.exists("A1", "A2");
		assert(true);
		assert(result == true);
	}
	catch (ValidationException ve) {
		assert(false);
	}
	catch (RepoException re) {
		assert(false);
	}
}


void Test::testFiltrareService() {
	Repository testRepo;
	MedicamentValidator testVal;
	Service testSrv{ testRepo, testVal };

	testSrv.addMedicament("A1", 3.89, "B2", "A3");
	assert(testSrv.getAllMedicamente().size() == 1);
	testSrv.addMedicament("B1", 3.45, "A2", "C3");
	testSrv.addMedicament("D1", 3.46, "D2", "C3");

	vector<Medicament> vec = testSrv.filtrarePret(3.45);
	assert(vec.size() == 1);
	assert(vec[0].getNume() == "B1");

	vector<Medicament> vec2 = testSrv.filtrareSubstanta("C3");
	assert(vec2.size() == 2);
	assert(vec2[0].getPret() == 3.45);
	assert(vec2[1].getPret() == 3.46);
}

void Test::testSortareService() {
	Repository testRepo;
	MedicamentValidator testVal;
	Service testSrv{ testRepo, testVal };

	testSrv.addMedicament("D1", 3.89, "B2", "D3");
	assert(testSrv.getAllMedicamente().size() == 1);
	testSrv.addMedicament("B1", 3.45, "A2", "C3");
	testSrv.addMedicament("A1", 3.40, "D2", "C3");
	testSrv.addMedicament("F1", 3.40, "F2", "G3");
	testSrv.addMedicament("G1", 3.40, "G2", "G3");

	vector<Medicament> vec = testSrv.sortareNume();
	assert(vec[0].getNume() == "A1");
	assert(vec[1].getNume() == "B1");
	assert(vec[2].getNume() == "D1");

	assert(testSrv.getAllMedicamente()[0].getNume() == "D1");
	assert(testSrv.getAllMedicamente()[1].getNume() == "B1");
	assert(testSrv.getAllMedicamente()[2].getNume() == "A1");

	vector<Medicament> vec2 = testSrv.sortareProducator();

	assert(vec2[0].getProducator() == "A2");
	assert(vec2[1].getProducator() == "B2");
	assert(vec2[2].getProducator() == "D2");


	assert(testSrv.getAllMedicamente()[0].getProducator() == "B2");
	assert(testSrv.getAllMedicamente()[1].getProducator() == "A2");
	assert(testSrv.getAllMedicamente()[2].getProducator() == "D2");


	vector<Medicament> vec3 = testSrv.sortareSubstSiPret();

	assert(vec3[0].getSubstanta() == "C3");
	assert(vec3[1].getSubstanta() == "C3");
	assert(vec3[2].getSubstanta() == "D3");

	assert(vec3[0].getPret() == 3.40);
	assert(vec3[1].getPret() == 3.45);
	assert(vec3[2].getPret() == 3.89);

	assert(testSrv.getAllMedicamente()[0].getProducator() == "B2");
	assert(testSrv.getAllMedicamente()[1].getProducator() == "A2");
	assert(testSrv.getAllMedicamente()[2].getProducator() == "D2");

}


void Test::testRecipeService() {

	Repository repoTest;
	MedicamentValidator valTest;
	Service srvTest = { repoTest, valTest };
	Medicament med1{ "D1", 3.89, "B2", "D3" };
	Medicament med2{ "B1", 3.45, "A2", "C3" };
	Medicament med3{ "A1", 3.40, "D2", "C3" };

	vector <Medicament> v;
	v.push_back(med1);
	v.push_back(med2);
	v.push_back(med3);

	srvTest.addToRecipe(med1);
	srvTest.addToRecipe(med2);
	srvTest.addToRecipe(med3);

	assert(srvTest.getRecipe().size() == 3);
	srvTest.eraseRecipe();
	assert(srvTest.getRecipe().size() == 0);

	srvTest.generateRecipe(8, v);
	assert(srvTest.getRecipe()[0].getNume() == "D1" || srvTest.getRecipe()[0].getNume() == "B1" || srvTest.getRecipe()[0].getNume() == "A1");
}


void Test::testGetNumberOfMedicamentsByPriceService() {
	Repository testRepo;
	MedicamentValidator testVal;
	Service testSrv{ testRepo, testVal };

	testSrv.addMedicament("D1", 3.89, "B2", "D3");
	assert(testSrv.getAllMedicamente().size() == 1);
	testSrv.addMedicament("B1", 3.45, "A2", "C3");
	testSrv.addMedicament("A1", 2.1, "D2", "C3");
	testSrv.addMedicament("F1", 3.40, "F2", "G3");
	testSrv.addMedicament("G1", 3.40, "G2", "G3");

	assert(testSrv.getNumberOfMedicamentsByPrice(3) == 4);
	assert(testSrv.getNumberOfMedicamentsByPrice(2) == 5);
	assert(testSrv.getNumberOfMedicamentsByPrice(4) == 0);
}


void Test::testUndoService() {
	Repository testRepo;
	MedicamentValidator testVal;
	Service testSrv{ testRepo, testVal };

	testSrv.addMedicament("D1", 3.89, "B2", "D3");
	assert(testSrv.getAllMedicamente().size() == 1);
	testSrv.addMedicament("B1", 3.45, "A2", "C3");
	assert(testSrv.getAllMedicamente().size() == 2);

	testSrv.deleteMedicament("B1", "A2");
	assert(testSrv.getAllMedicamente().size() == 1);

	testSrv.modifyMedicament("D1", "B2", "ASD", 6, "ASF", "ASH");
	assert(testSrv.getAllMedicamente()[0].getNume() == "ASD");
	assert(testSrv.getAllMedicamente()[0].getPret() == 6);
	assert(testSrv.getAllMedicamente()[0].getProducator() == "ASF");
	assert(testSrv.getAllMedicamente()[0].getSubstanta() == "ASH");

	testSrv.undo();
	assert(testSrv.getAllMedicamente()[0].getNume() == "D1");
	assert(testSrv.getAllMedicamente()[0].getPret() == 3.89);
	assert(testSrv.getAllMedicamente()[0].getProducator() == "B2");
	assert(testSrv.getAllMedicamente()[0].getSubstanta() == "D3");

	testSrv.undo();
	assert(testSrv.getAllMedicamente().size() == 2);
	assert(testSrv.getAllMedicamente()[1].getNume() == "B1");
	assert(testSrv.getAllMedicamente()[1].getPret() == 3.45);
	assert(testSrv.getAllMedicamente()[1].getProducator() == "A2");
	assert(testSrv.getAllMedicamente()[1].getSubstanta() == "C3");

	testSrv.undo();
	assert(testSrv.getAllMedicamente().size() == 1);

	testSrv.undo();
	assert(testSrv.getAllMedicamente().size() == 0);

	try {
		testSrv.undo();
		assert(false);
	}
	catch (UndoException ue) {
		assert(true);
		assert(ue.getErrorMessage() == "Nu mai exista operatii");
	}
}


void Test::testService() {
	testAddService();
	testDeleteService();
	testModifyService();
	testFindService();
	testExistsService();
	testFiltrareService();
	testSortareService();
	testRecipeService();
	testGetNumberOfMedicamentsByPriceService();
	testUndoService();
}


void Test::testStrtoint() {
	string str;
	str = "123\n";
	int s = strtoint(str);
	assert(s == 123);

	str = "\n";
	s = strtoint(str);
	assert(s == INT_MAX);

	str = "123asd\n";
	s = strtoint(str);
	assert(s == INT_MAX);

	str = "-123\n";
	s = strtoint(str);
	assert(s == -123);
}


void Test::testUtils() {
	testStrtoint();
}


void Test::testExportCSV() {
	Repository repoTest;
	MedicamentValidator valTest;
	Service srvTest = { repoTest, valTest };

	Medicament med1{ "D1", 3.89, "B2", "D3" };
	Medicament med2{ "B1", 3.45, "A2", "C3" };
	Medicament med3{ "A1", 3.40, "D2", "C3" };

	vector <Medicament> v;
	v.push_back(med1);
	v.push_back(med2);
	v.push_back(med3);

	srvTest.addToRecipe(med1);
	srvTest.addToRecipe(med2);
	srvTest.addToRecipe(med3);

	string nameOfFile = "test.csv";
	srvTest.exportRecipe(nameOfFile);

	std::ifstream in(nameOfFile);
	string line;
	string delimiter = ",";
	size_t pos;
	size_t numberOfLine = 0;
	vector <string> words;
	getline(in, line);
	while (getline(in, line)) {
		words.erase(words.begin(), words.end());
		while ((pos = line.find(delimiter)) != line.npos) {
			string word = line.substr(0, pos);
			words.push_back(word);
			line.erase(line.begin(), line.begin() + pos + delimiter.length());
		}
		words.push_back(line);
		assert(words[0] == v[numberOfLine].getNume());
		assert(words[1] == v[numberOfLine].getProducator());
		assert(words[2] == v[numberOfLine].getSubstanta());
		assert(stod(words[3]) == v[numberOfLine].getPret());
		++numberOfLine;
	}

	in.close();
	remove("test.csv");
}


void Test::testExportHTML() {
	Repository repoTest;
	MedicamentValidator valTest;
	Service srvTest = { repoTest, valTest };

	Medicament med1{ "D1", 3.89, "B2", "D3" };
	Medicament med2{ "B1", 3.45, "A2", "C3" };
	Medicament med3{ "A1", 3.40, "D2", "C3" };

	vector <Medicament> v;
	v.push_back(med1);
	v.push_back(med2);
	v.push_back(med3);

	srvTest.addToRecipe(med1);
	srvTest.addToRecipe(med2);
	srvTest.addToRecipe(med3);

	vector <string> words;
	std::ostringstream ss1;
	for (auto med : v) {
		words.push_back(med.getNume());
		words.push_back(med.getProducator());
		words.push_back(med.getSubstanta());
		ss1 << med.getPret();

		words.push_back(ss1.str());
		ss1.str("");
		ss1.clear();
	}

	size_t wordCount = 0;

	string nameOfFile = "test.html";

	srvTest.exportRecipe(nameOfFile);

	std::ifstream in(nameOfFile);
	string line;
	string startOfLine = "<td>";
	string endOfLine = "</td>";
	size_t posStart, posEnd;

	while (getline(in, line)) {

		posStart = line.find(startOfLine);
		posEnd = line.find(endOfLine);

		if (posStart != line.npos && posEnd != line.npos) {
			line.erase(line.begin(), line.begin() + posStart + startOfLine.length());
			posEnd = line.find(endOfLine);
			line.erase(line.begin() + posEnd, line.end());
			assert(line == words[wordCount++]);
		}
	}

	in.close();
	remove("test.html");
}


void Test::testFileValidator() {
	Repository repoTest;
	MedicamentValidator valTest;
	Service srvTest = { repoTest, valTest };

	try {
		srvTest.exportRecipe("as");
		assert(false);
	}
	catch (ValidationException& ve) {
		assert(ve.getErrorMessages() == "Numele fisierului este prea mic.\n");
	}

	try {
		srvTest.exportRecipe("as.dsad");
		assert(false);
	}
	catch (ValidationException& ve) {
		assert(ve.getErrorMessages() == "Numele fisierului nu are extensia CSV sau HTML.\n");
	}

	try {
		srvTest.exportRecipe("a.csva");
		assert(false);
	}
	catch (ValidationException& ve) {
		assert(ve.getErrorMessages() == "Numele fisierului nu are extensia CSV sau HTML.\n");
	}

	try {
		srvTest.exportRecipe("a.htmla");
		assert(false);
	}
	catch (ValidationException& ve) {
		assert(ve.getErrorMessages() == "Numele fisierului nu are extensia CSV sau HTML.\n");
	}
}


void Test::testMedicamentValidator() {
	MedicamentValidator val;
	Medicament med1{ "D1", 3.89, "B2", "D3" };
	try {
		val.valideaza(med1);
		assert(true);
	}
	catch (ValidationException ve) {
		assert(false);
	}
	Medicament med2{ "D", 3.89, "B2", "D3" };
	try {
		val.valideaza(med2);
		assert(false);
	}
	catch (ValidationException ve) {
		assert(true);
		assert(ve.getErrorMessages() == "Numele trebuie sa aiba cel putin 2 caractere.\n");
	}

	Medicament med3{ "D2", -1, "B2", "D3" };
	try {
		val.valideaza(med3);
		assert(false);
	}
	catch (ValidationException ve) {
		assert(true);
		assert(ve.getErrorMessages() == "Pretul trebuie sa fie pozitiv.\n");
	}

	try {
		val.valideazaNumeSiProd("DD", "B2");
		assert(true);
	}
	catch (ValidationException ve) {
		assert(false);
	}

	try {
		val.valideazaNumeSiProd("D", "B2");
		assert(false);
	}
	catch (ValidationException ve) {
		assert(true);
		assert(ve.getErrorMessages() == "Numele trebuie sa aiba cel putin 2 caractere.\n");
	}

	try {
		val.valideazaNumeSiProd("D2", "B");
		assert(false);
	}
	catch (ValidationException ve) {
		assert(true);
		assert(ve.getErrorMessages() == "Producatorul trebuie sa aiba cel putin 2 caractere.\n");
	}

	try {
		val.valideazaNumeSiProd("D", "B");
		assert(false);
	}
	catch (ValidationException ve) {
		assert(true);
		assert(ve.getErrorMessages() == "Numele trebuie sa aiba cel putin 2 caractere.\nProducatorul trebuie sa aiba cel putin 2 caractere.\n");
	}
}

void Test::testAddRepoProb() {
	RepoProbabilitati testRepo;
	testRepo.setProb10();
	Medicament med1{ "A", 3.45, "A2", "A3" };
	testRepo.store(med1);
	assert(testRepo.getAllMedicamente().size() == 1);

	Medicament med2{ "B", 3.42, "B2", "B3" };
	Medicament med3{ "A", 4.32, "A2", "A3" };
	try {
		testRepo.store(med3);
		assert(false);
	}
	catch (RepoException) {
		assert(true);
	}
}


void Test::testDeleteRepoProb() {
	RepoProbabilitati testRepo;
	testRepo.setProb10();
	Medicament med1{ "A1", 3.45, "A2", "A3" };
	testRepo.store(med1);
	assert(testRepo.getAllMedicamente().size() == 1);
	Medicament med2{ "B1", 3.42, "B2", "B3" };
	testRepo.store(med2);
	try {
		testRepo.deleteMedicament("A1", "A3");
		assert(false);
	}
	catch (RepoException) {
		assert(true);
	}
	testRepo.deleteMedicament("A1", "A2");
	assert(testRepo.getAllMedicamente().size() == 1);
	testRepo.deleteMedicament("B1", "B2");
	assert(testRepo.getAllMedicamente().size() == 0);
}


void Test::testFindRepoProb() {
	RepoProbabilitati testRepo;
	testRepo.setProb10();

	Medicament med1{ "AA", 3.24, "AA2", "AA3", };
	Medicament med2{ "BB", 2.44, "AA2", "AA3", };
	Medicament med3{ "CC", 4.45, "CC2", "AA3", };
	testRepo.store(med1);
	testRepo.store(med2);

	auto foundMed = testRepo.find("AA", "AA2");
	assert(foundMed.getProducator() == "AA2");
	assert(foundMed.getPret() == 3.24);
	assert(foundMed.getSubstanta() == "AA3");


	try {
		testRepo.find("DD", "DD2");
		assert(false);
	}
	catch (RepoException& ve) {
		assert(ve.getErrorMessage() == "Medicamentul cu numele DD si producatorul DD2 nu exista in lista");
	}
}


void Test::testModifyRepoProb() {
	RepoProbabilitati testRepo;
	testRepo.setProb10();
	Medicament med1{ "A1", 3.45, "A2", "A3" };
	testRepo.store(med1);
	assert(testRepo.getAllMedicamente().size() == 1);
	Medicament med2{ "B1", 3.42, "B2", "B3" };
	Medicament med3{ "C1", 3.41, "C2", "C3" };
	testRepo.store(med2);
	testRepo.modifyMedicament(med1, med3);

	//vector <Medicament>::const_iterator it = testRepo.getAllMedicamente().begin();
	//vector<Medicament>::const_iterator it = testRepo.getAllMedicamente().begin();
	/*assert(it->getNume() == "C1");
	assert(it->getPret() == 3.41);
	assert(it->getProducator() == "C2");
	assert(it->getSubstanta() == "C3");
	it++;
	assert(it->getNume() == "B1");
	assert(it->getPret() == 3.42);
	assert(it->getProducator() == "B2");
	assert(it->getSubstanta() == "B3");*/
}

void Test::testFiltrareRepoProb() {
	RepoProbabilitati testRepo;
	testRepo.setProb10();
	Medicament med1{ "A1", 3.89, "B2", "A3" };
	Medicament med2{ "B1", 3.45, "A2", "C3" };
	Medicament med3{ "D1", 3.46, "D2", "C3" };

	testRepo.store(med1);
	testRepo.store(med2);
	testRepo.store(med3);

	vector<Medicament> vec = testRepo.filtrare([](Medicament el) {return el.getPret() == 3.45; });
	assert(vec.size() == 1);
	assert(vec[0].getNume() == "B1");

	string substanta = "C3";
	vector<Medicament> vec2 = testRepo.filtrare([substanta](Medicament el) {return el.getSubstanta() == substanta; });
	assert(vec2.size() == 2);
	assert(vec2[0].getPret() == 3.45);
	assert(vec2[1].getPret() == 3.46);
}


void Test::testSortareRepoProb() {
	RepoProbabilitati testRepo;
	testRepo.setProb10();
	Medicament med1{ "D1", 3.89, "B2", "D3" };
	Medicament med2{ "B1", 3.45, "A2", "C3" };
	Medicament med3{ "A1", 3.40, "D2", "C3" };
	Medicament med4{ "F1", 3.40, "F2", "G3" };
	Medicament med5{ "G1", 3.40, "G2", "G3" };
	testRepo.store(med1);
	testRepo.store(med2);
	testRepo.store(med3);
	testRepo.store(med4);
	testRepo.store(med5);

	vector<Medicament> vec = testRepo.sortare([](Medicament el, Medicament el2) {return el.getNume() < el2.getNume(); });
	assert(vec[0].getNume() == "A1");
	assert(vec[1].getNume() == "B1");
	assert(vec[2].getNume() == "D1");

	assert(testRepo.getAllMedicamente()[0].getNume() == "D1");
	assert(testRepo.getAllMedicamente()[1].getNume() == "B1");
	assert(testRepo.getAllMedicamente()[2].getNume() == "A1");

	vector<Medicament> vec2 = testRepo.sortare([](Medicament el, Medicament el2) {return el.getProducator() < el2.getProducator(); });

	assert(vec2[0].getProducator() == "A2");
	assert(vec2[1].getProducator() == "B2");
	assert(vec2[2].getProducator() == "D2");


	assert(testRepo.getAllMedicamente()[0].getProducator() == "B2");
	assert(testRepo.getAllMedicamente()[1].getProducator() == "A2");
	assert(testRepo.getAllMedicamente()[2].getProducator() == "D2");


	vector<Medicament> vec3 = testRepo.sortare([](Medicament el, Medicament el2) {
		if (el.getSubstanta() < el2.getSubstanta())
			return true;
		else if (el.getSubstanta() == el2.getSubstanta() && el.getPret() < el2.getPret())
			return true;
		return false;
		});

	assert(vec3[0].getSubstanta() == "C3");
	assert(vec3[1].getSubstanta() == "C3");
	assert(vec3[2].getSubstanta() == "D3");

	assert(vec3[0].getPret() == 3.40);
	assert(vec3[1].getPret() == 3.45);
	assert(vec3[2].getPret() == 3.89);

	assert(testRepo.getAllMedicamente()[0].getProducator() == "B2");
	assert(testRepo.getAllMedicamente()[1].getProducator() == "A2");
	assert(testRepo.getAllMedicamente()[2].getProducator() == "D2");

}


void Test::testGetNumberOfMedicamentsByPriceRepoProb() {
	RepoProbabilitati testRepo;
	testRepo.setProb10();
	Medicament med1{ "D1", 5.89, "B2", "D3" };
	Medicament med2{ "B1", 4.45, "A2", "C3" };
	Medicament med3{ "A1", 3.40, "D2", "C3" };
	Medicament med4{ "F1", 2.40, "F2", "G3" };
	Medicament med5{ "G1", 3.40, "G2", "G3" };
	testRepo.store(med1);
	testRepo.store(med2);
	testRepo.store(med3);
	testRepo.store(med4);
	testRepo.store(med5);

	assert(testRepo.getNumberOfMedicamentsByPrice(2) == 5);
	assert(testRepo.getNumberOfMedicamentsByPrice(4) == 2);
	assert(testRepo.getNumberOfMedicamentsByPrice(5.90) == 0);
}


void Test::testRepoProb() {
	testAddRepoProb();
	testDeleteRepoProb();
	testFindRepoProb();
	testModifyRepoProb();
	testFiltrareRepoProb();
	testSortareRepoProb();
	testGetNumberOfMedicamentsByPriceRepoProb();
}

void Test::testAll() {
	testDomain();
	testRepo();
	testRepoProb();
	testService();
	testUtils();
	testExportCSV();
	testExportHTML();
	testFileValidator();
	testMedicamentValidator();
}