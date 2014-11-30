#version 150 core  
uniform mat4 projectionMatrix; 
uniform mat4 viewMatrix; 
uniform mat4 modelMatrix; 
in vec4 in_Position; 
in vec3 in_Normal;
in vec2 in_TextureCoord; 
out vec2 pass_TextureCoord; 
void main(void) { 	
gl_Position = projectionMatrix * viewMatrix * modelMatrix 	* in_Position; 
pass_TextureCoord = in_TextureCoord;
}