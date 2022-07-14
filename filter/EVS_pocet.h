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
	class EVSPocet : public IFIlter {
	public:
		EVSPocet(int dolnaHranica, int hornaHranica, int typSkupiny);
		virtual Slovensko* vyfiltruj(Slovensko* filtrovanaMnozina, TypUzemnejJednotky* typUJ);
		virtual void vypisInfoOFiltri();

	private:
		int dolnaHranica_;
		int hornaHranica_;
		int typSkupiny_;
	};

	inline EVSPocet::EVSPocet(int dolnaHranica, int hornaHranica, int typSkupiny) {
		dolnaHranica_ = dolnaHranica;
		hornaHranica_ = hornaHranica;
		typSkupiny_ = typSkupiny;
	}

	inline Slovensko* EVSPocet::vyfiltruj(Slovensko* filtrovanaMnozina, TypUzemnejJednotky* typUJ) {

		SortedSequenceTable<string, Kraj*>* krajeSlovenska = filtrovanaMnozina->getKraje();
		//ArrayList<string*>* krajeKluceRemovnutych = new ArrayList<string*>();

		int typJednotky = typUJ->getTyp();

		for (auto kraj : *krajeSlovenska) {
			Kraj* aktualnyKraj = kraj->accessData();


			if (typJednotky == 1) {
				Array<int>* EVSKraj = aktualnyKraj->getPodielEkonomickychSkupin();

				int zistovaneEVSKraj = EVSKraj->at(typSkupiny_);


				if (!(dolnaHranica_ <= zistovaneEVSKraj && zistovaneEVSKraj <= hornaHranica_)) {
					//krajeKluceRemovnutych->add(new string(kraj->getKey()));
					aktualnyKraj->makeUnvalid();

				}
				else {
					aktualnyKraj->setKriteriumEVSPocet(zistovaneEVSKraj);
				}

			} else {

				SortedSequenceTable<int, Okres*>* okresyAktualnehoKraja = aktualnyKraj->dajOkresy();
				//ArrayList<int>* okresyKluceRemovnutych = new ArrayList<int>();

				for (auto okres : *okresyAktualnehoKraja) {

					Okres* aktualnyOkres = okres->accessData();
					

					if (typJednotky == 2) {

						Array<int>* EVSOkres = aktualnyOkres->getPodielEkonomickychSkupin();

						int zistovaneEVSOkres = EVSOkres->at(typSkupiny_);

						if (!(dolnaHranica_ <= zistovaneEVSOkres && zistovaneEVSOkres <= hornaHranica_)) {
							//okresyKluceRemovnutych->add(okres->getKey());
							aktualnyOkres->makeUnvalid();

						}
						else {
							aktualnyOkres->setKriteriumEVSPocet(zistovaneEVSOkres);
						}

					}
					else {

						SortedSequenceTable<string, Obec*>* obceAktualnehoOkresu = aktualnyOkres->dajObce();

						//ArrayList<string*>* kluceRemovnutych = new ArrayList<string*>();

						for (auto obec : *obceAktualnehoOkresu) {

							Obec* aktualnaObec = obec->accessData();

							Array<int>* ekonomickaVekovaSkupina = aktualnaObec->getPodielEkonomickychSkupin();

							int zistovaneCislo = ekonomickaVekovaSkupina->at(typSkupiny_);

							if (!(dolnaHranica_ <= zistovaneCislo && zistovaneCislo <= hornaHranica_)) {
								//kluceRemovnutych->add(new string(obec->getKey()));
								aktualnaObec->makeUnvalid();

							}
							else {
								aktualnaObec->setKriteriumEVSPocet(zistovaneCislo);
							}
						}

						/*
						for (int i = 0; i < kluceRemovnutych->size(); i++) {
							Obec* removnuta = obceAktualnehoOkresu->remove(*kluceRemovnutych->at(i));
							delete removnuta;
							delete kluceRemovnutych->at(i);
						}


						delete kluceRemovnutych;
						*/

					}

				}

				/*
				for (int i = 0; i < okresyKluceRemovnutych->size(); i++) {
					Okres* removnutyOkres = okresyAktualnehoKraja->remove(okresyKluceRemovnutych->at(i));
					delete removnutyOkres;

				}

				delete okresyKluceRemovnutych;
				*/
			}

		}

		/*
		for (int i = 0; i < krajeKluceRemovnutych->size(); i++) {
			Kraj* removnutyKraj = krajeSlovenska->remove(*krajeKluceRemovnutych->at(i));
			delete removnutyKraj;
			delete krajeKluceRemovnutych->at(i);
		}

		delete krajeKluceRemovnutych;
		*/

		return filtrovanaMnozina;
	}

	inline void EVSPocet::vypisInfoOFiltri() {
		cout << "-------------------------------------------------------" << endl;
		cout << "Nazov: pocet ekonomickej vekovej skupiny" << endl;
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

		cout << "Dolna hranica: " << dolnaHranica_ << " obyvatelov" << endl;
		cout << "Horna hranica: " << hornaHranica_ << " obyvatelov" << endl;

	}
}
