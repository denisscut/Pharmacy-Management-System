#pragma once

#include "../Domain/medicament.h"
#include <vector>
#include <string>
#include <iostream>
using std::string;
//using std::VectDinNewDeleteT;

class ValidationException {
	vector<string> errorMsg;
public:
	ValidationException(vector<string> errorMessages) :errorMsg{ errorMessages } {};

	string getErrorMessages() {
		string fullMsg = "";
		for (const string e : errorMsg) {
			fullMsg += e + "\n";
		}
		return fullMsg;
	}
};


/// Clasa pentru validarea melodiilor
/// O melodie este valida daca:
///	are titlu format din mai mult de 2 caractere
///	are artist format din mai mult de 2 caractere
///	durata melodiei este intre 1 si 15;
///	formatul in care se da durata este MM.SS, numarul de secunde nu trece de 59
class MedicamentValidator {
public:
	void valideaza(const Medicament& m) {
		vector<string> errors;
		if (m.getNume().length() < 2) {
			string s1 = "Numele trebuie sa aiba cel putin 2 caractere.";
			errors.push_back(s1);
		}
		if (m.getProducator().length() < 2) {
			string s2 = "Producatorul trebuie sa aiba cel putin 2 caractere.";
			errors.push_back(s2);
		}
		if (m.getPret() <= 0) {
			string s3 = "Pretul trebuie sa fie pozitiv.";
			errors.push_back(s3);
		}
		if (errors.size() > 0)
			throw ValidationException(errors);
	}

	void valideazaNumeSiProd(string nume, string producator) {
		vector<string> errors;
		if (nume.length() < 2) {
			string s1 = "Numele trebuie sa aiba cel putin 2 caractere.";
			errors.push_back(s1);
		}
		if (producator.length() < 2) {
			string s2 = "Producatorul trebuie sa aiba cel putin 2 caractere.";
			errors.push_back(s2);
		}
		if (errors.size() > 0)
			throw ValidationException(errors);
	}
};


class FileValidator {
public:
	static int valideaza(string nameOfFile) {
		vector<string> errors;

		int length = static_cast<int>(nameOfFile.size());
		int result = 0;

		if (length <= 4)
			errors.push_back("Numele fisierului este prea mic.");
		else {
			string str1 = ".csv";
			string str2 = ".html";
			bool isCSVFile = true, isHTMLFile = true;

			size_t index_str;
			if ((index_str = nameOfFile.find(str1, 0)) != string::npos) {
				//csv
				if (static_cast<int>(index_str) + 1 != length - 3)
					isCSVFile = false;
				else
					isHTMLFile = false;
			}
			else
				isCSVFile = false;

			if (isCSVFile == false && (index_str = nameOfFile.find(str2, 0)) != string::npos) {
				//html
				if (static_cast<int>(index_str) + 1 != length - 4)
					isHTMLFile = false;
			}
			else
				isHTMLFile = false;

			if (!isHTMLFile && !isCSVFile)
				errors.push_back("Numele fisierului nu are extensia CSV sau HTML.");
			else if (isCSVFile)
				//It's a CSV file
				result = 1;
			else if (isHTMLFile)
				//It's an HTLM file
				result = 2;
		}

		if (errors.size() > 0)
			throw ValidationException(errors);
		return result;
	}
};