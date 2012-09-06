/*
 * Signal.h
 *
 *  Created on: 2012-6-25
 *      Author: Alex Lee
 */

#ifndef SIGNAL_H
#define SIGNAL_H

#include <string>

namespace FreeQuant {

class Signal {
public:
	/*!
	    \enum Signal::Type

	    This enum identifies the error that occurred.

	    \value Peak No error occurred.
	    \value Vallqy The host name lookup failed.
	    \value Crossover The server refused the connection.
	    \value Threshold Tried to send a command, but there is no connection to a server.
	    \value Comparison An error other than those specified above occurred.
	    \value Formula An error other than those specified above occurred.

	    \sa error()
	*/
	enum Type { Peak, Vallqy, Crossover, Threshold, Comparison, Formula };

	explicit Signal();
	virtual ~Signal();
	std::string name() const;

private:
	std::string mName;
};

} /* namespace FreeQuant */

#endif /* SIGNAL_H */
