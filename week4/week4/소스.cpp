#include <GLFW/glfw3.h>
#include <cstring>
#include <stdlib.h>		  // srand, rand
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds
#include "math.h"

double xpos, ypos;
GLFWwindow* window;

const int width = 750;
const int height = 480;

float* pixels = new float[width*height * 3];


void drawPixel(const int& i, const int& j, const float& red, const float& green, const float& blue)
{
	pixels[(i + width* j) * 3 + 0] = red;
	pixels[(i + width* j) * 3 + 1] = green;
	pixels[(i + width* j) * 3 + 2] = blue;
}

bool circle_check(double pos_x, double pos_y, int x_c, int y_c, int r)
{
	if (r < 40) return false;
	double circle = (pos_x - x_c)*(pos_x - x_c) + (pos_y - y_c)*(pos_y - y_c) - r*r;
	if (circle > 0)return false;
	else return true;
}

// scratched from https://courses.engr.illinois.edu/ece390/archive/archive-f2000/mp/mp4/anti.html
// see 'Rasterization' part.

void drawLine(const int& i0, const int& j0, const int& i1, const int& j1, const float& red, const float& green, const float& blue)
{
	for (int i = i0; i <= i1; i++)
	{
		const int j = (j1 - j0)*(i - i0) / (i1 - i0) + j0;

		drawPixel(i, j, red, green, blue);
	}
}

void drawcircle(const int&i0, const int& j0, int r)
{
	int x = r, y = 0, err = 0;
	float red, green, blue;
	red = 1.0f, green = 0.0f, blue = 0.0f;

	if (circle_check(xpos, height - ypos, i0, j0, r) == true)
	{
		red = 0.0f; green = 0.0f; blue = 1.0f;
	}

	while (x >= y)
	{
		drawPixel(i0 + x, j0 + y, red, green, blue);
		drawPixel(i0 + y, j0 + x, red, green, blue);
		drawPixel(i0 - y, j0 + x, red, green, blue);
		drawPixel(i0 - x, j0 + y, red, green, blue);
		drawPixel(i0 - x, j0 - y, red, green, blue);
		drawPixel(i0 - y, j0 - x, red, green, blue);
		drawPixel(i0 + y, j0 - x, red, green, blue);
		drawPixel(i0 + x, j0 - y, red, green, blue);

		y += 1;
		err += 1 + 2 * y;
		if (2 * (err - x) + 1 > 0)
		{
			x -= 1;
			err += 1 - 2 * x;
		}
	}
}

void drawOnPixelBuffer()
{
	//std::memset(pixels, 1.0f, sizeof(float)*width*height * 3); // doesn't work
	std::fill_n(pixels, width*height * 3, 1.0f);	// white background

													//for (int i = 0; i<width*height; i++) {
													//	pixels[i * 3 + 0] = 1.0f; // red 
													//	pixels[i * 3 + 1] = 1.0f; // green
													//	pixels[i * 3 + 2] = 1.0f; // blue
													//}

	const int i = rand() % width, j = rand() % height;
	//drawPixel(i, j, 0.0f, 0.0f, 0.0f);

			const int i0 = 80, j0 = 80, r = 50; // 2nd line circles
	
			drawcircle(i0, j0, r);
			drawcircle(i0, j0, r + 1);
			drawLine(50, 80, 105, 80, 1.0f, 0.0f, 0.0f);
			drawLine(80, 105, 105, 80, 1.0f, 0.0f, 0.0f);
			drawLine(80, 55, 105, 80, 1.0f, 0.0f, 0.0f);
	
			drawcircle(i0 + 130, j0, r);
			drawcircle(i0 + 130, j0, r + 1);
			drawLine(170, 60, 210, 110, 1.0f, 0.0f, 0.0f);
			drawLine(210, 110, 250, 60, 1.0f, 0.0f, 0.0f);
			drawLine(190, 85, 230, 85, 1.0f, 0.0f, 0.0f);
	
			drawcircle(i0 + 130 * 2, j0, r);
			drawcircle(i0 + 130 * 2, j0, r + 1);
			for (int j = 50; j <= 110; j++)
			{
				drawPixel(i0 + 130 * 2, j, 1.0f, 0.0f, 0.0f);
			}
	
			drawcircle(i0 + 130 * 3, j0, r);
			drawcircle(i0 + 130 * 3, j0, r + 1);
			drawLine(445, 80, 500, 80, 1.0f, 0.0f, 0.0f);
			drawLine(445, 80, 470, 105, 1.0f, 0.0f, 0.0f);
			drawLine(445, 80, 470, 55, 1.0f, 0.0f, 0.0f);
	
			drawcircle(i0 + 130 * 4, j0, r);
			drawcircle(i0 + 130 * 4, j0, r + 1);
			drawLine(575, 80, 600, 105, 1.0f, 0.0f, 0.0f);
			drawLine(600, 105, 625, 80, 1.0f, 0.0f, 0.0f);
			for (int j = 50; j <= 105; j++)
			{
				drawPixel(600, j, 1.0f, 0.0f, 0.0f);
			}
	
			const int i1 = 80, j1 = 300; // 1st line circles
	
			drawcircle(i1, j1, r);
			drawcircle(i1, j1, r + 1);
			drawLine(50, 270, 110, 330, 1.0f, 0.0f, 0.0f);
			drawLine(50, 269, 110, 329, 1.0f, 0.0f, 0.0f);
	
			drawcircle(i1 + 130, j1, r);
			drawcircle(i1 + 130, j1, r + 1);
			drawcircle(i1 + 130, j1, r - 30);
			drawcircle(i1 + 130, j1, r - 29);
			drawcircle(i1 + 130, j1, r - 28);
	
			drawcircle(i1 + 130 * 2, j1, r);
			drawcircle(i1 + 130 * 2, j1, r + 1);
			drawLine(310, 270, 370, 270, 1.0f, 0.0f, 0.0f);
			drawLine(310, 330, 370, 330, 1.0f, 0.0f, 0.0f);
			for (int j = 270; j <= 330; j++)
			{
				drawPixel(310, j, 1.0f, 0.0f, 0.0f);
			}
			for (int j = 270; j <= 330; j++)
			{
				drawPixel(370, j, 1.0f, 0.0f, 0.0f);
			}
	
			drawcircle(i1 + 130 * 3, j1, r);
			drawcircle(i1 + 130 * 3, j1, r + 1);
			drawLine(440, 270, 500, 330, 1.0f, 0.0f, 0.0f);
			drawLine(440, 330, 500, 270, 1.0f, 0.0f, 0.0f);
	
			drawcircle(i1 + 130 * 4, j1, r);
			drawcircle(i1 + 130 * 4, j1, r + 1);
			drawLine(575, 300, 600, 275, 1.0f, 0.0f, 0.0f);
			drawLine(600, 275, 625, 300, 1.0f, 0.0f, 0.0f);
			for (int j = 275; j <= 330; j++)
			{
				drawPixel(600, j, 1.0f, 0.0f, 0.0f);
			}
}

int main(void)
{
	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(width, height, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	glClearColor(1, 1, 1, 1); // while background
							  /* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		glfwGetCursorPos(window, &xpos, &ypos);
		drawOnPixelBuffer();

		glDrawPixels(width, height, GL_RGB, GL_FLOAT, pixels);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();

		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}

	glfwTerminate();

	delete[] pixels; // or you may reuse pixels array 

	return 0;
}