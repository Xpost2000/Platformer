#ifndef BUFFER_OBJECT_HANDLE_HPP
#define BUFFER_OBJECT_HANDLE_HPP
#include <memory>
#include "BufferTypes.h"
#include "BufferUsage.h"
#include "IObjectHandle.h"

class IDevice;
class Buffer : public IObjectHandle{
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
	void Bind(const BufferTypes target);
	void Unbind(const BufferTypes target);
	void BufferData( const BufferTypes target, size_t size, const GLvoid* data, const BufferUsage usage );
	const std::shared_ptr<IDevice>& get_device() { return device; }
	private:	
	std::shared_ptr<IDevice> device = nullptr;
};

#endif
