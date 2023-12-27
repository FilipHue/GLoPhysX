#pragma once

#include "glophysx/rendering/shader/shader.h"

#include "shaderc/shaderc.hpp"
#include "spirv_cross/spirv_cross.hpp"
#include "spirv_cross/spirv_glsl.hpp"

#include "glm.hpp"
#include "glad/glad.h"

#include <filesystem>

namespace GLOPHYSX {

	namespace RENDERING {

		static GLenum GetShaderType(ShaderType type) {
			switch (type)
			{
			case NONE:
				GLOP_CORE_WARN("Please specify a shader type");
				exit(-1);
			case VERTEX:
				return GL_VERTEX_SHADER;
			case GEOMETRY:
				return GL_GEOMETRY_SHADER;
			case TESSELATION:
				GLOP_CORE_WARN("Unsupported shader type by the current API ({0})", ShaderTypeToString(type));
				exit(-1);
			case COMPUTE:
				GLOP_CORE_WARN("Unsupported shader type by the current API ({0})", ShaderTypeToString(type));
				exit(-1);
			case FRAGMENT:
				return GL_FRAGMENT_SHADER;
			case PIXEL:
				GLOP_CORE_WARN("Unsupported shader type by the current API ({0})", ShaderTypeToString(type));
				exit(-1);
			case HULL:
				GLOP_CORE_WARN("Unsupported shader type by the current API ({0})", ShaderTypeToString(type));
				exit(-1);
			default:
				GLOP_CORE_WARN("Unkown shader type");
				exit(-1);
			}
		}

		static const char* GetCacheDirectory() { return "assets/cache/shader/opengl"; }
		static void CreateCacheDirectoryIfNeeded()
		{
			std::string cache_directory = GetCacheDirectory();
			if (!std::filesystem::exists(cache_directory))
			{
				std::filesystem::create_directories(cache_directory);
			}
		}

		static const char* GLShaderStageCachedOpenGLFileExtension(GLenum stage)
		{
			switch (stage)
			{
			case GL_VERTEX_SHADER:    return ".cached_opengl.vert";
			case GL_FRAGMENT_SHADER:  return ".cached_opengl.frag";
			}
			GLOP_CORE_CRITICAL("Unkown opengl stage: {0}", std::to_string(stage).c_str());
			exit(-1);
		}

		static const char* GLShaderStageCachedVulkanFileExtension(GLenum stage)
		{
			switch (stage)
			{
			case GL_VERTEX_SHADER:    return ".cached_vulkan.vert";
			case GL_FRAGMENT_SHADER:  return ".cached_vulkan.frag";
			}
			GLOP_CORE_CRITICAL("Unkown vulkan stage: {0}", std::to_string(stage).c_str());
			exit(-1);
		}

		static shaderc_shader_kind GLShaderStageToShaderC(GLenum stage)
		{
			switch (stage)
			{
			case GL_VERTEX_SHADER:   return shaderc_glsl_vertex_shader;
			case GL_FRAGMENT_SHADER: return shaderc_glsl_fragment_shader;
			}
			GLOP_CORE_CRITICAL("Unkown shaderc stage {0}", std::to_string(stage).c_str());
			exit(-1);
		}

		static const char* GLShaderStageToString(GLenum stage)
		{
			switch (stage)
			{
			case GL_VERTEX_SHADER:   return "GL_VERTEX_SHADER";
			case GL_FRAGMENT_SHADER: return "GL_FRAGMENT_SHADER";
			}
			GLOP_CORE_CRITICAL("Unkown shader stage: {0}", std::to_string(stage).c_str());
			return nullptr;
		}

		static std::string GetSPIRVTypeName(const spirv_cross::SPIRType& type)
		{
			switch (type.basetype)
			{
			case spirv_cross::SPIRType::Float:
				return "FLOAT";
			case spirv_cross::SPIRType::Int:
				return "INT";
			case spirv_cross::SPIRType::UInt:
				return "UINT";
			default:
				return "UNKNOWN";
			}
		}
	}
}
