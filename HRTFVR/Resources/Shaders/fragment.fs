#version 150
uniform sampler2D texture_diffuse;
in vec2 pass_TextureCoord;
out vec4 out_Color;
void main(void) {
	out_Color = texture(texture_diffuse, pass_TextureCoord);
}