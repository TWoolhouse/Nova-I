#pragma once
#include "npch.h"
#include "util/macro.h"

#define CEREAL_SERIALIZE_FUNCTION_NAME cornflake
#define CEREAL_LOAD_FUNCTION_NAME COMBINE(CEREAL_SERIALIZE_FUNCTION_NAME, _load)
#define CEREAL_SAVE_FUNCTION_NAME COMBINE(CEREAL_SERIALIZE_FUNCTION_NAME, _save)
#define CEREAL_LOAD_MINIMAL_FUNCTION_NAME COMBINE(CEREAL_LOAD_FUNCTION_NAME, _minimal)
#define CEREAL_SAVE_MINIMAL_FUNCTION_NAME COMBINE(CEREAL_SAVE_FUNCTION_NAME, _minimal)
#include <cereal/macros.hpp>
#include <cereal/access.hpp>

// Settings
#include <cereal/types/memory.hpp>

// Archives
#include <cereal/archives/binary.hpp>

namespace Nova {
	namespace cereal {
		#define NovaCerealise friend class Nova::cereal::access; template<typename Archive> void CEREAL_SERIALIZE_FUNCTION_NAME(Archive& serialise)
		#define NovaCerealiseExtern(Type, name) template<typename Archive> void CEREAL_SERIALIZE_FUNCTION_NAME(Archive& serialise, Type& name)
		#define NovaCerealRegister(Type) CEREAL_REGISTER_TYPE(Type)
		#define NovaCerealRegisterBase(Type, Base) NovaCerealRegister(Type) CEREAL_REGISTER_POLYMORPHIC_RELATION(Base, Type)
		using namespace ::cereal;
	}
}