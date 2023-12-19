#type VERTEX
#version 460 core

layout(location = 0) in vec3 a_position;
layout(location = 1) in vec4 a_color;
layout(location = 2) in vec2 a_texcoord;

out vec4 v_color;
out vec2 v_texcoord;

uniform mat4 u_view_projection;

void main()
{
	v_color = a_color;
	v_texcoord = a_texcoord;
	gl_Position = u_view_projection * vec4(a_position, 1.0);
}

#type FRAGMENT
#version 460 core

layout(location = 0) out vec4 color;

uniform vec3 u_color;
uniform sampler2D u_texture;

in vec2 v_color;
in vec2 v_texcoord;

void main()
{
	//color = texture(u_texture, v_texcoord);
	color = v_color;
}