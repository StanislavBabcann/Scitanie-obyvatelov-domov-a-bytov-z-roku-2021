#pragma once


#include <iostream>
#include <string>
#include <fstream>

#include "../structures/list/linked_list.h"
#include "../structures/array/array.h"
#include "../structures/table/sorted_sequence_table.h"



using namespace structures;
using namespace std;

namespace inputReader {

	class FileReader 
	{
	public:

		FileReader();

		LinkedList<string>* nacitajKraje();
		LinkedList<string>* nacitajOkresy();
		LinkedList<string>* nacitajObce();
		SortedSequenceTable<string, Array<int>*>* nacitajVek();
		SortedSequenceTable<string, Array<int>*>* nacitajVzdelanie();

	};

	inline FileReader::FileReader() {

	}

	inline LinkedList<string>* FileReader::nacitajKraje() {
		LinkedList<string>* loadedData = new LinkedList<string>();
		ifstream myFile;
		myFile.open("../inputData/kraje.csv");

		

		

		if (myFile.is_open()) {
			string line;
			getline(myFile, line);
		}

		if (myFile.is_open()) {
			while (myFile) {
				string line;
				getline(myFile, line);

				
				string word = "";
				int numberOfWords = 0;

				for (int i = 2; i < line.length(); i++) {
					if (line.at(i) != ';') {
						word += line.at(i);
					}
					else {
						if (word.length() != 0 && numberOfWords != 1) {
							loadedData->add(word);
							word = "";
						}
						else {
							word = "";
						}
						numberOfWords++;
					}
				}

				loadedData->add(word);

			}
		}

		return loadedData;
	}

	inline LinkedList<string>* FileReader::nacitajOkresy() {
		LinkedList<string>* loadedData = new LinkedList<string>();

		ifstream myFile;
		myFile.open("../inputData/okresy.csv");

		if (myFile.is_open()) {
			string line;
			getline(myFile, line);
		}

		if (myFile.is_open()) {
			while (myFile) {
				string line;
				getline(myFile, line);

				string word = "";

				int numberOfWords = 0;

				for (int i = 0; i < line.length(); i++) {
					if (line.at(i) != ';') {
						word += line.at(i);
					}
					else {
						if (numberOfWords != 0 && numberOfWords != 3 && numberOfWords != 4) {
							loadedData->add(word);
							word = "";
						}
						else {
							word = "";
						}

						numberOfWords++;
					}
				}

				loadedData->add(word);
			}
		}

		return loadedData;
	}

	inline LinkedList<string>* FileReader::nacitajObce() {
		LinkedList<string>* loadedData = new LinkedList<string>();

		ifstream myFile;
		myFile.open("../inputData/obce.csv");

		if (myFile.is_open()) {
			string line;
			getline(myFile, line);
		}

		if (myFile.is_open()) {
			while (myFile) {
				string line;
				getline(myFile, line);

				string word = "";

				
				int numberOfWords = 0;

				for (int i = 0; i < line.length(); i++) {
					if (line.at(i) != ';') {
						word += line.at(i);
					}
					else {
						if (numberOfWords != 0 && numberOfWords != 2 && numberOfWords != 4) {
							loadedData->add(word);
							word = "";
						}
						else {
							word = "";
						}

						numberOfWords++;
					}
				}

				loadedData->add(word);
			}
		}

		return loadedData;
	}

	inline SortedSequenceTable<string, Array<int>*>* FileReader::nacitajVek() {
		
		SortedSequenceTable<string, Array<int>*>* loadedData = new SortedSequenceTable<string, Array<int>*>();

		ifstream myFile;
		myFile.open("../inputData/vek.csv");

		if (myFile.is_open()) {
			string line;
			getline(myFile, line);
		}

		

		if (myFile.is_open()) {
			while (myFile) {
				
				Array<int>* nacitanyRiadok = new Array<int>(202);
				string line;
				getline(myFile, line);

				string word = "";


				int numberOfWords = 0;
				string key;
				int udaj;


				for (int i = 0; i < line.length(); i++) {
					if (line.at(i) != ';') {
						word += line.at(i);
					}
					else {
						
							if (numberOfWords == 0) {
								
								key = word.substr(3, 9);
								
							}
							else if (numberOfWords != 1){
								udaj = stoi(word);
								nacitanyRiadok->at(numberOfWords - 2) = udaj;
							}
						

						word = "";

						numberOfWords++;
					}
				}

				if (word.length() != 0) {
					udaj = stoi(word);
					nacitanyRiadok->at(numberOfWords - 2) = udaj;
					loadedData->insert(key, nacitanyRiadok);
				}
				else {
					delete nacitanyRiadok;
				}

				//nacitanyRiadok->at(numberOfWords - 2) = udaj;
				//loadedData->insert(key, nacitanyRiadok);


				
			}
		}

		return loadedData;
	}

	inline SortedSequenceTable<string, Array<int>*>* FileReader::nacitajVzdelanie() {

		SortedSequenceTable<string, Array<int>*>* loadedData = new SortedSequenceTable<string, Array<int>*>();

		ifstream myFile;
		myFile.open("../inputData/vzdelanie.csv");

		if (myFile.is_open()) {
			string line;
			getline(myFile, line);
		}

		
		if (myFile.is_open()) {
			
			while (myFile) {
				Array<int>* nacitanyRiadok = new Array<int>(8);

				

				string line;
				getline(myFile, line);

				string word = "";


				int numberOfWords = 0;
				string key;
				int udaj;

				for (int i = 0; i < line.length(); i++) {
					if (line.at(i) != ';') {
						word += line.at(i);
					}
					else {
						
							if (numberOfWords == 0) {
								
								key = word.substr(3, 9);
								

								
							}
							else if (numberOfWords != 1) {
								udaj = stoi(word);
								nacitanyRiadok->at(numberOfWords - 2) = udaj;
							}
						

						word = "";

						numberOfWords++;
					}
				}

				if (word.length() != 0) {
					udaj = stoi(word);
					nacitanyRiadok->at(numberOfWords - 2) = udaj;
					loadedData->insert(key, nacitanyRiadok);
				}
				else {
					delete nacitanyRiadok;
				}

				
				
			}
		}

		return loadedData;
	}
}