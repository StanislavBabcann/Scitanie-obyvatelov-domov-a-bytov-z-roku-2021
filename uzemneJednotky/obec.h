#pragma once

using namespace structures;

#include "../structures/array/array.h"

#include "iUzemnaJednotka.h"

namespace uzemneJednotky
{
	class Obec : public IUzemnaJednotka
	{
	public:
		Obec(string code, string title, int note, Array<int>* vek, Array<int>* vzdelanie, string nazovKraja, string nazovOkresu);
		Obec(Obec& other);
		~Obec();
		virtual string getTitle();
		string getCode();
		int getNote();
		string getNazovKraja();
		string getNazovOkresu();
		int getPocetObyvatelov();
		Array<int>* getPodielEkonomickychSkupin();
		Array<int>* getPodielVzdelanychSkupin();
		Array<int>* getVekoveSkupiny();
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
		


		//void pridajVek(Array<int>* data);
		//void pridajVzdelanie(Array<int>* data);

	private:
		string code_;
		string title_;
		int note_;
		string nazovKraja_;
		string nazovOkresu_;
		Array<int>* vek_;
		Array<int>* vzdelanie_;
		Array<int>* podielEkonomickychSkupin_;
		int pocetObyvatelov_;
		double kriteriumVzdelaniePodiel_;
		int kriteriumVzdelaniePocet_;
		int kriteriumVekovaSkupinaPocet_;
		double kriteriumVekovaSkupinaPodiel_;
		int kriteriumEVSPocet_;
		double kriteriumEVSPodiel_;
		bool valid_;
	};

	inline Obec::Obec(string code, string title, int note, Array<int>* vek, Array<int>* vzdelanie, string nazovKraja, string nazovOkresu) {
		code_ = code;
		title_ = title;
		note_ = note;

		vek_ = vek;
		vzdelanie_ = vzdelanie;

		nazovKraja_ = nazovKraja;
		nazovOkresu_ = nazovOkresu;

		valid_ = true;

		podielEkonomickychSkupin_ = new Array<int>(3);

		pocetObyvatelov_ = 0;
		kriteriumVzdelaniePodiel_ = double(INT_MAX);
		kriteriumVzdelaniePocet_ = INT_MAX;
		kriteriumVekovaSkupinaPocet_ = INT_MAX;
		kriteriumVekovaSkupinaPodiel_ = double(INT_MAX);
		kriteriumEVSPocet_ = INT_MAX;
		kriteriumEVSPodiel_ = double(INT_MAX);
		
		for (int i = 0; i < 3; i++) {
			podielEkonomickychSkupin_->at(i) = 0;
		}

		for (int i = 0; i < 101; i++) {
			if (i < 15) {
				podielEkonomickychSkupin_->at(0) += vek->at(i);
			}
			else if (i < 65) {
				podielEkonomickychSkupin_->at(1) += vek->at(i);
			}
			else {
				podielEkonomickychSkupin_->at(2) += vek->at(i);
			}

			pocetObyvatelov_ += vek->at(i);
			
		}

		for (int i = 101; i < 202; i++) {
			int helpIndex = i - 101;
			if (helpIndex < 15) {
				podielEkonomickychSkupin_->at(0) += vek->at(i);
			}
			else if (helpIndex < 65) {
				podielEkonomickychSkupin_->at(1) += vek->at(i);
			}
			else {
				podielEkonomickychSkupin_->at(2) += vek->at(i);
			}
			pocetObyvatelov_ += vek->at(i);
		}
		
	}

	inline Obec::Obec(Obec& other) {
		code_ = other.getCode();
		title_ = other.getTitle();
		note_ = other.getNote();
		vek_ = new Array<int>(*other.vek_);
		vzdelanie_ = new Array<int>(*other.getPodielVzdelanychSkupin());
		podielEkonomickychSkupin_ = new Array<int>(*other.getPodielEkonomickychSkupin());
		pocetObyvatelov_ = other.getPocetObyvatelov();

		valid_ = true;

		nazovKraja_ = other.getNazovKraja();
		nazovOkresu_ = other.getNazovOkresu();

		kriteriumVzdelaniePodiel_ = double(INT_MAX);
		kriteriumVzdelaniePocet_ = INT_MAX;
		kriteriumVekovaSkupinaPocet_ = INT_MAX;
		kriteriumVekovaSkupinaPodiel_ = double(INT_MAX);
		kriteriumEVSPocet_ = INT_MAX;
		kriteriumEVSPodiel_ = double(INT_MAX);
	}

