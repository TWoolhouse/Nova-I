#pragma once
#include "fpch.h"
#include <nova.h>
#include <sol.h>

class Flare final : public Nova::Application {
public:
	Flare();
	virtual ~Flare();

	virtual void update() final override;
	virtual void event(Nova::Event::Event& event) final override;
};
