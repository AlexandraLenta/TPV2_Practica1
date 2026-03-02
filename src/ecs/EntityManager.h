// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include <iostream>
#include <vector>
#include <array>
#include <cassert>

#include "Component.h"
#include "ecs.h"
#include "Entity.h"

namespace ecs {

/*
 * A class for managing the list of entities, groups, etc.
 *
 */
class EntityManager {

public:
	EntityManager();
	virtual ~EntityManager();

	// Adding an entity simply creates an instance of Entity, adds
	// it to the list of entities and returns it to the caller.
	//
	inline Entity* addEntity(ecs::grpId_t gId = ecs::grp::DEFAULT) {

		// create and initialise the entity
		auto e = new Entity(gId, this);
		e->setAlive(true);

		// add the entity 'e' to temporary list of entities. flush() will be called to add them to the entity list at the end of the frame.
		//
		_entsToAdd.push_back(e);

		// return it to the caller
		//
		return e;
	}

	// returns the vector of all entities
	//
	inline const auto& getEntities(grpId_t gId = ecs::grp::DEFAULT) {
		return _entsByGroup[gId];;
	}

	// associates the entity 'e' to the handler 'hId'
	//
	inline void setHandler(hdlrId_t hId, Entity *e) {
		assert(hId < ecs::maxHandlerId);
		_hdlrs[hId] = e;
	}

	// returns the entity associated to the handler 'hId'
	//
	inline Entity* getHandler(hdlrId_t hId) {
		assert(hId < ecs::maxHandlerId);
		return _hdlrs[hId];
	}

	// call update of all entities
	//
	void update() {
		for (auto &ents : _entsByGroup) {
			auto n = ents.size();
			for (auto i = 0u; i < n; i++)
				ents[i]->update();
		}
	}

	// call render of all entities
	//
	void render() {
		for (auto &ents : _entsByGroup) {
			auto n = ents.size();
			for (auto i = 0u; i < n; i++)
				ents[i]->render();
		}
	}

	// eliminate dead entities (the implementation of this method
	// is in Manager.cpp, but we could also defined it here).
	//
	void refresh();

	void flush() {
		for (auto& ent : _entsToAdd) {
			_entsByGroup[ent->groupId()].push_back(ent);
		}
		_entsToAdd.clear();
	}

private:

	std::array<Entity*, maxHandlerId> _hdlrs;
	std::array<std::vector<Entity*>, maxGroupId> _entsByGroup;

	std::vector<Entity*> _entsToAdd;
};

} // end of namespace
