#pragma once
#include <iostream>
#include <string>
#include <fstream>

#include "../uzemneJednotky/slovensko.h"
#include "../uzemneJednotky/kraj.h"
#include "../structures/list/array_list.h"
#include "iFilter.h"
#include "vzdelanie_pocet.h"
#include "vzdelanie_podiel.h"
#include "EVS_pocet.h"
#include "EVS_podiel.h"
#include "vekovaSkupina_pocet.h"
#include "vekovaSkupina_podiel.h"
#include "typUzemnejJednotky.h"
#include "prislusnost.h"
#include "../triedenie/triedenie_nazov.h"
#include "../triedenie/triedenie_cislo.h"

using namespace structures;
using namespace uzemneJednotky;
using namespace std;
using namespace triedenie;


namespace filter {
	class Filtrovanie  {
	public:
		Filtrovanie(Slovensko* slovensko);
		~Filtrovanie();
		void zacniFiltraciu();
		bool skontrolujVstup(string vstup);
		void upozernenieUzivatela();
		void ukoncenieFiltracie();
		void pridajFilter();
		void vytvorFilterVzdelaniePocet();
		void vytvorFilterVzdelaniePodiel();
		void vytvorFilterEVSPocet();
		void vytvorFilterEVSPodiel();
		void vytvorFilterVekovaSkupinaPocet();
		void vytvorFilterVekovaSkupinaPodiel();
		void vytvorFilterTypUzemnejJednotky();
		void vytvorFilterPrePrislusnost();
		void ponukniEVSSkupiny();
		void ponukniVzdelaneSkupiny();
		void aplikujZvoleneFiltre();
		void vypisVyfiltrovanuMnozinu();
		void vypisAplikovaneFiltre();
		void ponukniTriedenie();
		void vytvorTriedeniePodlaNazvu();
		void vytvorTriedeniePodlaCisla(int kriterium);

	private:
		Slovensko* slovensko_;
		ArrayList<IFIlter*>* zvoleneFiltre_;
		Array<bool>* aplikovaneFiltre_;
		TypUzemnejJednotky* typUJ_;
		Prislusnost* prislusnost_;
		TriedenieNazov* triedenieNazov_;
		TriedenieCislo* triedenieCislo_;
		
		bool vzdelaniePocet_;
		bool vzdelaniePodiel_;
		bool vekovaSkupinaPocet_;
		bool vekovaSkupinaPodiel_;
		
	};

	inline Filtrovanie::Filtrovanie(Slovensko* slovensko) {
		slovensko_ = slovensko;
		zvoleneFiltre_ = new ArrayList<IFIlter*>();
		aplikovaneFiltre_ = new Array<bool>(9);
		typUJ_ = new TypUzemnejJednotky(0);

		for (int i = 0; i < aplikovaneFiltre_->size(); i++) {
			aplikovaneFiltre_->at(i) = false;
		}

		prislusnost_ = new Prislusnost();

		triedenieNazov_ = nullptr;
		triedenieCislo_ = nullptr;

		vzdelaniePocet_ = false;
		vzdelaniePodiel_ = false;
		vekovaSkupinaPocet_ = false;
		vekovaSkupinaPodiel_ = false;
	}

	inline Filtrovanie::~Filtrovanie() {
		delete slovensko_;
		for (auto item : *zvoleneFiltre_) {
			delete item;
		}

		delete zvoleneFiltre_;
		delete aplikovaneFiltre_;

		
		delete typUJ_;
		delete prislusnost_;

		if (triedenieNazov_ != nullptr) {
			delete triedenieNazov_;
		}

		if (triedenieCislo_ != nullptr) {
			delete triedenieCislo_;
		}
	}



