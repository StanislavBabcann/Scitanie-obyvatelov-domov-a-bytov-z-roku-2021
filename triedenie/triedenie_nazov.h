#pragma once
#include <iostream>
#include <string>

#include "../structures/table/sorted_sequence_table.h"
#include "../uzemneJednotky/obec.h"
#include "../uzemneJednotky/okres.h"
#include "../uzemneJednotky/kraj.h"
#include "../structures/table/unsorted_sequence_table.h"

using namespace structures;
using namespace std;
using namespace uzemneJednotky;

namespace triedenie {

	class TriedenieNazov {
	public:
		TriedenieNazov(int triedenaMnozina, int smerTriedenia);
		~TriedenieNazov();
		int getPocetTriedenych();
		void pridajUJ(IUzemnaJednotka* uzemnaJednotka);
		void QuickSort(int zaciatok, int koniec);
		string getUtriedeneUJ();
		void vypisInfo();
	private:
		int triedenaMnozina_;
		int smerTriedenia_;
		string unikatnost_;
		UnsortedSequenceTable<string, IUzemnaJednotka*>* utriedeneUJ_;
		
	};

	inline TriedenieNazov::TriedenieNazov(int triedenaMnozina, int smerTriedenia) {
		triedenaMnozina_ = triedenaMnozina;
		smerTriedenia_ = smerTriedenia;

		utriedeneUJ_ = new UnsortedSequenceTable<string, IUzemnaJednotka*>();

	}

	inline TriedenieNazov::~TriedenieNazov() {
		delete utriedeneUJ_;
	}


	inline void TriedenieNazov::pridajUJ(IUzemnaJednotka* uzemnaJednotka) {
		string key = uzemnaJednotka->getStringKey();

		

		utriedeneUJ_->insert(key, uzemnaJednotka);

		
	}

	inline int TriedenieNazov::getPocetTriedenych() {
		return utriedeneUJ_->size();
	}

	inline void TriedenieNazov::QuickSort(int zaciatok, int koniec) {
		IUzemnaJednotka* pivotnaJednotka = utriedeneUJ_->getItemAtIndex(zaciatok + (koniec - zaciatok) / 2).accessData();
		string pivot = pivotnaJednotka->getTitle();
		int lavy = zaciatok;
		int pravy = koniec;
		
		
		while (lavy <= pravy) {

			while (utriedeneUJ_->getItemAtIndex(lavy).accessData()->getTitle() < pivot) {
				lavy++;

			}

			while (utriedeneUJ_->getItemAtIndex(pravy).accessData()->getTitle() > pivot) {
				pravy--;
			}

			if (lavy <= pravy) {
				utriedeneUJ_->swap(lavy, pravy);
				lavy++;
				pravy--;
			}
		}

		if (zaciatok < pravy) {
			QuickSort(zaciatok, pravy);
		}

		if (lavy < koniec) {
			QuickSort(lavy, koniec);
		}
		
	}


	inline string TriedenieNazov::getUtriedeneUJ() {
		string vystup = "";

		for (auto uzemna : *utriedeneUJ_) {
			string vystupUJ = uzemna->accessData()->vypisKriteria();

			if (smerTriedenia_ == 1) {
				vystup = vystup + vystupUJ;
			}
			else {
				vystup = vystupUJ + vystup;
			}
		}

		return vystup;
	}

	inline void TriedenieNazov::vypisInfo() {
		cout << "-------------------------------------------------------" << endl;
		cout << "Pouzite triedenie: " << endl;
		cout << "-------------------------------------------------------" << endl;
		cout << "Kriterium : nazov";

		if (smerTriedenia_ == 1) {
			cout << "(vzostupne)" << endl;
		}
		else {
			cout << "(zostupne)" << endl;
		}
 	}
	




}