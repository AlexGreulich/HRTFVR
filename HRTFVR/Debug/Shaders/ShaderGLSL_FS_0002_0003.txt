#version 150
uniform sampler2D tex0;
in vec2 pass_TextureCoord;
out vec4 out_Color;
void main(void) {
	out_Color = texture(tex0, pass_TextureCoord);
}