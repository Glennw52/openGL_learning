#include "Cube.hpp"
#include <iostream>
#include <string.h>
#include <cstring>

static GLfloat base_vertices[] = {
	-1.0f, -1.0f, 1.0f, // bottom left front 	0
	1.0f, -1.0f, 1.0f, // bottom right front 	1
	-1.0f, 1.0f, 1.0f, // top left front 		2
	1.0f, 1.0f, 1.0f, // top right front 		3
	-1.0f, 1.0f, -1.0f, // top left back 		4
	1.0f, 1.0f, -1.0f, // top right back 		5
	-1.0f, -1.0f, -1.0f, // bottom left back	6
	1.0f, -1.0f, -1.0f // bottom right back		7
};
static glm::vec3 v3_base_vertices[] = {
	glm::vec3(-1.0f, -1.0f, 1.0f), // bottom left front 	0
	glm::vec3(1.0f, -1.0f, 1.0f), // bottom right front 	1
	glm::vec3(-1.0f, 1.0f, 1.0f), // top left front 		2
	glm::vec3(1.0f, 1.0f, 1.0f), // top right front 		3
	glm::vec3(-1.0f, 1.0f, -1.0f), // top left back 		4
	glm::vec3(1.0f, 1.0f, -1.0f), // top right back 		5
	glm::vec3(-1.0f, -1.0f, -1.0f), // bottom left back	6
	glm::vec3(1.0f, -1.0f, -1.0f) // bottom right back		7
};

// cube
static GLuint mesh_indices[] = {
	1, 3, 2, 0, 1, 2,	// front
	4, 6, 0, 4,			// left
	5, 3, 2, 5,			// top
	7, 6, 4, 7,			// back
	1, 3, 5, 1,			// right
	0, 6, 7				// bottom
};

// static GLuint frame_indices[] = {
// 	4, 5, 6, 4, // back bottom triangle
// 	6, 7, 7, 5, // back top triangle
// 	6, 0, // left top triangle
// 	2, 4, // left bottom triangle
// 	7, 1, // right bottom triangle
// 	3, 5, // right top triangle
// 	0, 1, 2, 0, // front bottom triangle
// 	2, 3, 3, 1 // front top triangle
// };

static void matmul(GLfloat matrix[3][3], GLfloat *in, GLfloat *out)
{
	GLfloat temp[3];
	for (uint i = 0; i < 3; ++i)
		temp[i] = in[0] * matrix[0][i] + in[1] * matrix[1][i] + in[2] * matrix[2][i];
	for (uint i = 0; i < 3; ++i)
		out[i] = temp[i];
}

void Cube::Delete(void)
{
	this->_VAO.Delete();
	this->_VBO.Delete();
	this->_EBO.Delete();
	delete [] this->_draw_buffer;
}

void	Cube::Clear(void)
{
	std::memcpy(this->_draw_buffer, base_vertices, sizeof(base_vertices));
}

void	Cube::Transform(GLfloat mat[3][3])
{
	for (size_t i = 0; i < sizeof(base_vertices) / sizeof(GLfloat); i += 3)
	{
		matmul(mat, &this->_draw_buffer[i], &this->_draw_buffer[i]);
	}
}

void	Cube::DrawMesh(GLfloat dist)
{
	for (size_t i = 0; i < sizeof(base_vertices) / sizeof(GLfloat); i += 3)
	{
		GLfloat z = 1 / (dist - _draw_buffer[i + 2]);
		GLfloat projection[3][3] = {
			{z, 0, 0},
			{0, z, 0},
			{0, 0, 0}
		};
		matmul(projection, &this->_draw_buffer[i], &this->_draw_buffer[i]);
	}
	this->_VAO.Bind();
	this->_VBO.Update(this->_draw_buffer, sizeof(base_vertices));
	glDrawElements(GL_LINE_STRIP, sizeof(mesh_indices), GL_UNSIGNED_INT, 0);
	this->_VAO.Unbind();

}
void	Cube::DrawFrame(GLfloat dist)
{
	for (size_t i = 0; i < sizeof(base_vertices) / sizeof(GLfloat); i += 3)
	{
		GLfloat z = 1 / (dist - _draw_buffer[i + 2]);
		GLfloat projection[3][3] = {
			{z, 0, 0},
			{0, z, 0},
			{0, 0, 0}
		};
		matmul(projection, &this->_draw_buffer[i], &this->_draw_buffer[i]);
	}
	this->_VAO.Bind();
	this->_VBO.Update(this->_draw_buffer, sizeof(base_vertices));
	glDrawElements(GL_LINES, sizeof(mesh_indices), GL_UNSIGNED_INT, 0);
	this->_VAO.Unbind();

}

Cube::Cube(glm::vec3 coords, GLfloat size): _coords(coords), _size(size)
{
	this->_draw_buffer = new GLfloat[sizeof(base_vertices)];
	// _size = 0;
	this->Clear();
	this->_VAO.Bind();
	this->_VBO = VBO(this->_draw_buffer, sizeof(base_vertices));
	this->_EBO = EBO(mesh_indices, sizeof(mesh_indices));
	this->_VAO.LinkAtr(this->_VBO, 0, 3, GL_FLOAT, 3 * sizeof(float), (void *)0);
	this->_VAO.Unbind();
	this->_VBO.Unbind();
	this->_EBO.Unbind();
}

Cube::~Cube()
{
}

// Cube	&Cube::operator=(Cube const &rhs)
// {
// 	(void)rhs;
// 	return (*this);
// }

// Cube::Cube(Cube const &src)
// {
// 	*this = src;
// }
