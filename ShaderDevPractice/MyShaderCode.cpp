const char* vertexShaderCode =
"#version 430\r\n" //declare what vision 
""
"in layout(location = 0) vec2 position;" //vec2: for attribute 0, 2 floats for position
"in layout(location = 1) vec3 vertexColor;"
""
"out vec3 theColor;" // send to the fragmentShader
""
"void main()"
"{"
"	gl_Position = vec4(position, 0.0, 1.0);"
"	theColor = vertexColor;"
"}";



const char* fragmentShaderCode =
"#version 430\r\n"
""
"out vec4 daColor;"
"in vec3 theColor;" // from vertex shader
""
"void main()"
"{"
"	daColor = vec4(theColor, 1.0);"
"}";

