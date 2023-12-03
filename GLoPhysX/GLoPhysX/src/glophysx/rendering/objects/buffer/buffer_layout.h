#pragma once
/**
* @file shader_data_types.h
* @brief Declaration of ShaderDataType, BufferElement, and BufferLayout classes.
*
* This header file defines key components related to shader data types and buffer layouts within the GLoPhysX RENDERING.
* It introduces the ShaderDataType enum, the BufferElement struct, and the BufferLayout class, providing a comprehensive
* set of tools for managing data types used in shaders and organizing buffer layouts efficiently.
*
* @version 1.0
* @date 2023-10-27
* @author Secareanu Filip
*/

#include "glophysx/core/core.h"

namespace GLOPHYSX {

	namespace RENDERING {

		enum class ShaderDataType {
			None, Float, Float2, Float3, Float4, Int, Int2, Int3, Int4, Mat3, Mat4, Bool
		};

		static uint32_t ShaderDataSize(ShaderDataType type) {
			switch (type)
			{
			case ShaderDataType::Float:
				return 4;
			case ShaderDataType::Float2:
				return 8;
			case ShaderDataType::Float3:
				return 12;
			case ShaderDataType::Float4:
				return 16;
			case ShaderDataType::Int:
				return 4;
			case ShaderDataType::Int2:
				return 8;
			case ShaderDataType::Int3:
				return 12;
			case ShaderDataType::Int4:
				return 16;
			case ShaderDataType::Mat3:
				return 36;
			case ShaderDataType::Mat4:
				return 64;
			case ShaderDataType::Bool:
				return 1;
			default:
				break;
			}

			GLOP_CORE_CRITICAL("Unknown data type");
			exit(-1);
		}

		struct BufferElement {
			ShaderDataType type;
			const char* name;
			uint32_t size;
			uint32_t offset;

			BufferElement() = default;
			GLOP_API BufferElement(ShaderDataType type, const char* name) : type(type), name(name), size(ShaderDataSize(type)), offset(0) {}

			GLOP_API uint32_t GetComponentCount() const {
				switch (type)
				{
					case ShaderDataType::None:
						return 0;
					case ShaderDataType::Float:
						return 1;
					case ShaderDataType::Float2:
						return 2;
					case ShaderDataType::Float3:
						return 3;
					case ShaderDataType::Float4:
						return 4;
					case ShaderDataType::Int:
						return 1;
					case ShaderDataType::Int2:
						return 2;
					case ShaderDataType::Int3:
						return 3;
					case ShaderDataType::Int4:
						return 4;
					case ShaderDataType::Mat3:
						return 9;
					case ShaderDataType::Mat4:
						return 16;
					case ShaderDataType::Bool:
						return 1;
					default:
						break;
				}

				GLOP_CORE_CRITICAL("Unknown data type");
				exit(-1);
			}
		};

		class BufferLayout
		{
		public:
			BufferLayout() {}
			GLOP_API BufferLayout(std::initializer_list<BufferElement> elements) : m_elements(elements) {
				CalculateLayout();
			}

			GLOP_API const std::vector<BufferElement>& GetElements() const { return m_elements; }
			GLOP_API uint32_t GetStride() const { return m_stride; }

			GLOP_API std::vector<BufferElement>::iterator begin() { return m_elements.begin(); }
			GLOP_API std::vector<BufferElement>::iterator end() { return m_elements.end(); }
			GLOP_API std::vector<BufferElement>::const_iterator begin() const { return m_elements.begin(); }
			GLOP_API std::vector<BufferElement>::const_iterator end() const { return m_elements.end(); }

		private:
			void CalculateLayout() {
				uint32_t offset = 0;
				m_stride = 0;

				for (auto& element : m_elements) {
					element.offset = offset;
					offset += element.size;
					m_stride += element.size;
				}
			}

		private:
			std::vector<BufferElement> m_elements;
			uint32_t m_stride = 0;
		};

	}
}
