#pragma once

#include <cerberus/Component.h>

#include <vector>

namespace components {
namespace {
std::vector<Component*> m_components;
}

void add(Component* component) {
    m_components.push_back(component);
}

void clear() {
    m_components.clear();
}

void initialize() {
    std::cout << "initializing components..." << std::endl;
    for (std::size_t i = 0; i < m_components.size(); i++) {
        std::cout << "initializing component " << i << std::endl;
        if (m_components[i]->isInitialized() == false) {
            m_components[i]->initialize();
            m_components[i]->setInitialized(true);
        }
        std::cout << "is component initialized = " << m_components[i]->isInitialized() << std::endl;
    }
}

void deinitialize() {
    for (std::size_t i = 0; i < m_components.size(); i++) {
        if (m_components[i]->isInitialized() == true) {
            m_components[i]->deinitialize();
            m_components[i]->setInitialized(false);
        }
    }
}

void update() {
    for (std::size_t i = 0; i < m_components.size(); i++) {
        // std::cout << "is component initialized = " << m_components[i]->isInitialized() << std::endl;
        if (m_components[i]->isInitialized() == true && m_components[i]->updateCondition() == true) {
            // std::cout << "updating component " << i << std::endl;
            m_components[i]->update();
        }
    }
}
}  // namespace components