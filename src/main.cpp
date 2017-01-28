#include <iostream>
#include "display.hpp"
#include "keyboard.hpp"
#include "shader.hpp"
#include "index_buffer.hpp"
#include "vertex_array.hpp"
#include "exception.hpp"


int game_main()
{
	using namespace gp;
	
	Display display("Hello GProj", 800, 600);
	Shader shader("../shaders/simple.vs", "../shaders/simple.fs");
	shader.enable();


	GLfloat vertices[] {
		 0.5f, 0.5f, 0.0f,
		 0.5f,-0.5f, 0.0f,
		-0.5f,-0.5f, 0.0f,
		-0.5f, 0.5f, 0.0f
	};

	GLushort indices[] {
		0, 1, 3,
		2, 1, 3
	};


	VertexArray vao;
	VertexBuffer vbo(vertices, 4 * 3, 3);
	IndexBuffer ibo(indices, 6);
	vao.addBuffer(std::move(vbo), 0); 

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

