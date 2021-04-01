#pragma once
#include "npch.h"

namespace Nova {

	namespace Texture {
		struct Wrap {
			enum class Type : unsigned char {
				Repeat = 0,
				Mirror, ClampEdge, ClampBorder
			};
			Type x, y, z;
			Wrap(const Type& x, const Type& y, const Type& z)
				: x(x), y(y), z(z) {}
			Wrap(const Type& x, const Type& y) : Wrap(x, y, x) {}
			Wrap(const Type& x) : Wrap(x, x, x) {}
			Wrap() : Wrap(Type::Repeat) {}
		};
		struct Filtering {
			enum class Type : unsigned char {
				Linear = 0, Nearest
			};
			Type minify, magnify;
			Filtering(const Type& minify, const Type& magnify)
				: minify(minify), magnify(magnify) {}
			Filtering(const Type& type) : Filtering(type, type) {}
			Filtering() : Filtering(Type::Nearest) {}
		};
	}

	class NOVA_API Texture2D {
	public:
		static Texture2D* Create(const Texture::Wrap& wrap, const Texture::Filtering& filter);
		static Texture2D* Create(const std::string& filename, const Texture::Wrap& wrap, const Texture::Filtering& filter);

		virtual void bind() = 0;
		virtual void unbind() = 0;

		virtual operator bool() = 0;

		virtual ~Texture2D() {}
	};

}