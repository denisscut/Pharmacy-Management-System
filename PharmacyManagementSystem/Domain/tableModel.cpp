#include "tableModel.h"

int TableModel::rowCount(const QModelIndex&) const{
	return (int)medicaments.size();
}

int TableModel::columnCount(const QModelIndex&) const {
	return 4;
}

QVariant TableModel::data(const QModelIndex& index, int role) const {
	if (role == Qt::DisplayRole) {
		auto medicament = medicaments[index.row()];
		if(index.column() == 0)
			return QString(QString::fromStdString(medicament.getNume()));
		else if (index.column() == 1)
			return QString(QString::fromStdString(medicament.getProducator()));
		else if (index.column() == 2)
			return QString(QString::fromStdString(medicament.getSubstanta()));
		else if (index.column() == 3)
			return QString(QString::fromStdString(std::to_string(medicament.getPret())));
	}
	return QVariant();
}

void TableModel::setMedicaments(const std::vector<Medicament>& medicaments2) {
	this->medicaments = medicaments2;
	auto topLeft = createIndex(0, 0);
	auto bottomRight = createIndex(rowCount(), columnCount());
	emit dataChanged(topLeft, bottomRight);
	emit layoutChanged();
}