	inline void Filtrovanie::zacniFiltraciu() {
		system("CLS");
		cout << "*********************************" << endl;
		cout << "----- Menu filtracie -----" << endl;
		cout << "Zadaj pocet filtrov, ktore chces aplikovat." << endl;
		string input;
		cin >> input;

		bool kontrola = skontrolujVstup(input);

		if (kontrola) {
			int moznost = stoi(input);
			if (moznost == 0) {
				ukoncenieFiltracie();
			}
			else {
				if (moznost > 8) {
					cout << "Zadany neplatny pocet filtrov!" << endl;
					zacniFiltraciu();
				}
				else {
					for (int i = 0; i < moznost; i++) {
						pridajFilter();
					}
					aplikujZvoleneFiltre();
					ponukniTriedenie();
					vypisVyfiltrovanuMnozinu();
				}
			}
		}
		else {
			upozernenieUzivatela();
			zacniFiltraciu();
		}


		
	}

	inline void Filtrovanie::pridajFilter() {
		system("CLS");
		cout << "*********************************" << endl;
		cout << "----- Menu pre pridanie filtra -----" << endl;
		cout << "Zvol filter, ktory chces aplikovat:" << endl;
		if (!aplikovaneFiltre_->at(1)) {
			cout << "1: filter pre pocet vzdelania" << endl;
		}
		if (!aplikovaneFiltre_->at(2)) {
			cout << "2: filter pre podiel vzdelania" << endl;
		}

		if (!aplikovaneFiltre_->at(3)) {
			cout << "3: filter pre pocet EVS" << endl;
		}

		if (!aplikovaneFiltre_->at(4)) {
			cout << "4: filter pre podiel EVS" << endl;
		}

		if (!aplikovaneFiltre_->at(5)) {
			cout << "5: filter pre pocet vekovej skupiny" << endl;
		}

		if (!aplikovaneFiltre_->at(6)) {
			cout << "6: filter pre podiel vekovej skupiny" << endl;
		}

		if (!aplikovaneFiltre_->at(7)) {
			cout << "7: filter pre uzemnu jednotku" << endl;
		}

		if (!aplikovaneFiltre_->at(8)) {
			cout << "8: filter pre prislusnost k uzemnej jednotke" << endl;
		}

		string input;
		cin >> input;

		bool kontrola = skontrolujVstup(input);

		if (kontrola) {
			int moznost = stoi(input);

			if (moznost > 0 && moznost < 9) {
				if (!aplikovaneFiltre_->at(moznost)) {
					switch (moznost) {
					case 1:
						vytvorFilterVzdelaniePocet();
						break;
					case 2:
						vytvorFilterVzdelaniePodiel();
						break;
					case 3:
						vytvorFilterEVSPocet();
						break;
					case 4:
						vytvorFilterEVSPodiel();
						break;
					case 5:
						vytvorFilterVekovaSkupinaPocet();
						break;
					case 6:
						vytvorFilterVekovaSkupinaPodiel();
						break;
					case 7:
						vytvorFilterTypUzemnejJednotky();
						break;
					case 8:
						vytvorFilterPrePrislusnost();
						break;

					default:
						upozernenieUzivatela();
						pridajFilter();
						break;
					}

					aplikovaneFiltre_->at(moznost) = true;
				}
				else {
					upozernenieUzivatela();
					pridajFilter();
				}
			}
			else {
				upozernenieUzivatela();
				pridajFilter();
			}
			
		}
		else {
			upozernenieUzivatela();
			pridajFilter();
		}


	}

