#pragma once

#include "../structures/table/sorted_sequence_table.h"

#include "../uzemneJednotky/obec.h"
#include "../uzemneJednotky/iUzemnaJednotka.h"

using namespace structures;

namespace uzemneJednotky
{
	class Okres : public IUzemnaJednotka
	{
	public:
		Okres(string code, string title, int note, string nazovKraja);
		Okres(Okres& other);
		~Okres();
		void pridajObce(LinkedList<string>* nacitaneData, SortedSequenceTable<string, Array<int>*>* dataOVeku, SortedSequenceTable<string, Array<int>*>* dataOVzdelani);

		string getCode();
		virtual string getTitle();
		string getNazovKraja();
		int getNote();
		char getCisloOkresu();
		int getPocetObyvatelov();
		Array<int>* getPodielEkonomickychSkupin();
		Array<int>* getPodielVzdelanychSkupin();
		Array<int>* getPodielVekovychSkupin();
		SortedSequenceTable<string, Obec*>* dajObce();
		virtual int getKriteriumVzdelaniePocet();
		virtual double getKriteriumVzdelaniePodiel();
		virtual int getKriteriumVekovaSkupinaPocet();
		virtual double getKriteriumVekovaSkupinaPodiel();
		void setKriteriumVzdelaniePocet(int vzdelaniePocet);
		void setKriteriumVzdelaniePodiel(double vzdelaniePodiel);
		void setKriteriumVekovaSkupinaPocet(int vekovaPocet);
		void setKriteriumVekovaSkupinaPodiel(double vekovaPodiel);
		void setKriteriumEVSPocet(int EVSPocet);
		void setKriteriumEVSPodiel(double EVSPodiel);
		bool getValidation();
		void makeUnvalid();
		virtual string vypisKriteria();
		virtual string getStringKey();

	private:
		SortedSequenceTable<string, Obec*>* obce_;
		string code_;
		string title_;
		string nazovKraja_;
		int note_;
		//int cisloKraja_;
		char cisloOkresu_;
		int pocetObyvatelov_;
		Array<int>* podielEkonomickychSkupin_;
		Array<int>* podielVzdelanychSkupin_;
		Array<int>* podielVekovychSkupin_;
		double kriteriumVzdelaniePodiel_;
		int kriteriumVzdelaniePocet_;
		int kriteriumVekovaSkupinaPocet_;
		double kriteriumVekovaSkupinaPodiel_;
		int kriteriumEVSPocet_;
		double kriteriumEVSPodiel_;
		bool valid_;
	};

	inline Okres::Okres(string code, string title, int note, string nazovKraja) 
	{
		obce_ = new SortedSequenceTable<string, Obec*>();
		code_ = code;
		title_ = title;
		note_ = note;
		cisloOkresu_ = code.at(5);
		nazovKraja_ = nazovKraja;

		pocetObyvatelov_ = 0;

		kriteriumVzdelaniePodiel_ = double(INT_MAX);
		kriteriumVzdelaniePocet_ = INT_MAX;
		kriteriumVekovaSkupinaPocet_ = INT_MAX;
		kriteriumVekovaSkupinaPodiel_ = double(INT_MAX);
		kriteriumEVSPocet_ = INT_MAX;
		kriteriumEVSPodiel_ = double(INT_MAX);

		podielEkonomickychSkupin_ = new Array<int>(3);

		podielVzdelanychSkupin_ = new Array<int>(8);

		podielVekovychSkupin_ = new Array<int>(202);

		valid_ = true;

		for (int i = 0; i < 3; i++) {
			podielEkonomickychSkupin_->at(i) = 0;
		}

		for (int i = 0; i < 8; i++) {
			podielVzdelanychSkupin_->at(i) = 0;
		}

		for (int i = 0; i < 202; i++) {
			podielVekovychSkupin_->at(i) = 0;
		}
	}

	inline Okres::Okres(Okres& other) {
		obce_ = new SortedSequenceTable<string, Obec*>();

		for (auto item : *other.dajObce()) {
			Obec* novaObec = new Obec(*item->accessData());
			obce_->insert(item->getKey(), novaObec);
		}

		code_ = other.getCode();
		title_ = other.getTitle();
		note_ = other.getNote();
		cisloOkresu_ = other.getCisloOkresu();
		pocetObyvatelov_ = other.getPocetObyvatelov();
		nazovKraja_ = other.getNazovKraja();

		valid_ = true;

		podielEkonomickychSkupin_ = new Array<int>(*other.getPodielEkonomickychSkupin());
		podielVzdelanychSkupin_ = new Array<int>(*other.getPodielVzdelanychSkupin());
		podielVekovychSkupin_ = new Array<int>(*other.getPodielVekovychSkupin());

		kriteriumVzdelaniePodiel_ = double(INT_MAX);
		kriteriumVzdelaniePocet_ = INT_MAX;
		kriteriumVekovaSkupinaPocet_ = INT_MAX;
		kriteriumVekovaSkupinaPodiel_ = double(INT_MAX);
		kriteriumEVSPocet_ = INT_MAX;
		kriteriumEVSPodiel_ = double(INT_MAX);
	}



