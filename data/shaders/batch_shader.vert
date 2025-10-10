#version 450 core

layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoords;
layout (location = 3) in float aTexIndex;

uniform mat4 camMatrix;
uniform mat4 model;

out vec4 vertexColor;
out vec2 texCoords;
out float texIndex;

void main() {
	texCoords = aTexCoords;
	texIndex = aTexIndex;
	vertexColor = vec4(aColor, 1.0);
	gl_Position = camMatrix * model * vec4(aPosition, 1.0);
}
