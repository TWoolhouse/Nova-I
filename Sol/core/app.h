#include "spch.h"
#include <nova.h>
#include "panel.h"
#include "editor/camera.h"

namespace Sol {
	class App : public Nova::Application {
	public:
		App();
		~App() {}
		virtual void update() override;
		virtual void event(Nova::Event::Event& event) override;

	public:
		Nova::Render::Camera* camera;
		Nova::Star<Nova::imgui::App> gui;
		Nova::Star<Nova::ecs::World> world;
	private:
		Sol::Editor::Camera camera_controller;
		// gui
		std::unordered_map<std::string, Panel::Panel*> m_panels;
	};
}