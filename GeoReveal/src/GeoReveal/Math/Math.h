#pragma once
#include "GeoReveal/Core/Core.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/matrix_decompose.hpp>
#include <glm/gtx/compatibility.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/hash.hpp>
#include <glm/glm.hpp>

namespace std {
	inline std::ostream& operator<<(std::ostream& os, const glm::quat& vector) { return os << glm::to_string(vector); }

	inline std::ostream& operator<<(std::ostream& os, const glm::vec4& vector) { return os << glm::to_string(vector); }
	inline std::ostream& operator<<(std::ostream& os, const glm::ivec4& vector) { return os << glm::to_string(vector); }
	inline std::ostream& operator<<(std::ostream& os, const glm::uvec4& vector) { return os << glm::to_string(vector); }
	inline std::ostream& operator<<(std::ostream& os, const glm::dvec4& vector) { return os << glm::to_string(vector); }

	inline std::ostream& operator<<(std::ostream& os, const glm::vec3& vector) { return os << glm::to_string(vector); }
	inline std::ostream& operator<<(std::ostream& os, const glm::ivec3& vector) { return os << glm::to_string(vector); }
	inline std::ostream& operator<<(std::ostream& os, const glm::uvec3& vector) { return os << glm::to_string(vector); }
	inline std::ostream& operator<<(std::ostream& os, const glm::dvec3& vector) { return os << glm::to_string(vector); }

	inline std::ostream& operator<<(std::ostream& os, const glm::vec2& vector) { return os << glm::to_string(vector); }
	inline std::ostream& operator<<(std::ostream& os, const glm::ivec2& vector) { return os << glm::to_string(vector); }
	inline std::ostream& operator<<(std::ostream& os, const glm::uvec2& vector) { return os << glm::to_string(vector); }
	inline std::ostream& operator<<(std::ostream& os, const glm::dvec2& vector) { return os << glm::to_string(vector); }

	inline std::ostream& operator<<(std::ostream& os, const glm::mat4& vector) { return os << glm::to_string(vector); }
	inline std::ostream& operator<<(std::ostream& os, const glm::mat4x3& vector) { return os << glm::to_string(vector); }
	inline std::ostream& operator<<(std::ostream& os, const glm::mat4x2& vector) { return os << glm::to_string(vector); }

	inline std::ostream& operator<<(std::ostream& os, const glm::mat3& vector) { return os << glm::to_string(vector); }
	inline std::ostream& operator<<(std::ostream& os, const glm::mat3x4& vector) { return os << glm::to_string(vector); }
	inline std::ostream& operator<<(std::ostream& os, const glm::mat3x2& vector) { return os << glm::to_string(vector); }

	inline std::ostream& operator<<(std::ostream& os, const glm::mat2& vector) { return os << glm::to_string(vector); }
	inline std::ostream& operator<<(std::ostream& os, const glm::mat2x4& vector) { return os << glm::to_string(vector); }
	inline std::ostream& operator<<(std::ostream& os, const glm::mat2x3& vector) { return os << glm::to_string(vector); }
}

#define TRANSFORM_UP_DIRECTION glm::vec3(.0f,1.0f,.0f)
#define TRANSFORM_RIGHT_DIRECTION glm::vec3(1.0f,.0f,.0f)
#define TRANSFORM_FOREWARD_DIRECTION glm::vec3(.0f,.0f,-1.0f)

#define PI			3.141592653f
#define PI_2		1.570796326f
#define LOG_2E		1.442695040f
#define M_E			2.718281828f
#define M_RAD2DEG	360.0f / (PI * 2.0f)

namespace GV {
	using PrecisionType = float_t;
	using VecType = glm::vec<2, PrecisionType, glm::defaultp>;
}