	inline void Filtrovanie::vytvorFilterVzdelaniePocet()
	{
		system("CLS");
		cout << "*********************************" << endl;
		cout << "----- Tvorba filtru pre pocet vzdelania -----" << endl;
		cout << "Vyber skupinu, ktoru chces filtrovat: " << endl;
		ponukniVzdelaneSkupiny();
		string input;
		cin >> input;

		bool kontrola = skontrolujVstup(input);

		if (kontrola) {
			int skupina = stoi(input);

			if (skupina > 0 && skupina < 9) {
				cout << "Zvol minimalny pocet obyvatelov pre skupinu: " << endl;
				cin >> input;

				if (skontrolujVstup(input)) {
					int dolnaHranica = stoi(input);
					cout << "Zvol maximalny pocet obyvatelov pre skupinu: " << endl;
					cin >> input;

					if (skontrolujVstup(input)) {
						int hornaHranica = stoi(input);

						IFIlter* novyFilter = new VzdelaniePocet(dolnaHranica, hornaHranica, skupina - 1);
						zvoleneFiltre_->add(novyFilter);
						vzdelaniePocet_ = true;
					}
					else {
						upozernenieUzivatela();
						vytvorFilterVzdelaniePocet();
					}
				}
				else {
					upozernenieUzivatela();
					vytvorFilterVzdelaniePocet();
				}

			}
			else {
				upozernenieUzivatela();
				vytvorFilterVzdelaniePocet();
			}
		}
		else {
			upozernenieUzivatela();
			vytvorFilterVzdelaniePocet();
		}
		
	}

	inline void Filtrovanie::vytvorFilterVzdelaniePodiel()
	{
		system("CLS");
		cout << "*********************************" << endl;
		cout << "----- Tvorba filtru pre podiel vzdelania -----" << endl;
		cout << "Vyber skupinu, ktoru chces filtrovat: " << endl;
		ponukniVzdelaneSkupiny();

		string input;
		cin >> input;

		bool kontrola = skontrolujVstup(input);

		if (kontrola) {
			int skupina = stoi(input);

			if (skupina > 0 && skupina < 9) {
				cout << "Zvol dolnu hranicu obyvatelov(%) pre skupinu: " << endl;
				cin >> input;

				if (skontrolujVstup(input)) {
					double podielDolnaHranica = (double)stoi(input);
					
					cout << "Zvol hornu hranicu(%) obyvatelov pre skupinu: " << endl;
					cin >> input;

					if (skontrolujVstup(input)) {

						double podielHornaHranica = (double)stoi(input);
						
						IFIlter* novyFilter = new VzdelaniePodiel(podielDolnaHranica, podielHornaHranica, skupina - 1);
						zvoleneFiltre_->add(novyFilter);
						vzdelaniePodiel_ = true;
					}
					else {
						upozernenieUzivatela();
						vytvorFilterVzdelaniePodiel();
					}
				}
				else {
					upozernenieUzivatela();
					vytvorFilterVzdelaniePodiel();
				}

			}
			else {
				upozernenieUzivatela();
				vytvorFilterVzdelaniePodiel();
			}
		}
		else {
			upozernenieUzivatela();
			vytvorFilterVzdelaniePodiel();
		}
	}

	inline void Filtrovanie::vytvorFilterEVSPocet()
	{
		system("CLS");
		cout << "*********************************" << endl;
		cout << "----- Tvorba filtru pre pocet EVS -----" << endl;
		cout << "Vyber skupinu, ktoru chces filtrovat: " << endl;
		ponukniEVSSkupiny();
		string input;
		cin >> input;

		bool kontrola = skontrolujVstup(input);

		if (kontrola) {
			int skupina = stoi(input);

			if (skupina > 0 && skupina < 4) {
				cout << "Zvol minimalny pocet obyvatelov pre skupinu: " << endl;
				cin >> input;

				if (skontrolujVstup(input)) {
					int dolnaHranica = stoi(input);
					cout << "Zvol maximalny pocet obyvatelov pre skupinu: " << endl;
					cin >> input;

					if (skontrolujVstup(input)) {
						int hornaHranica = stoi(input);

						IFIlter* novyFilter = new EVSPocet(dolnaHranica, hornaHranica, skupina - 1);
						zvoleneFiltre_->add(novyFilter);



					}
					else {
						upozernenieUzivatela();
						vytvorFilterEVSPocet();
					}
				}
				else {
					upozernenieUzivatela();
					vytvorFilterEVSPocet();
				}

			}
			else {
				upozernenieUzivatela();
				vytvorFilterEVSPocet();
			}
		}
		else {
			upozernenieUzivatela();
			vytvorFilterEVSPocet();
		}
	}

