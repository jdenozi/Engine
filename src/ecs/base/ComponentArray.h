#pragma once
#include "Types.h"
#include "utility/Logger.h"

namespace ecs{

    class ComponentArrayInterface{
        ComponentArrayInterface() = default;
        virtual ~ComponentArrayInterface() = default;;
    public:
        virtual void remove(const EntityID id){}
    };

    template<typename T>
    requires IsComponent<T>
    class ComponentArray: public ComponentArrayInterface{

        void insert(const T& t){
            auto it = std::find_if(m_array.cbegin(), m_array.cend(), [&](const T& c){return c.getID() == t.getID();});
            if(it!=m_array.cend()){
                m_array.push_back(it);
            }
        }

        void remove(const T& t) override{
            auto it = std::find_if(m_array.cbegin(), m_array.cend(), [&](const T& c){return c.getID() == t.getID();});
            if(it!=m_array.cend()){
                m_array.erase(it);
            }
        }

        T get(const EntityID id){
            auto it = std::find_if(m_array.cbegin(), m_array.cend(), [&](const T& c){return c.getID() == id;});
            if(it!=m_array.cend()){
                LOG_WARNING(fmt::format("Can't get non existing id {:d}", id));
            }
            return it.get().getID();
        }

    private:
        std::vector<T> m_array;
    };

}
