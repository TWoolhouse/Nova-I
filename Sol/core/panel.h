#pragma once
#include "spch.h"
#include <nova.h>

namespace Sol { class App; }
namespace Sol::Panel {
	class Panel {
		friend class App;
	public:
		Panel(const std::string& name, const ImGuiWindowFlags& flags = ImGuiWindowFlags_None, const bool& open = true) : m_window_name(name), m_open(open), m_window_flags(flags) {}
		virtual ~Panel() {}
		const bool open() const { return m_open; }
		void open(const bool open) { m_open = open; }
		void open_toggle() { m_open = !m_open; }
		const std::string& name() const { return m_window_name; }
	protected:
		const std::string m_window_name;
		ImGuiWindowFlags m_window_flags;
		virtual void gui() = 0;
	private:
		bool m_open;
		void render() {
			if (m_open) {
				if (Nova::gui::Begin(m_window_name.c_str(), &m_open, m_window_flags)) {
					gui();
				} Nova::gui::End();
			}
		}
	};
}