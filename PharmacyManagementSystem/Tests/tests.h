#pragma once
#include <iostream>
#include <sstream>
#include <assert.h>
#include "../Domain/medicament.h"
#include "../Repository/repository.h"
#include "../Service/service.h"
#include "../Utils/utils.h"
#include <fstream>
#include<stdio.h>

class Test {
private:
	static void testGetSetMedicament();
	static void testOperatorPrintMedicament();
	static void testToStringMedicament();
	static void testDomain();

	static void testRepo();
	static void testAddRepo();
	static void testDeleteRepo();
	static void testFindRepo();
	static void testModifyRepo();
	static void testFiltrareRepo();
	static void testSortareRepo();
	static void testRecipe();
	static void testGetNumberOfMedicamentsByPriceRepo();

	static void testRepoProb();
	static void testAddRepoProb();
	static void testDeleteRepoProb();
	static void testFindRepoProb();
	static void testModifyRepoProb();
	static void testFiltrareRepoProb();
	static void testSortareRepoProb();
	static void testGetNumberOfMedicamentsByPriceRepoProb();

	static void testService();
	static void testAddService();
	static void testDeleteService();
	static void testModifyService();
	static void testFindService();
	static void testExistsService();
	static void testFiltrareService();
	static void testSortareService();
	static void testRecipeService();
	static void testGetNumberOfMedicamentsByPriceService();
	static void testUndoService();

	static void testFileValidator();
	static void testExportCSV();
	static void testExportHTML();
	static void testStrtoint();
	static void testUtils();
	static void testMedicamentValidator();
public:
	static void testAll();
};