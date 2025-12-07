#include "graphics/mesh.h"

namespace limb {
namespace graphics {

Mesh::~Mesh() {
	if (m_ebo != 0)
		glDeleteBuffers(1, &m_ebo);

	if (m_vbo != 0)
		glDeleteBuffers(1, &m_vbo);

	if (m_vao != 0)
		glDeleteVertexArrays(1, &m_vao);
}

tl::expected<bool, std::string> Mesh::Init(const VertexLayout& layout, const std::vector<float>& vertex_data, const std::vector<unsigned int>& indices) {
	// m_vertex_count = vertex_data.size() / layout.components;
	m_index_count = static_cast<GLsizei>(indices.size());

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
	glBufferData(GL_ARRAY_BUFFER, vertex_data.size() * sizeof(float), vertex_data.data(), GL_STATIC_DRAW);

	if (!indices.empty()) {
		glGenBuffers(1, &m_ebo);
		if (m_ebo == 0) {
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindVertexArray(0);
			return tl::unexpected<std::string>("Failed to create EBO.");
		}
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);
	} else {
		m_ebo = 0;
	}

	for (const auto& attr : layout.attributes) {
		glEnableVertexAttribArray(attr.location);
		glVertexAttribPointer(
			attr.location,
			attr.components,
			attr.type,
			attr.normalized,
			layout.stride,
			(void*)attr.offset
		);
	}

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	if (m_ebo != 0) {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	return true;
}

} // namespace graphics
} // namespace limb
