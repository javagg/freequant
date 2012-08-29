/*
 * Currency.h
 *
 *  Created on: 2012-6-25
 *      Author: alex
 */

#ifndef CURRENCY_H
#define CURRENCY_H

#include <iostream>
#include <memory>

#include "instrument.h"

namespace xh {

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
	std::shared_ptr<Data> data_;
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

} /* namespace Bw */

#endif /* CURRENCY_H */
