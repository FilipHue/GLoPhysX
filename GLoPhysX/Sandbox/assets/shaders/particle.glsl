#type VERTEX
#version 450 core

uniform mat4 u_view_projection;
uniform float u_delta_time;
uniform float u_total_time;

struct Particle
{
	vec4 position;
	vec4 velocity;
	vec4 acceleration;

	float dampening;
};

struct ParticleData
{
	vec4 initial_position;
	vec4 initial_velocity;
	vec4 position;
	vec4 velocity;
	vec4 acceleration;
	float initial_delay;
	float initial_lifetime;
	float current_delay;
	float current_lifetime;
	float dampening;
};

layout(std430, binding = 0) buffer particles
{
	ParticleData data[];
};

void main()
{
	if (data[gl_VertexID].current_delay < data[gl_VertexID].initial_delay)
	{
		data[gl_VertexID].current_delay = data[gl_VertexID].current_delay + u_delta_time;
		gl_Position = u_view_projection * vec4(0.0f, 0.0f, 0.0f, 1.0f);
		return;
	}

	vec3 pos = data[gl_VertexID].position.xyz;
	vec3 vel = data[gl_VertexID].velocity.xyz;
	vec3 acc = data[gl_VertexID].acceleration.xyz;

	vel = vel + acc * u_delta_time;
	pos = pos + vel * u_delta_time;
	vel = vel * pow(data[gl_VertexID].dampening, u_delta_time);

	data[gl_VertexID].current_lifetime = data[gl_VertexID].current_lifetime + u_delta_time;
	if (data[gl_VertexID].current_lifetime > data[gl_VertexID].initial_lifetime)
	{
		pos = data[gl_VertexID].initial_position.xyz;
		vel = data[gl_VertexID].initial_velocity.xyz;
		data[gl_VertexID].current_lifetime = 0.0f;
		data[gl_VertexID].current_delay = 0.0f;
	}

	data[gl_VertexID].position = vec4(pos, 1.0f);
	data[gl_VertexID].velocity = vec4(vel, 1.0f);

	gl_Position = u_view_projection * vec4(pos, 1.0f);
}

#type GEOMETRY
#version 450

layout(points) in;
layout(triangle_strip, max_vertices = 4) out;

uniform mat4 u_view_projection;

out vec2 texture_coord;

vec3 vpos = gl_in[0].gl_Position.xyz;
vec3 forward = vec3(0, 0, -1);
vec3 right = normalize(cross(forward, vec3(0, 1, 0)));
vec3 up = normalize(cross(forward, right));

void EmitPoint(vec2 offset)
{
	vec3 pos = right * offset.x + up * offset.y + vpos;
	gl_Position = u_view_projection * vec4(pos, 1.0);
	EmitVertex();
}


void main()
{
	float ds = 0.005f;

	texture_coord = vec2(0, 0);
	EmitPoint(vec2(-ds, -ds));

	texture_coord = vec2(1, 0);
	EmitPoint(vec2(ds, -ds));

	texture_coord = vec2(0, 1);
	EmitPoint(vec2(-ds, ds));

	texture_coord = vec2(1, 1);
	EmitPoint(vec2(ds, ds));

	EndPrimitive();
}

#type FRAGMENT
#version 450 core

layout(location = 0) out vec4 o_color;
in vec2 texture_coord;

uniform vec4 u_color;
uniform sampler2D u_texture;

void main()
{
	o_color = texture(u_texture, texture_coord) * u_color;
}
