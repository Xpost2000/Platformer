#ifndef RENDERBUFFER_H
#define RENDERBUFFER_H
#include "IObjectHandle.h"
#include "Comparable.h"

class Renderbuffer : public IObjectHandle, public Comparable<Renderbuffer>{
	public:
	Renderbuffer( const Renderbuffer& other ) = default;
	Renderbuffer();
	~Renderbuffer();
	const HandleType is_type() const { return HandleType::HANDLE_RENDERBUFFER; }
	bool operator > ( Renderbuffer rhs ){
		return true;
	}
	bool operator < ( Renderbuffer rhs ){
		return true;
	}
	bool operator >= ( Renderbuffer rhs ){
		return true;
	}
	bool operator <= ( Renderbuffer rhs ){
		return true;
	}
	bool operator == ( Renderbuffer rhs ){
		return (obj == rhs.obj); 
	}
	private:
};

#endif
