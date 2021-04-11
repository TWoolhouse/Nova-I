#pragma once
#include "npch.h"

namespace Nova {

	namespace Texture {
		struct Colour {
			enum class Type {
				RGBA = 0, RGB,
				RGBAW,
			};
			Type format, inner;
			Colour() = default;
			Colour(const Type& colour) : format(colour), inner(colour) {}
			Colour(const Type& format, const Type& inner) : format(format), inner(inner) {}
		};
		struct Wrap {
			enum class Type : unsigned char {
				Repeat = 0,
				Mirror, ClampEdge, ClampBorder
			};
			Type x, y, z;
			Wrap() : Wrap(Type::Repeat) {}
			Wrap(const Type& x) : Wrap(x, x, x) {}
			Wrap(const Type& x, const Type& y) : Wrap(x, y, x) {}
			Wrap(const Type& x, const Type& y, const Type& z)
				: x(x), y(y), z(z) {}
		};
		struct Filtering {
			enum class Type : unsigned char {
				Linear = 0, Nearest
			};
			Type minify, magnify;
			Filtering() : Filtering(Type::Nearest) {}
			Filtering(const Type& type) : Filtering(type, type) {}
			Filtering(const Type& minify, const Type& magnify)
				: minify(minify), magnify(magnify) {}
		};
		struct Properties {
			Colour colour;
			Wrap wrap;
			Filtering filter;
		};
	}

	class NOVA_API Texture2D {
	public:
		static Texture2D* Create(const Texture::Properties& properties);
		static Texture2D* Create(const unsigned int width, const unsigned int height, const Texture::Properties& properties);
		static Texture2D* Create(const std::string& filename, const Texture::Properties& properties);
		Texture2D(unsigned int width = 0, unsigned int height = 0) : m_width(width), m_height(height) {}

		virtual void bind(unsigned int slot=0) = 0;
		virtual void unbind(unsigned int slot = 0) = 0;

		inline const std::pair<unsigned int, unsigned int> size() const { return { m_width, m_height }; }

		virtual void image(unsigned int slot = 0) = 0;

		virtual operator bool() = 0;

		virtual ~Texture2D() {}
	protected:
		unsigned int m_width, m_height;
	};

}