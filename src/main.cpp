#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<stb/stb_image.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

#include"Texture.h"
#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"
#include "zebatki.h"

using namespace std;

const unsigned int WTDH = 640;      // wysokosc okna
const unsigned int HGHT = 480;      // szserokosc okna

int main()
{
    // Inicjalizja GLFW i informacja dla programu,
    // ze uzywamy OpenGL 3.3 i pofilu core

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Tworzenie oka o nazwie "Zebatki" i testowanie czy
	// sworzenie okna udalo sie
	GLFWwindow* window = glfwCreateWindow(WTDH, HGHT, "Zebatki", NULL, NULL);
	if (window == NULL)
	{
	    // Jezeli nie program wypisuje informacje o bledzie
		cout << "ERROR: Failed to create GLFW window" << endl;
		glfwTerminate();
		return -1;
	}

	// Konfiguracja okna i widoku
	// Ladowanie biblioteki GLAD w celu konfiguracji OpenGL
	// Dostrajanie widoku, czyli tego co "widzi" nasza "kamera"
	// Do poprawnego dostrojenia widoku potrzebne sa wysokosc i szerokosc okna
	glfwMakeContextCurrent(window);
	gladLoadGL();
	glViewport(0, 0, WTDH, HGHT);

	// Tworzenie shaderow przy uzyciu plikow default.vert i default.frag
	Shader shaderProgram("default.vert", "default.frag");

    // Generacja zebatek
	int rozP, rozT;
	float *punkty = NULL;
    unsigned int *trojkaty = NULL;

    // Zebatka numer 1

    // Punkty
    punkty = genGearPoints(0.0, 0.0, 0.0, 0.1, 12, &rozP);
    GLfloat vertices_1[784] = {0};    // Liczba zebow to 12
    for(int i=0;i<rozP;i++)         // 784 = 8 * (12 * 4 + 1) * 2
    {
        vertices_1[i] = punkty[i];
    }

    // Trojkoty
    trojkaty = genGearTriangles(12, &rozT);
    GLuint indices_1[576] = {0};      // Liczba zebow to 12
    for(int i=0;i<rozT;i++)         // 288 = 3 * (12 * 4) * 2
    {
        indices_1[i] = trojkaty[i];
    }

    // Debugowanie - informacje o rozmiarze tblicy
    // przechowujacej punktty i trojkaty wchodzace
    // w sklad modelu zebatki
    cout << "Zebatka numer 1:" << endl;
    cout << "  vertices:\t" << rozP << endl;
    cout << "  indices:\t" << rozT << endl;
    cout << " Liczba:" << endl;
    cout << "  punktow:\t" << rozP/8 << endl;
    cout << "  trojkatow:\t" << rozT/3 << endl;

// Zebatka numer 2
// Chwilowo nie dziala
/*
    punkty = genGearPoints(0.0, 0.0, 0.0, 0.1, 8, &rozP);

    GLfloat vertices_2[528] = {0};    // Liczba zebow to 8
    for(int i=0;i<rozP;i++)         // 528 = 8 * (8 * 4 + 1) * 2
    {
        vertices_2[i] = punkty[i];
    }

    trojkaty = genGearTriangles(8, &rozT);

    GLuint indices_2[384] = {0};      // Liczba zebow to 8
    for(int i=0;i<rozT;i++)         // 384 = 3 * (8 * 4) * 2
    {
        indices_2[i] = trojkaty[i];
    }

    // Debugowanie
    cout << "Zebatka numer 2:" << endl;
    cout << "  vertices:\t" << rozP << endl;
    cout << "  indices:\t" << rozT << endl;
    cout << " Liczba:" << endl;
    cout << "  punktow:\t" << rozP/8 << endl;
    cout << "  trojkatow:\t" << rozT/3 << endl;
*/

	// Twrzeie tablicy puktow
	VAO VAO1;
	VAO1.Bind();

	// Tworzenie i podlaczanie buforow puntow i trojkatow
    // wchodzacych w sklad modelu zebatki
	VBO VBO1(vertices_1, sizeof(vertices_1));
	EBO EBO1(indices_1, sizeof(indices_1));

	// Podlaczanie atrybutow takich jak pozycje punktow i kolory
	// a nastepnie odlaczanie ich po zakonczeniu proceseu aby
	// zapobiec ich przypadkowemu nadpisaniu
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*) 0); // Nie mam pojecia pokiego tu to ZERO ale bez niego program nie dziala
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	// Cos zwiazanego ze skala, nie mam pewosci co
	// ale jest to istotne do poprawnego dzialania
	GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");

	// Tekdturowanie modelu
	Texture brickTex("resources/raw_steel.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	brickTex.texUnit(shaderProgram, "tex0", 0);
	// Notatka:
	//  Brak tekstury powoduje powstanie calego czarnego modelu
	//  Pytanie brzmi czy da sie sprawic by istniala domyslna
	//  teksura dla wszystkich tworzonych modeli


	// Mechanizm obracania modelem
	float rotation = 0.0f;
	double prevTime = glfwGetTime();

	// Bufor glebokosci
	glEnable(GL_DEPTH_TEST);

	// Main while loop
	while (!glfwWindowShouldClose(window))
	{
		// Specify the color of the background
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		// Clean the back buffer and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// Tell OpenGL which Shader Program we want to use
		shaderProgram.Activate();

		// Simple timer
		double crntTime = glfwGetTime();
		if (crntTime - prevTime >= 1 / 60)
		{
			rotation += 0.02f;
			prevTime = crntTime;
		}

		// Initializes matrices so they are not the null matrix
		glm::mat4 zebatka_1 = glm::mat4(1.0f);
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 proj = glm::mat4(1.0f);

		zebatka_1 = glm::rotate(zebatka_1, glm::radians(45.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		zebatka_1 = glm::rotate(zebatka_1, glm::radians(rotation), glm::vec3(0.0f, 1.0f, 0.0f));

		view = glm::translate(view, glm::vec3(-0.0f, 0.1f, -1.0f));
		proj = glm::perspective(glm::radians(60.0f), (float)WTDH / HGHT, 0.1f, 100.0f);

		// Outputs the matrices into the Vertex Shader
		int modelLoc = glGetUniformLocation(shaderProgram.ID, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(zebatka_1));
		int viewLoc = glGetUniformLocation(shaderProgram.ID, "view");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		int projLoc = glGetUniformLocation(shaderProgram.ID, "proj");
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj));

		// Assigns a value to the uniform; NOTE: Must always be done after activating the Shader Program
		glUniform1f(uniID, 0.5f);
		// Binds texture so that is appears in rendering
		brickTex.Bind();
		// Bind the VAO so OpenGL knows to use it
		VAO1.Bind();
		// Draw primitives, number of indices, datatype of indices, index of indices
		glDrawElements(GL_TRIANGLES, sizeof(indices_1) / sizeof(int), GL_UNSIGNED_INT, 0);
		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
		// Take care of all GLFW events
		glfwPollEvents();
	}



	// Delete all the objects we've created
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	brickTex.Delete();
	shaderProgram.Delete();
	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();
	return 0;
}


