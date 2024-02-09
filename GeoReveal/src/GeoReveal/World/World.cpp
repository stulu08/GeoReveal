#include "gv_pch.h"
#include "World.h"

namespace GV {
	World::World() {
		m_leftRoot = new WorldNode(-180, -90, 180, 180);
		m_rightRoot = new WorldNode(0, -90, 180, 180);
	}
	World::~World() {
		delete m_leftRoot;
		delete m_rightRoot;
	}
	void World::Explore(const VecType& pos) {
		WorldNode* node = (pos.x >= 0 ? m_rightRoot : m_leftRoot);

		node->Explore(pos);
	}
	bool World::IsExplored(const VecType& pos) const {
		WorldNode* node = (pos.x >= 0 ? m_rightRoot : m_leftRoot);
		return node->IsExplored(pos);
	}
}