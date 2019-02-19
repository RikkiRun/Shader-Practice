#version 430

out vec4 daColor;


in vec3 normalWorld;
in vec3 vertexPositionWorld;
in vec2 TexCoords;

uniform sampler2D screenTexture;


void main()
{
daColor = texture(screenTexture, TexCoords);
}