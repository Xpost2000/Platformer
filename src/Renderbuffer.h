#ifndef RENDERBUFFER_H
#define RENDERBUFFER_H
#include "IObjectHandle.h"
#include "Comparable.h"
#include <memory>
class IDevice;
class Renderbuffer : public IObjectHandle, public Comparable<Renderbuffer>{
	public:
	Renderbuffer( const Renderbuffer& other ) = default;
	Renderbuffer( const std::shared_ptr<IDevice>& dev );
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
	std::shared_ptr<IDevice> device = nullptr;
};

#endif
