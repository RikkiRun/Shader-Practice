#version 430

in layout(location = 0) vec4 vertexPositionModel; 
in layout(location = 1) vec4 vertexColor;
in layout(location = 2) vec3 normalModel;
in layout(location = 3) vec2 UV;
in layout(location = 4) vec3 tangent;


uniform mat4 modelToProjectionMatrix; 
uniform mat4 modelToWorldMatrix;


out vec3 normalWorld;
out vec3 vertexPositionWorld;
out vec2 TexCoords;

void main()
{	
	TexCoords = UV;
	gl_Position = modelToProjectionMatrix * vertexPositionModel;
	normalWorld = vec3(modelToWorldMatrix * vec4(normalModel, 0));
	vertexPositionWorld = vec3 (modelToWorldMatrix * vertexPositionModel);
}