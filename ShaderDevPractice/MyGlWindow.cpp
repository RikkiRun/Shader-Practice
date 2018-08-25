#include <gl\glew.h>
#include <MyGlWindow.h>

void MyGlWindow::initializeGL() {
	glewInit();

	GLfloat verts[] = {
		+0.0f, +1.0f,  
		-1.0f, -1.0f, 
		+1.0f, -1.0f, 
	};
	GLuint myBufferID;

	glGenBuffers(1, &myBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, myBufferID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);

}


void MyGlWindow::paintGL() {
	glViewport(0, 0, width(), height());
	//glDrawArrays(GL_TRIANGLES, 0, 3);
}