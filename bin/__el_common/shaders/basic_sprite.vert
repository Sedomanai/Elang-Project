#version 460

in vec2 vPosition2D;
in vec2 vUV;

out vec2 fUV;
out vec4 fColor;

uniform vec4 uColor = vec4(1, 1, 1, 1);
uniform mat4 uView;

out gl_PerVertex {
  vec4 gl_Position;
};

void main() {
	gl_Position = uView * vec4(vPosition2D, 0, 1);
	
	fUV = vUV;
	fColor = uColor;
}