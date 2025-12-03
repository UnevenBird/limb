#ifndef LIMB_SHADER_H
#define LIMB_SHADER_H

#include "glad/glad.h"
#include <tl/expected.hpp>
#include <string>

namespace limb {
namespace graphics {

class Shader {
public:
	Shader();
	~Shader();

	tl::expected<bool, std::string> Init(const std::string& vertex, const std::string& fragment);
	GLuint GetProgram() const;

private:
	GLuint m_program = 0;
};

} // namespace graphics
} // namespace limb

#endif // LIMB_SHADER_H
