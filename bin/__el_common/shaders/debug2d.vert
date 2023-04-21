#version 460

in vec2 vPosition2D;
in vec4 v8Color;

uniform mat4 uView;

out vec4 fColor;

out gl_PerVertex {
  vec4 gl_Position;
  float gl_PointSize;
  float gl_ClipDistance[];
};

void main() {
	gl_Position = uView * vec4(vPosition2D, 0.0, 1.0);
    fColor = v8Color;
}