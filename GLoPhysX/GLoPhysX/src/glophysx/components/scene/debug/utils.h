#pragma once

#include "glophysx.h"

#include "box2d/b2_draw.h"

static void sCheckGLError()
{
	GLenum errCode = glGetError();
	if (errCode != GL_NO_ERROR)
	{
		fprintf(stderr, "OpenGL error = %d\n", errCode);
		assert(false);
	}
}

static void sPrintLog(GLuint object)
{
	GLint log_length = 0;
	if (glIsShader(object))
		glGetShaderiv(object, GL_INFO_LOG_LENGTH, &log_length);
	else if (glIsProgram(object))
		glGetProgramiv(object, GL_INFO_LOG_LENGTH, &log_length);
	else
	{
		fprintf(stderr, "printlog: Not a shader or a program\n");
		return;
	}

	char* log = (char*)malloc(log_length);

	if (glIsShader(object))
		glGetShaderInfoLog(object, log_length, NULL, log);
	else if (glIsProgram(object))
		glGetProgramInfoLog(object, log_length, NULL, log);

	fprintf(stderr, "%s", log);
	free(log);
}

static GLuint sCreateShaderFromString(const char* source, GLenum type)
{
	GLuint res = glCreateShader(type);
	const char* sources[] = { source };
	glShaderSource(res, 1, sources, NULL);
	glCompileShader(res);
	GLint compile_ok = GL_FALSE;
	glGetShaderiv(res, GL_COMPILE_STATUS, &compile_ok);
	if (compile_ok == GL_FALSE)
	{
		fprintf(stderr, "Error compiling shader of type %d!\n", type);
		sPrintLog(res);
		glDeleteShader(res);
		return 0;
	}

	return res;
}

static GLuint sCreateShaderProgram(const char* vs, const char* fs)
{
	GLuint vsId = sCreateShaderFromString(vs, GL_VERTEX_SHADER);
	GLuint fsId = sCreateShaderFromString(fs, GL_FRAGMENT_SHADER);
	assert(vsId != 0 && fsId != 0);

	GLuint programId = glCreateProgram();
	glAttachShader(programId, vsId);
	glAttachShader(programId, fsId);
	glBindFragDataLocation(programId, 0, "color");
	glLinkProgram(programId);

	glDeleteShader(vsId);
	glDeleteShader(fsId);

	GLint status = GL_FALSE;
	glGetProgramiv(programId, GL_LINK_STATUS, &status);
	assert(status != GL_FALSE);

	return programId;
}

struct GLRenderPoints {
public:
	void Create()
	{
		const char* vs = \
			"#version 330\n"
			"uniform mat4 projectionMatrix;\n"
			"layout(location = 0) in vec2 v_position;\n"
			"layout(location = 1) in vec4 v_color;\n"
			"layout(location = 2) in float v_size;\n"
			"out vec4 f_color;\n"
			"void main(void)\n"
			"{\n"
			"	f_color = v_color;\n"
			"	gl_Position = projectionMatrix * vec4(v_position, 0.0f, 1.0f);\n"
			"   gl_PointSize = v_size;\n"
			"}\n";

		const char* fs = \
			"#version 330\n"
			"in vec4 f_color;\n"
			"out vec4 color;\n"
			"void main(void)\n"
			"{\n"
			"	color = f_color;\n"
			"}\n";

		m_program_id = sCreateShaderProgram(vs, fs);

		glGenVertexArrays(1, &m_vao);
		glGenBuffers(3, m_vbos);

		glBindVertexArray(m_vao);
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);

