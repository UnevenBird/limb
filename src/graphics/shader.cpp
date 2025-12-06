#include "graphics/shader.h"
#include <glm/gtc/type_ptr.hpp>
#include <vector>

namespace limb {
namespace graphics {

Shader::Shader() = default;

Shader::~Shader() {
	if (m_program != 0)
		glDeleteProgram(m_program);
}

static std::string GetShaderLog(GLuint obj, bool is_program) {
	GLint length = 0;
	if (is_program)	{
		glGetProgramiv(obj, GL_INFO_LOG_LENGTH, &length);
	} else {
		glGetShaderiv(obj, GL_INFO_LOG_LENGTH, &length);
	}

	if (length <= 1) return std::string();

	std::vector<char> char_buf(length);
	if (is_program) {
		glGetProgramInfoLog(obj, length, nullptr, char_buf.data());
	} else {
		glGetShaderInfoLog(obj, length, nullptr, char_buf.data());
	}

	return std::string(char_buf.data(), char_buf.data() + length);
}

static std::pair<GLint, GLuint> CompileShader(const char* code, GLenum type) {
	GLuint shader = glCreateShader(type);
	glShaderSource(shader, 1, &code, nullptr);
	glCompileShader(shader);

	GLint status = GL_FALSE;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	return std::make_pair(status, shader);
}

tl::expected<bool, std::string> Shader::Init(const std::string& vertex_src, const std::string& fragment_src) {
	// compile vertex sahder
	auto vertex_result = CompileShader(vertex_src.c_str(), GL_VERTEX_SHADER);
	auto vertex_shader = vertex_result.second;
	if (vertex_result.first != GL_TRUE) {
		std::string log = GetShaderLog(vertex_shader, false);
		return tl::unexpected<std::string>("Vertex shader: " + log);
	}

	// compile fragment shader
	auto fragment_result = CompileShader(fragment_src.c_str(), GL_FRAGMENT_SHADER);
	auto fragment_shader = fragment_result.second;
	if (fragment_result.first != GL_TRUE) {
		std::string log = GetShaderLog(fragment_shader, false);
		return tl::unexpected<std::string>("Fragment shader: " + log);
	}

	// create program
	m_program = glCreateProgram();
	if (m_program == 0) {
		glDeleteShader(vertex_shader);
		glDeleteShader(fragment_shader);
		return tl::unexpected<std::string>("Shader program creation failed.");
	}

	// link shaders
	glAttachShader(m_program, vertex_shader);
	glAttachShader(m_program, fragment_shader);
	glLinkProgram(m_program);

	// check for linking errors
	GLint status = GL_FALSE;
	glGetProgramiv(m_program, GL_LINK_STATUS, &status);
	if (status != GL_TRUE) {
		glDeleteProgram(m_program);
		glDeleteShader(vertex_shader);
		glDeleteShader(fragment_shader);

		std::string log = GetShaderLog(fragment_shader, false);
		return tl::unexpected<std::string>(log);
	}

	glDetachShader(m_program, vertex_shader);
	glDetachShader(m_program, fragment_shader);
	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);

	return true;
}

bool Shader::SendUniform(const std::string& name, float value) {
	GLint loc = glGetUniformLocation(m_program, name.c_str());
	if (loc == -1) return false;
	// glUseProgram(m_program);
	glUniform1f(loc, value);
	return true;
}

bool Shader::SendUniform(const std::string& name, const glm::vec2& vec) {
	GLint loc = glGetUniformLocation(m_program, name.c_str());
	if (loc == -1) return false;
	// glUseProgram(m_program);
	glUniform2fv(loc, 1, glm::value_ptr(vec));
	return true;
}

bool Shader::SendUniform(const std::string& name, const glm::vec3& vec) {
	GLint loc = glGetUniformLocation(m_program, name.c_str());
	if (loc == -1) return false;
	// glUseProgram(m_program);
	glUniform3fv(loc, 1, glm::value_ptr(vec));
	return true;
}

bool Shader::SendUniform(const std::string& name, const glm::vec4& vec) {
	GLint loc = glGetUniformLocation(m_program, name.c_str());
	if (loc == -1) return false;
	// glUseProgram(m_program);
	glUniform4fv(loc, 1, glm::value_ptr(vec));
	return true;
}

GLuint Shader::GetProgram() const {
	return m_program;
}

} // namespace graphics
} // namespace limb
