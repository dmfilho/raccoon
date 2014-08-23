/*
 * axe_uf8.h
 *
 *  Created on: Apr 15, 2014
 *      Author: Dimas Melo Filho
 */

#ifndef AXE_UTF8_H_
#define AXE_UTF8_H_

#include <axe.h>
#include <climits>

namespace axe {
template<class T>
class r_utf8_t AXE_RULE
{
	T low;
	T high;
public:
	explicit r_utf8_t(T low, T high) : low(low), high(high) {}
	explicit r_utf8_t() : low(0), high(UINT_MAX) {}

	template<class Iterator>
	axe::result<Iterator> operator()(Iterator i1, Iterator i2) const
	{
		bool matched = false;
		unsigned int c = 0;
		int inc = 0;
		if (i1 != i2) {
			if ((*i1 & 0x80) == 0) { // single byte
				c = (unsigned int)*i1;
				inc = 1;
			} else if ((*i1 & 0xFE) == 0xFC) { // 6 bytes
				c = (*i1 & 0x01); c <<= 6;
				c |= (*(i1+1) & 0x3F); c <<= 6;
				c |= (*(i1+2) & 0x3F); c <<= 6;
				c |= (*(i1+3) & 0x3F); c <<= 6;
				c |= (*(i1+4) & 0x3F); c <<= 6;
				c |= (*(i1+5) & 0x3F);
				inc = 6;
			} else if ((*i1 & 0xFC) == 0xF8) { // 5 bytes
				c = (*i1 & 0x03); c <<= 6;
				c |= (*(i1+1) & 0x3F); c <<= 6;
				c |= (*(i1+2) & 0x3F); c <<= 6;
				c |= (*(i1+3) & 0x3F); c <<= 6;
				c |= (*(i1+4) & 0x3F);
				inc = 5;
			} else if ((*i1 & 0xF8) == 0xF0) { // 4 bytes
				c = (*i1 & 0x07); c <<= 6;
				c |= (*(i1+1) & 0x3F); c <<= 6;
				c |= (*(i1+2) & 0x3F); c <<= 6;
				c |= (*(i1+3) & 0x3F);
				inc = 4;
			} else if ((*i1 & 0xF0) == 0xE0) { // 3 bytes
				c = (*i1 & 0x0F); c <<= 6;
				c |= (*(i1+1) & 0x3F); c <<= 6;
				c |= (*(i1+2) & 0x3F);
				inc = 3;
			} else if ((*i1 & 0xE0) == 0xC0) { // 2 bytes
				c = (*i1 & 0x1F); c <<= 6;
				c |= (*(i1+1) & 0x3F);
				inc = 2;
			}
			matched = true;
		}
		return axe::make_result(matched, i1 + inc, i1);
	}
};

class r_utf8v_t AXE_RULE
{
	unsigned int low;
	unsigned int high;
public:
	explicit r_utf8v_t(unsigned int low, unsigned int high) : low(low), high(high) {}
	explicit r_utf8v_t() : low(0), high(UINT_MAX) {}

	template<class Iterator>
	axe::result<Iterator> operator()(Iterator i1, Iterator i2) const
	{
		bool matched = false;
		unsigned int c = 0;
		int inc = 0;
		if (i1 != i2) {
			if ((*i1 & 0x80) == 0) { // single byte
				c = (unsigned int)*i1;
				inc = 1;
			} else if ((*i1 & 0xFE) == 0xFC) { // 6 bytes
				c = (*i1 & 0x01); c <<= 6;
				c |= (*(i1+1) & 0x3F); c <<= 6;
				c |= (*(i1+2) & 0x3F); c <<= 6;
				c |= (*(i1+3) & 0x3F); c <<= 6;
				c |= (*(i1+4) & 0x3F); c <<= 6;
				c |= (*(i1+5) & 0x3F);
				inc = 6;
			} else if ((*i1 & 0xFC) == 0xF8) { // 5 bytes
				c = (*i1 & 0x03); c <<= 6;
				c |= (*(i1+1) & 0x3F); c <<= 6;
				c |= (*(i1+2) & 0x3F); c <<= 6;
				c |= (*(i1+3) & 0x3F); c <<= 6;
				c |= (*(i1+4) & 0x3F);
				inc = 5;
			} else if ((*i1 & 0xF8) == 0xF0) { // 4 bytes
				c = (*i1 & 0x07); c <<= 6;
				c |= (*(i1+1) & 0x3F); c <<= 6;
				c |= (*(i1+2) & 0x3F); c <<= 6;
				c |= (*(i1+3) & 0x3F);
				inc = 4;
			} else if ((*i1 & 0xF0) == 0xE0) { // 3 bytes
				c = (*i1 & 0x0F); c <<= 6;
				c |= (*(i1+1) & 0x3F); c <<= 6;
				c |= (*(i1+2) & 0x3F);
				inc = 3;
			} else if ((*i1 & 0xE0) == 0xC0) { // 2 bytes
				c = (*i1 & 0x1F); c <<= 6;
				c |= (*(i1+1) & 0x3F);
				inc = 2;
			}
			matched = (c >= low && c <= high);
		}
		return axe::make_result(matched, i1 + inc, i1);
	}
};

inline axe::r_pred_t<r_utf8v_t> r_any8()
{ return r_utf8v_t(); }

template<class T>
inline axe::r_pred_t<r_utf8_t<T>> r_any8(T from, T to)
{ return r_utf8_t<T>(from, to); }

template<class T>
inline axe::r_pred_t<r_utf8_t<T>> r_any8(T c)
{ return r_utf8_t<T>(c, c); }


}; /* namespace axe */

#endif /* AXE_UTF8_H_ */
