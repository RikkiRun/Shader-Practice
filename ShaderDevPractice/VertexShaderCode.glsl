#version 430

in layout(location = 0) vec4 vertexPositionModel; 
in layout(location = 1) vec4 vertexColor;
in layout(location = 2) vec3 normalModel;
in layout(location = 3) vec2 UV;
in layout(location = 4) vec3 tangent;

uniform mat3 normalMatrix;
uniform mat4 modelToProjectionMatrix; //AKA: MVP
uniform mat4 modelToWorldMatrix;
uniform mat4 modelToViewMatrix;
uniform mat4 shadowMatrix;

out vec3 normalWorld;
out vec3 vertexPositionWorld;
out vec4 shadowCoord;
uniform mat4 depthMVP;

void main()
{	
//	TexCoord = UV;

	normalWorld = normalize(vec3(modelToWorldMatrix * vec4(normalModel, 0)));

	vertexPositionWorld = vec3 (modelToWorldMatrix * vertexPositionModel);

	// shadowmatrix converts from modeling coordinates to shadow map coordinates
	shadowCoord = shadowMatrix * vertexPositionModel;
		gl_Position = depthMVP * vertexPositionModel;
//	gl_Position = modelToProjectionMatrix * vertexPositionModel;

}