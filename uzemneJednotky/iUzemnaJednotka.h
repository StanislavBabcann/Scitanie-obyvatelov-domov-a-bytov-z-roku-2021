#pragma once

#include <iostream>

using namespace std;

namespace uzemneJednotky {
	class IUzemnaJednotka {
	public:
		virtual ~IUzemnaJednotka() {};
		virtual string getTitle() = 0;
		virtual int getKriteriumVzdelaniePocet() = 0;
		virtual double getKriteriumVzdelaniePodiel() = 0;
		virtual int getKriteriumVekovaSkupinaPocet() = 0;
		virtual double getKriteriumVekovaSkupinaPodiel() = 0;
		virtual string vypisKriteria() = 0;
		virtual string getStringKey() = 0;
	};
}