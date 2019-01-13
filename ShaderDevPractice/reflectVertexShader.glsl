#version 430

in layout(location = 0) vec3 vertexPosition;
in layout(location = 1) vec3 vertexColor;
in layout(location = 2) vec3 vertexNormal;
in layout(location = 3) vec2 UV;
in layout(location = 4) vec3 tangent;


out vec3 reflectVectorWorld; // reflection direction
out vec3 refractVectorWorld; // transmitted direction

//uniform bool drawSkyBox;

uniform vec3 worldCameraPostion;
uniform mat4 modelViewMatirx;
uniform mat4 modelMatix;
uniform mat4 normalMatrix;
uniform mat4 projectionMatrix;
uniform mat4 MVP;

void main(){
	//compute the reflected direction in world coords
	vec3 worldPos = vec3(modelMatix * vec4(vertexPosition, 1.0));
	vec3 worldNorm = vec3(modelMatix * vec4(vertexNormal, 0.0));
	vec3 worldView = normalize(worldCameraPostion - worldPos);
	reflectVectorWorld = reflect(-worldView, worldNorm);

	float refractionRatio = float(1.00/1.33);
	refractVectorWorld = refract(-worldView, (-worldNorm), refractionRatio);

	gl_Position = MVP * vec4(vertexPosition, 1.0);
}