#version 330

in vec3 vertex_color;

out vec4 final_color;

void main(void) {
	//final_color = vec4(1.0f, 0.5f, 0.2f, 1.0f);
	final_color = vec4(vertex_color, 1.0f);
}
