#pragma once
#include "npch.h"

namespace Nova::sol::Panel {
	class Base {
	public:
		Base(const std::string& name, const ImGuiWindowFlags& flags = ImGuiWindowFlags_None, const bool& open = true) : m_open(open), m_window_name(name), m_window_flags(flags) {}
		void render() {
			if (m_open) {
				if (Nova::imgui::Begin(m_window_name.c_str(), &m_open, m_window_flags))
					gui();
				Nova::imgui::End();
			}
		}
	protected:
		const std::string m_window_name;
		const ImGuiWindowFlags m_window_flags;
		virtual void gui() = 0;
	private:
		bool m_open;
	};
}