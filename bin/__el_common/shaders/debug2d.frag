#version 460

in vec4 fColor;

out vec4 oColor;

void main() {
	if (fColor.a < 0.05)
      discard; 
	oColor = fColor;
	//oColor = vec4(1, 1, 1, 1);
}