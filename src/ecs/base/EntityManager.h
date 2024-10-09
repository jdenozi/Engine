#pragma once

#include <queue>
#include <map>
#include <memory>
#include "Types.h"
#include "System.h"
#include "Component.h"
#include "ComponentArray.h"

namespace ecs {
    class EntityManager {
    public:
        EntityManager() : m_entity_count{}, m_available_entities(), m_entities_signatures(), m_register_systems(), m_component_arrays() {
            for (EntityID id = 0u; id < MAX_ENTITY_COUNT; id++) {
                m_available_entities.push(id);
            }
        }

        ~EntityManager() = default;

        void update(){
            for(auto& system : m_register_systems){
                system.second->get()->update();
            }
        }

        void render(){
            for(auto& system : m_register_systems){
                system.second->get()->render();
            }
        }

        EntityID addEntity() {
            const EntityID entityID = m_available_entities.front();
            m_available_entities.pop();
            m_entity_count++;
            return entityID;
        }

        void removeEntity(const EntityID id) {
            if (id > MAX_ENTITY_COUNT) {
                LOG_ERROR(fmt::format("Entity {:d} out of range", id));
                return;
            }
            m_entities_signatures.erase(id);
            for (auto &array: m_component_arrays) {
                array.second->remove(id);
            }
            for (auto &array: m_entities_signatures) {
                array.second->erase(id);
            }
            m_entity_count--;
        }


        template<typename T, typename ... Args>
        void addComponent(const EntityID id, Args&& ...args){
            if (id > MAX_ENTITY_COUNT) {
                LOG_ERROR(fmt::format("Entity {:d} out of range", id));
                return;
            }
            T component(std::forward<Args>(args)...);
            component.entityID = id;
            getComponentArray<T>()->insert(component);

            const ComponentTypeID componentTypeID = ComponentType<T>();
            m_entities_signatures.at(id)->insert(componentTypeID);
            //attachEntitityToSystem(id);
        }

        template<typename T>
        void addComponentsArray(){
            const auto componentTypeID = ComponentType<T>();
            if(m_component_arrays.find(componentTypeID) == m_component_arrays.cend()){
                LOG_ERROR(fmt::format("Component list {:d} already registered", componentTypeID));
                return;
            }
            m_component_arrays[componentTypeID]  = std::move(std::make_shared<ComponentArray<T>>());
        }

        template<typename T>
        std::shared_ptr<ComponentArrayInterface> getComponentArray(){
            const ComponentTypeID component_type_id = ComponentType<T>();
            return m_component_arrays.at(component_type_id);
        }

        void addEntitySignature(const EntityID id){
            if(m_entities_signatures.find(id) == m_entities_signatures.cend()){
                LOG_ERROR(fmt::format("Signature{:d} not found", id));
            }
            m_entities_signatures[id] = std::move(std::make_shared<EntitySignature>());
        }


    private:
        int m_entity_count;
        std::queue<EntityID> m_available_entities;
        std::map<EntityID, std::shared_ptr<EntitySignature>> m_entities_signatures;
        std::map<SystemTypeID, std::shared_ptr<std::unique_ptr<System>>> m_register_systems;
        std::map<ComponentTypeID, std::shared_ptr<ComponentArrayInterface>> m_component_arrays;
    };
}