#version 430


in layout(location = 0) vec3 vertexPosition;
in layout(location = 1) vec4 vertexColor;
in layout(location = 2) vec3 vertexNormal;
in layout(location = 3) vec2 UV;
in layout(location = 4) vec3 tangent;

out vec3 reflectDir;
out vec3 refractDir;
//out vec3 test;
out vec3 pass_normal;
out vec2 pass_texCoord;
out vec3 vertexPositionWorld;

uniform float drawSkyBox;

uniform vec3 worldCameraPosition;
uniform mat4 modelViewMatrix;
uniform mat4 modelMatrix;
uniform mat3 normalMatrix;
uniform mat4 projectionMatrix;
uniform mat4 MVP;



void main(){
	vec3 v = vertexPosition;
	// smooth surface normal!
	pass_normal = mat3(transpose(inverse(modelMatrix)))*vertexNormal;
//	pass_normal = vec3(mat4(transpose(modelMatrix))*vec4(vertexNormal, 0));
//	pass_normal = vec3(modelMatrix * vec4(vertexNormal,1.0));
	pass_texCoord = UV;
	vertexPositionWorld = vec3(modelMatrix * vec4(vertexPosition, 1.0));
	if(drawSkyBox == 1.0){
		reflectDir = vec3(vertexPosition.x, -vertexPosition.yz);

	} else {
		// computer the reflection direction ion world coords
		vec3 worldPos = vec3(modelMatrix * vec4(vertexPosition, 1.0));
//		vec3 worldNor = vec3(modelMatrix * vec4(vertexNormal, 1.0));
		vec3 worldView = normalize(worldCameraPosition - worldPos);
		vec3 reflectResult = reflect(worldView, normalize(pass_normal));
	    reflectDir = vec3(reflectResult.x, reflectResult.y, reflectResult.z);
		//test = reflectDir;
		float refractionRatio = float(1.00/1.52);
		refractDir = refract(-worldView, normalize(pass_normal), refractionRatio);
	}
	gl_Position = MVP*vec4(vertexPosition, 1.0);

}