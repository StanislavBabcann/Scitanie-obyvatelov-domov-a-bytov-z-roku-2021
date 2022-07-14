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

	class TriedenieCislo {
	public:
		TriedenieCislo(int triedenaMnozina, int smerTriedenia, int kriteriumTriedenia);
		~TriedenieCislo();
		void zmenUnikatnost();
		int getPocetTriedenych();
		void pridajUJ(IUzemnaJednotka* uzemnaJednotka);
		double getKriteriumZUzemnejJednotky(IUzemnaJednotka* uzemnaJednotka);
		void QuickSort(int zaciatok, int koniec);
		string getUtriedeneUJ();
		void vypisInfo();
		

	private:
		int triedenaMnozina_;
		int smerTriedenia_;
		double unikatnost_;
		int kriteriumTriedenia_;
		UnsortedSequenceTable<double, IUzemnaJednotka*>* utriedeneUJ_;


	};

	inline TriedenieCislo::TriedenieCislo(int triedenaMnozina, int smerTriedenia, int kriteriumTriedenia) {
		triedenaMnozina_ = triedenaMnozina;
		smerTriedenia_ = smerTriedenia;

		/*
		if (triedenaMnozina_ == 1) {
			utriedeneKraje_ = new SortedSequenceTable<double, Kraj*>();
		}
		else if (triedenaMnozina_ == 2) {
			utriedeneOkresy_ = new SortedSequenceTable<double, Okres*>();
		}
		else {
			utriedeneObce_ = new SortedSequenceTable<double, Obec*>();
		}
		*/

		utriedeneUJ_ = new UnsortedSequenceTable<double, IUzemnaJednotka*>();

		unikatnost_ = 0.000000000001;

		kriteriumTriedenia_ = kriteriumTriedenia;
	}

	inline TriedenieCislo::~TriedenieCislo() {
		delete utriedeneUJ_;
	}

	inline void TriedenieCislo::pridajUJ(IUzemnaJednotka* uzemnaJednotka) {
		double key = getKriteriumZUzemnejJednotky(uzemnaJednotka);

		key += unikatnost_;

		utriedeneUJ_->insert(key, uzemnaJednotka);

		zmenUnikatnost();
	}

	inline void TriedenieCislo::zmenUnikatnost() {
		unikatnost_ += 0.000000000001;
	}

	inline int TriedenieCislo::getPocetTriedenych() {
		return utriedeneUJ_->size();
	}

	inline double TriedenieCislo::getKriteriumZUzemnejJednotky(IUzemnaJednotka* uzemnaJednotka) {
		double kriterium;

		if (kriteriumTriedenia_ == 1) {
			//cout << "tu" << endl;
			kriterium = (double)(uzemnaJednotka->getKriteriumVzdelaniePocet());
		}
		else if (kriteriumTriedenia_ == 2) {
			//cout << "tu2" << endl;
			kriterium = uzemnaJednotka->getKriteriumVzdelaniePodiel();
		}
		else if (kriteriumTriedenia_ == 3) {
			//cout << "tu3" << endl;
			kriterium = (double)(uzemnaJednotka->getKriteriumVekovaSkupinaPocet());
		}
		else {
			//cout << "tu4" << endl;
			kriterium = uzemnaJednotka->getKriteriumVekovaSkupinaPodiel();
		}

		return kriterium;

	}

	inline void TriedenieCislo::QuickSort(int zaciatok, int koniec) {
		IUzemnaJednotka* pivotnaJednotka = utriedeneUJ_->getItemAtIndex(zaciatok + (koniec - zaciatok) / 2).accessData();
		double pivot = getKriteriumZUzemnejJednotky(pivotnaJednotka);
		int lavy = zaciatok;
		int pravy = koniec;

		while (lavy <= pravy) {
			
			while (getKriteriumZUzemnejJednotky(utriedeneUJ_->getItemAtIndex(lavy).accessData()) < pivot) {
				lavy++;
			}

			

			while (getKriteriumZUzemnejJednotky(utriedeneUJ_->getItemAtIndex(pravy).accessData()) > pivot) {
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

	inline string TriedenieCislo::getUtriedeneUJ() {
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

	inline void TriedenieCislo::vypisInfo() {
		cout << "-------------------------------------------------------" << endl;
		cout << "Pouzite triedenie: " << endl;
		cout << "-------------------------------------------------------" << endl;
		cout << "Kriterium: ";

		if (kriteriumTriedenia_ == 1) {
			cout << "pocet vzdelanej skupiny";
		}
		else if (kriteriumTriedenia_ == 2) {
			cout << "podiel vzdelanej skupiny";
		}
		else if (kriteriumTriedenia_ == 3) {
			cout << "pocet vekovej skupiny";
		}
		else {
			cout << "podiel vekovej skupiny";
		}

		if (smerTriedenia_ == 1) {
			cout << "(vzostupne)" << endl;
		}
		else {
			cout << "(zostupne)" << endl;
		}
	}
}
