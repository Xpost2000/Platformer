#ifndef BUFFER_OBJECT_HANDLE_HPP
#define BUFFER_OBJECT_HANDLE_HPP
#include <memory>
#include "BufferTypes.h"
#include "BufferUsage.h"
#include "IObjectHandle.h"
#include "Comparable.h"

/*
	Buffer class.
	
	Mostly intended to be an OpenGL buffer wrapper.
	easy usage and almost 1 - 1 function call coorelation
*/

class IDevice;
class Buffer : public IObjectHandle, public Comparable<Buffer>{
	public:
	Buffer(const Buffer&) = default; // No copy constructors wanted.
	Buffer(const std::shared_ptr<IDevice>& dev);
	Buffer();
	~Buffer();
	void set_device(const std::shared_ptr<IDevice>& dev);
	const HandleType is_type() const { return HandleType::HANDLE_BUFFER; }
	/*
	 * Implement visitor pattern methods.
	 */
	// Visitor stuff here.
	// And this class is the visitor.
	void bind(const BufferTypes target);
	void unbind(const BufferTypes target);
	void bufferData( const BufferTypes target, size_t size, const GLvoid* data, const BufferUsage usage );
	const std::shared_ptr<IDevice>& get_device() { return device; }
	bool operator >  ( Buffer rhs )  { return true; }
	bool operator <  ( Buffer rhs )  { return true; }
	bool operator >= ( Buffer rhs ) { return true; }
        bool operator <= ( Buffer rhs ) { return true; }
	bool operator == ( Buffer rhs ) {return ( obj == rhs.obj );}
	private:	
	std::shared_ptr<IDevice> device = nullptr;
};

#endif
