#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H
#include "IObjectHandle.h"
#include "Comparable.h"

class Framebuffer : public IObjectHandle, public Comparable<Framebuffer> {
	public:
		Framebuffer( const Framebuffer& other ) = default;
		Framebuffer();
		~Framebuffer();
		const HandleType is_type() const { return HandleType::HANDLE_FRAMEBUFFER; }
		bool operator > ( Framebuffer rhs ){
			return true;
		}
		bool operator < ( Framebuffer rhs ){
			return true;
		}
		bool operator >= ( Framebuffer rhs ){
			return true;
		}
		bool operator <= ( Framebuffer rhs ){
			return true;
		}
		bool operator == ( Framebuffer rhs ){
			return (obj == rhs.obj);
		}
	private:
};

#endif