	inline Obec::~Obec() {
		delete vek_;

		delete vzdelanie_;

		delete podielEkonomickychSkupin_;
	}

	inline string Obec::getTitle()
	{
		return title_;
	}

	inline string Obec::getCode()
	{
		return code_;
	}

	inline int Obec::getNote()
	{
		return note_;
	}

	inline string Obec::getNazovKraja()
	{
		return nazovKraja_;
	}

	inline string Obec::getNazovOkresu()
	{
		return nazovOkresu_;
	}

	inline int Obec::getPocetObyvatelov()
	{
		return pocetObyvatelov_;
	}

	inline Array<int>* Obec::getPodielEkonomickychSkupin()
	{
		return podielEkonomickychSkupin_;
	}

	inline Array<int>* Obec::getPodielVzdelanychSkupin()
	{
		return vzdelanie_;
	}

	inline Array<int>* Obec::getVekoveSkupiny()
	{
		return vek_;
	}

	inline int Obec::getKriteriumVzdelaniePocet()
	{
		return kriteriumVzdelaniePocet_;
	}

	inline double Obec::getKriteriumVzdelaniePodiel()
	{
		return kriteriumVzdelaniePodiel_;
	}

	inline int Obec::getKriteriumVekovaSkupinaPocet()
	{
		return kriteriumVekovaSkupinaPocet_;
	}

	inline double Obec::getKriteriumVekovaSkupinaPodiel()
	{
		return kriteriumVekovaSkupinaPodiel_;
	}

	inline void Obec::setKriteriumVzdelaniePocet(int vzdelaniePocet)
	{
		kriteriumVzdelaniePocet_ = vzdelaniePocet;
	}

	inline void Obec::setKriteriumVzdelaniePodiel(double vzdelaniePodiel)
	{
		kriteriumVzdelaniePodiel_ = vzdelaniePodiel;
	}

	inline void Obec::setKriteriumVekovaSkupinaPocet(int vekovaPocet)
	{
		kriteriumVekovaSkupinaPocet_ = vekovaPocet;
	}

	inline void Obec::setKriteriumVekovaSkupinaPodiel(double vekovaPodiel)
	{
		kriteriumVekovaSkupinaPodiel_ = vekovaPodiel;
	}

	inline void Obec::setKriteriumEVSPocet(int EvsPocet)
	{
		kriteriumEVSPocet_ = EvsPocet;
	}

	inline void Obec::setKriteriumEVSPodiel(double EvsPodiel)
	{
		kriteriumEVSPodiel_ = EvsPodiel;
	}

	inline bool Obec::getValidation()
	{
		return valid_;
	}

	inline void Obec::makeUnvalid()
	{
		valid_ = false;
	}

	inline string Obec::vypisKriteria() {
		string vystup = "-----------------------------------------------\n";
		//cout << "-----------------------------------------------" << endl;
		string pomocny = title_ + " <--" + nazovOkresu_ + " <-- " + nazovKraja_ + "\n";
		vystup = vystup + pomocny;
		//cout << "Obec " << title_ << " <-- " << nazovOkresu_ << " <-- " << nazovKraja_ << endl;
		if (kriteriumVzdelaniePocet_ != INT_MAX) {
			//cout << "Kriterium vzdelanie pocet: " << kriteriumVzdelaniePocet_ << endl;
			pomocny = "Kriterium vzdeanie pocet: " + to_string(kriteriumVzdelaniePocet_)  + "\n";
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

	inline string Obec::getStringKey()
	{
		return title_ + nazovOkresu_ + nazovKraja_;
	}

	
}
