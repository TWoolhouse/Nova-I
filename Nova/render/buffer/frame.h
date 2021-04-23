#pragma once
#include "npch.h"
#include "render/texture.h"

namespace Nova::Buffer {

	typedef int Render;

	class NOVA_API Frame {
	public:
		#ifndef NDEBUG
		typedef std::variant<Nova::Texture2D*, Render*> Attachment;
		#else
		union Attachment {
			Nova::Texture2D* texture;
			Render* renderbuffer; // RenderBuffer Object
		};
		#endif // !NDEBUG
		static Frame* Create();

		Frame() : ma_colour(nullptr), ma_depth(), ma_stencil() {}

		virtual void bind() = 0;
		virtual void unbind() = 0;

		virtual const bool validate() = 0;

		virtual void attach_colour(Texture2D* texture) = 0;
		virtual void attach_depth_stencil(Texture2D* texture) = 0;

		Texture2D* const get_colour() const { return ma_colour; };
		template<typename T>T* const get_depth() const = delete;
		template<typename T>T* const get_stencil() const = delete;
		#ifndef NDEBUG
		template<>Texture2D* const get_depth<Texture2D>() const { return std::get<Texture2D*>(ma_depth); }
		template<>Render* const get_depth<Render>() const { return std::get<Render*>(ma_depth); }

		template<>Texture2D* const get_stencil<Texture2D>() const { return std::get<Texture2D*>(ma_stencil); }
		template<>Render* const get_stencil<Render>() const { return std::get<Render*>(ma_stencil); }
		#else
		template<>Texture2D* const get_depth<Texture2D>() const { return ma_depth.texture; }
		template<>Render* const get_depth<Render>() const { return ma_depth.renderbuffer; }

		template<>Texture2D* const get_stencil<Texture2D>() const { return ma_stencil.texture; }
		template<>Render* const get_stencil<Render>() const { return ma_stencil.renderbuffer; }
		#endif // !NDEBUG
		
		virtual operator bool() = 0;
		virtual ~Frame() {
			delete ma_colour;
			#ifndef NDEBUG
			if (auto b = std::get_if<Nova::Texture2D*>(&ma_depth))
				delete* b;
			else if (auto b = std::get_if<Render*>(&ma_depth))
				delete* b;
			if (auto b = std::get_if<Nova::Texture2D*>(&ma_stencil))
				delete* b;
			else if (auto b = std::get_if<Render*>(&ma_stencil))
				delete* b;
			#else
			delete ma_depth.texture;
			delete ma_stencil.texture;
			#endif // !NDEBUG

		}
	protected:
		Texture2D* ma_colour;
		Attachment ma_depth;
		Attachment ma_stencil;

		template<typename T> inline void set_attachment_depth(T* depth) = delete;
		template<typename T> inline void set_attachment_stencil(T* stencil) = delete;
		#ifndef NDEBUG
		template<> inline void set_attachment_depth(Texture2D* depth) { ma_depth = depth; }
		template<> inline void set_attachment_depth(Render* depth) { ma_depth = depth; }

		template<> inline void set_attachment_stencil(Texture2D* stencil) { ma_depth = stencil; }
		template<> inline void set_attachment_stencil(Render* stencil) { ma_depth = stencil; }
		#else
		template<> inline void set_attachment_depth(Texture2D* depth) { ma_depth.texture = depth; }
		template<> inline void set_attachment_depth(Render* depth) { ma_depth.renderbuffer = depth; }

		template<> inline void set_attachment_stencil(Texture2D* stencil) { ma_stencil.texture = stencil; }
		template<> inline void set_attachment_stencil(Render* stencil) { ma_stencil.renderbuffer = stencil; }
		#endif // !NDEBUG

	}; 

}