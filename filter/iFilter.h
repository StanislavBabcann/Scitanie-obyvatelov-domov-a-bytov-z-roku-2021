#pragma once
#include "../uzemneJednotky/slovensko.h"
#include "../filter/typUzemnejJednotky.h"


namespace filter {
	class IFIlter
	{
	public:
		virtual ~IFIlter() {};
		virtual Slovensko* vyfiltruj(Slovensko* filtrovanaMnozina, TypUzemnejJednotky* typUJ) = 0;
		virtual void vypisInfoOFiltri() = 0;
	};
}
