#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H
#include "Comparable.h"
#include <memory>
#include "IObjectHandle.h"

class IDevice;
class Shader;
class ShaderProgram : public IObjectHandle, public Comparable<ShaderProgram>{
	public:
		ShaderProgram(const ShaderProgram& other) = default;	
		ShaderProgram(const std::shared_ptr<IDevice> & device);
		ShaderProgram(const std::shared_ptr<IDevice> & device, Shader& a, Shader& b);
		ShaderProgram();
		~ShaderProgram();

		const HandleType is_type() const{ return HandleType::HANDLE_SHADERPROGRAM; }
		void set_linked(bool val) { linked = val; }
		void use();
		void unuse();
		void link();
		void attach(Shader&);
		void detach(Shader&);
		bool is_linked() { return linked; }

		bool operator > ( ShaderProgram rhs ) { return true;}
		bool operator < ( ShaderProgram rhs ) { return true;}
		bool operator >= ( ShaderProgram rhs ) { return true;}
		bool operator <= ( ShaderProgram rhs ) { return true; }
		bool operator == ( ShaderProgram rhs ) { return (obj == rhs.obj);}
	private:
		std::shared_ptr<IDevice> device = nullptr;
		bool linked = false;
};

#endif
