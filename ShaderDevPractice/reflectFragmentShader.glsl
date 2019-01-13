#version 430

in vec3 reflectVectorWorld;
in vec3 refractVectorWorld;

uniform samplerCube skybox;
uniform float reflectFactor; // amount of reflection

//uniform vec4 matrialColor;


out vec4 fragColor;

void main(){
	vec4 matrialColor = vec4(0.5, 0.5, 0.5, 1.0);
	// access the cupmap texture
//	vec4 cubeMapColor = texture(skybox, reflectFactor);
	//fragColor = mix(matrialColor, cubeMapColor, reflectFactor);
	
}
