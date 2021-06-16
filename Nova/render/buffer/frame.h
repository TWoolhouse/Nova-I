#pragma once
#include "npch.h"
#include "../texture.h"

namespace Nova::Buffer {

	typedef int Render;

	class NOVA_API Frame {
	public:
		#ifndef NOVA_RELEASE
		typedef std::variant<Star<Texture2D>, Star<Render>> Attachment;
		#else
		union Attachment {
			Star<Texture2D> texture;
			Star<Render> renderbuffer; // RenderBuffer Object
			Attachment() {}
			~Attachment() {}
		};
		#endif // !NOVA_RELEASE
		static Frame* Create();

		Frame() : ma_colour(), ma_depth(), ma_stencil() {}

		virtual void bind() = 0;
		virtual void unbind() = 0;

		virtual const bool validate() = 0;

		virtual void attach_colour(const Star<Texture2D>& texture) = 0;
		virtual void attach_depth_stencil(const Star<Texture2D>& texture) = 0;

		const Star<Texture2D>& get_colour() const { return ma_colour; };
		template<typename T>const Star<T>& get_depth() const = delete;
		template<typename T>const Star<T>& get_stencil() const = delete;
		#ifndef NOVA_RELEASE
		template<>const Star<Texture2D>& get_depth<Texture2D>() const { return std::get<Star<Texture2D>>(ma_depth); }
		template<>const Star<Render>& get_depth<Render>() const { return std::get<Star<Render>>(ma_depth); }

		template<>const Star<Texture2D>& get_stencil<Texture2D>() const { return std::get<Star<Texture2D>>(ma_stencil); }
		template<>const Star<Render>& get_stencil<Render>() const { return std::get<Star<Render>>(ma_stencil); }
		#else
		template<>const Star<Texture2D>& const get_depth<Texture2D>() const { return ma_depth.texture; }
		template<>const Star<Render>& get_depth<Render>() const { return ma_depth.renderbuffer; }

		template<>const Star<Texture2D>& get_stencil<Texture2D>() const { return ma_stencil.texture; }
		template<>const Star<Render>& get_stencil<Render>() const { return ma_stencil.renderbuffer; }
		#endif // !NOVA_RELEASE
		
		virtual operator bool() = 0;
		virtual ~Frame() {}
	protected:
		Star<Texture2D> ma_colour;
		Attachment ma_depth;
		Attachment ma_stencil;

		template<typename T> inline void set_attachment_depth(const Star<T>& depth) = delete;
		template<typename T> inline void set_attachment_stencil(const Star<T>& stencil) = delete;
		#ifndef NOVA_RELEASE
		template<> inline void set_attachment_depth(const Star<Texture2D>& depth) { ma_depth = depth; }
		template<> inline void set_attachment_depth(const Star<Render>& depth) { ma_depth = depth; }

		template<> inline void set_attachment_stencil(const Star<Texture2D>& stencil) { ma_depth = stencil; }
		template<> inline void set_attachment_stencil(const Star<Render>& stencil) { ma_depth = stencil; }
		#else
		template<> inline void set_attachment_depth(const Star<Texture2D>& depth) { ma_depth.texture = depth; }
		template<> inline void set_attachment_depth(const Star<Render>& depth) { ma_depth.renderbuffer = depth; }

		template<> inline void set_attachment_stencil(const Star<Texture2D>& stencil) { ma_stencil.texture = stencil; }
		template<> inline void set_attachment_stencil(const Star<Render>& stencil) { ma_stencil.renderbuffer = stencil; }
		#endif // !NOVA_RELEASE

	}; 

}