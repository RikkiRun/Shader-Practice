#version 430

out vec4 FragColor;

in vec3 reflectDir;
in vec3 refractDir;
in vec3 pass_normal;
in vec2 pass_texCoord;
in vec3 vertexPositionWorld;
//in vec3 test;

uniform samplerCube skybox;

uniform vec3 lightPositionWorld;
uniform vec3 worldCameraPosition;
//uniform vec3 ambientLight;


uniform float drawSkyBox;
uniform float reflectionFactor; // amound of reflection
uniform vec4 materialColor; // color of the object's "Tint"
uniform float reflectFactor; // amount of reflection

vec3 ambientLight = vec3(0.25f, 0.25f, 0.25f);


void main(){
//------------access cubemap texture
	//vec3 newReflectDir = vec3( -reflectDir.x, -reflectDir.y, -reflectDir.z);
	vec4 reflectColor = texture(skybox, reflectDir);
	vec4 refractColor = texture(skybox, refractDir);
    vec3 matrialColor = vec3(0.5, 1.0, 0.5);
//	vec3 testCololr = texture(skybox, test).xyz;
//------------divecffuse light
	vec3 lightVectorWorld = normalize(lightPositionWorld - vertexPositionWorld);
//	float brightness = max(dot(-lightDirction, normalize(pass_normal)), 0.0);
// do i need to invert the lightVectorWorld???? why
	float brightness = dot(lightVectorWorld, normalize(pass_normal));
	vec4 diffuseLight = vec4(brightness, brightness, brightness, 0);

//------------specular light
	vec3 reflectedLightVectorWorld = reflect(-lightVectorWorld, pass_normal);
	vec3 eyeVectorWorld = normalize(worldCameraPosition - vertexPositionWorld);
	float s = dot(reflectedLightVectorWorld, worldCameraPosition);
	s = pow(s, 10);
	vec4 specularLight = vec4(s,s,s,1);

	
	if(drawSkyBox == 1.0){
		FragColor = reflectColor;
	}else{
//	FragColor = reflectColor;
	// not sure if i need to add diffuse
	// if not add ambient it will become whole dark if move the specular.

	FragColor = vec4(refractColor.rgb, 1.0);
//	FragColor = mix(reflectColor, refractColor, reflectionFactor) * (vec4(ambientLight, 1.0) + clamp(specularLight, 0,1) + clamp(diffuseLight, 0, 1));
//		FragColor = mix(reflectColor, refractColor, 0.8) + clamp(specularLight, 0, 1);
//     FragColor = mix(reflectColor, refractColor, reflectFactor);
//     FragColor = clamp(diffuseLight, 0, 1);
	}
}
