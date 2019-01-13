#version 430

out vec4 FragColor;

in vec3 reflectDir;
in vec3 refractDir;
in vec3 pass_normal;
in vec2 pass_texCoord;
//in vec3 test;

uniform samplerCube skybox;


uniform float drawSkyBox;
uniform float reflectionFactor; // amound of reflection
uniform vec4 materialColor; // color of the object's "Tint"
uniform float reflectFactor; // amount of reflection

const vec3 lightDirction = normalize(vec3(0.2, -1.0, 0.3));
const float ambient = 0.3;

void main(){
	float brightness = max(dot(-lightDirction, normalize(pass_normal)), 0.0) + ambient;
	FragColor = vec4(brightness, brightness, brightness, 1.0);
//access cubemap texture
	vec4 reflectColor = texture(skybox, reflectDir);
	vec4 refractColor = texture(skybox, refractDir);
    vec3 matrialColor = vec3(0.5, 1.0, 0.5);
//	vec3 testCololr = texture(skybox, test).xyz;
	if(drawSkyBox == 1.0){
		FragColor = reflectColor;
	}else{
		//FragColor = mix(materialColor, cubeMapColor, reflectionFactor);
//		vec4 matrialColor = vec4(0.5, 1.0, 0.5, 1.0);
//FragColor = reflectColor;
		FragColor = mix(reflectColor, refractColor, 0.8);
//     FragColor = mix(reflectColor, refractColor, reflectFactor);
//	// access the cupmap texture
//		vec4 cubeMapColor = texture(skybox, reflectDir);
//		FragColor = mix(matrialColor, cubeMapColor, reflectFactor);
//
	}
}
