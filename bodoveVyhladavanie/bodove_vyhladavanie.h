#pragma once

#include <iostream>
#include <string>

#include "../uzemneJednotky/slovensko.h"

using namespace uzemneJednotky;
using namespace std;

namespace bodoveVyhladavanie
{
	class BodoveVyhladavanie
	{
	public:
		BodoveVyhladavanie(Slovensko* prehladavaneSlovensko);
		~BodoveVyhladavanie();
		//Slovensko* dajInfoSlovensko();
		void zakladneMenu();
		void menuPreSlovensko();
		void menuPreKraj(Kraj* prehladavanyKraj);
		void menuPreOkres(Okres* prehladavanaObec, Kraj* krajOkresu);
		void vypisSlovensko();
		void vypisKraj(Kraj* kraj);
		void vypisOkres(Okres* okres, Kraj* kraj);
		void vypisObec(Obec* obec, Okres* okres, Kraj* kraj);
		void vypisInfo(int pocetObyvatelov, Array<int>* ekonomickeSkupiny, Array<int>* vzdelaneSkupiny);
		void upozernenieUzivatela();
		bool skontrolujVstup(string vstup);

	private:
		Slovensko* slovensko_;
		
	};

	inline BodoveVyhladavanie::BodoveVyhladavanie(Slovensko* prehladavaneSlovensko)
	{
		slovensko_ = prehladavaneSlovensko;
	}

	inline BodoveVyhladavanie::~BodoveVyhladavanie()
	{
		delete slovensko_;
	}

	inline void BodoveVyhladavanie::zakladneMenu() 
	{
		system("CLS");
		cout << "*********************************" << endl;
		cout << "----- Menu Slovenska -----" << endl;
		cout << "Zadaj cislo pre pozadovanu operaciu:" << endl;
		cout << "1: vyber kraj Slovesnka" << endl;
		cout << "2: vypis informacie o Slovensku" << endl;
		cout << "0: ukoncenie bodoveho vyhladavania" << endl;
		string input;
		cin >> input;

		bool kontrola = skontrolujVstup(input);

		if (kontrola) {
			int moznost = stoi(input);

			if (moznost == 1) {
				menuPreSlovensko();
			}
			else if (moznost == 2) {
				vypisSlovensko();
				zakladneMenu();
			}
			else if (moznost == 0) {
				// do nothing
			}
			else {
				upozernenieUzivatela();
				zakladneMenu();
			}
		}
		else {
			upozernenieUzivatela();
			zakladneMenu();
		}
	}

	inline void BodoveVyhladavanie::menuPreSlovensko() 
	{
		system("CLS");
		cout << "*********************************" << endl;
		cout << "----- Menu pre vyber kraja -----" << endl;
		cout << "Zadaj cislo pre pozadovanu operaciu:" << endl;

		SortedSequenceTable<string, Kraj*>* krajeSlovenska = slovensko_->getKraje();

		//Array<string*>* kluceKrajov = new Array<string*>(krajeSlovenska->size());

		Array<Kraj*>* ponuknuteKraje = new Array<Kraj*>(krajeSlovenska->size());

		int moznost = 0;
		int i = 0;
		for (auto item : *krajeSlovenska) {

			moznost = i + 1;

			//string* key = new string(item->getKey());

			cout << moznost << ": " << item->accessData()->getTitle() << endl;
			//kluceKrajov->at(i) = key;
			ponuknuteKraje->at(i) = item->accessData();

			i++;
		}

		cout << "0: ukoncenie menu pre Slovensko" << endl;

		cout << "Zvolena operacia: ";

		string input;
		cin >> input;

		bool kontrola = skontrolujVstup(input);
		bool nekorektnyVstup = false;

		if (kontrola) {
			int moznost = stoi(input) - 1;

			if (moznost > -1 && moznost < ponuknuteKraje->size()) {
				Kraj* vybranyKraj = ponuknuteKraje->at(moznost);
				menuPreKraj(vybranyKraj);

			}
			else if (moznost == -1) {
				zakladneMenu();
			}
			else {
				upozernenieUzivatela();
				nekorektnyVstup = true;
			}
		}
		else {
			upozernenieUzivatela();
			nekorektnyVstup = true;
		}




		if (nekorektnyVstup) {
			menuPreSlovensko();
		}

		delete ponuknuteKraje;


	}

