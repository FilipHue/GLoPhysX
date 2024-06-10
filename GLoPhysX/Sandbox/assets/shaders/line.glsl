#type VERTEX
#version 450 core

layout(location = 0) in vec3 a_position;
layout(location = 1) in vec4 a_color;
layout(location = 2) in int a_entity_id;

layout(location = 0) out vec4 v_color;
layout(location = 1) out flat int v_entity_id;

layout(std140, binding = 0) uniform camera
{
	mat4 u_view_projection;
};

void main()
{
	v_color = a_color;
	v_entity_id = a_entity_id;

	gl_Position = u_view_projection * vec4(a_position, 1.0);
}

#type FRAGMENT
#version 450 core

layout(location = 0) out vec4 color;
layout(location = 1) out int entity_id;

layout(location = 0) in vec4 v_color;
layout(location = 1) in flat int v_entity_id;

void main()
{
	color = v_color;

	entity_id = v_entity_id;
}