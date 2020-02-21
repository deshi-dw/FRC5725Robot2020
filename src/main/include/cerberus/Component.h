#pragma once

class Component {
   public:
    virtual void update() = 0;
    virtual void initialize() = 0;
    virtual void deinitialize() = 0;

    virtual bool updateCondition() {
        return true;
    }

    bool isInitialized() {
        return m_isInitialized;
    }

    void setInitialized(bool initialized) {
        m_isInitialized = initialized;
    }

   protected:
    bool m_isInitialized = false;
};