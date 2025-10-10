#version 450 core

out vec4 FragColor;

in vec2 texCoords;

uniform sampler2D texID;
uniform vec3 texColor;

void main() {
	FragColor = vec4(texColor, 1.0) * vec4(1.0, 1.0, 1.0, texture(texID, texCoords).r);
}
