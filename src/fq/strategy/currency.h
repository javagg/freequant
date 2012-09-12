/*
 * Currency.h
 *
 *  Created on: 2012-6-25
 *      Author: alex
 */

#ifndef FQ_STRATEGY_CURRENCY_H
#define FQ_STRATEGY_CURRENCY_H

#include <iostream>
#include <memory>

#include "instrument.h"

namespace FreeQuant { namespace Strategy {

/*!
    \class Currency
    \brief The Currency class provides.

    \ingroup network
    \inmodule QtNetwork
*/
class Currency: public Instrument {
public:
	/*!
	    Constructs a QFtp object with the given \a parent.
	*/
//	explicit Currency();
	virtual ~Currency();

    //! currency name, e.g, "U.S. Dollar"
    const std::string& name() const;

	Currency(const Currency &obj);
    Currency &operator= (const Currency &);
	Currency &operator+ (const Currency &);
	Currency &operator-(const Currency &);
	Currency &operator* (const Currency &);
	Currency &operator/ (const Currency &);
	double value() const;

	struct Data;
//	std::shared_ptr<Data> data_;
};

Currency operator+(const Currency& x, const Currency& y);
Currency operator-(const Currency& x, const Currency& y);
Currency operator*(const Currency& x, const Currency& y);
Currency operator/(const Currency& x, const Currency& y);
bool operator== (const Currency& x, const Currency& y);
bool operator!= (const Currency& x, const Currency& y);
bool operator<=(const Currency& x, const Currency& y);
bool operator>=(const Currency& x, const Currency& y);
bool operator<(const Currency& x, const Currency& y);
bool operator>(const Currency& x, const Currency& y);
std::ostream &operator<<(std::ostream &os, const Currency &obj);
std::istream &operator>>(std::istream &is, Currency &obj);

}} /* namespace Bw */

#endif /* FQ_STRATEGY_CURRENCY_H */