/*
// Zebatka (chwilowo nie dzia³a)
    int rozP1, rozT1;
    GLfloat *vertices = genGearPoints(0.0, 0.0, 0.06, 12, 17.5, &rozP1);
    GLuint *indices = genGearTriangles(0.0, 0.0, 0.06, 12, 0, &rozT1);



// Vertices coordinates
GLfloat vertices[] =
{ //     COORDINATES     /        COLORS      /   TexCoord  //
	-0.4f, 0.6f,  0.4f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
	-0.4f, 0.6f, -0.4f,     0.83f, 0.70f, 0.44f,	5.0f, 0.0f,
	 0.4f, 0.6f, -0.4f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
	 0.4f, 0.6f,  0.4f,     0.83f, 0.70f, 0.44f,	5.0f, 0.0f,
	 0.0f, 0.9f,  0.0f,     0.92f, 0.86f, 0.76f,	2.5f, 5.0f,
	 0.0f, 0.0f,  0.0f,     0.0f,  0.0f,  0.0f,	    0.0f, 0.0f      // Modyfikacja
};

// Indices for vertices order
GLuint indices[] =
{
	0, 1, 2,
	0, 2, 3,
	0, 1, 4,
	1, 2, 4,
	2, 3, 4,
	3, 0, 4,
	3, 4, 5     // Modyfikacja
};


// Vertices coordinates
GLfloat vertices[] =
{ //     COORDINATES     /        COLORS      /   TexCoord  //
	0,      	    0,      	    0,      0,      0,      0,      0,      0,
    0.173867,       0,      	    0,      0,      0,      0,      0,      0,
    0.150573,       0.0869333,      0,      0,      0,      0,      0,      0,
    0.0869333,      0.150573,       0,      0,      0,      0,      0,      0,
    1.06459e-17,    0.173867,       0,      0,      0,      0,      0,      0,
    -0.0869333,     0.150573,       0,      0,      0,      0,      0,      0,
    -0.150573,      0.0869333,      0,      0,      0,      0,      0,      0,
    -0.173867,      2.12918e-17,    0,      0,      0,      0,      0,      0,
    -0.150573,      -0.0869333,     0,      0,      0,      0,      0,      0,
    -0.0869333,     -0.150573,      0,      0,      0,      0,      0,      0,
    -3.19377e-17,   -0.173867,      0,      0,      0,      0,      0,      0,
    0.0869333,      -0.150573,      0,      0,      0,      0,      0,      0,
    0.150573,       -0.0869333,     0,      0,      0,      0,      0,      0,
    0.26264,        0.0393159,      0,      0,      0,      0,      0,      0,
    0.247111,       0.0972715,      0,      0,      0,      0,      0,      0,
    0.0972715,      0.247111,       0,      0,      0,      0,      0,      0,
    0.0393159,      0.26264,        0,      0,      0,      0,      0,      0,
    -0.165369,      0.207795,       0,      0,      0,      0,      0,      0,
    -0.207795,      0.165369,       0,      0,      0,      0,      0,      0,
    -0.26264,       -0.0393159,     0,      0,      0,      0,      0,      0,
    -0.247111,      -0.0972715,     0,      0,      0,      0,      0,      0,
    -0.0972715,     -0.247111,      0,      0,      0,      0,      0,      0,
    -0.0393159,     -0.26264,       0,      0,      0,      0,      0,      0,
    0.165369,       -0.207795,      0,      0,      0,      0,      0,      0,
    0.207795,       -0.165369,      0,      0,      0,      0,      0,      0
};

// Indices for vertices order
GLuint indices[] =
{
    0,      1,      13,
    0,      13,     14,
    0,      14,     2,
    0,      2,      3,
    0,      3,      15,
    0,      15,     16,
    0,      16,     4,
    0,      4,      5,
    0,      5,      17,
    0,      17,     18,
    0,      18,     6,
    0,      6,      7,
    0,      7,      19,
    0,      19,     20,
    0,      20,     8,
    0,      8,      9,
    0,      9,      21,
    0,      21,     22,
    0,      22,     10,
    0,      10,     11,
    0,      11,     23,
    0,      23,     24,
    0,      24,     12,
    0,      12,     1
};
*/
