type VERTEX
#version 460 core

layout(location = 0) in vec3 a_position;

uniform mat4 u_view_projection;
uniform mat4 u_model;

void main()
{
	gl_Position = u_view_projection * u_model * vec4(a_position, 1.0);
}

#type FRAGMENT
#version 460 core

layout(location = 0) out vec4 color;

uniform vec3 u_color;

void main()
{
	color = vec4(u_color, 1.0);
}