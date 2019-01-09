#version 430

out vec4 FragColor;

in vec3 reflectDir;

uniform samplerCube skybox;


uniform float drawSkyBox;
uniform float reflectionFactor; // amound of reflection
uniform vec4 materialColor; // color of the object's "Tint"

void main(){
//access cubemap texture
	vec3 cubeMapColor = texture( skybox, reflectDir).xyz;
	FragColor = vec4(cubeMapColor, 1.0);
//	if(drawSkyBox == 1.0){
//		FragColor = vec4(cubeMapColor, 1.0);
//		//FragColor = vec4(1.0,0.0,0.0,0.0);
//	}else{
//		//FragColor = mix(materialColor, cubeMapColor, reflectionFactor);
//		FragColor = vec4(0.0,0.0,1.0,0.0);
//	}
}
