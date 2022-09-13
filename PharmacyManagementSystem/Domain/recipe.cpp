#include "recipe.h"

void Recipe::eraseRecipe() {
	this->medicamente.erase(this->medicamente.begin(), this->medicamente.end());
	notify();
}

void Recipe::addToRecipe(Medicament med) {
	this->medicamente.push_back(med);
	notify();
}

vector <Medicament>& Recipe::getRecipe() {
	return this->medicamente;
}


void Recipe::generateRecipe(int number, vector <Medicament> v) {
	while (number--) {
		std::mt19937 mt{ std::random_device{}() };
		std::uniform_int_distribution<> dist(0, static_cast<int>(v.size()) - 1);
		int rndNr = dist(mt);// numar aleator intre [0,size-1]

		this->medicamente.push_back(v[rndNr]);
	}
	notify();
}

void Recipe::generateRecipeWithoutVec(int number) {
	while (number--) {
		std::mt19937 mt{ std::random_device{}() };
		std::uniform_int_distribution<> dist(0, static_cast<int>(repo.getAllMedicamente().size()) - 1);
		int rndNr = dist(mt);// numar aleator intre [0,size-1]

		this->medicamente.push_back(repo.getAllMedicamente()[rndNr]);
	}
	notify();
}

void Recipe::exportCSV(string nameOfFile) {
	std::ofstream out(nameOfFile);
	out << "Nume,Producator,Substanta,Pret\n";
	for (auto med : this->medicamente)
		out << med.getNume() << ',' << med.getProducator() << ',' << med.getSubstanta() << ',' << med.getPret() << '\n';

	out.close();
}


void Recipe::exportHTML(string nameOfFile) {
	std::ofstream out(nameOfFile);
	out << "<html>\n";
	out << "<head>\n";
	out << "<meta charset = \"utf - 8\">\n";
	out << "<title>Reteta</title>\n";
	out << "<link rel=\"stylesheet\" href=\"https://cdn.jsdelivr.net/npm/bootstrap@4.0.0/dist/css/bootstrap.min.css\" integrity=\"sha384-Gn5384xqQ1aoWXA+058RXPxPg6fy4IWvTNh0E263XmFcJlSAwiGgFAW/dAiS6JXm\" crossorigin=\"anonymous\">\n";
	out << "</head>\n";
	out << "<body>\n";
	out << "<table class=\"table table-bordered table-hover table-sm\">\n";
	out << "<thead class = \"thead-dark\">\n";
	out << "<tr>\n<th>Nume</th>\n<th>Producator</th>\n<th>Substanta</th>\n<th>Pret</th>\n</tr>\n";
	out << "</thead>\n";
	out << "<tbody>\n";
	for (auto med : this->medicamente)
		out << "<tr>\n"
		<< "<td>" << med.getNume() << "</td>\n"
		<< "<td>" << med.getProducator() << "</td>\n"
		<< "<td>" << med.getSubstanta() << "</td>\n"
		<< "<td>" << med.getPret() << "</td>\n" <<
		"</tr>\n";
	out << "</tbody>\n";
	out << "</table>\n";
	out << "</body>\n";
	out << "</html>";
	out.close();
}