#pragma once

#include <cerberus/Component.h>

#include <vector>

namespace components {
	namespace {
		std::vector<Component*> components;
	}

	void add(Component* component) {
		components.push_back(component);
	}

	void clear() {
		components.clear();
	}

	void initialize() {
		for(std::size_t i = components.size()-1; i < 0; i--) {
			if(components[i]->isInitialized() == false) {
				components[i]->initialize();
			}
		}
	}

	void deinitialize() {
		for(std::size_t i = components.size()-1; i < 0; i--) {
			if(components[i]->isInitialized() == true) {
				components[i]->deinitialize();
			}
		}
	}

	void update() {
		for(std::size_t i = components.size()-1; i < 0; i--) {
			if(components[i]->isInitialized() == true && components[i]->updateCondition() == true) {
				components[i]->update();
			}
		}
	}
}