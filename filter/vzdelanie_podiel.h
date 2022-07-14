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
	class VzdelaniePodiel : public IFIlter {
	public:
		VzdelaniePodiel(double dolnaHranicaPodiel, double hornaHranicaPodiel, int typVzdelania);
		virtual Slovensko* vyfiltruj(Slovensko* filtrovanaMnozina, TypUzemnejJednotky* typUJ);
		virtual void vypisInfoOFiltri();

	private:
		int typVzdelania_;
		double dolnaHranicaPodiel_;
		double hornaHranicaPodiel_;
	};

	inline VzdelaniePodiel::VzdelaniePodiel(double dolnaHranicaPodiel, double hornaHranicaPodiel, int typVzdelania)
	{
		typVzdelania_ = typVzdelania;
		dolnaHranicaPodiel_ = dolnaHranicaPodiel;
		hornaHranicaPodiel_ = hornaHranicaPodiel;
	}

	inline Slovensko* VzdelaniePodiel::vyfiltruj(Slovensko* filtrovanaMnozina, TypUzemnejJednotky* typUJ) {

		SortedSequenceTable<string, Kraj*>* krajeSlovenska = filtrovanaMnozina->getKraje();
		//ArrayList<string*>* krajeKluceRemovnutych = new ArrayList<string*>();

		int typJednotky = typUJ->getTyp();


		for (auto kraj : *krajeSlovenska) {
			Kraj* aktualnyKraj = kraj->accessData();

			if (typJednotky == 1) {
				Array<int>* skupinaVzdelaniaKraja = aktualnyKraj->getPodielVzdelanychSkupin();

				double pocetObyvatelovKraja = (double)aktualnyKraj->getPocetObyvatelov();

				double pocetVzdelanejKraj = (double)skupinaVzdelaniaKraja->at(typVzdelania_);

				double podielSkupinyKraja = pocetVzdelanejKraj / pocetObyvatelovKraja * 100;

				if (!(podielSkupinyKraja >= dolnaHranicaPodiel_ && podielSkupinyKraja <= hornaHranicaPodiel_)) {
					//krajeKluceRemovnutych->add(new string(kraj->getKey()));
					aktualnyKraj->makeUnvalid();
				}
				else {
					aktualnyKraj->setKriteriumVzdelaniePodiel(podielSkupinyKraja);
				}
			}
			else {
				SortedSequenceTable<int, Okres*>* okresyAktualnehoKraja = aktualnyKraj->dajOkresy();
				//ArrayList<int>* okresyKluceRemovnutych = new ArrayList<int>();

				for (auto okres : *okresyAktualnehoKraja) {

					Okres* aktualnyOkres = okres->accessData();


					if (typJednotky == 2) {
						Array<int>* skupinaVzdelaniaOKresu = aktualnyOkres->getPodielVzdelanychSkupin();


						double pocetObyvatelovOkresu = (double)aktualnyOkres->getPocetObyvatelov();

						double pocetVzdelanejOkres = (double)skupinaVzdelaniaOKresu->at(typVzdelania_);

						double podielSKupinyOkresu = pocetVzdelanejOkres / pocetObyvatelovOkresu * 100;

						if (!(podielSKupinyOkresu >= dolnaHranicaPodiel_ && podielSKupinyOkresu <= hornaHranicaPodiel_)) {
							//okresyKluceRemovnutych->add(okres->getKey());
							aktualnyOkres->makeUnvalid();
						}
						else {
							aktualnyOkres->setKriteriumVzdelaniePodiel(podielSKupinyOkresu);
						}


					}
					else {
						SortedSequenceTable<string, Obec*>* obceAktualnehoOkresu = aktualnyOkres->dajObce();

						//ArrayList<string*>* kluceRemovnutych = new ArrayList<string*>();

						for (auto obec : *obceAktualnehoOkresu) {

							Obec* aktualnaObec = obec->accessData();

							Array<int>* skupinaVzdelania = aktualnaObec->getPodielVzdelanychSkupin();

							double pocetHladanejVzdelanejSkupiny = (double)skupinaVzdelania->at(typVzdelania_);

							double pocetObyvatelov = (double)aktualnaObec->getPocetObyvatelov();

							double podielSkupiny = pocetHladanejVzdelanejSkupiny / pocetObyvatelov * 100;


							if (!(podielSkupiny >= dolnaHranicaPodiel_ && podielSkupiny <= hornaHranicaPodiel_)) {
								//kluceRemovnutych->add(new string(obec->getKey()));
								aktualnaObec->makeUnvalid();
							}
							else {
								aktualnaObec->setKriteriumVzdelaniePodiel(podielSkupiny);
							}
						}


					}


				}

			}
		}

		return filtrovanaMnozina;

	}

	inline void VzdelaniePodiel::vypisInfoOFiltri() {
		cout << "-------------------------------------------------------" << endl;
		cout << "Nazov: podiel vzdelanostnej skupiny" << endl;
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
		cout << "Kriterium: " << dolnaHranicaPodiel_ << "% - " << hornaHranicaPodiel_ << "% obyvatelov" << endl;

		
	}
}