#version 430
out float fragDepth;
//out vec4 fragColor;

in vec3 normalWorld;
in vec3 vertexPositionWorld;
in vec4 shadowCoord;

uniform vec3 lightPositionWorld;
uniform vec3 eyePositionWorld;
uniform vec3 ambientLight;
uniform mat4 modelToWorldMatrix;
uniform sampler2DShadow shadowMap;

//vec3 phongModelDiffAndSpec()
//{
//}
//
//subroutine void renderPassType();
//subroutine uniform renderPassType renderPass;
//subroutine(renderPassType)
//
//void shadeWithShadow(){
//	
//	float shadow = textureProj(shadowMap, shadowCoord);
//	fragColor = vec4()
//}
//
//subroutine(renderPassType)
//
//void recordDepth()
//{
//}

void main()
{
fragDepth = gl_FragCoord.z;
//	renderPass();
	//diffuse
	vec3 lightVectorWorld = normalize(lightPositionWorld - vertexPositionWorld);
	float brightness = dot(lightVectorWorld, normalize(normalWorld));
	vec4 diffuseLight = vec4(0, brightness, 0, 1.0);
	
	//specular
	vec3 reflectedLightVectorWorld = reflect(-lightVectorWorld, normalWorld);
	vec3 eyeVectorWorld = normalize(eyePositionWorld - vertexPositionWorld);
	float s = dot(reflectedLightVectorWorld, eyeVectorWorld);
	s =  pow(s, 10);
	vec4 specularLight = vec4(50*s, 0, 0, 1);


	vec4 diffAndSpec = clamp(diffuseLight, 0, 1) + clamp(specularLight, 0, 1);
	// lookup normal from normal map
//	vec4 texColor = texture(Tex1, TexCoord);

	//do the shadow map look-up
	float shadow = textureProj(shadowMap, shadowCoord);
//	fragColor = vec4(diffAndSpec * shadow + (ambientLight,1.0));
//	daColor = vec4(specularLight * shadow  + vec4(ambientLight, 1.0));
//	daColor = texColor;
//	daColor = vec4(ambientLight,1.0)+ clamp(specularLight,0,1) + clamp(diffuseLight,0,1);
//	daColor = vec4(normalTextureInfoInWorld.xyz,0.0);

//	fragColor += shadow;
}