		glBindBuffer(GL_ARRAY_BUFFER, m_vbos[0]);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (const void*)0);
		glBufferData(GL_ARRAY_BUFFER, sizeof(m_vertices), m_vertices, GL_DYNAMIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, m_vbos[1]);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (const void*)0);
		glBufferData(GL_ARRAY_BUFFER, sizeof(m_colors), m_colors, GL_DYNAMIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, m_vbos[2]);
		glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, 0, (const void*)0);
		glBufferData(GL_ARRAY_BUFFER, sizeof(m_sizes), m_sizes, GL_DYNAMIC_DRAW);

		sCheckGLError();

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

		m_vertices_count = 0;
	}

	void Destroy()
	{
		if (m_vao)
		{
			glDeleteVertexArrays(1, &m_vao);
			glDeleteBuffers(3, m_vbos);
			m_vao = 0;
		}

		if (m_program_id)
		{
			glDeleteProgram(m_program_id);
			m_program_id = 0;
		}
	}

	void Batch(const b2Vec2& vertices, const b2Color& colors, float size)
	{
		if (m_vertices_count == MAX_VERTICES)
		{
			Flush();
		}
		m_vertices[m_vertices_count] = vertices;
		m_colors[m_vertices_count] = colors;
		m_sizes[m_vertices_count] = size;

		++m_vertices_count;
	}

	void Flush()
	{
		if (m_vertices_count == 0)
		{
			return;
		}

		glUseProgram(m_program_id);

		glUniformMatrix4fv(glGetUniformLocation(m_program_id, "projectionMatrix"), 1, GL_FALSE, &(m_projection[0][0]));

		glBindVertexArray(m_vao);

		glBindBuffer(GL_ARRAY_BUFFER, m_vbos[0]);
		glBufferSubData(GL_ARRAY_BUFFER, 0, m_vertices_count * sizeof(b2Vec2), m_vertices);

		glBindBuffer(GL_ARRAY_BUFFER, m_vbos[1]);
		glBufferSubData(GL_ARRAY_BUFFER, 0, m_vertices_count * sizeof(b2Color), m_colors);

		glBindBuffer(GL_ARRAY_BUFFER, m_vbos[2]);
		glBufferSubData(GL_ARRAY_BUFFER, 0, m_vertices_count * sizeof(float), m_sizes);

		glEnable(GL_PROGRAM_POINT_SIZE);
		glDrawArrays(GL_POINTS, 0, m_vertices_count);
		glDisable(GL_PROGRAM_POINT_SIZE);

		sCheckGLError();

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
		glUseProgram(0);

		m_vertices_count = 0;
	}

	void SetProjection(glm::mat4 projection)
	{
		m_projection = projection;
	}

private:
	static const int MAX_VERTICES = 512;
	b2Vec2 m_vertices[MAX_VERTICES];
	b2Color m_colors[MAX_VERTICES];
	float m_sizes[MAX_VERTICES];

	int m_vertices_count;
	glm::mat4 m_projection;

	GLuint m_vao;
	GLuint m_vbos[3];
	GLuint m_ibo;

	GLuint m_program_id;
};

struct GLRenderLines {
public:
	void Create()
	{
		const char* vs = \
			"#version 330\n"
			"uniform mat4 projectionMatrix;\n"
			"layout(location = 0) in vec2 v_position;\n"
			"layout(location = 1) in vec4 v_color;\n"
			"out vec4 f_color;\n"
			"void main(void)\n"
			"{\n"
			"	f_color = v_color;\n"
			"	gl_Position = projectionMatrix * vec4(v_position, 0.0f, 1.0f);\n"
			"}\n";

		const char* fs = \
			"#version 330\n"
			"in vec4 f_color;\n"
			"out vec4 color;\n"
			"void main(void)\n"
			"{\n"
			"	color = f_color;\n"
			"}\n";

		m_program_id = sCreateShaderProgram(vs, fs);

		glGenVertexArrays(1, &m_vao);
		glGenBuffers(3, m_vbos);

		glBindVertexArray(m_vao);
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);

		glBindBuffer(GL_ARRAY_BUFFER, m_vbos[0]);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (const void*)0);
		glBufferData(GL_ARRAY_BUFFER, sizeof(m_vertices), m_vertices, GL_DYNAMIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, m_vbos[1]);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (const void*)0);
		glBufferData(GL_ARRAY_BUFFER, sizeof(m_colors), m_colors, GL_DYNAMIC_DRAW);

		sCheckGLError();

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

		m_vertices_count = 0;
	}

	void Destroy()
	{
		if (m_vao)
		{
			glDeleteVertexArrays(1, &m_vao);
			glDeleteBuffers(2, m_vbos);
			m_vao = 0;
		}

		if (m_program_id)
		{
			glDeleteProgram(m_program_id);
			m_program_id = 0;
		}
	}

	void Batch(const b2Vec2& vertices, const b2Color& colors)
	{
		if (m_vertices_count == MAX_VERTICES)
		{
			Flush();
		}
		m_vertices[m_vertices_count] = vertices;
		m_colors[m_vertices_count] = colors;

		++m_vertices_count;
	}

	void Flush()
	{
		if (m_vertices_count == 0)
		{
			return;
		}

		glUseProgram(m_program_id);

		glUniformMatrix4fv(glGetUniformLocation(m_program_id, "projectionMatrix"), 1, GL_FALSE, &(m_projection[0][0]));

		glBindVertexArray(m_vao);

		glBindBuffer(GL_ARRAY_BUFFER, m_vbos[0]);
		glBufferSubData(GL_ARRAY_BUFFER, 0, m_vertices_count * sizeof(b2Vec2), m_vertices);

		glBindBuffer(GL_ARRAY_BUFFER, m_vbos[1]);
		glBufferSubData(GL_ARRAY_BUFFER, 0, m_vertices_count * sizeof(b2Color), m_colors);

		glDrawArrays(GL_LINES, 0, m_vertices_count);

		sCheckGLError();

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
		glUseProgram(0);

		m_vertices_count = 0;
	}

	void SetProjection(glm::mat4 projection)
	{
		m_projection = projection;
	}

