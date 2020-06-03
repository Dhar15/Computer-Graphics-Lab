//Program to rotate a triangle about the origin and a fixed point

#include<stdio.h>
#include<GL/glut.h>

int x, y;
int where_to_rotate = 0;
float rotate_angle = 0.0;
float translate_x = 0.0, translate_y = 0.0;

void draw_pixel(float x1, float y1)
{
	glPointSize(10.0);
	glBegin(GL_POINTS);
	glVertex2f(x1, y1);
	glEnd();
}

void triangle(int x, int y)
{
	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex2f(x, y);
	glVertex2f(x + 400, y + 300);
	glVertex2f(x + 300, y + 10);
	glEnd();
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	glColor3f(1, 1, 1);
	draw_pixel(0.0, 0.0);

	if (where_to_rotate == 1)	//Rotate about origin
	{
		translate_x = 0.0;
		translate_y = 0.0;
		rotate_angle += 0.9;
	}
	if (where_to_rotate == 2)	//Rotate about fixed point
	{
		translate_x = x;
		translate_y = y;
		rotate_angle += 0.9;
		glColor3f(1.0, 0.0, 0.0);
		draw_pixel(x, y);
	}

	glTranslatef(translate_x, translate_y, 0.0);
	glRotatef(rotate_angle, 0.0, 0.0, 1.0);
	glTranslatef(-translate_x, -translate_y, 0.0);
	triangle(translate_x, translate_y);
	glutPostRedisplay();	//Marks the current window as needing to be redisplayed
	glutSwapBuffers();		//Swaps the buffers of the current window if double buffered
}

void myinit()
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-800.0, 800.0, -800.0, 800.0);
	glMatrixMode(GL_MODELVIEW);
}

void rotateMenu(int option)
{
	if (option == 1)
		where_to_rotate = 1;
	if (option == 2)
		where_to_rotate = 2;
	if (option == 3)
		where_to_rotate = 3;
}

int main(int argc, char** argv)
{
	printf("Enter Fixed Points (x,y) for Rotation: \n");
	scanf_s("%d %d", &x, &y);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(800, 800);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Create and Rotate Triangle");
	myinit();
	glutDisplayFunc(display);
	glutCreateMenu(rotateMenu);
	glutAddMenuEntry("Rotate around ORIGIN", 1);
	glutAddMenuEntry("Rotate around FIXED POINT", 2);
	glutAddMenuEntry("Stop Rotation", 3);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutMainLoop();
}
