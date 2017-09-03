#ifndef TEXT_SHADER_SET_H
#define TEXT_SHADER_SET_H
#include "IDevice.h"
#include "IShaderSet.h"
#include "matrix_typedef.h"
#include <glm/glm.hpp>
class ShaderUniform;
/*
 * This is the test shader I used for 
 * "Mountainy Mountains".
 *
 * I used this to test the IShaderSet interface
 * to (technically) reduce the amount of code written
 * in the main function.
 */
class TextShader : public IShaderSet{
	public:
	TextShader(const std::shared_ptr<IDevice> &dev);
	~TextShader();
	void SetMatrices( glm::mat4 proj, glm::mat4 view );
	void setTex( int index=0 );
	void viewMatrixActive( bool move=true );
	private:
	ShaderUniform* projection_uniform=nullptr;
	ShaderUniform* view_uniform=nullptr;
	ShaderUniform* view_active_uniform=nullptr;
	ShaderUniform* tex_uniform=nullptr;
	std::shared_ptr<IDevice> device = nullptr;
};

#endif
