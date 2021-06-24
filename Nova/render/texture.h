#pragma once
#include "npch.h"
#include "phys/lib.h"
#include "asset/library.h"

namespace Nova {

	namespace Texture {
		struct Colour {
			enum class Type {
				RGBA = 0, RGB,
				RGBAW,
				DEPTH_STENCIL,
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

			// MipMapping
		};
	}

	class NOVA_API Texture2D : public Asset::Base<Texture2D> {
		inline static Star<Texture2D> LibCreate(const std::string& filename, const Texture::Properties& properties) { return Create(filename, properties); }
		friend class Asset::Library<Texture2D>;
	public:
		class NOVA_API Sub;

		static Star<Texture2D> Create(const Texture::Properties& properties);
		static Star<Texture2D> Create(const unsigned int width, const unsigned int height, const Texture::Properties& properties);
		static Star<Texture2D> Create(const std::string& filename, const Texture::Properties& properties);
		Texture2D(unsigned int width = 0, unsigned int height = 0) : m_width(width), m_height(height) {}

		virtual void bind(unsigned int slot=0) = 0;
		virtual void unbind(unsigned int slot = 0) = 0;

		inline const mlb::vec2 size() const { return { m_width, m_height }; }

		virtual void image(unsigned int slot = 0) = 0;

		virtual void resize(const unsigned int width, const unsigned int height) = 0;
		virtual void set(const unsigned char* data, const unsigned int width, const unsigned int height = 1, const unsigned int xoff = 0, const unsigned int yoff = 0) = 0;

		virtual operator bool() = 0;

		//TEMP
		virtual const unsigned int& id() const = 0;

		virtual ~Texture2D() {}
	protected:
		unsigned int m_width, m_height;
	};

	class NOVA_API Texture2D::Sub {
	public:
		Sub(const Star<Texture2D>& texture, const mlb::vec2& min, const mlb::vec2& max);
		Sub(const Star<Texture2D>& texture, const mlb::vec2& pos, const mlb::vec2& size, const mlb::vec2& grid);

		const Star<Texture2D>& texture() const { return m_texture; }
		const std::array<mlb::vec2, 4>& positions() const { return m_pos; }

	protected:
		const Star<Texture2D> m_texture;
		std::array<mlb::vec2, 4> m_pos;
	};

	namespace Texture {
		class NOVA_API Atlas {
		public:
			Atlas(const Star<Texture2D>& texture, const mlb::vec2& grid) : m_texture(texture), m_grid(grid) {}
			Texture2D::Sub subtexture(const mlb::vec2& pos, const mlb::vec2& size = { 1.0f, 1.0f }) const;
			const Star<Texture2D>& texture() const { return m_texture; }
		protected:
			const Star<Texture2D> m_texture;
			const mlb::vec2 m_grid;
		};
	}

}