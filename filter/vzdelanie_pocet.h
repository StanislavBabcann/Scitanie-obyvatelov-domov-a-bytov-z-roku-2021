#pragma once


#include <iostream>
#include <string>
#include <fstream>

#include "../uzemneJednotky/slovensko.h"
#include "../uzemneJednotky/kraj.h"
#include "../structures/list/array_list.h"
#include "../filter/iFilter.h"
#include "../filter/typUzemnejJednotky.h"


using namespace uzemneJednotky;
using namespace std;

namespace filter {
	class VzdelaniePocet : public IFIlter {
	public:
		VzdelaniePocet(int dolnaHranica, int hornaHranica, int typVzdelania);
		virtual Slovensko* vyfiltruj(Slovensko* filtrovanaMnozina, TypUzemnejJednotky* typUJ);
		virtual void vypisInfoOFiltri();

	private:
		int dolnaHranica_;
		int hornaHranica_;
		int typVzdelania_;
	};

	inline VzdelaniePocet::VzdelaniePocet(int dolnaHranica, int hornaHranica, int typVzdelania)
	{
		dolnaHranica_ = dolnaHranica;
		hornaHranica_ = hornaHranica;
		typVzdelania_ = typVzdelania;
	}

	
	inline Slovensko* VzdelaniePocet::vyfiltruj(Slovensko* filtrovanaMnozina, TypUzemnejJednotky* typUJ) {
		
		SortedSequenceTable<string, Kraj*>* krajeSlovenska = filtrovanaMnozina->getKraje();
		//ArrayList<string*>* krajeKluceRemovnutych = new ArrayList<string*>();


		int typJednotky = typUJ->getTyp();

		for (auto kraj : *krajeSlovenska) {
			Kraj* aktualnyKraj = kraj->accessData();


			if (typJednotky == 1) {
				Array<int>* skupinaVzdelaniaKraja = aktualnyKraj->getPodielVzdelanychSkupin();

				int krajPocetVzdelania = skupinaVzdelaniaKraja->at(typVzdelania_);

				if (!(dolnaHranica_ <= krajPocetVzdelania && krajPocetVzdelania <= hornaHranica_)) {
					//krajeKluceRemovnutych->add(new string(kraj->getKey()));
					aktualnyKraj->makeUnvalid();

				}
				else {
					aktualnyKraj->setKriteriumVzdelaniePocet(krajPocetVzdelania);
				}



			} else {

				SortedSequenceTable<int, Okres*>* okresyAktualnehoKraja = aktualnyKraj->dajOkresy();
				//ArrayList<int>* okresyKluceRemovnutych = new ArrayList<int>();
				
				for (auto okres : *okresyAktualnehoKraja) {

					Okres* aktualnyOkres = okres->accessData();


					if (typJednotky == 2) {

						Array<int>* skupinaVzdelaniaOKresu = aktualnyOkres->getPodielVzdelanychSkupin();

						int okresPocetVzdelania = skupinaVzdelaniaOKresu->at(typVzdelania_);


						if (!(dolnaHranica_ <= okresPocetVzdelania && okresPocetVzdelania <= hornaHranica_)) {
							//okresyKluceRemovnutych->add(okres->getKey());
							aktualnyOkres->makeUnvalid();

						}
						else {
							aktualnyOkres->setKriteriumVzdelaniePocet(okresPocetVzdelania);
						}
					}
					else {
						SortedSequenceTable<string, Obec*>* obceAktualnehoOkresu = aktualnyOkres->dajObce();

						//ArrayList<string*>* ObceKluceRemovnutych = new ArrayList<string*>();

						for (auto obec : *obceAktualnehoOkresu) {

							Obec* aktualnaObec = obec->accessData();

							Array<int>* skupinaVzdelaniaObce = aktualnaObec->getPodielVzdelanychSkupin();

							int obecPocetVzdelania = skupinaVzdelaniaObce->at(typVzdelania_);

							if (!(dolnaHranica_ <= obecPocetVzdelania && obecPocetVzdelania <= hornaHranica_)) {
								//ObceKluceRemovnutych->add(new string(obec->getKey()));
								aktualnaObec->makeUnvalid();

							}
							else {
								aktualnaObec->setKriteriumVzdelaniePocet(obecPocetVzdelania);
							}
						}

						
					}

				}
				
			}
		}

		

		return filtrovanaMnozina;

	}

	inline void VzdelaniePocet::vypisInfoOFiltri() {
		cout << "-------------------------------------------------------" << endl;
		cout << "Nazov: pocet vzdelanostnej skupiny" << endl;
		cout << "Kriterium: ";
		switch (typVzdelania_) {
		case 0:
			cout << "bez ukonceneho vzdelania";
			break;
		case 1:
			cout << "zakladne vzdelanie";
			break;
		case 2:
			cout << "stredne odborne vzdelanie";
			break;
		case 3:
			cout << "uplne stredne vzdelanie";
			break;
		case 4:
			cout << "vyssie odborne vzdeanie";
			break;
		case 5:
			cout << "vysokoskolske vzdelanie";
			break;
		case 6:
			cout << "bez skolskeho vzdelania";
			break;
		case 7:
			cout << "nezistene";
			break;
		}

		cout << endl;
		cout << "Dolna hranica: " << dolnaHranica_ << " obyvatelov" << endl;
		cout << "Horna hranica: " << hornaHranica_ << " obyvatelov" << endl;

	}
}
