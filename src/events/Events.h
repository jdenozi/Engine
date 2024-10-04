#pragma once
class Events {
public:

    Events &operator=(const Events&) = delete;

    Events(const Events& event) = delete;

    static Events &getInstance(){
        static Events ref;
        return ref;
    }

    void polls();

    void init();


private:
    Events();
};

static Events &PoolEvent = Events::getInstance();