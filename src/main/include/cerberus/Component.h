#pragma once

class Component {
	public:
	virtual void update() = 0;
	virtual void initialize() = 0;
    virtual void deinitialize() = 0;
};