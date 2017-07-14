#ifndef COMPARABLE_TYPE_H
#define COMPARABLE_TYPE_H

/*
	an abstract class that can be treated like a property of a class.
	All derived from this will have the ability to be compared with each
	other of the same type
*/

template<typename T>
class Comparable{
	virtual bool operator >  ( T rhs ) = 0;
	virtual bool operator <  ( T rhs ) = 0;
	virtual bool operator >= ( T rhs ) = 0;
	virtual bool operator <= ( T rhs ) = 0;
	virtual bool operator == ( T rhs ) = 0;
};

#endif
