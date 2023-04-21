#version 460

in vec2 fUV;
in vec4 fColor;

out vec4 oColor;

uniform sampler2D uDiffuse; 

void main() {
	oColor = texture(uDiffuse, fUV) * fColor;
	
	if (oColor.a < 0.05)
      discard; 
}