#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define WIDTH 1200
#define HEIGHT 900
 
 

 float scale= (float)1/(WIDTH*(WIDTH/HEIGHT));

 int** matrix;
 int iteration = HEIGHT-1;	

int main(void)
{
	srand(time(NULL));

	matrix = (int**)calloc(WIDTH,sizeof(int*));

	for(int i=0;i<WIDTH;i++){
	matrix[i] = (int*)calloc(HEIGHT,sizeof(int));	
	matrix[i][HEIGHT-1] = rand() % 2;
	}

	GLFWwindow* window;

	if (!glfwInit())
	return -1;

	window = glfwCreateWindow(WIDTH, HEIGHT, "Hello World", NULL, NULL);
    
	if (!window)
	{
	glfwTerminate();
	return -1;
	}

    glfwMakeContextCurrent(window);

    while (!glfwWindowShouldClose(window) || iteration >= 0)
    {
        glClear(GL_COLOR_BUFFER_BIT);
	
	glLoadIdentity();
	glScalef(scale*2,scale*2,scale*2);
	glBegin(GL_POINTS);

	for(int x=0;x<WIDTH;++x){
	for(int y=HEIGHT-1;y>0;--y){
	if(matrix[x][y]!=0)glVertex2f(x-(WIDTH/2),y-(HEIGHT/2));	
	}
	}
	glEnd();

	for(int i=0;i<WIDTH;i++){
	if(i-1 <0 || i+1 >= WIDTH) {continue;}
		matrix[i][iteration-1] =matrix[i-1][iteration]^matrix[i+1][iteration];
	}
	if(iteration == 0) getchar();		
	iteration--;
	glfwSwapBuffers(window);
	glfwPollEvents();
    }
    matrix = NULL;
    free(matrix);
    glfwTerminate();
    return 0;
}


