#version 400
in vec3 color;
out vec4 fragment_color;

uniform sampler2D ourTexture;

void main () {
	fragment_color = vec4 (color, 1.0);
//	fragment_color = texture(ourTexture, color.xy);
}