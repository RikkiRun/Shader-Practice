#version 430


in layout(location = 0) vec3 vertexPosition;
in layout(location = 1) vec3 vertexColor;
in layout(location = 2) vec3 vertexNormal;
in layout(location = 3) vec2 UV;
in layout(location = 4) vec3 tangent;

out vec3 test;
out vec3 pass_normal;
out vec3 vertexPositionWorld;



uniform vec3 worldCameraPosition;
uniform mat4 modelMatrix;
uniform mat3 normalMatrix;
uniform mat4 projectionMatrix;
uniform mat4 MVP;



void main(){
	pass_normal = vec3(mat4(transpose(inverse(modelMatrix)))*vec4(vertexNormal, 0));
	TBNtangentToModel = mat3(tangent, biTangentModel, vertexNormal);
	vertexPositionWorld = vec3(modelMatrix * vec4(vertexPosition, 1.0));
	gl_Position = MVP * vec4(vertexPosition, 1.0);

}