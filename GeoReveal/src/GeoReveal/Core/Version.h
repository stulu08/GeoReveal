#pragma once
#include "Core.h"

#define GV_MAKE_VERSION(major, minor, patch) ((((uint32_t)(major)) << 22) | (((uint32_t)(minor)) << 12) | ((uint32_t)(patch)))
namespace GV {
	struct Version {
		uint32_t major = 1;
		uint32_t minor = 0;
		uint32_t patch = 0;

		Version(uint32_t major = 1, uint32_t minor = 0, uint32_t patch = 0)
			: major(major), minor(minor), patch(patch) {}

		operator uint32_t() const {
			return GV_MAKE_VERSION(major, minor, patch);
		}

		std::string to_string() {
			return std::to_string(major) + "." + std::to_string(minor) + "." + std::to_string(patch);
		}
	};
}


inline std::ostream& operator<<(std::ostream& os, const GV::Version& e) {
	return os << e.major << "." << e.minor << "." << e.patch;
}