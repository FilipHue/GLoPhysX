#type VERTEX
#version 450 core

layout(location = 0) in vec3 a_position;

void main()
{
}

#type GEOMETRY
#version 450 core

layout(points) in;
layout(triangle_strip, max_vertices = 4) out;

void main()
{
}

#type FRAGMENT
#version 450 core

layout(location = 0) out vec4 color;

void main()
{
}
