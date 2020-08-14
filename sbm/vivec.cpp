#include "pch.h"
#include "vivec.h"

using namespace std;

Vivec::Vivec(uint sz) : _sz{ sz } {
	v = vector<COORD>(sz);
}

void Vivec::push_back(COORD el) {
	if(_used < _sz)
		v[_used++] = std::move(el);
	else
		throw out_of_range("push_back OOR exc");
}

COORD Vivec::pop_front() {
	if (_used > 0) {
		--_used;
		return v[abeg()-1];
	}
	else
		throw out_of_range("pop_front OOR exc");
}

inline uint Vivec::sitlvl() {
	return _used % _sz;
}

inline uint Vivec::asitlvl() {
	if (_used < _sz)
		return _used++ % _sz;
	else
		throw out_of_range("asitlvl OOR exc");
}

inline uint Vivec::ssitlvl() {
	if (_used > 0)
		return _used-- % _sz;
	else
		throw out_of_range("ssitlvl OOR exc");
}

inline uint Vivec::abeg() {
	if (_beg < _sz - 1)
		return _beg++;
	else
		_beg = 0;
		return _sz - 1;
}

inline uint Vivec::sbeg() {
	if (_beg > 0)
		return _beg--;
	else
	{
		_beg = _sz - 1;
		return 0;
	}
}

inline COORD& Vivec::operator[](uint n) {
	uint acc = n + _beg;
	if (acc >= _sz)
		acc -= _sz;
	if (acc >= _used)
		throw out_of_range("subscript OOR exc");
	return v[acc];
}