#pragma once

#include <iostream>
#include <string>
#include <fstream>

#include "../uzemneJednotky/slovensko.h"
#include "../uzemneJednotky/kraj.h"
#include "../structures/list/array_list.h"
#include "../filter/iFilter.h"

using namespace uzemneJednotky;
using namespace std;

namespace filter {
	class VekovaSkupinaPodiel : public IFIlter {
	public:
		VekovaSkupinaPodiel(int dolnaHranicaVek, int hornaHranicaVek, double podielDolnaHranica, double podielHornaHranica);
		virtual Slovensko* vyfiltruj(Slovensko* filtrovanaMnozina, TypUzemnejJednotky* typUJ);
		virtual void vypisInfoOFiltri();

	private:
		int dolnaHranicaVek_;
		int hornaHranicaVek_;
		double podieDolnaHranica_;
		double podielHornaHranica_;

	};

	inline VekovaSkupinaPodiel::VekovaSkupinaPodiel(int dolnaHranicaVek, int hornaHranicaVek, double podielDolnaHranica, double podielHornaHranica) {
		dolnaHranicaVek_ = dolnaHranicaVek;
		hornaHranicaVek_ = hornaHranicaVek;
		podieDolnaHranica_ = podielDolnaHranica;
		podielHornaHranica_ = podielHornaHranica;
	}

	inline Slovensko* VekovaSkupinaPodiel::vyfiltruj(Slovensko* filtrovanaMnozina, TypUzemnejJednotky* typUJ) {
		SortedSequenceTable<string, Kraj*>* krajeSlovenska = filtrovanaMnozina->getKraje();
		//ArrayList<string*>* krajeKluceRemovnutych = new ArrayList<string*>();

		int typJednotky = typUJ->getTyp();

		for (auto kraj : *krajeSlovenska) {
			Kraj* aktualnyKraj = kraj->accessData();


			if (typJednotky == 1) {
				Array<int>* vekovaSkupinaKraj = aktualnyKraj->getPodielVekovychSkupin();

				double pocetObyvatelovKraj = 0.0;
				double celkovyPocetObyvatelovOKraju = aktualnyKraj->getPocetObyvatelov();

				for (int i = 0; i < 101; i++) {
					if (i >= dolnaHranicaVek_ && i <= hornaHranicaVek_) {
						pocetObyvatelovKraj += (double)vekovaSkupinaKraj->at(i);
					}
				}

				for (int i = 101; i < 202; i++) {
					int helpIndex = i - 101;

					if (helpIndex >= dolnaHranicaVek_ && helpIndex <= hornaHranicaVek_) {
						pocetObyvatelovKraj += (double)vekovaSkupinaKraj->at(i);
					}
				}

				double podielSkupiny = pocetObyvatelovKraj / celkovyPocetObyvatelovOKraju * 100;

				if (!(podielSkupiny >= podieDolnaHranica_ && podielSkupiny <= podielHornaHranica_)) {
					//krajeKluceRemovnutych->add(new string(kraj->getKey()));
					aktualnyKraj->makeUnvalid();
				}
				else {
					aktualnyKraj->setKriteriumVekovaSkupinaPodiel(podielSkupiny);
				}
			}
			else {
				SortedSequenceTable<int, Okres*>* okresyAktualnehoKraja = aktualnyKraj->dajOkresy();
				//ArrayList<int>* okresyKluceRemovnutych = new ArrayList<int>();

				for (auto okres : *okresyAktualnehoKraja) {

					Okres* aktualnyOkres = okres->accessData();

					if (typJednotky == 2) {

						Array<int>* vekovaSkupinaOkres = aktualnyOkres->getPodielVekovychSkupin();

						double pocetObyvatelovOkres = 0.0;
						double celkovyPocetObyvatelovOkresu = aktualnyOkres->getPocetObyvatelov();

						for (int i = 0; i < 101; i++) {
							if (i >= dolnaHranicaVek_ && i <= hornaHranicaVek_) {
								pocetObyvatelovOkres += (double)vekovaSkupinaOkres->at(i);
							}
						}

						for (int i = 101; i < 202; i++) {
							int helpIndex = i - 101;

							if (helpIndex >= dolnaHranicaVek_ && helpIndex <= hornaHranicaVek_) {
								pocetObyvatelovOkres += (double)vekovaSkupinaOkres->at(i);
							}
						}

						double podielSkupiny = pocetObyvatelovOkres / celkovyPocetObyvatelovOkresu * 100;

						if (!(podielSkupiny >= podieDolnaHranica_ && podielSkupiny <= podielHornaHranica_)) {
							//okresyKluceRemovnutych->add(okres->getKey());
							aktualnyOkres->makeUnvalid();
						}
						else {
							aktualnyOkres->setKriteriumVekovaSkupinaPodiel(podielSkupiny);
						}
					}
					else {
						SortedSequenceTable<string, Obec*>* obceAktualnehoOkresu = aktualnyOkres->dajObce();

						//ArrayList<string*>* kluceRemovnutych = new ArrayList<string*>();

						for (auto obec : *obceAktualnehoOkresu) {

							Obec* aktualnaObec = obec->accessData();

							Array<int>* vekovaSkupina = aktualnaObec->getVekoveSkupiny();

							double pocetObyvatelovVekovejSkupiny = 0.0;
							double celkovyPocetObyvatelovObce = (double)aktualnaObec->getPocetObyvatelov();



							for (int i = 0; i < 101; i++) {
								if (i >= dolnaHranicaVek_ && i <= hornaHranicaVek_) {
									pocetObyvatelovVekovejSkupiny += (double)vekovaSkupina->at(i);
								}
							}

							for (int i = 101; i < 202; i++) {
								int helpIndex = i - 101;

								if (helpIndex >= dolnaHranicaVek_ && helpIndex <= hornaHranicaVek_) {
									pocetObyvatelovVekovejSkupiny += (double)vekovaSkupina->at(i);
								}
							}

							double podielSkupiny = pocetObyvatelovVekovejSkupiny / celkovyPocetObyvatelovObce * 100;

							if (!(podielSkupiny >= podieDolnaHranica_ && podielSkupiny <= podielHornaHranica_)) {
								//kluceRemovnutych->add(new string(obec->getKey()));
								aktualnaObec->makeUnvalid();
							}
							else {
								aktualnaObec->setKriteriumVekovaSkupinaPodiel(podielSkupiny);
							}

						}

						
					}

				}
				
				

			}
		}


		return filtrovanaMnozina;
	}

	inline void VekovaSkupinaPodiel::vypisInfoOFiltri() {
		cout << "-------------------------------------------------------" << endl;
		cout << "Nazov: podiel vekovej skupiny" << endl;
		cout << "Kriterium: " << dolnaHranicaVek_ << " - " << hornaHranicaVek_ << " rokov" << endl;
		cout << "Kriterium: " << podieDolnaHranica_ << "% - " << podielHornaHranica_ << "% obyvatelov" << endl;

		
	}
}
