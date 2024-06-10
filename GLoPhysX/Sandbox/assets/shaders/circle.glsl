#type VERTEX
#version 450 core

layout(location = 0) in vec3 a_world_position;
layout(location = 1) in vec3 a_local_position;
layout(location = 2) in vec4 a_color;
layout(location = 3) in float a_thickness;
layout(location = 4) in float a_fade;
layout(location = 5) in int a_entity_id;

layout(location = 0) out vec3 v_local_position;
layout(location = 1) out vec4 v_color;
layout(location = 2) out float v_thickness;
layout(location = 3) out float v_fade;
layout(location = 4) out flat int v_entity_id;

layout(std140, binding = 0) uniform camera
{
	mat4 u_view_projection;
};

void main()
{
	v_local_position = a_local_position;
	v_color = a_color;
	v_thickness = a_thickness;
	v_fade = a_fade;
	v_entity_id = a_entity_id;

	gl_Position = u_view_projection * vec4(a_world_position, 1.0);
}

#type FRAGMENT
#version 450 core

layout(location = 0) out vec4 color;
layout(location = 1) out int entity_id;

layout(location = 0) in vec3 v_local_position;
layout(location = 1) in vec4 v_color;
layout(location = 2) in float v_thickness;
layout(location = 3) in float v_fade;
layout(location = 4) in flat int v_entity_id;

void main()
{
	float distance = 1.0 - length(v_local_position.xy);
	float circle_alpha = smoothstep(0.0, v_fade, distance);
	circle_alpha *= smoothstep(v_thickness + v_fade, v_thickness, distance);

	if (circle_alpha == 0.0)
	{
		discard;
	}

	color = v_color;
	color.a *= circle_alpha;

	entity_id = v_entity_id;
}