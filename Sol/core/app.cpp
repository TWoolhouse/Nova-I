#include "spch.h"
#include "app.h"

#include "editor/panels.h"

namespace Sol {

	App::App() :
		camera(new Nova::Camera::Ortho(1280, 720)),
		gui(Nova::gui::App::Create()),
		world(Nova::ecs::World::Create()),
		camera_controller(camera),
		m_panels(Panel::generate()) {

		Nova::Render::Command::VSync(true);

		// Insert Editor World Systems
		world->system<Nova::ecs::sys::Render>();

		// Temporary ECS Test
		auto e = world->instantiate();
		e.emplace<Nova::Component::Name>("My Entity");
		e.emplace<Nova::Component::Transform>(Nova::mlb::vec3{ -1.0, -1.0, 0.0 });
		e.emplace<Nova::Component::Sprite>(Nova::mlb::vec4{0.5, 0.5, 1.0, 1.0});

		auto g = world->instantiate();
		g.emplace<Nova::Component::Name>("Other");

		auto f = world->instantiate();
		f.emplace<Nova::Component::Name>("Child");
		f.emplace<Nova::Component::Parent>(e);
		f.emplace<Nova::Component::Transform>(Nova::mlb::vec3{0.5, 0.5, 0.1});
		auto& sprite = f.emplace<Nova::Component::Sprite>(Nova::mlb::vec4{ 0.0, 0.687, 0.41, 1.0 });
		sprite.texture = Nova::Texture2D::Create("Sol/asset/texture/test.jpg", {});

	}

	void App::update() {

		// ### Render ###
		Nova::Render::Draw(camera);

		if (!gui->blocking())
			camera_controller.update();
		world->update();

		Nova::Render::Draw();

		// ### GUI ###
		gui->begin();
		static bool open_viewport = true;

		// Main Menu Bar at top of Main Window
		if (Nova::gui::BeginMainMenuBar()) {
			if (Nova::gui::BeginMenu("File")) {
				if (Nova::gui::MenuItem("Quit", "Alt+F4")) {
					Nova::Event::WindowClose close;
					event_callback(close);
				}
				Nova::gui::EndMenu();
			} // File

			// Open and Close Windows
			if (Nova::gui::BeginMenu("View")) {
				static std::string view_menu_items[] = {
					// "" is a Seperator
					"", "Settings", "Stats",
					"", "Scene Hierarchy", "Entity",
					"", "Asset Explorer",
				};
				if (Nova::gui::MenuItem("Viewport", 0, open_viewport)) {
					open_viewport = !open_viewport;
				}
				for (auto& name : view_menu_items) {
					if (name.empty()) {
						ImGui::Separator();
						continue;
					}
					auto& panel = m_panels[name];
					if (Nova::gui::MenuItem(name.c_str(), 0, panel->open())) {
						panel->open_toggle();
					}
				}
				Nova::gui::EndMenu();
			} // View
			Nova::gui::EndMainMenuBar();
		} // MainMenu

		// Create Dockspace
		Nova::gui::DockSpaceOverViewport(Nova::gui::GetMainViewport());

		if (open_viewport) {
			Nova::gui::PushStyleVar(ImGuiStyleVar_WindowMinSize, { 100, 100 });
			if (Nova::gui::Begin("Viewport", &open_viewport)) {
				const auto& focus_window = Nova::gui::IsWindowFocused();
				const auto& focus_hover = Nova::gui::IsWindowHovered();
				gui->block_events(!focus_window || !focus_hover);

				auto size = Nova::gui::GetContentRegionAvail();
				auto& fb = Nova::RenderState::Get().framebuffer;
				auto& fbsize = fb->size();
				auto& tex = fb->get_colour();
				Nova::gui::Image(tex, size);
				if (size.x != fbsize.x || size.y != fbsize.y) {
					static_cast<Sol::Panel::Stats*>(m_panels["Stats"])->state("Resize Framebuffer");
					fb->resize(size.x, size.y);
					camera->size(size.x, size.y);
				}
			} Nova::gui::End();
			Nova::gui::PopStyleVar();
		} // Viewport

		// Render all other Panels
		for (auto& [name, panel] : m_panels) {
			panel->render();
		}

		gui->end();
	}

	void App::event(Nova::Event::Event& event) {
		if (auto e = event.cast<Nova::Event::KeyPress>()) {
			if (e.match(Nova::Input::Key::ESCAPE)) {
				Nova::Event::WindowClose close;
				event_callback(close);
			}
		}
		gui->event(event);
		if (event.done) return;

		if (auto e = event.cast<Nova::Event::MouseScroll>()) {
			const auto& off = e.offset().second;
			camera->zoom(off * Nova::DeltaTime::dt());
		}

		world->event(event);

	}

}
