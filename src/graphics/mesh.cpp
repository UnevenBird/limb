#include "graphics/mesh.h"

namespace limb {
namespace graphics {

Mesh::Mesh() = default;

Mesh::~Mesh() {
	if (m_ebo != 0)
		glDeleteBuffers(1, &m_ebo);

	if (m_vbo != 0)
		glDeleteBuffers(1, &m_vbo);

	if (m_vao != 0)
		glDeleteVertexArrays(1, &m_vao);
}

tl::expected<bool, std::string> Mesh::Init(const std::vector<float>& vertices, const std::vector<unsigned int>& indices) {
	m_vertex_count = vertices.size() / 3;
	m_index_count = indices.size();

	glGenVertexArrays(1, &m_vao);
	if (m_vao == 0) {
		return tl::unexpected<std::string>("Failed to create VAO.");
	}
	glBindVertexArray(m_vao);

	glGenBuffers(1, &m_vbo);
	if (m_vbo == 0) {
		glBindVertexArray(0);
		return tl::unexpected<std::string>("Failed to create VBO.");
	}
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

	glGenBuffers(1, &m_ebo);
	if (m_ebo == 0) {
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
		return tl::unexpected<std::string>("Failed to create EBO.");
	}
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

	// layout(location = 0) vec3 position
	GLuint location = 0;
	GLint component_count = 3;
	GLenum attr_type = GL_FLOAT;
	GLboolean normalized = GL_FALSE;
	GLsizei stride = component_count * sizeof(float);
	const void* pointer = nullptr;

	glEnableVertexAttribArray(location);
	glVertexAttribPointer(location, component_count, attr_type, normalized, stride, pointer);

	glBindVertexArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	return true;
}

void Mesh::Render() const {
	if (m_vao == 0 || m_ebo == 0) return;
	glBindVertexArray(m_vao);
	glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(m_index_count), GL_UNSIGNED_INT, nullptr);
	// glBindVertexArray(0); // no need to unbind it every time
}

} // namespace graphics
} // namespace limb
