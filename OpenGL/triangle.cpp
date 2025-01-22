#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

//vertex_shader
layout(location = 0) in vec3 aPos;

void main()
{
	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
}


//função do buffer_callback
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

//verifica se tecla está sendo pressionada
void verificar_input(GLFWwindow *window) 
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

int main()
{
	//função inicializadora
	glfwInit();
	//configuração de opções
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//limita os recursos ao opengl_core_profile
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//cria "objeto" janela
	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
	//mostra mensagem de erro se falha ao criar janela
	if (window == NULL) {
		std::cout << "Falha ao criar a janela" << std::endl;
		return -1;
	}
	//faz a janela o "contexto principal na thread
	glfwMakeContextCurrent(window);

	//verifica se o GLAD foi inicializado
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) 
	{
		std::cout << "Falha ao inicializar o GLAD" << std::endl;
		return -1;
	}

	//passa o tamanho da janela para o gl
	glViewport(0, 0, 800, 600);

	//função para reajustar janela
	void framebuffer_size_callback(GLFWwindow * window, int width, int height);

	//chama resize
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	//Cria vértices
	float vertices[] = {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f, 0.5f, 0.0f
	};

	//Cria vertex buffer object
	unsigned int VBO;
	glGenBuffers(1, &VBO);

	//bind o buffer ao VBO. GL_ARRAY_BUFFER "se torna" VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	

	//render loop. É aqui que roda tudo!
	while (!glfwWindowShouldClose(window)) {
		verificar_input(window);
		//limpa buffer de cor
		glClearColor(0.2f, 0.5f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	//finaliza programa
	glfwTerminate();

	return 0;
}