private:
	static const int MAX_VERTICES = 512 * 2;
	b2Vec2 m_vertices[MAX_VERTICES];
	b2Color m_colors[MAX_VERTICES];
	float m_sizes[MAX_VERTICES];

	int m_vertices_count;
	glm::mat4 m_projection;

	GLuint m_vao;
	GLuint m_vbos[2];
	GLuint m_ibo;

	GLuint m_program_id;
};

struct GLRenderTriangles {
public:
	void Create()
	{
		const char* vs = \
			"#version 330\n"
			"uniform mat4 projectionMatrix;\n"
			"layout(location = 0) in vec2 v_position;\n"
			"layout(location = 1) in vec4 v_color;\n"
			"out vec4 f_color;\n"
			"void main(void)\n"
			"{\n"
			"	f_color = v_color;\n"
			"	gl_Position = projectionMatrix * vec4(v_position, 0.0f, 1.0f);\n"
			"}\n";

		const char* fs = \
			"#version 330\n"
			"in vec4 f_color;\n"
			"out vec4 color;\n"
			"void main(void)\n"
			"{\n"
			"	color = f_color;\n"
			"}\n";

		m_program_id = sCreateShaderProgram(vs, fs);

		glGenVertexArrays(1, &m_vao);
		glGenBuffers(2, m_vbos);

		glBindVertexArray(m_vao);
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);

		glBindBuffer(GL_ARRAY_BUFFER, m_vbos[0]);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (const void*)0);
		glBufferData(GL_ARRAY_BUFFER, sizeof(m_vertices), m_vertices, GL_DYNAMIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, m_vbos[1]);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (const void*)0);
		glBufferData(GL_ARRAY_BUFFER, sizeof(m_colors), m_colors, GL_DYNAMIC_DRAW);

		sCheckGLError();

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

		m_vertices_count = 0;
	}

	void Destroy()
	{
		if (m_vao)
		{
			glDeleteVertexArrays(1, &m_vao);
			glDeleteBuffers(2, m_vbos);
			m_vao = 0;
		}

		if (m_program_id)
		{
			glDeleteProgram(m_program_id);
			m_program_id = 0;
		}
	}

	void Batch(const b2Vec2& vertices, const b2Color& colors)
	{
		if (m_vertices_count == MAX_VERTICES)
		{
			Flush();
		}
		m_vertices[m_vertices_count] = vertices;
		m_colors[m_vertices_count] = colors;

		++m_vertices_count;
	}

	void Flush()
	{
		if (m_vertices_count == 0)
		{
			return;
		}

		glUseProgram(m_program_id);

		glUniformMatrix4fv(glGetUniformLocation(m_program_id, "projectionMatrix"), 1, GL_FALSE, &(m_projection[0][0]));

		glBindVertexArray(m_vao);

		glBindBuffer(GL_ARRAY_BUFFER, m_vbos[0]);
		glBufferSubData(GL_ARRAY_BUFFER, 0, m_vertices_count * sizeof(b2Vec2), m_vertices);

		glBindBuffer(GL_ARRAY_BUFFER, m_vbos[1]);
		glBufferSubData(GL_ARRAY_BUFFER, 0, m_vertices_count * sizeof(b2Color), m_colors);

		glDrawArrays(GL_TRIANGLES, 0, m_vertices_count);

		sCheckGLError();

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
		glUseProgram(0);

		m_vertices_count = 0;
	}

	void SetProjection(glm::mat4 projection)
	{
		m_projection = projection;
	}

private:
	static const int MAX_VERTICES = 512 * 2;
	b2Vec2 m_vertices[MAX_VERTICES];
	b2Color m_colors[MAX_VERTICES];
	float m_sizes[MAX_VERTICES];

	int m_vertices_count;
	glm::mat4 m_projection;

	GLuint m_vao;
	GLuint m_vbos[2];
	GLuint m_ibo;

	GLuint m_program_id;
};
