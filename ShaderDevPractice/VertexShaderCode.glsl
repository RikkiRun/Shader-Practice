#version 430

in layout(location = 0) vec4 vertexPositionModel; 
in layout(location = 1) vec4 vertexColor;
in layout(location = 2) vec3 normalModel;
in layout(location = 3) vec2 UV;
in layout(location = 4) vec3 tangent;

uniform mat3 normalMatrix;
uniform mat4 modelToProjectionMatrix; //AKA: MVP
uniform mat4 modelToWorldMatrix;
uniform mat4 modelToViewMatrix;


out mat3 TBNtangentToModel;
//out vec3 normalWorld;
out vec3 vertexPositionWorld;
out vec2 TexCoord;

void main()
{	
	TexCoord = UV;
//	vec3 norm = normalize(normalMatrix * normalModel);
//	vec3 tang = normalize(normalMatrix * vec3(tangent));
//	vec3 binormal = normalize(normalMatrix * vec3(tangent));

	gl_Position = modelToProjectionMatrix * vertexPositionModel;

	vec3 biTangentModel = normalize(cross(normalModel, tangent)) * 1;
	TBNtangentToModel = mat3(tangent, biTangentModel, normalModel);


//	normalWorld = vec3(modelToWorldMatrix * vec4(normalModel, 0));

	vertexPositionWorld = vec3 (modelToWorldMatrix * vertexPositionModel);
//	mat3 toObjectLocal = mat3(tang.x, binormal.x, norm.x, tang.y, binormal.y, norm.y, tang.z, binormal.z, norm.z );
//	vec3 pos = vec3( modelToWorldMatrix * vertexPositionModel);
//	lightDir = normalize(toObjectLocal * (Light.Position.xyz - pos));
//	viewDir = toObjectLocal * normalize(-pos);


}