#include <gl\glew.h>
#include <MyGlWindow.h>

void MyGlWindow::initializeGL() {
	glewInit();

	GLfloat verts[] = {
		+0.0f, +0.0f,  
		+0.0f, +0.0f, +0.0f,
		+1.0f, +1.0f, 
		+0.0f, +0.0f, +0.0f,
		-1.0f, +1.0f, 
		+0.0f, +0.0f, +0.0f,
		-1.0f, -1.0f,
		+0.0f, +0.0f, +0.0f,
		+1.0f, -1.0f,
		+0.0f, +0.0f, +0.0f,
	};
	GLuint vertexBufferID; // vertex bufferID
	 
	glGenBuffers(1, &vertexBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0); //position
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, 0); //GL_FALSE: Not normalize data; stride: where the data begins, the first position to the second position

	// describe color attribute
	glEnableVertexAttribArray(1); //color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (char*)(sizeof(float) * 2)); // last one: 2 float until we get to the beginning of the color data

	GLushort indices[] = { 0, 1, 2, 0, 3, 4 }; // save memory
	GLuint indexBufferID; // element bufferID
	glGenBuffers(1, &indexBufferID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

}


void MyGlWindow::paintGL() {
	glViewport(0, 0, width(), height());
	//glDrawArrays(GL_TRIANGLES, 0, 6);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);

}