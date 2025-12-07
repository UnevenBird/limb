#ifndef LIMB_SHADER_H
#define LIMB_SHADER_H

#include <tl/expected.hpp>
#include "glad/glad.h"
#include <string>

#include "glm/vec2.hpp"
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"
#include "graphics/texture.h"

namespace limb {
namespace graphics {

class Shader {
public:
	Shader() = default;
	~Shader();

	tl::expected<bool, std::string> Init(const std::string& vertex, const std::string& fragment);
	bool SendUniform(const std::string& name, float value);
	bool SendUniform(const std::string& name, const glm::vec2& vec);
	bool SendUniform(const std::string& name, const glm::vec3& vec);
	bool SendUniform(const std::string& name, const glm::vec4& vec);
	bool SendUniform(const std::string& name, const Texture& texture);
	GLuint GetProgram() const;

private:
	GLuint m_program = 0;
};

} // namespace graphics
} // namespace limb

#endif // LIMB_SHADER_H
