#include "spch.h"
#include "app.h"

#include "editor/panels.h"

#include "example/ants.h"

static Ants* ants;

namespace Sol {

	App::App() :
		camera(new Nova::Camera::Ortho(1280, 720)),
		gui(Nova::imgui::App::Create()),
		world(Nova::ecs::World::Create()),
		camera_controller(camera),
		m_panels(Panel::generate()) {

		Nova::Render::Command::VSync(true);

		// Insert Editor World Systems
		world->system<Nova::ecs::sys::Render>();

		// Temporary ECS Test
		auto e = world->instantiate();
		e.emplace<Nova::Component::Name>("My Entity");
		e.emplace<Nova::Component::Transform>(Nova::glm::vec3{ -1.0, -1.0, 0.0 });
		auto& sprite1 = e.emplace<Nova::Component::Sprite>(Nova::glm::vec4{0.5, 0.5, 1.0, 1.0});
		sprite1.texture = Nova::Resource::Stock::Texture::invalid;

		auto g = world->instantiate();
		g.emplace<Nova::Component::Name>("Other");
		g.emplace<Nova::Component::Transform>();

		auto f = world->instantiate();
		f.emplace<Nova::Component::Name>("Child");
		f.emplace<Nova::Component::Parent>(e);
		f.emplace<Nova::Component::Transform>(Nova::glm::vec3{0.5, 0.5, 0.1});
		auto& sprite2 = f.emplace<Nova::Component::Sprite>(Nova::glm::vec4{ 0.0, 0.687, 0.41, 1.0 });
		sprite2.texture = Nova::Texture2D::Create("Sol/texture/test.jpg", {});

		ants = new Ants(16, 1280, 720);
		auto ant = world->instantiate();
		ant.emplace<Nova::Component::Name>("Ants");
		ant.emplace<Nova::Component::Transform>(Nova::glm::vec3{ 1.0, 1.0, 0.0 });
		auto& sprite3 = ant.emplace<Nova::Component::Sprite>();
		sprite3.texture = ants->get_texture();
	}

	void App::update() {

		// ### Render ###
		Nova::Render::Draw(camera);

		ants->update();

		if (!gui->blocking())
			camera_controller.update();
		world->update();

		Nova::Render::Draw();

		// ### GUI ###
		gui->begin();
		static bool open_viewport = true;

		// Main Menu Bar at top of Main Window
		if (Nova::imgui::BeginMainMenuBar()) {
			if (Nova::imgui::BeginMenu("File")) {
				if (Nova::imgui::MenuItem("Quit", "Alt+F4")) {
					Nova::Event::WindowClose close;
					event_callback(close);
				}
				Nova::imgui::EndMenu();
			} // File

			// Open and Close Windows
			if (Nova::imgui::BeginMenu("View")) {
				static std::string view_menu_items[] = {
					// "" is a Seperator
					"", "Settings", "Stats",
					"", "Scene Hierarchy", "Entity",
					"", "Asset Explorer",
				};
				if (Nova::imgui::MenuItem("Viewport", 0, open_viewport)) {
					open_viewport = !open_viewport;
				}
				for (auto& name : view_menu_items) {
					if (name.empty()) {
						ImGui::Separator();
						continue;
					}
					auto& panel = m_panels[name];
					if (Nova::imgui::MenuItem(name.c_str(), 0, panel->open())) {
						panel->open_toggle();
					}
				}
				Nova::imgui::EndMenu();
			} // View
			Nova::imgui::EndMainMenuBar();
		} // MainMenu

		// Create Dockspace
		Nova::imgui::DockSpaceOverViewport(Nova::imgui::GetMainViewport());

		if (open_viewport) {
			Nova::imgui::PushStyleVar(ImGuiStyleVar_WindowMinSize, { 100, 100 });
			if (Nova::imgui::Begin("Viewport", &open_viewport)) {
				const auto& focus_window = Nova::imgui::IsWindowFocused();
				const auto& focus_hover = Nova::imgui::IsWindowHovered();
				gui->block_events(!focus_window || !focus_hover);

				auto size = Nova::imgui::GetContentRegionAvail();
				auto& fb = Nova::Render::State().framebuffer;
				auto& fbsize = fb->size();
				auto& tex = fb->get_colour();
				Nova::imgui::Image(tex, size);
				if (size.x != fbsize.x || size.y != fbsize.y) {
					static_cast<Sol::Panel::Stats*>(m_panels["Stats"])->state("Resize Framebuffer");
					fb->resize(size.x, size.y);
					camera->size(size.x, size.y);
				}
			} Nova::imgui::End();
			Nova::imgui::PopStyleVar();
		} // Viewport

		// Render all other Panels
		for (auto& [name, panel] : m_panels) {
			panel->render();
		}

		gui->end();
	}

	void App::event(Nova::Event::Event& event) {
		ants->event(event);
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
