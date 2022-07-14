#pragma once

#include <iostream>
#include <string>
#include <fstream>

#include "../bodoveVyhladavanie/bodove_vyhladavanie.h"
#include "../filter/filtrovanie.h"

using namespace bodoveVyhladavanie;
using namespace filter;

namespace userInterface {
	class UserInterface {
	public:
		UserInterface(Slovensko* slovensko);
		~UserInterface();
		void uvod();
		void mainMenu();


	private:
		Slovensko* slovensko_;
		BodoveVyhladavanie* bodoveVyhladavanie_;
	};

	inline UserInterface::UserInterface(Slovensko* slovensko) {
		slovensko_ = slovensko;
		bodoveVyhladavanie_ = new BodoveVyhladavanie(slovensko);
	}

	inline UserInterface::~UserInterface() {
		delete bodoveVyhladavanie_;
	}

	inline void UserInterface::uvod() {
		cout << "****************************************************************************************" << endl;
		cout << endl;
		cout << "Vitaj v aplikacii na spracovanie udajov zo scitania obyvatelov domov a bytov z roku 2021" << endl;
		cout << endl;
		cout << "****************************************************************************************" << endl;
		cout << "Stlac znak pre pokracovanie: ";

		string input;
		cin >> input;

		system("CLS");

		cout << "****************************************************************************************" << endl;
		cout << endl;
		cout << "UPOZORNENIE:" << endl;
		cout << "Pri praci s aplikaciou nezadavaj znaky, ktore obsahuju diakritiku. Sposobi to nekorektne spravanie aplikacie!" << endl;
		cout << endl;
		cout << "****************************************************************************************" << endl;
		cout << "Stlac znak pre pokracovanie: ";

		cin >> input;

		system("CLS");

		cout << "****************************************************************************************" << endl;
		cout << endl;
		cout << "Informacia:" << endl;
		cout << "Aplikacia ma nastavene ako predvolene uzemne jednotky pre filtrovanie obce." << endl;
		cout << "Pre pracu s inymi uzemnymi jednotkami aplikuj prislusny filter." << endl;
		cout << endl;
		cout << "****************************************************************************************" << endl;
		cout << "Stlac znak pre pokracovanie: ";

		cin >> input;
		
		
		mainMenu();
	}



	void UserInterface::mainMenu() {
		system("CLS");
		cout << "**************************************************" << endl;
		cout << "Zvol si operaciu: " << endl;
		cout << "1: Bodove vyhladavanie" << endl;
		cout << "2: Filtrovanie" << endl;
		cout << "0: ukoncenie aplikacie" << endl;
		string input;
		cin >> input;

		bool kontrola = bodoveVyhladavanie_->skontrolujVstup(input);

		if (kontrola) {
			int moznost = stoi(input);

			if (moznost == 1) {
				bodoveVyhladavanie_->menuPreSlovensko();
				mainMenu();
			}
			else if (moznost == 2) {
				Slovensko* copySlovensko = new Slovensko(*slovensko_);
				Filtrovanie* filtrovanie = new Filtrovanie(copySlovensko);
				filtrovanie->zacniFiltraciu();
				delete filtrovanie;
				mainMenu();
			}
			else if (moznost == 0) {
				return;
			}
			else {
				bodoveVyhladavanie_->upozernenieUzivatela();
				mainMenu();
			}
		}
		else {
			bodoveVyhladavanie_->upozernenieUzivatela();
			mainMenu();
		}
	}

	
}
