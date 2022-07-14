#pragma once

namespace filter {
	class TypUzemnejJednotky {
	public:
		TypUzemnejJednotky(int typUzemnejJednotky);
		int getTyp();
		void setTyp(int typUzemnejJednotky);

	private:
		int typ_;
	};

	inline TypUzemnejJednotky::TypUzemnejJednotky(int typUzemnejJednotky)
	{
		typ_ = typUzemnejJednotky;
	}

	inline int TypUzemnejJednotky::getTyp() {
		return typ_;
	}

	inline void TypUzemnejJednotky::setTyp(int typUzemnejJednotky) {
		typ_ = typUzemnejJednotky;
	}
}
