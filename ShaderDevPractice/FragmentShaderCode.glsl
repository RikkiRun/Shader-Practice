#version 430

out vec4 daColor;

in mat3 TBNtangentToModel;
//in vec3 normalWorld;
in vec3 vertexPositionWorld;
in vec2 TexCoord;



uniform vec3 lightPositionWorld;
uniform vec3 eyePositionWorld;
uniform vec3 ambientLight;
uniform mat4 modelToWorldMatrix;
uniform sampler2D Tex1;


void main()
{
	vec4 normalTextureInfo = normalize(texture(Tex1, TexCoord)*2 - 1);
	vec4 testNormalTengent = vec4(0.0, 0.0, 1.0, 0.0);
	vec3 normalTextureInfoInObj = TBNtangentToModel * normalTextureInfo.xyz;
	vec3 normalTextureInfoInWorld = vec3(modelToWorldMatrix * vec4(normalTextureInfoInObj, 1.0));


	//diffuse
	vec3 lightVectorWorld = normalize(lightPositionWorld - vertexPositionWorld);
	float brightness = dot(lightVectorWorld, normalize(normalTextureInfoInWorld));
	vec4 diffuseLight = vec4(0, brightness, 0, 1.0);
	
	//specular
	vec3 reflectedLightVectorWorld = reflect(-lightVectorWorld, normalTextureInfoInWorld);
	vec3 eyeVectorWorld = normalize(eyePositionWorld - vertexPositionWorld);
	float s = dot(reflectedLightVectorWorld, eyeVectorWorld);
	s =  pow(s, 10);
	vec4 specularLight = vec4(50*s, 0, 0, 1);

	// lookup normal from normal map

	//vec4 texColor = texture(Tex1, TexCoord);

	//daColor = texColor;
	daColor = vec4(ambientLight,1.0)+ clamp(specularLight,0,1) + clamp(diffuseLight,0,1);
//	daColor = vec4(normalTextureInfoInWorld.xyz,0.0);
}