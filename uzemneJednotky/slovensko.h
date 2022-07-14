#pragma once


#include "../structures/table/sorted_sequence_table.h"
#include "../structures/list/linked_list.h"
#include "../structures/list/array_list.h"

#include "../uzemneJednotky/kraj.h"

using namespace structures;

namespace uzemneJednotky {

	class Slovensko
	{
	public:
		Slovensko();
		Slovensko(Slovensko& other);
		~Slovensko();
		void pridajKraje(LinkedList<string>* data);
		void pridakOkresy(LinkedList<string>* data);
		void pridajObce(LinkedList<string>* data, SortedSequenceTable<string, Array<int>*>* dataOVeku, SortedSequenceTable<string, Array<int>*>* dataOVzdelani);
		int getPocetObyvatelov();
		SortedSequenceTable<string, Kraj*>* getKraje();
		Array<int>* getPodielEkonomickychSkupin();
		Array<int>* getPodielVzdelanychSkupin();
		
	private:
		SortedSequenceTable<string, Kraj*>* kraje_;
		int pocetObyvatelov_;
		Array<int>* podielEkonomickychSkupin_;
		Array<int>* podielVzdelanychSkupin_;
	};

	
	inline Slovensko::Slovensko()
	{
		kraje_ = new SortedSequenceTable<string, Kraj*>();

		pocetObyvatelov_ = 0;

		podielEkonomickychSkupin_ = new Array<int>(3);

		podielVzdelanychSkupin_ = new Array<int>(8);

		for (int i = 0; i < 3; i++) {
			podielEkonomickychSkupin_->at(i) = 0;
		}

		for (int i = 0; i < 8; i++) {
			podielVzdelanychSkupin_->at(i) = 0;
		}

	}

	inline Slovensko::Slovensko(Slovensko& other)
	{
		kraje_ = new SortedSequenceTable<string, Kraj*>();

		for (auto item : *other.getKraje()) {
			Kraj* novyOkres = new Kraj(*item->accessData());
			kraje_->insert(item->getKey(), novyOkres);
		}

		pocetObyvatelov_ = other.getPocetObyvatelov();
		podielEkonomickychSkupin_ = new Array<int>(*other.getPodielEkonomickychSkupin());
		podielVzdelanychSkupin_ = new Array<int>(*other.getPodielVzdelanychSkupin());
	}

	inline Slovensko::~Slovensko()
	{
		for (auto item : *kraje_) {
			delete item->accessData();
		}

		delete kraje_;
		delete podielEkonomickychSkupin_;
		delete podielVzdelanychSkupin_;
	}

	inline SortedSequenceTable<string, Kraj*>* Slovensko::getKraje() {
		return kraje_;
	}

	inline Array<int>* Slovensko::getPodielEkonomickychSkupin()
	{
		return podielEkonomickychSkupin_;
	}

	inline Array<int>* Slovensko::getPodielVzdelanychSkupin()
	{
		return podielVzdelanychSkupin_;
	}

	inline void Slovensko::pridajKraje(LinkedList<string>* data)
	{
		while (data->size() > 1)
		{
			int code = stoi(data->removeAt(0));
			string title = data->removeAt(0);
			string note = data->removeAt(0);


			if (title != "Zahranicie") {
				Kraj* pridavanyKraj = new Kraj(code, title, note);

				string key = note.substr(5, 5);
				kraje_->insert(key, pridavanyKraj);
			}

			

		}

		
	}

	inline void Slovensko::pridakOkresy(LinkedList<string>* data) {
		for (auto kraj : *kraje_) {
			kraj->accessData()->pridajOkresy(data);
			SortedSequenceTable<int, Okres*>* okresy_ = kraj->accessData()->dajOkresy();
		}

	}

	inline void Slovensko::pridajObce(LinkedList<string>* data, SortedSequenceTable<string, Array<int>*>* dataOVeku, SortedSequenceTable<string, Array<int>*>* dataOVzdelani) {
		for (auto kraj : *kraje_) {
			
				kraj->accessData()->pridajObce(data, dataOVeku, dataOVzdelani);

				Array<int>* zoznamEkonomickychSkupinKraja = kraj->accessData()->getPodielEkonomickychSkupin();

				for (int i = 0; i < 3; i++) {
					podielEkonomickychSkupin_->at(i) += zoznamEkonomickychSkupinKraja->at(i);
				}

				Array<int>* zoznamVzdelanychSkupinKraja = kraj->accessData()->getPodielVzdelanychSkupin();

				for (int i = 0; i < 8; i++) {
					podielVzdelanychSkupin_->at(i) += zoznamVzdelanychSkupinKraja->at(i);
				}

				pocetObyvatelov_ += kraj->accessData()->getPocetObyvatelov();
			

		}

	}

	inline int Slovensko::getPocetObyvatelov()
	{
		return pocetObyvatelov_;
	}

}