	inline void BodoveVyhladavanie::menuPreKraj(Kraj* prehladavanyKraj)
	{
		system("CLS");
		cout << "*********************************" << endl;
		cout << "----- Menu pre " + prehladavanyKraj->getTitle() << " -----" << endl;
		cout << "Zadaj cislo pre pozadovanu operaciu:" << endl;

		SortedSequenceTable<int, Okres*>* okresyKraja = prehladavanyKraj->dajOkresy();

		//Array<int>* kluceOkresov = new Array<int>(okresyKraja->size());

		Array<Okres*>* ponuknuteOkresy = new Array<Okres*>(okresyKraja->size());

		string medzera;
		int moznost = 0;
		int i = 0;
		for (auto item : *okresyKraja) {

			moznost = i + 1;

			medzera = ":   ";

			if (moznost > 99) {
				medzera = ": ";
			}
			else if (moznost > 9) {
				medzera = ":  ";
			}

			cout << moznost << medzera << item->accessData()->getTitle() << endl;
			//kluceOkresov->at(i) = item->getKey();
			ponuknuteOkresy->at(i) = item->accessData();

			i++;
		}

		moznost++;

		medzera = ":   ";

		if (moznost > 99) {
			medzera = ": ";
		}
		else if (moznost > 9) {
			medzera = ":  ";
		}

		

		cout << moznost << medzera << "vypis info o kraji" << endl;
		cout << "0:   ukoncenie menu pre " << prehladavanyKraj->getTitle() << endl;

		moznost--;

		cout << "Zvolena operacia: " << endl;
		string input;
		cin >> input;

		bool kontrola = skontrolujVstup(input);
		bool nekorektnyVstup = false;

		if (kontrola) {
			int volba = stoi(input) - 1;

			if (volba > -1 && volba < ponuknuteOkresy->size()) {
				Okres* prehladavanyOkres = ponuknuteOkresy->at(volba);
				menuPreOkres(prehladavanyOkres, prehladavanyKraj);
			}
			else if (volba == moznost) {
				vypisKraj(prehladavanyKraj);
				menuPreKraj(prehladavanyKraj);

			}
			else if (volba == -1) {
				menuPreSlovensko();
			}
			else {
				upozernenieUzivatela();
				nekorektnyVstup = true;
			}
		}
		else {
			upozernenieUzivatela();
			nekorektnyVstup = true;
		}

		//delete kluceOkresov;

		if (nekorektnyVstup) {
			menuPreKraj(prehladavanyKraj);
		}

		delete ponuknuteOkresy;
	}

	inline void BodoveVyhladavanie::menuPreOkres(Okres* prehladavanyOkres, Kraj* krajOkresu)
	{
		system("CLS");
		cout << "*********************************" << endl;
		cout << "----- Menu pre " + prehladavanyOkres->getTitle() << " -----" << endl;
		cout << "Zadaj cislo pre pozadovanu operaciu:" << endl;

		SortedSequenceTable<string, Obec*>* obcePrehladavanehoOkresu = prehladavanyOkres->dajObce();

		Array<Obec*>* ponuknuteObce = new Array<Obec*>(obcePrehladavanehoOkresu->size());

		string medzera;

		int moznost = 0;
		int i = 0;
		for (auto item : *obcePrehladavanehoOkresu) {

			moznost = i + 1;

			medzera = ":   ";

			if (moznost > 99) {
				medzera = ": ";
			}
			else if (moznost > 9) {
				medzera = ":  ";
			}

			cout << moznost << medzera << item->accessData()->getTitle() << endl;
			ponuknuteObce->at(i) = item->accessData();

			i++;
		}

		moznost++;

		medzera = ":   ";

		if (moznost > 99) {
			medzera = ": ";
		}
		else if (moznost > 9) {
			medzera = ":  ";
		}

		cout << moznost << medzera << "vypis info o okrese" << endl;
		cout << "0:   ukoncenie menu pre " << prehladavanyOkres->getTitle() << endl;

		cout << "Zvolena operacia: ";

		moznost--;

		string input;
		cin >> input;

		bool kontrola = skontrolujVstup(input);
		bool nekorektnyVstup = false;

		if (kontrola) {
			int volba = stoi(input) - 1;

			if (volba > -1 && volba < ponuknuteObce->size()) {
				Obec* vybranaObec = ponuknuteObce->at(volba);
				vypisObec(vybranaObec, prehladavanyOkres, krajOkresu);
				menuPreOkres(prehladavanyOkres, krajOkresu);

			}
			else if (moznost == volba) {
				vypisOkres(prehladavanyOkres, krajOkresu);
				menuPreOkres(prehladavanyOkres, krajOkresu);
			}
			else if (volba == -1) {
				menuPreKraj(krajOkresu);
			}
			else {
				upozernenieUzivatela();
				nekorektnyVstup = true;
			}
		}
		else {
			upozernenieUzivatela();
			nekorektnyVstup = true;
		}


		if (nekorektnyVstup) {
			menuPreOkres(prehladavanyOkres, krajOkresu);
		}

		delete ponuknuteObce;


	}

