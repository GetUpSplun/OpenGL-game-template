#include "shader.hpp"

std::string getFileContents(std::string filepath) {
	std::ifstream file(filepath);
	if (!file) {
		std::cerr << "Failed to open file." << std::endl;
	} else {
		std::string line, contents;
		while (std::getline(file, line)) {
			contents += line;
			contents += "\n";
		}
		return contents;
	}
	file.close();
}

GL::Shader::Shader(std::string vertex_shader_filepath, std::string fragment_shader_filepath) {
	ID = glCreateProgram();

	{
		std::string vertexCode = getFileContents(vertex_shader_filepath);
		const char* vertexSource = vertexCode.c_str();

		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &vertexSource, NULL);
		glCompileShader(vertexShader);

		GLint result;
		char infoLog[1024] = "";

		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &result);
		if (result == GL_FALSE) {
			glGetShaderInfoLog(vertexShader, 1024, NULL, infoLog);
			std::cout << "Failed to compile vertex shader: " << infoLog << std::endl;
		}

		glAttachShader(ID, vertexShader);

		glDeleteShader(vertexShader);
	}
	{
		std::string fragmentCode = getFileContents(fragment_shader_filepath);
		const char* fragmentSource = fragmentCode.c_str();

		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
		glCompileShader(fragmentShader);

		GLint result;
		char infoLog[1024] = "";

		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &result);
		if (result == GL_FALSE) {
			glGetShaderInfoLog(fragmentShader, 1024, NULL, infoLog);
			std::cout << "Failed to compile fragment shader: " << infoLog << std::endl;
		}

		glAttachShader(ID, fragmentShader);

		glDeleteShader(fragmentShader);
	}

	glLinkProgram(ID);

	GLint result;
	char infoLog[1024];

	glGetShaderiv(ID, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE) {
		glGetShaderInfoLog(ID, 1024, NULL, infoLog);
		std::cout << "Failed to link shader: " << infoLog << std::endl;
	}
}

GL::Shader::~Shader() {
	glDeleteProgram(ID);
}

void GL::Shader::bind() {
	glUseProgram(ID);
}

void GL::Shader::unbind() {
	glUseProgram(0);
}