	inline void Filtrovanie::vytvorFilterEVSPodiel()
	{
		system("CLS");
		cout << "*********************************" << endl;
		cout << "----- Tvorba filtru pre podiel EVS -----" << endl;
		cout << "Vyber skupinu, ktoru chces filtrovat: " << endl;
		ponukniEVSSkupiny();

		string input;
		cin >> input;

		bool kontrola = skontrolujVstup(input);

		if (kontrola) {
			int skupina = stoi(input);

			if (skupina > 0 && skupina < 4) {
				cout << "Zvol dolnu hranicu obyvatelov(%) pre skupinu: " << endl;
				cin >> input;

				if (skontrolujVstup(input)) {
					double podielDolnaHranica = (double)stoi(input);
					cout << "Zvol hornu hranicu obyvatelov(%) pre skupinu: " << endl;
					cin >> input;

					if (skontrolujVstup(input)) {

						double podielHornaHranica = (double)stoi(input);

						IFIlter* novyFilter = new EVSPodiel(podielDolnaHranica, podielHornaHranica, skupina - 1);
						zvoleneFiltre_->add(novyFilter);
						
					}
					else {
						upozernenieUzivatela();
						vytvorFilterEVSPodiel();
					}
				}
				else {
					upozernenieUzivatela();
					vytvorFilterEVSPodiel();
				}

			}
			else {
				upozernenieUzivatela();
				vytvorFilterEVSPodiel();
			}
		}
		else {
			upozernenieUzivatela();
			vytvorFilterEVSPodiel();
		}
	}

	inline void Filtrovanie::vytvorFilterVekovaSkupinaPocet()
	{
		system("CLS");
		cout << "*********************************" << endl;
		cout << "----- Tvorba filtru pre pocet vekovej skupiny -----" << endl;
		cout << "Zadaj dolnu hranicu pre vek: " << endl;

		string input;
		cin >> input;

		if (skontrolujVstup(input)) {
			int dolnaHranicaVek = stoi(input);

			cout << "Zadaj hornu hranicu pre vek: " << endl;
			cin >> input;

			if (skontrolujVstup(input)) {
				int hornaHranicaVek = stoi(input);

				cout << "Zadaj dolnu hranicu pre pocet obyvatelov vekovej skupiny: " << endl;
				cin >> input;

				if (skontrolujVstup(input)) {
					int dolnaHranicaPocetObyvatelov = stoi(input);

					cout << "Zadaj hornu hranicu pre pocet obyvatelov vekovej skupiny: " << endl;
					cin >> input;

					if (skontrolujVstup(input)) {
						int hornaHranicaPocetObyvatelov = stoi(input);

						IFIlter* novyFilter = new VekovaSkupinaPocet(dolnaHranicaPocetObyvatelov, hornaHranicaPocetObyvatelov, dolnaHranicaVek, hornaHranicaVek);
						zvoleneFiltre_->add(novyFilter);
						vekovaSkupinaPocet_ = true;
					}
					else {
						upozernenieUzivatela();
						vytvorFilterVekovaSkupinaPocet();
					}
				}
				else {
					upozernenieUzivatela();
					vytvorFilterVekovaSkupinaPocet();
				}
			}
			else {
				upozernenieUzivatela();
				vytvorFilterVekovaSkupinaPocet();
			}
		}
		else {
			upozernenieUzivatela();
			vytvorFilterVekovaSkupinaPocet();
		}


	}

