#version 430

out vec4 daColor;


in vec3 normalWorld;
in vec3 vertexPositionWorld;
in vec2 TexCoord;

uniform vec3 lightPositionWorld;
uniform vec3 eyePositionWorld;
uniform vec4 ambientLight;
uniform sampler2D Tex1;
uniform sampler2D specularTex;


void main()
{
	vec4 texColor = texture(Tex1, TexCoord);
	vec4 texSpecular = texture(specularTex, TexCoord);

	vec3 lightVectorWorld = normalize(lightPositionWorld - vertexPositionWorld);
	float brightness = dot(lightVectorWorld, normalize(normalWorld));
	vec4 diffuseLight = vec4(brightness, brightness, brightness, 1.0);
	
	vec3 reflectedLightVectorWorld = reflect(-lightVectorWorld, normalWorld);
	vec3 eyeVectorWorld = normalize(eyePositionWorld - vertexPositionWorld);
	float s = dot(reflectedLightVectorWorld, eyeVectorWorld);
	s =  pow(s, 5);
	vec4 specularLight = vec4(s, s, s, 1);


//	daColor = clamp(specularLight, 0, 1) * texColor;
//	daColor = ambientLight;
	daColor = texColor* (ambientLight + clamp(diffuseLight, 0, 1)) + clamp(specularLight, 0, 1);
}