	inline Okres::~Okres()
	{
		for (auto item : *obce_) {
			string nameOfObec = item->accessData()->getTitle();
			delete item->accessData();
		}

		delete obce_;
		delete podielEkonomickychSkupin_;
		delete podielVzdelanychSkupin_;
		delete podielVekovychSkupin_;
	}

	inline string Okres::getCode()
	{
		return this->code_;
	}

	inline string Okres::getTitle()
	{
		return title_;
	}

	inline int Okres::getNote()
	{
		return note_;
	}

	inline char Okres::getCisloOkresu()
	{
		return cisloOkresu_;
	}


	inline string Okres::getNazovKraja() {
		return nazovKraja_;
	}
	
	inline int Okres::getPocetObyvatelov()
	{
		return pocetObyvatelov_;
	}

	inline Array<int>* Okres::getPodielEkonomickychSkupin()
	{
		return podielEkonomickychSkupin_;
	}

	inline Array<int>* Okres::getPodielVzdelanychSkupin()
	{
		return podielVzdelanychSkupin_;
	}

	inline Array<int>* Okres::getPodielVekovychSkupin() {
		return podielVekovychSkupin_;
	}

	inline bool Okres::getValidation() {
		return valid_;
	}

	inline void Okres::makeUnvalid() {
		valid_ = false;
	}

	inline int Okres::getKriteriumVzdelaniePocet()
	{
		return kriteriumVzdelaniePocet_;
	}

	inline double Okres::getKriteriumVzdelaniePodiel()
	{
		return kriteriumVzdelaniePodiel_;
	}

	inline int Okres::getKriteriumVekovaSkupinaPocet()
	{
		return kriteriumVekovaSkupinaPocet_;
	}

	inline double Okres::getKriteriumVekovaSkupinaPodiel()
	{
		return kriteriumVekovaSkupinaPodiel_;
	}

	inline void Okres::pridajObce(LinkedList<string>* nacitaneData, SortedSequenceTable<string, Array<int>*>* dataOVeku, SortedSequenceTable<string, Array<int>*>* dataOVzdelani)
	{
		string code = nacitaneData->at(0);
		string title = nacitaneData->at(1);
		int note = stoi(nacitaneData->at(2));

		char cisloOkresuObce = code.at(5);

		//cout << title << " pridavana obec" << endl;

		//cout << "cislo okresu " << cisloOkresu_ << endl;
		//cout << "cislo okresu pre obec " << cisloOkresuObce << endl;

		while (cisloOkresuObce == cisloOkresu_) {
			//cout << title << endl;
			
			string kluc = code.substr(3, 9);

			int cisloObce = stoi(code.substr(3, 9));

			Array<int>* zoznamPreVek = dataOVeku->remove(kluc);
			Array<int>* zoznamPreVzdelanie = dataOVzdelani->remove(kluc);
			


			Obec* novaObec = new Obec(code, title, note, zoznamPreVek, zoznamPreVzdelanie, nazovKraja_, this->getTitle());

			Array<int>* zoznamEkonomickychSkupinObce = novaObec->getPodielEkonomickychSkupin();

			for (int i = 0; i < 3; i++) {
				podielEkonomickychSkupin_->at(i) += zoznamEkonomickychSkupinObce->at(i);
			}

			for (int i = 0; i < 8; i++) {
				podielVzdelanychSkupin_->at(i) += zoznamPreVzdelanie->at(i);
			}

			for (int i = 0; i < zoznamPreVek->size(); i++) {
				podielVekovychSkupin_->at(i) += zoznamPreVek->at(i);
			}

			pocetObyvatelov_ += novaObec->getPocetObyvatelov();

			obce_->insert(kluc, novaObec);
			
			nacitaneData->removeAt(0);
			nacitaneData->removeAt(0);
			nacitaneData->removeAt(0);

			/*
			if (nacitaneData->size() > 2) {
				code = nacitaneData->at(0);
				title = nacitaneData->at(1);
				if (nacitaneData->at(2).length() != 0) {
					note = stoi(nacitaneData->at(2));
				}
				else {
					cisloOkresuObce = -1;
				}

				cisloOkresuObce = code.at(5);
			}
			else {
				cisloOkresuObce = -1;
			}
			*/
			if (nacitaneData->size() > 2) {
				code = nacitaneData->at(0);
				title = nacitaneData->at(1);
				note = stoi(nacitaneData->at(2));
				cisloOkresuObce = code.at(5);
			}
			else {
				break;
			}

			//cout << "cislo okresu, kde patri obec " << cisloOkresuObce << endl;
			//cout << "cislo okresu kde sa pridvaju obce " << cisloOkresu_ << endl;


		}


	}

