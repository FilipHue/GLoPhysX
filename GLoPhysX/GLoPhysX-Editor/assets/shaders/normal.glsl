#type VERTEX
#version 450 core

layout(location = 0) in vec3 a_position;
layout(location = 1) in vec4 a_color;
layout(location = 2) in vec2 a_texture_coord;
layout(location = 3) in float a_texture_index;
layout(location = 4) in float a_tiling_factor;
layout(location = 5) in int a_entity_id;

layout(location = 0) out vec4 v_color;
layout(location = 1) out vec2 v_texture_coord;
layout(location = 2) out flat float v_texture_index;
layout(location = 3) out float v_tiling_factor;
layout(location = 4) out flat int v_entity_id;

layout(std140, binding = 0) uniform camera
{
	mat4 u_view_projection;
};

void main()
{
	v_color = a_color;
	v_texture_coord = a_texture_coord;
	v_texture_index = a_texture_index;
	v_tiling_factor = a_tiling_factor;
	v_entity_id = a_entity_id;

	gl_Position = u_view_projection * vec4(a_position, 1.0);
}

#type FRAGMENT
#version 450 core

layout(location = 0) out vec4 color;
layout(location = 1) out int entity_id;

layout(location = 0) in vec4 v_color;
layout(location = 1) in vec2 v_texture_coord;
layout(location = 2) in flat float v_texture_index;
layout(location = 3) in float v_tiling_factor;
layout(location = 4) in flat int v_entity_id;

layout(binding = 0) uniform sampler2D u_textures[32];

void main()
{
	color = texture(u_textures[int(v_texture_index)], v_texture_coord * v_tiling_factor) * v_color;

	entity_id = v_entity_id;
}