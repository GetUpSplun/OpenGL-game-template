#version 450 core

out vec4 FragColor;

in vec4 vertexColor;
in vec2 texCoords;
in float texIndex;

uniform sampler2D texID;

void main() {
	int index = int(texIndex);

	FragColor = texture(texID, texCoords) * vertexColor;
}
