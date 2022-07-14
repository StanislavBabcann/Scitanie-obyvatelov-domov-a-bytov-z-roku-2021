#pragma once

#include <iostream>
#include <string>

#include "../uzemneJednotky/slovensko.h"
#include "../uzemneJednotky/kraj.h"
#include "../structures/list/array_list.h"
#include "../filter/iFilter.h"

using namespace uzemneJednotky;
using namespace std;

namespace filter {
	class EVSPodiel : public IFIlter {
	public:
		EVSPodiel(double dolnaHranicaPodiel, double hornaHranicaPodiel, int typSkupiny);
		virtual Slovensko* vyfiltruj(Slovensko* filtrovanaMnozina, TypUzemnejJednotky* typUJ);
		virtual void vypisInfoOFiltri();

	private:
		int typSkupiny_;
		double podielDolnaHranica_;
		double podielHornaHranica_;
	};

	inline EVSPodiel::EVSPodiel(double dolnaHranicaPodiel, double hornaHranicaPodiel, int typSkupiny) {
		podielDolnaHranica_ = dolnaHranicaPodiel;
		podielHornaHranica_ = hornaHranicaPodiel;
		typSkupiny_ = typSkupiny;
		
	}

	inline Slovensko* EVSPodiel::vyfiltruj(Slovensko* filtrovanaMnozina, TypUzemnejJednotky* typUJ) {
		SortedSequenceTable<string, Kraj*>* krajeSlovenska = filtrovanaMnozina->getKraje();
		//ArrayList<string*>* krajeKluceRemovnutych = new ArrayList<string*>();

		int typJednotky = typUJ->getTyp();


		for (auto kraj : *krajeSlovenska) {
			Kraj* aktualnyKraj = kraj->accessData();

			if (typJednotky == 1) {
				Array<int>* EVSKraj = aktualnyKraj->getPodielEkonomickychSkupin();

				double pocetEVSKraj = (double)EVSKraj->at(typSkupiny_);

				double pocetObyvatelovKraja = (double)aktualnyKraj->getPocetObyvatelov();

				double podielSKupinyKraj = pocetEVSKraj / pocetObyvatelovKraja * 100;

				if (!(podielSKupinyKraj >= podielDolnaHranica_ && podielSKupinyKraj <= podielHornaHranica_)) {
					//krajeKluceRemovnutych->add(new string(kraj->getKey()));
					aktualnyKraj->makeUnvalid();
				}
				else {
					aktualnyKraj->setKriteriumEVSPodiel(podielSKupinyKraj);
				}
			}
			else {
				SortedSequenceTable<int, Okres*>* okresyAktualnehoKraja = aktualnyKraj->dajOkresy();
				//ArrayList<int>* okresyKluceRemovnutych = new ArrayList<int>();

				for (auto okres : *okresyAktualnehoKraja) {

					Okres* aktualnyOkres = okres->accessData();


					if (typJednotky == 2) {
						Array<int>* EVSOkres = aktualnyOkres->getPodielEkonomickychSkupin();

						double pocetEVSOkres = (double)EVSOkres->at(typSkupiny_);

						double pocetObyvatelovOkresu = (double)aktualnyOkres->getPocetObyvatelov();

						double podielSkupinyOkres = pocetEVSOkres / pocetObyvatelovOkresu * 100;

						if (!(podielSkupinyOkres >= podielDolnaHranica_ && podielSkupinyOkres <= podielHornaHranica_)) {
							//okresyKluceRemovnutych->add(okres->getKey());
							aktualnyOkres->makeUnvalid();
						}
						else {
							aktualnyOkres->setKriteriumEVSPodiel(podielSkupinyOkres);
						}
					}
					else {
						SortedSequenceTable<string, Obec*>* obceAktualnehoOkresu = aktualnyOkres->dajObce();

						//ArrayList<string*>* kluceRemovnutych = new ArrayList<string*>();

						for (auto obec : *obceAktualnehoOkresu) {

							Obec* aktualnaObec = obec->accessData();

							Array<int>* ekonomickaSkupina = aktualnaObec->getPodielEkonomickychSkupin();

							double pocetHladanejVzdelanejSkupiny = (double)ekonomickaSkupina->at(typSkupiny_);

							double pocetObyvatelov = (double)aktualnaObec->getPocetObyvatelov();

							double podielSkupiny = pocetHladanejVzdelanejSkupiny / pocetObyvatelov * 100;




							if (!(podielSkupiny >= podielDolnaHranica_ && podielSkupiny <= podielHornaHranica_)) {
								//kluceRemovnutych->add(new string(obec->getKey()));
								aktualnaObec->makeUnvalid();
							}
							else {
								aktualnaObec->setKriteriumEVSPodiel(podielSkupiny);
							}
						}

						

					}

				}

				

			}

		}


		return filtrovanaMnozina;

	}

	inline void EVSPodiel::vypisInfoOFiltri() {
		cout << "-------------------------------------------------------" << endl;
		cout << "Nazov: podiel ekonomickej vekovej skupiny" << endl;
		cout << "Kriterium: ";
		switch (typSkupiny_) {
		case 0:
			cout << "predproduktivna";
			break;
		case 1:
			cout << "produktivna";
			break;
		case 2:
			cout << "poproduktivna";
			break;
		}

		cout << endl;

		cout << "Kriterium: " << podielDolnaHranica_ << "% - " << podielHornaHranica_ << "% obyvatelov" << endl;

		
	}
}
