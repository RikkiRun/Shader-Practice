#version 430

out vec4 FragColor;

in vec3 reflectDir;
in vec3 test;

uniform samplerCube skybox;


uniform float drawSkyBox;
uniform float reflectionFactor; // amound of reflection
uniform vec4 materialColor; // color of the object's "Tint"
uniform float reflectFactor; // amount of reflection

void main(){
//access cubemap texture
	vec3 cubeMapColor = texture( skybox, reflectDir).xyz;
    vec3 matrialColor = vec3(0.5, 1.0, 0.5);
	vec3 testCololr = texture(skybox, test).xyz;
//	FragColor = vec4(cubeMapColor, 1.0);
	if(drawSkyBox == 1.0){
		FragColor = vec4(cubeMapColor, 1.0);
	}else{
		//FragColor = mix(materialColor, cubeMapColor, reflectionFactor);
//		vec4 matrialColor = vec4(0.5, 1.0, 0.5, 1.0);
		vec4 color1 = vec4(testCololr, 1.0);
		FragColor = vec4(test, 1.0);
//	// access the cupmap texture
//		vec4 cubeMapColor = texture(skybox, reflectDir);
//		FragColor = mix(matrialColor, cubeMapColor, reflectFactor);
//
	}
}