	inline SortedSequenceTable<string, Obec*>* Okres::dajObce()
	{
		return obce_;
	}

	inline void Okres::setKriteriumVzdelaniePocet(int vzdelaniePocet)
	{
		kriteriumVzdelaniePocet_ = vzdelaniePocet;
	}

	inline void Okres::setKriteriumVzdelaniePodiel(double vzdelaniePodiel)
	{
		kriteriumVzdelaniePodiel_ = vzdelaniePodiel;
	}

	inline void Okres::setKriteriumVekovaSkupinaPocet(int vekovaPocet)
	{
		kriteriumVekovaSkupinaPocet_ = vekovaPocet;
	}

	inline void Okres::setKriteriumVekovaSkupinaPodiel(double vekovaPodiel)
	{
		kriteriumVekovaSkupinaPodiel_ = vekovaPodiel;
	}

	inline void Okres::setKriteriumEVSPocet(int EvsPocet)
	{
		kriteriumEVSPocet_ = EvsPocet;
	}

	inline void Okres::setKriteriumEVSPodiel(double EvsPodiel)
	{
		kriteriumEVSPodiel_ = EvsPodiel;
	}

	inline string Okres::vypisKriteria() {
		//cout << "-----------------------------------------------" << endl;
		//cout << title_ << " <-- " << nazovKraja_ << endl;

		string vystup = "-----------------------------------------------\n";
		string pomocny = title_ + " <-- " + nazovKraja_ + "\n";

		vystup = vystup + pomocny;

		if (kriteriumVzdelaniePocet_ != INT_MAX) {
			//cout << "Kriterium vzdelanie pocet: " << kriteriumVzdelaniePocet_ << endl;
			pomocny = "Kriterium vzdeanie pocet: " + to_string(kriteriumVzdelaniePocet_) + "\n";
			vystup = vystup + pomocny;
		}

		if (kriteriumVzdelaniePodiel_ != double(INT_MAX)) {
			//cout << "Kriterium vzdelanie podiel: " << kriteriumVzdelaniePodiel_ << endl;
			pomocny = "Kriterium vzdelanie podiel: " + to_string(kriteriumVzdelaniePodiel_) + "\n";
			vystup = vystup + pomocny;
		}

		if (kriteriumVekovaSkupinaPocet_ != INT_MAX) {
			//cout << "Kriterium vekova skupina pocet: " << kriteriumVekovaSkupinaPocet_ << endl;
			pomocny = "Kriterium vekova skupina pocet: " + to_string(kriteriumVekovaSkupinaPocet_) + "\n";
			vystup = vystup + pomocny;
		}

		if (kriteriumVekovaSkupinaPodiel_ != double(INT_MAX)) {
			//cout << "Kriterium vekova skupina podiel: " << kriteriumVekovaSkupinaPodiel_ << endl;
			pomocny = "Kriterium vekova skupina podiel: " + to_string(kriteriumVekovaSkupinaPodiel_) + "\n";
			vystup = vystup + pomocny;
		}

		if (kriteriumEVSPocet_ != INT_MAX) {
			//cout << "Kriterium EVS pocet: " << kriteriumEVSPocet_ << endl;
			pomocny = "Kriterium EVS pocet: " + to_string(kriteriumEVSPocet_) + "\n";
			vystup = vystup + pomocny;
		}

		if (kriteriumEVSPodiel_ != double(INT_MAX)) {
			//cout << "Kriterium EVS podiel: " << kriteriumEVSPodiel_ << endl;
			pomocny = "Kriterium EVS podiel: " + to_string(kriteriumEVSPodiel_) + "\n";
			vystup = vystup + pomocny;
		}

		return vystup;

	}

	inline string Okres::getStringKey()
	{
		return title_ + nazovKraja_;
	}

	
}
