#pragma once
#include "Types.h"

namespace ecs {
    class System {
        friend class Manager;

    public:

        System() = default;

        virtual ~System() = default;

        void removeEntity(const EntityID id) {
            auto it = std::find(m_entities.cbegin(), m_entities.cend(), id);
            if (it == m_entities.cend()) { return; }
            m_entities.erase(it);
        }

        void addEntity(const EntityID id) {
            m_entities.push_back(id);
        }

        [[nodiscard]] EntitySignature getSignature() const {
            return m_signature;
        }

        template<typename T> void addSignature() {
            m_signature.insert((ComponentType<T>()));
        }

        virtual void start() {
        };

        virtual void update() {
        };

        virtual void destroy() {
        };

        virtual void render() {
        };
    private:
        std::vector<EntityID> m_entities;
        EntitySignature m_signature;
    };

}