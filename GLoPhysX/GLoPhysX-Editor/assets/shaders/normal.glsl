#type VERTEX
#version 460 core

layout(location = 0) in vec3 a_position;
layout(location = 1) in vec4 a_color;
layout(location = 2) in vec2 a_texture_coord;
layout(location = 3) in float a_texture_index;
layout(location = 4) in float a_tiling_factor;

out vec4 v_color;
out vec2 v_texture_coord;
out float v_texture_index;
out float v_tiling_factor;

uniform mat4 u_view_projection;
uniform mat4 u_model;

void main()
{
	v_color = a_color;
	v_texture_coord = a_texture_coord;
	v_texture_index = a_texture_index;
	v_tiling_factor = a_tiling_factor;

	gl_Position = u_view_projection * vec4(a_position, 1.0);
}

#type FRAGMENT
#version 460 core

layout(location = 0) out vec4 color1;
layout(location = 1) out uint color2;

uniform float u_tiling_factor;
uniform sampler2D u_textures[32];

in vec4 v_color;
in vec2 v_texture_coord;
in float v_texture_index;
in float v_tiling_factor;

void main()
{
	color1 = texture(u_textures[int(v_texture_index)], v_texture_coord * v_tiling_factor) * v_color;

	color2 = 50;
}