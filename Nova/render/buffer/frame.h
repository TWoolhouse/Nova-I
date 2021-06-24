#pragma once
#include "npch.h"
#include "../texture.h"

namespace Nova::Buffer {

	// TEMP CLASS
	class Render {
	public:
		void resize(const unsigned int& width, const unsigned int& height) {}
		void bind() {}
	protected:
		unsigned int m_id;
	};

	class NOVA_API Frame {
	public:
		struct Attachment {
			Attachment() : buffer() { init_array(); }
			Attachment(const Star<Texture2D>& texture) : buffer(texture) { init_array(); }
			Attachment(const Star<Render>& rendered) : buffer(rendered) { init_array(); }

			std::variant<Star<Texture2D>, Star<Render>> buffer;

			operator bool() const {
				return !buffer.valueless_by_exception() && (
					(std::get_if<0>(&buffer) ? std::get<0>(buffer) : false) ||
					(std::get_if<1>(&buffer) ? std::get<1>(buffer) : false));
			}

			template<typename T> const Star<T>& get() const = delete;
			template<> const Star<Texture2D>& get() const { return std::get<Star<Texture2D>>(buffer); };
			template<> const Star<Render>& get() const { return std::get<Star<Render>>(buffer); };

			const Star<Texture2D>& texture() const { return get<Texture2D>(); }
			const Star<Render>& rendered() const { return get<Render>(); }

			void resize(const unsigned int& width, const unsigned int& height) { (this->*func_resize_array[buffer.index()])(width, height); }
		protected:
			void init_array() {
				func_resize_array[0] = &Attachment::resize_impl<0>;
				func_resize_array[1] = &Attachment::resize_impl<1>;
			}

			template<size_t I>
			void resize_impl(const unsigned int& width, const unsigned int& height) { std::get<I>(buffer)->bind(); std::get<I>(buffer)->resize(width, height); }
			void (Attachment::* func_resize_array[2])(const unsigned int&, const unsigned int&);
		};
		static Frame* Create();

		Frame() : ma_colour(), ma_depth_stencil() {}
		virtual void bind() = 0;
		virtual void unbind() = 0;

		virtual const bool validate() = 0;

		const mlb::vec2 size() const { return ma_colour->size(); }
		void resize(const unsigned int& width, const unsigned int& height) {
			ma_colour->bind();
			ma_colour->resize(width, height);
			for (Attachment* attachment = const_cast<Attachment*>(m_buffer_begin); attachment < m_buffer_end; ++attachment) {
				if (*attachment) attachment->resize(width, height);
			}
		}

		virtual void attach_colour(const Star<Texture2D>& texture) = 0;
		virtual void attach_depth_stencil(const Star<Texture2D>& texture) = 0;
		
		const Star<Texture2D>& get_colour() const { return ma_colour; };
		const Attachment& get_depth_stencil() const { return ma_depth_stencil; }
		
		virtual operator bool() = 0;
		virtual ~Frame() {}
	protected:
		Star<Texture2D> ma_colour;
		// Attachemnts must be sequential!
		Attachment ma_depth_stencil;

		// Attachment Block Pointers
		const Attachment* m_buffer_begin = &ma_depth_stencil;
		const Attachment* m_buffer_end = (Attachment*)&m_buffer_begin;
	}; 

}