	inline void Filtrovanie::vytvorFilterVekovaSkupinaPodiel()
	{
		system("CLS");
		cout << "*********************************" << endl;
		cout << "----- Tvorba filtru pre podiel vekovej skupiny -----" << endl;
		cout << "Zadaj dolnu hranicu pre vek: " << endl;

		string input;
		cin >> input;

		if (skontrolujVstup(input)) {
			int dolnaHranicaVek = stoi(input);

			cout << "Zadaj hornu hranicu pre vek: " << endl;
			cin >> input;

			if (skontrolujVstup(input)) {
				int hornaHranicaVek = stoi(input);

				cout << "Zvol dolnu hranicu obyvatelov(%) pre skupinu: " << endl;
				cin >> input;

				if (skontrolujVstup(input)) {
					double podielVekovejDolnaHranica = (double)stoi(input);

					cout << "Zvol hornu hranicu obyvatelov(%) pre skupinu: " << endl;

					cin >> input;

					if (skontrolujVstup(input)) {
						double podielVekovejHornaHranica = (double)stoi(input);

						IFIlter* novyFilter = new VekovaSkupinaPodiel(dolnaHranicaVek, hornaHranicaVek, podielVekovejDolnaHranica, podielVekovejHornaHranica);
						zvoleneFiltre_->add(novyFilter);
						vekovaSkupinaPodiel_ = true;
						
					}
					else {
						upozernenieUzivatela();
						vytvorFilterVekovaSkupinaPodiel();
					}
				}
				else {
					upozernenieUzivatela();
					vytvorFilterVekovaSkupinaPodiel();
				}
			}
			else {
				upozernenieUzivatela();
				vytvorFilterVekovaSkupinaPodiel();
			}
		}
		else {
			upozernenieUzivatela();
			vytvorFilterVekovaSkupinaPodiel();
		}
	}

	inline void Filtrovanie::vytvorFilterTypUzemnejJednotky()
	{
		system("CLS");
		cout << "*********************************" << endl;
		cout << "----- Tvorba filtru pre typ uzemnej jednotky -----" << endl;
		cout << "1: kraje" << endl;
		cout << "2: okresy" << endl;
		cout << "3: obce" << endl;

		string input;
		cin >> input;

		if (skontrolujVstup(input)) {
			int moznost = stoi(input);

			if (moznost > 0 && moznost < 4) {
				typUJ_->setTyp(moznost);
			}
			else {
				upozernenieUzivatela();
				vytvorFilterTypUzemnejJednotky();
			}
		}
		else {
			upozernenieUzivatela();
			vytvorFilterTypUzemnejJednotky();
		}
	}

	inline void Filtrovanie::vytvorFilterPrePrislusnost()
	{
		system("CLS");
		int zvolenyTypUJ = typUJ_->getTyp();
		if (zvolenyTypUJ == 1) {
			cout << "Nemozno aplikovat filter pre prislusnost, filtruje sa mnozina krajov";
		}
		else {
			cout << "*********************************" << endl;
			cout << "----- Tvorba filtru pre prislusnot uzemnej jednotky -----" << endl;
			cout << "1: zvol kraj" << endl;
			cout << "2: zvol okres" << endl;

			string input;
			cin >> input;

			if (skontrolujVstup(input)) {
				int moznost = stoi(input);

				bool korektne = false;
				bool ponukniPrislusnostKraju = false;
				bool ponukniPrislusnostOkresu = false;

				if (moznost == 1) {
					ponukniPrislusnostKraju = true;
					korektne = true;
				}
				else if (moznost == 2) {
					ponukniPrislusnostOkresu = true;
					korektne = true;
				}
				else {
					upozernenieUzivatela();
					vytvorFilterPrePrislusnost();
				}

				if (korektne) {
					ArrayList<string*>* ponukyPrislusnosti = new ArrayList<string*>();
					

					if (ponukniPrislusnostKraju) {
						delete ponukyPrislusnosti;
						ponukyPrislusnosti = prislusnost_->ponukniPrislusnostKraju(slovensko_);
					}
					else if (ponukniPrislusnostOkresu) {
						delete ponukyPrislusnosti;
						ponukyPrislusnosti = prislusnost_->ponukniPrislusnostOkresu(slovensko_);
					}

					cout << "Zvol prisusnost: " << endl;
					cin >> input;

					if (skontrolujVstup(input)) {
						int moznost = stoi(input) - 1;

						if (moznost > -1 && moznost < ponukyPrislusnosti->size()) {
							string zvolenaPrislusnost = *ponukyPrislusnosti->at(moznost);
							prislusnost_->setPrislusnost(zvolenaPrislusnost);
						}
						else {
							upozernenieUzivatela();
							vytvorFilterPrePrislusnost();
						}
					}
					else {
						upozernenieUzivatela();
						vytvorFilterPrePrislusnost();
					}

					for (int i = 0; i < ponukyPrislusnosti->size(); i++) {
						delete ponukyPrislusnosti->at(i);
					}

					delete ponukyPrislusnosti;
				}

				
			}
			else {
				upozernenieUzivatela();
				vytvorFilterPrePrislusnost();
			}
		}
	}

