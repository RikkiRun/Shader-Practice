#version 430

in layout(location = 0) vec3 vertexPosition;
in layout(location = 1) vec3 vertexNormal;
in layout(location = 2) vec2 vertexTexCoord;

out vec3 reflectDir;

//uniform float drawSkyBox;

uniform vec3 worldCameraPosition;
uniform mat4 modelViewMatrix;
uniform mat4 modelMatrix;
uniform mat3 normalMatrix;
uniform mat4 projectionMatrix;
uniform mat4 MVP;

void main(){
	vec3 v = vertexPosition;
//	if(drawSkyBox == 1.0f){
//		reflectDir = vertexPosition;
//	} else {
//		// computer the reflection direction ion world coords
//		vec3 worldPos = vec3(modelMatrix * vec4(vertexPosition, 1.0));
//		vec3 worldNor = -vec3(modelMatrix * vec4(vertexNormal, 1.0));
//		vec3 worldView = normalize(worldCameraPosition - worldPos);
//	}
	gl_Position = MVP*vec4(vertexPosition, 1.0);
	reflectDir = vec3(vertexPosition.x, -vertexPosition.yz);

}