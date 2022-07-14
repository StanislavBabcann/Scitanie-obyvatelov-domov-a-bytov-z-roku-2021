#pragma once

#include <iostream>
#include <string>

using namespace std;

namespace filter {
	class Prislusnost {
	public:
		Prislusnost();
		string getPrislusnost();
		ArrayList<string*>* ponukniPrislusnostKraju(Slovensko* slovensko);
		ArrayList<string*>* ponukniPrislusnostOkresu(Slovensko* slovensko);
		void setPrislusnost(string prislusnost);
	private:
		string prislusnost_;

	};

	inline Prislusnost::Prislusnost() {
		prislusnost_ = "";
	}

	inline string Prislusnost::getPrislusnost() {
		return prislusnost_;
	}

	inline void Prislusnost::setPrislusnost(string prislusnost) {
		prislusnost_ = prislusnost;
	}
	inline ArrayList<string*>* Prislusnost::ponukniPrislusnostKraju(Slovensko* slovensko)
	{
		SortedSequenceTable<string, Kraj*>* kraje = slovensko->getKraje();
		ArrayList<string*>* zoznam = new ArrayList<string*>();

		cout << "Vyber kraj: " << endl;

		int counter = 1;
		for (auto kraj : *kraje) {
			cout << counter << ": " << kraj->accessData()->getTitle() << endl;
			counter++;
			zoznam->add(new string(kraj->accessData()->getTitle()));
		}

		return zoznam;
	}
	inline ArrayList<string*>* Prislusnost::ponukniPrislusnostOkresu(Slovensko* slovensko)
	{
		SortedSequenceTable<string, Kraj*>* kraje = slovensko->getKraje();
		ArrayList<string*>* zoznam = new ArrayList<string*>();

		cout << "Vyber okres: " << endl;
		int counter = 1;

		for (auto kraj : *kraje) {
			Kraj* aktualnyKraj = kraj->accessData();

			SortedSequenceTable<int, Okres*>* okresy = aktualnyKraj->dajOkresy();

			for (auto okres : *okresy) {
				string medzera = "  ";
				if (counter > 9) {
					medzera = " ";
				}
				cout << counter << medzera << okres->accessData()->getTitle() << endl;
				counter++;
				zoznam->add(new string(okres->accessData()->getTitle()));
			}
		}

		return zoznam;

	}
}
