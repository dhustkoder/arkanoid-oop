#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include "display.hpp"
#include "keyboard.hpp"
#include "shader.hpp"
#include "index_buffer.hpp"
#include "vertex_array.hpp"
#include "exception.hpp"


int game_main()
{
	using namespace gp;

	constexpr const int kWinWidth = 800;
	constexpr const int kWinHeight = 600;
	
	Display display("Hello GProj", kWinWidth, kWinHeight);
	Shader shader("../shaders/simple.vs", "../shaders/simple.fs");
	shader.enable();

	const glm::mat4 projection = glm::ortho(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);
	const glm::mat4 model = glm::translate(glm::mat4(1), glm::vec3(4, 3, 0));
	
	shader.setUniformMat4("projection", projection);
	shader.setUniformMat4("model", model);

	GLfloat vertices[] {
		0, 0, 0,
		0, 3, 0,
		8, 3, 0,
		8, 0, 0
	};

	GLushort indices[] {
		0, 1, 2,
		2, 3, 0
	};

	VertexArray vao;
	IndexBuffer ibo(indices, 6);
	vao.addBuffer(VertexBuffer(vertices, 4 * 3, 3), 0); 

	while (!display.shouldClose()) {
		display.clear(0.4f, 0, 0, 1);
		
		vao.enable();
		ibo.enable();
		glDrawElements(GL_TRIANGLES, ibo.getCount(), GL_UNSIGNED_SHORT, 0);
		ibo.disable();
		vao.disable();

		display.update();
	}

	return EXIT_SUCCESS;
}


int main()
{
	try  {
		int exitcode = game_main();
		return exitcode;
	} catch (gp::Exception& exception) {
		std::cerr << exception.what() << '\n';
	} catch (...) {
		std::cerr << "Unknown exception...\n";
	}

	return EXIT_FAILURE;
}

