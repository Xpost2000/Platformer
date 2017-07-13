#ifndef COMPARABLE_TYPE_H
#define COMPARABLE_TYPE_H

template<typename T>
class Comparable{
	virtual bool operator >  ( T rhs ) = 0;
	virtual bool operator <  ( T rhs ) = 0;
	virtual bool operator >= ( T rhs ) = 0;
	virtual bool operator <= ( T rhs ) = 0;
	virtual bool operator == ( T rhs ) = 0;
};

#endif