	inline void Filtrovanie::ponukniEVSSkupiny()
	{
		cout << "1: predproduktivny vek" << endl;
		cout << "2: produktivny vek" << endl;
		cout << "3: poproduktivny vek" << endl;
	}

	inline void Filtrovanie::ponukniVzdelaneSkupiny()
	{
		cout << "1: bez ukonceneho vzdelania" << endl;
		cout << "2: zakladne vzdelanie" << endl;
		cout << "3: stredne odborne vzdelanie" << endl;
		cout << "4: uplne stredne vzdeanie" << endl;
		cout << "5: vyssie odborne vzdelanie" << endl;
		cout << "6: vysokoskolske vzdelanie" << endl;
		cout << "7: bez skolskeho vzdelania" << endl;
		cout << "8: nezistene" << endl;
	}

	inline void Filtrovanie::aplikujZvoleneFiltre()
	{
		for (int i = 0; i < zvoleneFiltre_->size(); i++) {
			IFIlter* aktualny = zvoleneFiltre_->at(i);
			slovensko_ = aktualny->vyfiltruj(slovensko_, typUJ_);
		}
	}

	inline void Filtrovanie::vypisVyfiltrovanuMnozinu()
	{
		system("CLS");
		cout << "*************************************************************" << endl;
		vypisAplikovaneFiltre();
		
		if (triedenieNazov_ == nullptr && triedenieCislo_ == nullptr) {
			cout << endl;
			cout << "Vyfiltrovane uzemne jednotky:" << endl;
		}
		SortedSequenceTable<string, Kraj*>* kraje = slovensko_->getKraje();

		int typ = typUJ_->getTyp();

		string zvolenaPrislusnost = prislusnost_->getPrislusnost();
		
		for (auto kraj : *kraje) {
			Kraj* aktualnyKraj = kraj->accessData();


			if (typ == 1) {
				
				if (triedenieNazov_ == nullptr && triedenieCislo_ == nullptr && aktualnyKraj->getValidation()) {
					cout << aktualnyKraj->vypisKriteria();
				}
				else if (triedenieNazov_ != nullptr && triedenieCislo_ == nullptr && aktualnyKraj->getValidation()){
					triedenieNazov_->pridajUJ(aktualnyKraj);
				}
				else if (triedenieNazov_ == nullptr && triedenieCislo_ != nullptr && aktualnyKraj->getValidation()) {
					triedenieCislo_->pridajUJ(aktualnyKraj);
				}
			}
			else {
				SortedSequenceTable<int, Okres*>* okresy = aktualnyKraj->dajOkresy();

				for (auto okres : *okresy) {
					Okres* aktualnyOkres = okres->accessData();


					if (typ == 2 && (zvolenaPrislusnost == "" || zvolenaPrislusnost == aktualnyKraj->getTitle())) {
						
						if (triedenieNazov_ == nullptr && triedenieCislo_ == nullptr && aktualnyOkres->getValidation()) {
							cout << aktualnyOkres->vypisKriteria();
						}
						else if (triedenieNazov_ != nullptr && triedenieCislo_ == nullptr && aktualnyOkres->getValidation()){
							triedenieNazov_->pridajUJ(aktualnyOkres);
						}
						else if (triedenieNazov_ == nullptr && triedenieCislo_ != nullptr && aktualnyOkres->getValidation()){
							triedenieCislo_->pridajUJ(aktualnyOkres);
						}
					}
					else {
						SortedSequenceTable<string, Obec*>* obce = aktualnyOkres->dajObce();

						if (zvolenaPrislusnost == "" || zvolenaPrislusnost == aktualnyKraj->getTitle() || zvolenaPrislusnost == aktualnyOkres->getTitle()) {
							for (auto obec : *obce) {

								Obec* aktualnaObec = obec->accessData();
								

								if (triedenieNazov_ == nullptr && triedenieCislo_ == nullptr && aktualnaObec->getValidation()) {
									cout << aktualnaObec->vypisKriteria();
								}
								else if (triedenieNazov_ != nullptr && triedenieCislo_ == nullptr && aktualnaObec->getValidation()){
									triedenieNazov_->pridajUJ(aktualnaObec);
								}
								else if (triedenieNazov_ == nullptr && triedenieCislo_ != nullptr && aktualnaObec->getValidation()) {
									triedenieCislo_->pridajUJ(aktualnaObec);
								}
							}
						}

					}
				}
				
			}
			
		}

		if (triedenieNazov_ != nullptr) {
			if (triedenieNazov_->getPocetTriedenych() != 0) {
				triedenieNazov_->QuickSort(0, triedenieNazov_->getPocetTriedenych() - 1);
				triedenieNazov_->vypisInfo();
			}
			cout << endl;
			cout << "Vyfiltrovane uzemne jednotky:" << endl;
			if (triedenieNazov_->getPocetTriedenych() != 0) {
				cout << triedenieNazov_->getUtriedeneUJ();
			}
		}
		else if (triedenieCislo_ != nullptr) {
			if (triedenieCislo_->getPocetTriedenych() != 0) {
				triedenieCislo_->QuickSort(0, triedenieCislo_->getPocetTriedenych() - 1);
				triedenieCislo_->vypisInfo();
			}
			cout << endl;
			if (triedenieCislo_->getPocetTriedenych() != 0) {
				cout << "Vyfiltrovane uzemne jednotky:" << endl;
				cout << triedenieCislo_->getUtriedeneUJ();
			}
		}
		cout << "*************************************************************" << endl;

		cout << "Stlac znak pre pokracovanie" << endl;

		string input;
		cin >> input;
	}

