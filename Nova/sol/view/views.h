#pragma once
#include "base.h"
#include "name.h"
#include "transform.h"
#include "sprite.h"

#define SolViewFin() \
namespace Nova::sol::View { \
	NovaVarTypeListFin(Pack) \
}