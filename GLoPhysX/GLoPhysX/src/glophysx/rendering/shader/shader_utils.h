#pragma once

#include <string>

namespace GLOPHYSX {

	namespace RENDERING {

		enum ShaderType {
			NONE,
			VERTEX = 1,
			GEOMETRY = 2,
			TESSELATION = 4,
			COMPUTE = 8,
			FRAGMENT = 16,
			PIXEL = 32,
			HULL = 64 // Direct3D nomenclature
		};

		static ShaderType ShaderTypeFromString(std::string type) {
			if (type == "VERTEX") {
				return VERTEX;
			}
			if (type == "GEOMETRY") {
				return GEOMETRY;
			}
			if (type == "TESSELATION") {
				return TESSELATION;
			}
			if (type == "COMPUTE") {
				return COMPUTE;
			}
			if (type == "FRAGMENT") {
				return FRAGMENT;
			}
			if (type == "PIXEL") {
				return PIXEL;
			}
			if (type == "HULL") {
				return HULL;
			}

			return NONE;
		}

		static std::string ShaderTypeToString(ShaderType type) {
			if (type & VERTEX) {
				return "VERTEX";
			}
			if (type & GEOMETRY) {
				return "GEOMETRY";
			}
			if (type & TESSELATION) {
				return "TESSELATION";
			}
			if (type & COMPUTE) {
				return "COMPUTE";
			}
			if (type & FRAGMENT) {
				return "FRAGMENT";
			}
			if (type & PIXEL) {
				return "PIXEL";
			}
			if (type & HULL) {
				return "HULL";
			}

			return "NONE";
		}
	}
}