	inline void Filtrovanie::vypisAplikovaneFiltre()
	{
		cout << "Aplikovane filtre: " << endl;
		int typ = typUJ_->getTyp();
		cout << "-------------------------------------------------------" << endl;
		cout << "Nazov: typ uzemnej jednotky" << endl;
		cout << "Kriterium: ";
		if (typ == 1) {
			cout << "kraje";
		}
		else if (typ == 2) {
			cout << "okresy";
		}
		else {
			cout << "obce";
		}

		cout << endl;


		if (prislusnost_->getPrislusnost() != "") {
			cout << "-------------------------------------------------------" << endl;
			cout << "Nazov: prislusnost uzemnej jednotke" << endl;
			cout << "Kriterium: " << prislusnost_->getPrislusnost() << endl;
		}

		for (int i = 0; i < zvoleneFiltre_->size(); i++) {
			IFIlter* aktualny = zvoleneFiltre_->at(i);
			aktualny->vypisInfoOFiltri();
		}
	}

	inline void Filtrovanie::ponukniTriedenie()
	{
		system("CLS");
		cout << "-------------------------------------------------------" << endl;
		cout << "Zvol si triedenie podla kriteria: " << endl;
		cout << "0: ziadne triedenie" << endl;
		cout << "1: triedenie podla nazvu UJ" << endl;
		if (vzdelaniePocet_) {
			cout << "2: triedenie podla poctu vzdelanej skupiny" << endl;
		}

		if (vzdelaniePodiel_) {
			cout << "3: triedenie podla podielu vzdelanej skupiny" << endl;
		}
		
		if (vekovaSkupinaPocet_) {
			cout << "4: triedenie podla poctu vekovej skupiny" << endl;
		}

		if (vekovaSkupinaPodiel_) {
			cout << "5: triedenie podla podielu vekovej skupiny" << endl;
		}


		string input;
		cin >> input;

		if (skontrolujVstup(input)) {
			int moznost = stoi(input);

			if (moznost == 0) {
				//do nothing
			}
			else if (moznost == 1) {
				vytvorTriedeniePodlaNazvu();
			}
			else if (moznost > 1 && moznost < 6) {
				bool korektne = false;
				if (moznost == 2) {
					if (vzdelaniePocet_) {
						korektne = true;
					}
				}
				else if (moznost == 3) {
					if (vzdelaniePodiel_) {
						korektne = true;
					}
				}
				else if (moznost == 4) {
					if (vekovaSkupinaPocet_) {
						korektne = true;
					}
				}
				else if (moznost == 5) {
					if (vekovaSkupinaPodiel_) {
						korektne = true;
					}
				}

				if (korektne) {
					vytvorTriedeniePodlaCisla(moznost - 1);
				}
				else {
					upozernenieUzivatela();
					ponukniTriedenie();
				}
			}
			else {
				upozernenieUzivatela();
				ponukniTriedenie();
			}
		}
		else {
			upozernenieUzivatela();
			ponukniTriedenie();
		}
	}

