#version 450 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 texCoord;

out vec3 fragColor;
uniform mat4 MVP;


void main(void) {
	gl_Position = MVP *  vec4(position, 1.0);
	fragColor = texCoord;
}