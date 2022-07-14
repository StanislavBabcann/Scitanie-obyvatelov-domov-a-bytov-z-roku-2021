
#include <iostream>
#include <string>
#include <fstream>

#include "../structures/heap_monitor.h"
#include "../structures/list/linked_list.h"
#include "../structures/table/sorted_sequence_table.h"
#include "../inputReader/file_reader.h"
#include "../uzemneJednotky/slovensko.h"
#include "../uzemneJednotky/obec.h"
#include "../bodoveVyhladavanie/bodove_vyhladavanie.h"
#include "../filter/vzdelanie_pocet.h"
#include "../filter/vzdelanie_podiel.h"
#include "../filter/filtrovanie.h"
#include "../userInterface/user_interface.h"

using namespace std;
using namespace structures;
using namespace inputReader;
using namespace uzemneJednotky;
using namespace bodoveVyhladavanie;
using namespace filter;
using namespace userInterface;



int main() {
	initHeapMonitor();

	FileReader* myReader = new inputReader::FileReader();
	LinkedList<string>* nacitaneDataOKrajoch = myReader->nacitajKraje();
	
	Slovensko* slovensko = new Slovensko();
	slovensko->pridajKraje(nacitaneDataOKrajoch);

	LinkedList<string>* nacitaneDataOOkresoch = myReader->nacitajOkresy();
	slovensko->pridakOkresy(nacitaneDataOOkresoch);

	LinkedList<string>* nacitaneDataOObciach = myReader->nacitajObce();

	SortedSequenceTable<string, Array<int>*>* dataOVeku = myReader->nacitajVek();
	SortedSequenceTable<string, Array<int>*>* dataOVzdelani = myReader->nacitajVzdelanie();

	slovensko->pridajObce(nacitaneDataOObciach, dataOVeku, dataOVzdelani);

	UserInterface* userInt = new UserInterface(slovensko);
	userInt->uvod();

	delete userInt;
	

	delete nacitaneDataOKrajoch;
	delete nacitaneDataOOkresoch;
	delete nacitaneDataOObciach;
	delete dataOVeku;
	delete dataOVzdelani;

	delete myReader;



	return 0;
}