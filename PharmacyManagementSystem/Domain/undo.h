#pragma once
#include "medicament.h"
#include "../Repository/repository.h"

class undoAction {
public:
	virtual void doUndo() = 0;

	virtual ~undoAction() {};
};


class undoAdd : public undoAction {
private:
	Medicament med;
	RepoAbstract& repo;
public:
	undoAdd(Medicament& med, RepoAbstract& repo) : med{ med }, repo{ repo } {}

	void doUndo() override {
		repo.deleteMedicament(med.getNume(), med.getProducator());
	}
};

class undoDelete : public undoAction {
private:
	Medicament med;
	RepoAbstract& repo;
public:
	undoDelete(Medicament& med, RepoAbstract& repo) : med{ med }, repo{ repo } {}

	void doUndo() override {
		repo.store(med);
	}
};

class undoModify : public undoAction {
private:
	Medicament med;
	Medicament newMed;
	RepoAbstract& repo;
public:
	undoModify(Medicament& med, Medicament& newMed, RepoAbstract& repo) : med{ med }, newMed{ newMed }, repo{ repo } {}

	void doUndo() override {
		repo.modifyMedicament(med, newMed);
	}
};

class UndoException {
private:
	string errorMsg;
public:
	UndoException(string errorMsg) :errorMsg{ errorMsg } {};
	string getErrorMessage() {
		return this->errorMsg;
	}
};