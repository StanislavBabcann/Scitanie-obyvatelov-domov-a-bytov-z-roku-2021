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
	class VekovaSkupinaPocet : public IFIlter {
	public:
		VekovaSkupinaPocet(int dolnaHranicaPocet, int hornaHranicaPocet, int dolnaHranicaVek, int hornaHranicaVek);
		virtual Slovensko* vyfiltruj(Slovensko* filtrovanaMnozina, TypUzemnejJednotky* typUJ);
		virtual void vypisInfoOFiltri();

	private:
		int dolnaHranicaPocet_;
		int hornaHranicaPocet_;
		int dolnaHranicaVek_;
		int hornaHranicaVek_;

	};

	inline VekovaSkupinaPocet::VekovaSkupinaPocet(int dolnaHranicaPocet, int hornaHranicaPocet, int dolnaHranicaVek, int hornaHranicaVek) {
		dolnaHranicaPocet_ = dolnaHranicaPocet;
		hornaHranicaPocet_ = hornaHranicaPocet;
		dolnaHranicaVek_ = dolnaHranicaVek;
		hornaHranicaVek_ = hornaHranicaVek;
	}

	inline Slovensko* VekovaSkupinaPocet::vyfiltruj(Slovensko* filtrovanaMnozina, TypUzemnejJednotky* typUJ) {
		SortedSequenceTable<string, Kraj*>* krajeSlovenska = filtrovanaMnozina->getKraje();
		//ArrayList<string*>* krajeKluceRemovnutych = new ArrayList<string*>();

		int typJednotky = typUJ->getTyp();

		for (auto kraj : *krajeSlovenska) {
			Kraj* aktualnyKraj = kraj->accessData();
			
			if (typJednotky == 1) {
				Array<int>* vekovaSkupinaOkres = aktualnyKraj->getPodielVekovychSkupin();

				int pocetObyvatelovKraja = 0;

				for (int i = 0; i < 101; i++) {
					if (i >= dolnaHranicaVek_ && i <= hornaHranicaVek_) {
						pocetObyvatelovKraja += vekovaSkupinaOkres->at(i);
					}
				}

				for (int i = 101; i < 202; i++) {
					int helpIndex = i - 101;

					if (helpIndex >= dolnaHranicaVek_ && helpIndex <= hornaHranicaVek_) {
						pocetObyvatelovKraja += vekovaSkupinaOkres->at(i);
					}
				}


				if (pocetObyvatelovKraja < dolnaHranicaPocet_ || pocetObyvatelovKraja > hornaHranicaPocet_) {
					//krajeKluceRemovnutych->add(new string(kraj->getKey()));
					aktualnyKraj->makeUnvalid();
				}
				else {
					aktualnyKraj->setKriteriumVekovaSkupinaPocet(pocetObyvatelovKraja);
				}

			} 
			else 
			{

			SortedSequenceTable<int, Okres*>* okresyAktualnehoKraja = aktualnyKraj->dajOkresy();
			//ArrayList<int>* okresyKluceRemovnutych = new ArrayList<int>();

				for (auto okres : *okresyAktualnehoKraja) {

					Okres* aktualnyOkres = okres->accessData();


					if (typJednotky == 2) {


						Array<int>* vekovaSkupinaOkres = aktualnyOkres->getPodielVekovychSkupin();

						int pocetObyvatelovOkresu = 0;

						for (int i = 0; i < 101; i++) {
							if (i >= dolnaHranicaVek_ && i <= hornaHranicaVek_) {
								pocetObyvatelovOkresu += vekovaSkupinaOkres->at(i);
							}
						}

						for (int i = 101; i < 202; i++) {
							int helpIndex = i - 101;

							if (helpIndex >= dolnaHranicaVek_ && helpIndex <= hornaHranicaVek_) {
								pocetObyvatelovOkresu += vekovaSkupinaOkres->at(i);
							}
						}


						if (pocetObyvatelovOkresu < dolnaHranicaPocet_ || pocetObyvatelovOkresu > hornaHranicaPocet_) {
							//okresyKluceRemovnutych->add(okres->getKey());
							aktualnyOkres->makeUnvalid();

						}
						else {
							aktualnyOkres->setKriteriumVekovaSkupinaPocet(pocetObyvatelovOkresu);
						}
					}
					else {
						SortedSequenceTable<string, Obec*>* obceAktualnehoOkresu = aktualnyOkres->dajObce();

						//ArrayList<string*>* kluceRemovnutych = new ArrayList<string*>();

						for (auto obec : *obceAktualnehoOkresu) {

							Obec* aktualnaObec = obec->accessData();

							Array<int>* vekovaSkupina = aktualnaObec->getVekoveSkupiny();

							int pocetObyvatelov = 0;

							for (int i = 0; i < 101; i++) {
								if (i >= dolnaHranicaVek_ && i <= hornaHranicaVek_) {
									pocetObyvatelov += vekovaSkupina->at(i);
								}
							}

							for (int i = 101; i < 202; i++) {
								int helpIndex = i - 101;

								if (helpIndex >= dolnaHranicaVek_ && helpIndex <= hornaHranicaVek_) {
									pocetObyvatelov += vekovaSkupina->at(i);
								}
							}


							if (pocetObyvatelov < dolnaHranicaPocet_ || pocetObyvatelov > hornaHranicaPocet_) {
								//kluceRemovnutych->add(new string(obec->getKey()));
								aktualnaObec->makeUnvalid();
							}
							else {
								aktualnaObec->setKriteriumVekovaSkupinaPocet(pocetObyvatelov);
							}
						}

						
					}
				}

			}



		}

		return filtrovanaMnozina;
	}

	inline void VekovaSkupinaPocet::vypisInfoOFiltri() {
		cout << "-------------------------------------------------------" << endl;
		cout << "Nazov: pocet vekovej skupiny" << endl;
		cout << "Kriterium: " << dolnaHranicaVek_ << " - " << hornaHranicaVek_ << " rokov" << endl;
		cout << "Kriterium: " << dolnaHranicaPocet_ << " - " << hornaHranicaPocet_ << " obyvatelov" << endl;

		
	}
}
