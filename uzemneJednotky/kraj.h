#pragma once


#include "../structures/table/sorted_sequence_table.h"

#include "../uzemneJednotky/okres.h"
#include "../uzemneJednotky/iUzemnaJednotka.h"
#include "../structures/list/array_list.h"

using namespace structures;

namespace uzemneJednotky
{

	class Kraj : public IUzemnaJednotka
	{
		
	public:
		Kraj(int code, string title, string note);
		Kraj(Kraj& other);
		~Kraj();
		void pridajOkresy(LinkedList<string>* nacitaneData);
		int getCode();
		virtual string getTitle();
		string getNote();
		void pridajObce(LinkedList<string>* nacitandeData, SortedSequenceTable<string, Array<int>*>* dataOVeku, SortedSequenceTable<string, Array<int>*>* dataOVzdelani);
		int getPocetObyvatelov();
		Array<int>* getPodielEkonomickychSkupin();
		Array<int>* getPodielVzdelanychSkupin();
		Array<int>* getPodielVekovychSkupin();
		SortedSequenceTable<int, Okres*>* dajOkresy();
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
		SortedSequenceTable<int, Okres*>* okresy_;
		int code_;
		string title_;
		string note_;
		int cisloKraja_;
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

	inline Kraj::Kraj(int code, string title, string note)
	{
		okresy_ = new SortedSequenceTable<int, Okres*>();
		code_ = code;
		title_ = title;
		note_ = note;

		pocetObyvatelov_ = 0;

		kriteriumVzdelaniePodiel_ = double(INT_MAX);
		kriteriumVzdelaniePocet_ = INT_MAX;
		kriteriumVekovaSkupinaPocet_ = INT_MAX;
		kriteriumVekovaSkupinaPodiel_ = double(INT_MAX);
		kriteriumEVSPocet_ = INT_MAX;
		kriteriumEVSPodiel_ = double(INT_MAX);

		valid_ = true;

		podielEkonomickychSkupin_ = new Array<int>(3);

		podielVzdelanychSkupin_ = new Array<int>(8);

		podielVekovychSkupin_ = new Array<int>(202);

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

	inline Kraj::Kraj(Kraj& other) {
		okresy_ = new SortedSequenceTable<int, Okres*>();


		for (auto item : *other.dajOkresy()) {
			Okres* novyOkres = new Okres(*item->accessData());
			okresy_->insert(item->getKey(), novyOkres);
		}

		code_ = other.getCode();
		title_ = other.getTitle();
		note_ = other.getNote();

		pocetObyvatelov_ = other.getPocetObyvatelov();

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

	inline Kraj::~Kraj()
	{
		for (auto item : *okresy_) {
			string nameOfOkres = item->accessData()->getTitle();
			delete item->accessData();
		}
		
		delete okresy_;
		delete podielEkonomickychSkupin_;
		delete podielVzdelanychSkupin_;
		delete podielVekovychSkupin_;
		//delete kluceNaNajdenieOkresu_;
	}

	inline int Kraj::getPocetObyvatelov()
	{
		return pocetObyvatelov_;
	}

	inline Array<int>* Kraj::getPodielEkonomickychSkupin()
	{
		return podielEkonomickychSkupin_;
	}

	inline Array<int>* Kraj::getPodielVzdelanychSkupin()
	{
		return podielVzdelanychSkupin_;
	}

	inline Array<int>* Kraj::getPodielVekovychSkupin()
	{
		return podielVekovychSkupin_;
	}


	inline void Kraj::pridajOkresy(LinkedList<string>* nacitandeData) {
		//cout << code_ << " kod moreffdfdf" << endl;
		string kod = nacitandeData->at(0);
		string title = nacitandeData->at(1);
		string noteAsString = nacitandeData->at(2);
		if (noteAsString.length() != 0) {
			int note = stoi(noteAsString);
			
			while (note < (code_ + 1) * 100 && nacitandeData->size() > 3) {
				
				int res = title.compare("Zahranicie");

				if (res == 0) {
					break;
				}

				Okres* novyOkres = new Okres(kod, title, note, this->getTitle());

				char znak = kod.at(5);

				
				int cisloOkresu = (int)(kod.at(5)) - 48;

				if (!isdigit(znak)) {
					cisloOkresu -= 100;
				}
				
				okresy_->insert(cisloOkresu, novyOkres);
				

				nacitandeData->removeAt(0);
				nacitandeData->removeAt(0);
				nacitandeData->removeAt(0);

				
					kod = nacitandeData->at(0);
					title = nacitandeData->at(1);
					noteAsString = nacitandeData->at(2);
					if (noteAsString.length() != 0) {
						note = stoi(noteAsString);
					}

			}


		}
		
	}

	inline int Kraj::getCode()
	{
		return code_;
	}

	inline string Kraj::getTitle()
	{
		return title_;
	}

	inline string Kraj::getNote()
	{
		return note_;
	}

	inline void Kraj::pridajObce(LinkedList<string>* nacitandeData, SortedSequenceTable<string, Array<int>*>* dataOVeku, SortedSequenceTable<string, Array<int>*>* dataOVzdelani) {
		for (auto item : *okresy_) {
			item->accessData()->pridajObce(nacitandeData, dataOVeku, dataOVzdelani);
			//cout << item->accessData()->getTitle() << " okres" << endl;;

			Array<int>* zoznamEkonomickychSkupinOkresu = item->accessData()->getPodielEkonomickychSkupin();

			//cout << zoznamEkonomickychSkupinOkresu->size() << endl;
			for (int i = 0; i < 3; i++) {
				podielEkonomickychSkupin_->at(i) += zoznamEkonomickychSkupinOkresu->at(i);
			}

			Array<int>* zoznamVzdelanychSkupinOkresu = item->accessData()->getPodielVzdelanychSkupin();

			for (int i = 0; i < 8; i++) {
				podielVzdelanychSkupin_->at(i) += zoznamVzdelanychSkupinOkresu->at(i);
			}

			Array<int>* zoznamVekovychSkupinOkresu = item->accessData()->getPodielVekovychSkupin();

			for (int i = 0; i < 202; i++) {
				podielVekovychSkupin_->at(i) += zoznamVekovychSkupinOkresu->at(i);
			}

			pocetObyvatelov_ += item->accessData()->getPocetObyvatelov();
		}

		
	}

	inline SortedSequenceTable<int, Okres*>* Kraj::dajOkresy()
	{
		return okresy_;
	}

	inline int Kraj::getKriteriumVzdelaniePocet()
	{
		return kriteriumVzdelaniePocet_;
	}

	inline double Kraj::getKriteriumVzdelaniePodiel()
	{
		return kriteriumVzdelaniePodiel_;
	}

	inline int Kraj::getKriteriumVekovaSkupinaPocet()
	{
		return kriteriumVekovaSkupinaPocet_;
	}

	inline double Kraj::getKriteriumVekovaSkupinaPodiel()
	{
		return kriteriumVekovaSkupinaPodiel_;
	}

	inline void Kraj::setKriteriumVzdelaniePocet(int vzdelaniePocet)
	{
		kriteriumVzdelaniePocet_ = vzdelaniePocet;
	}

	inline void Kraj::setKriteriumVzdelaniePodiel(double vzdelaniePodiel)
	{
		kriteriumVzdelaniePodiel_ = vzdelaniePodiel;
	}

	inline void Kraj::setKriteriumVekovaSkupinaPocet(int vekovaPocet)
	{
		kriteriumVekovaSkupinaPocet_ = vekovaPocet;
	}

	inline void Kraj::setKriteriumVekovaSkupinaPodiel(double vekovaPodiel)
	{
		kriteriumVekovaSkupinaPodiel_ = vekovaPodiel;
	}

	inline void Kraj::setKriteriumEVSPocet(int EvsPocet)
	{
		kriteriumEVSPocet_ = EvsPocet;
	}

	inline void Kraj::setKriteriumEVSPodiel(double EvsPodiel)
	{
		kriteriumEVSPodiel_ = EvsPodiel;
	}

	inline bool Kraj::getValidation()
	{
		return valid_;
	}

	inline void Kraj::makeUnvalid()
	{
		valid_ = false;
	}

	inline string Kraj::vypisKriteria() {
		//cout << "-----------------------------------------------" << endl;
		//cout << title_ << endl;

		string vystup = "-----------------------------------------------\n";
		string pomocny = title_ +  "\n";

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

	inline string Kraj::getStringKey()
	{
		return title_;
	}

	
}
