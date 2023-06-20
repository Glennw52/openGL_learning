#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTex;

out vec3 color;
out vec2 tex;

uniform mat4 transform;

void main()
{
   gl_Position = transform * vec4(aPos, 1.0);


//   color = vec3(1);
   // color = (aPos + 1) / 2;
   color = aColor;
   tex = aTex;
//   color = aColor * ((aPos + 1));
}