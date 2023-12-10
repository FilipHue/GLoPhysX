#type VERTEX
#version 460 core

layout(location = 0) in vec3 a_position;
layout(location = 1) in vec3 a_color;

uniform mat4 u_view_projection;
uniform mat4 u_model;

out vec3 v_color;

void main()
{
	v_color = a_color;
	gl_Position = u_view_projection * u_model * vec4(a_position, 1.0);
}

#type FRAGMENT
#version 460 core

layout(location = 0) out vec4 color;

in vec3 v_color;

void main()
{
	color = vec4(v_color * 0.5 + 0.5, 1.0);
}