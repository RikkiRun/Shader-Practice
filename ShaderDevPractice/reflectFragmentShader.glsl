#version 430

out vec4 FragColor;

in vec3 pass_normal;
in vec3 vertexPositionWorld;
in vec3 test;

uniform samplerCube skybox;
uniform sampler2D Tex1;

uniform vec3 lightPositionWorld;
uniform vec3 worldCameraPosition;
//uniform vec3 ambientLight;


//uniform vec4 materialColor; // color of the object's "Tint"
uniform float reflectFactor; // amount of reflection
uniform mat4 modelMatrix;


void main(){
	vec3 I = normalize(vertexPositionWorld - worldCameraPosition);
	vec3 reflection = reflect(I, normalize(pass_normal));
	FragColor = vec4(texture(skybox, reflection).rgb, 1.0);
}