	inline void BodoveVyhladavanie::vypisSlovensko()
	{
		system("CLS");
		cout << "******************************************" << endl;
		cout << "Slovenska republika" << endl;
		vypisInfo(slovensko_->getPocetObyvatelov(), slovensko_->getPodielEkonomickychSkupin(), slovensko_->getPodielVzdelanychSkupin());
	}

	inline void BodoveVyhladavanie::vypisKraj(Kraj* kraj)
	{
		system("CLS");
		cout << "******************************************" << endl;
		cout << "Kraj:              " << kraj->getTitle() << endl;
		cout << "Kod kraja:         " << kraj->getNote() << endl;
		vypisInfo(kraj->getPocetObyvatelov(), kraj->getPodielEkonomickychSkupin(), kraj->getPodielVzdelanychSkupin());
	}

	inline void BodoveVyhladavanie::vypisOkres(Okres* okres, Kraj* kraj)
	{
		system("CLS");
		cout << "******************************************" << endl;
		cout << "Okres:            " << okres->getTitle() << endl;
		cout << "Kod okresu:       " << okres->getCode() << endl;
		cout << "Kraj:             " << kraj->getTitle() << endl;
		vypisInfo(okres->getPocetObyvatelov(), okres->getPodielEkonomickychSkupin(), okres->getPodielVzdelanychSkupin());
	}

	inline void BodoveVyhladavanie::vypisObec(Obec* obec, Okres* okres, Kraj* kraj)
	{
		system("CLS");
		cout << "******************************************" << endl;
		cout << "Obec:             " << obec->getTitle() << endl;
		cout << "Kod obce:         " << obec->getCode() << endl;
		cout << "Okres:            " << okres->getTitle() << endl;
		cout << "Kraj:             " << kraj->getTitle() << endl;
		vypisInfo(obec->getPocetObyvatelov(), obec->getPodielEkonomickychSkupin(), obec->getPodielVzdelanychSkupin());

	}

	inline void BodoveVyhladavanie::vypisInfo(int pocetObyvatelov, Array<int>* ekonomickeSkupiny, Array<int>* vzdelaneSkupiny)
	{
		cout << "Pocet obyvatelov: " << pocetObyvatelov << endl;
		cout << "------------------------------------------" << endl;
		cout << "Ekonomicke vekove skupiny (EVS): " << endl;
		cout << "Predproduktivna skupina: " << ekonomickeSkupiny->at(0) << endl;
		cout << "Produktivna skupina    : " << ekonomickeSkupiny->at(1) <<endl;
		cout << "Poproduktivna skupina  : " << ekonomickeSkupiny->at(2) << endl;
		cout << "------------------------------------------" << endl;
		cout << "Vzdelanostne skupiny: " << endl;
		cout << "Bez ukonceneho vzdelania: " << vzdelaneSkupiny->at(0) << endl;
		cout << "Zakladne vzdelanie      : " << vzdelaneSkupiny->at(1) << endl;
		cout << "Stredne oborne vzdelanie: " << vzdelaneSkupiny->at(2) << endl;
		cout << "Uplne stredne vzdelanie : " << vzdelaneSkupiny->at(3) << endl;
		cout << "Vyssie odborne vzdelanie: " << vzdelaneSkupiny->at(4) << endl;
		cout << "Vysokoskolske vzdelanie : " << vzdelaneSkupiny->at(5) << endl;
		cout << "Bez skolskeho vzdelania : " << vzdelaneSkupiny->at(6) << endl;
		cout << "Nezistene               : " << vzdelaneSkupiny->at(7) << endl;
		cout << "------------------------------------------" << endl;
		cout << "******************************************" << endl;

		cout << "Stlac znak pre pokracovanie." << endl;
		string input;
		cin >> input;
		system("CLS");
	}

	inline void BodoveVyhladavanie::upozernenieUzivatela() 
	{
		system("CLS");
		cout << "Zadany neplatny vstup!" << endl;
		cout << "Stlac znak pre pokracovanie." << endl;
		string input;
		cin >> input;
		system("CLS");
	}

	inline bool BodoveVyhladavanie::skontrolujVstup(string vstup)
	{
		for (int i = 0; i < vstup.length(); i++) {
			if (!isdigit(vstup.at(i))) {
				return false;
			}
		}

		return true;
	}

	
}
