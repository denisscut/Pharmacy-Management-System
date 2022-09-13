#pragma once
#include <QAbstractTableModel>
#include "medicament.h"
class TableModel : public QAbstractTableModel {
public:
	std::vector<Medicament> medicaments;
	TableModel(const std::vector<Medicament>& medicaments) : medicaments{ medicaments } {};
	/**
	* number of rows
	*/
	int rowCount(const QModelIndex& parent = QModelIndex()) const override;
	/**
	* number of columns
	*/
	int columnCount(const QModelIndex& parent = QModelIndex()) const override;
	/**
	* Value at a given position
	*/
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

	void setMedicaments(const std::vector<Medicament>& medicaments2);
};