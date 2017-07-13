#ifndef OBJECT_HANDLE_HPP
#define OBJECT_HANDLE_HPP
#include <GL/glew.h> // For the typedefs.
#include "ObjectTypes.h"

/*
 * Abstract class for type safe OpenGL object handles.
 *
 * It's actually extremely bare bones and all the classes that derive from this
 * are pretty much just differently name objects.
 */
class IObjectHandle
{
public:
	/*
	 * Remove Constructor and destructor. Let the derived handle themselves.
	 */
	//IObjectHandle();
	//virtual ~IObjectHandle() = 0;
	virtual const HandleType is_type() const = 0;
	GLuint& get_handle() { return obj; }

protected:
	GLuint obj = 0;
	/* data */
};
#endif
