#ifndef LIMB_MESH_H
#define LIMB_MESH_H

#include "glad/glad.h"
#include <tl/expected.hpp>
#include <string>

namespace limb {
namespace graphics {

class Mesh {
public:
	Mesh();
	~Mesh();

    tl::expected<bool, std::string> Init(const std::vector<float>& vertices, const std::vector<unsigned int>& indices);
	void Render() const;

private:
    GLuint m_vbo = 0;
    GLuint m_vao = 0;
    GLuint m_ebo = 0;
    size_t m_vertex_count = 0;
    size_t m_index_count = 0;
};

} // namespace graphics
} // namespace limb

#endif // LIMB_MESH_H
