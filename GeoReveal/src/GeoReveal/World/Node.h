#pragma once
#include "GeoReveal/Core/Core.h"
#include "GeoReveal/Math/Math.h"

namespace GV {
	
	constexpr int MAX_TREE_DEPTH = 18; // Maximum depth of the quadtree

	enum class NodeState : uint8_t{
		Unexplored, 
		Explored, 
		ContainsExplored
	};

	// Top-left corner orientated
	class WorldNode {
	public:
		WorldNode(PrecisionType x, PrecisionType y, PrecisionType width, PrecisionType height, uint8_t depth = 0, NodeState state = NodeState::Unexplored);
		~WorldNode();

		bool Contains(const VecType& pos) const;
		bool IsExplored(const VecType& pos) const;
		void Explore(const VecType& pos);

		void Subdivide();
		void AllocateQuadrant(uint8_t index);
		void AllocateQuadrant(const VecType& pos);
		uint8_t GetQuadrant(const VecType& pos) const;

		WorldNode* operator[](uint8_t index) {
			return m_children[index];
		}
	public:
		union {
			PrecisionType m_y;
			PrecisionType Latitude = (PrecisionType)53.595011;
		};
		union {
			PrecisionType m_x;
			PrecisionType Longitude = (PrecisionType)7.275600;
		};

	private:
		PrecisionType m_width, m_height;
		uint8_t m_depth;
		NodeState m_state;
		WorldNode* m_children[4];

		void DeleteQuadrants();
	};
}