	inline void Filtrovanie::vytvorTriedeniePodlaNazvu()
	{
		system("CLS");
		cout << "-------------------------------------------------------" << endl;
		cout << "Zvol si smer triedenia podla nazvu: " << endl;
		cout << "1: vzostupne" << endl;
		cout << "2: zostupne" << endl;

		string input;
		cin >> input;

		if (skontrolujVstup(input)) {
			int moznost = stoi(input);

			if (moznost == 1 || moznost == 2) {
				int typ = typUJ_->getTyp();
				triedenieNazov_ = new TriedenieNazov(typ, moznost);
			}
			else {
				upozernenieUzivatela();
				vytvorTriedeniePodlaNazvu();
			}
		}
		else {
			upozernenieUzivatela();
			vytvorTriedeniePodlaNazvu();
		}
	}

	inline void Filtrovanie::vytvorTriedeniePodlaCisla(int kriterium) {
		system("CLS");
		cout << "-------------------------------------------------------" << endl;
		cout << "Zvol si smer triedenia podla ";

		if (kriterium == 1) {
			cout << "poctu vzdelanej skupiny: " << endl;
		}
		else if (kriterium == 2) {
			cout << "podielu vzdelanej skupiny" << endl;
		}
		else if (kriterium == 3) {
			cout << " poctu vekovej skupiny" << endl;
		}
		else {
			cout << " podielu vekovej skupiny" << endl;
		}

		cout << "1: vzostupne" << endl;
		cout << "2: zostupne" << endl;

		string input;
		cin >> input;

		if (skontrolujVstup(input)) {
			int moznost = stoi(input);

			if (moznost == 1 || moznost == 2) {
				int typ = typUJ_->getTyp();

				triedenieCislo_ = new TriedenieCislo(typ, moznost, kriterium);
			}
			else {
				upozernenieUzivatela();
				vytvorTriedeniePodlaCisla(kriterium);
			}

		}
		else {
			upozernenieUzivatela();
			vytvorTriedeniePodlaCisla(kriterium);
		}


	}

	inline void Filtrovanie::upozernenieUzivatela()
	{
		system("CLS");
		cout << "Zadany neplatny vstup!" << endl;
		cout << "Stlac znak pre pokracovanie." << endl;
		string input;
		cin >> input;
		system("CLS");
	}

	inline bool Filtrovanie::skontrolujVstup(string vstup)
	{
		for (int i = 0; i < vstup.length(); i++) {
			if (!isdigit(vstup.at(i))) {
				return false;
			}
		}

		return true;
	}

	inline void Filtrovanie::ukoncenieFiltracie() {
		system("CLS");
		cout << "Filtracia ukoncena" << endl;
		cout << "Stlac znak pre pokracovanie." << endl;
		string input;
		cin >> input;
		system("CLS");
	}
}
