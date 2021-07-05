#pragma once
#include "npch.h"
#include "cereal.h"

#include <cereal/cereal.hpp>
#include <fstream>

namespace Nova::cereal {

	template<typename T>
	void CornSave(cstring filename, const T& object) {
		std::ofstream stream{ filename, std::ios::binary };
		cereal::BinaryOutputArchive archive{ stream };
		archive(object);
	}
	template<typename T>
	void CornLoad(cstring filename, T& object) {
		std::ifstream stream{ filename, std::ios::binary };
		cereal::BinaryInputArchive archive{ stream };
		archive(object);
	}

}