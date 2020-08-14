#pragma once
#include "pch.h"

using namespace std;

class Vivec { // Virtually-infinite vector
	vector<COORD> v;
	uint _sz;
	uint _beg{ 0 };
	uint _used{ 0 };

	inline uint sitlvl();
	inline uint asitlvl();
	inline uint ssitlvl();

	inline uint abeg();
	inline uint sbeg();

public:
	Vivec(uint sz);
	inline COORD& operator[](uint n);
	COORD pop_front();
	void push_back(COORD el);
};