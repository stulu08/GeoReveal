#pragma once
#include "Node.h"

namespace GV {
	// northpole = 0,-90
	// southpole = 0, 90
	// y coord is flipped
	class GV_API World {
	public:
		World();
		~World();

		void Explore(const VecType& pos);
		bool IsExplored(const VecType& pos) const;

		// in bytes
		inline size_t MaxSize() const {
			size_t value = 0;
			for (uint8_t depth = 0; depth < MAX_TREE_DEPTH; depth++) {
				value += (size_t)std::pow(4, MAX_TREE_DEPTH);
			}
			return value * sizeof(WorldNode);
		}
		inline PrecisionType MinDegree() const {
			return (PrecisionType)180 / (PrecisionType)std::pow(2, MAX_TREE_DEPTH);
		}
	private:
		WorldNode* m_leftRoot;
		WorldNode* m_rightRoot;
	};
}