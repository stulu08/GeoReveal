#include "gv_pch.h"
#include "Node.h"

namespace GV {
	WorldNode::WorldNode(PrecisionType x, PrecisionType y, PrecisionType width, PrecisionType height, uint8_t depth, NodeState state) 
		: m_x(x), m_y(y), m_width(width), m_height(height), m_depth(depth), m_state(state) {
		for (int i = 0; i < 4; ++i) {
			m_children[i] = nullptr;
		}
	}

	WorldNode::~WorldNode() {
		DeleteQuadrants();
	}
	void WorldNode::DeleteQuadrants() {
		for (int i = 0; i < 4; ++i) {
			if (m_children[i])
				delete m_children[i];
		}
	}

	bool WorldNode::IsExplored(const VecType& pos) const {
		if (!Contains(pos)) {
			return false;
		}
		if (m_state == GV::NodeState::Unexplored)
			return false;
		if (m_state == GV::NodeState::Explored)
			return true;

		const uint8_t index = GetQuadrant(pos);
		const WorldNode* quadrant = m_children[index];
		if (!quadrant) {
			return false;
		}
		return quadrant->IsExplored(pos);
	}

	void WorldNode::Explore(const VecType& pos) {
		if (!Contains(pos) || m_state == NodeState::Explored) {
			return;
		}

		if (m_depth == MAX_TREE_DEPTH) {
			m_state = NodeState::Explored;
			return;
		}

		const uint8_t index = GetQuadrant(pos);
		if (!m_children[index]) {
			AllocateQuadrant(index);
		}

		WorldNode* quadrant = m_children[index];
		quadrant->Explore(pos);

		//if(quadrant->m_state == NodeState::Explored)
		m_state = NodeState::ContainsExplored;

		if (m_state == NodeState::ContainsExplored) {
			for (uint8_t i = 0; i < 4; i++) {
				if (!m_children[i] || m_children[i]->m_state != NodeState::Explored)
					return;
			}
			m_state = NodeState::Explored;
			DeleteQuadrants();
		}
	}

	bool WorldNode::Contains(const VecType& pos) const {
		return (pos.x >= m_x && pos.x < m_x + m_width && pos.y >= m_y && pos.y < m_y + m_height);
	}

	void WorldNode::Subdivide() {
		const PrecisionType subWidth = m_width / (PrecisionType)2.0;
		const PrecisionType subHeight = m_height / (PrecisionType)2.0;

		m_children[0] = new WorldNode(m_x, m_y, subWidth, subHeight, m_depth + 1, NodeState::Unexplored);
		m_children[1] = new WorldNode(m_x + subWidth, m_y, subWidth, subHeight, m_depth + 1, NodeState::Unexplored);
		m_children[2] = new WorldNode(m_x, m_y + subHeight, subWidth, subHeight, m_depth + 1, NodeState::Unexplored);
		m_children[3] = new WorldNode(m_x + subWidth, m_y + subHeight, subWidth, subHeight, m_depth + 1, NodeState::Unexplored);
	}
	void WorldNode::AllocateQuadrant(uint8_t index) {
		const PrecisionType subWidth = m_width / (PrecisionType)2.0;
		const PrecisionType subHeight = m_height / (PrecisionType)2.0;
		switch (index)
		{
		case 0:
			m_children[0] = new WorldNode(m_x, m_y, subWidth, subHeight, m_depth + 1, NodeState::Unexplored);
			break;
		case 1:
			m_children[1] = new WorldNode(m_x + subWidth, m_y, subWidth, subHeight, m_depth + 1, NodeState::Unexplored);
			break;
		case 2:
			m_children[2] = new WorldNode(m_x, m_y + subHeight, subWidth, subHeight, m_depth + 1, NodeState::Unexplored);
			break;
		case 3:
			m_children[3] = new WorldNode(m_x + subWidth, m_y + subHeight, subWidth, subHeight, m_depth + 1, NodeState::Unexplored);
			break;
		}
	}
	void WorldNode::AllocateQuadrant(const VecType& pos) {
		const PrecisionType subWidth = m_width / (PrecisionType)2.0;
		const PrecisionType subHeight = m_height / (PrecisionType)2.0;
		const PrecisionType midX = m_x + subWidth;
		const PrecisionType midY = m_y + subHeight;

		if (pos.x < midX) {
			if (pos.y < midY) {
				m_children[0] = new WorldNode(m_x, m_y, subWidth, subHeight, m_depth + 1, NodeState::Unexplored);
			}
			else {
				m_children[2] = new WorldNode(m_x, m_y + subHeight, subWidth, subHeight, m_depth + 1, NodeState::Unexplored);
			}
		}
		else {
			if (pos.y < midY) {
				m_children[1] = new WorldNode(m_x + subWidth, m_y, subWidth, subHeight, m_depth + 1, NodeState::Unexplored);
			}
			else {
				m_children[3] = new WorldNode(m_x + subWidth, m_y + subHeight, subWidth, subHeight, m_depth + 1, NodeState::Unexplored);
			}
		}
	}
	uint8_t WorldNode::GetQuadrant(const VecType& pos) const {
		const PrecisionType midX = m_x + (m_width / (PrecisionType)2.0);
		const PrecisionType midY = m_y + (m_height / (PrecisionType)2.0);

		if (pos.x < midX) {
			if (pos.y < midY) {
				return 0; // Top-left
			}
			else {
				return 2; // Bottom-left
			}
		}
		else {
			if (pos.y < midY) {
				return 1; // Top-right
			}
			else {
				return 3; // Bottom-right
			}
		}
	}

}