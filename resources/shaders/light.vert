#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec3 aColor;
layout (location = 3) in vec2 aTex;

out vec3 normal;
out vec3 color;
out vec2 tex;
out vec3 fragPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	gl_Position = projection * view * model * vec4(aPos, 1.0);
	normal = mat3(transpose(inverse(model))) * aNormal;
	color = aColor;
	tex = aTex;
	fragPos = vec3(model * vec4(aPos, 1.0));
}