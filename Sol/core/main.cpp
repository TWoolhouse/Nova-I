#include "spch.h"
#define NOVA
#include <nova.h>
#include <iostream>

struct WindowState {
	bool viewport = true;
	bool settings = false;
	bool stats = false;
};

class Sol : public Nova::Application {
public:
	Sol()
		: camera(1280, 720) {
		Nova::Render::Command::VSync(true);
		gui = Nova::gui::App::Create();

		texture = Nova::Texture2D::Create("asset/texture/test.jpg", {});
	}

	~Sol() {
		
	}

	virtual void update() override {

		// ### Render ###
		Nova::Render::Draw(&camera);

		Nova::Draw::Quad(
			Nova::mlb::vec2{ 0.5, 0.5 },
			Nova::mlb::vec2{ 0.5, 0.5 },
			Nova::mlb::vec4{ 0.5, 0.5, 1.0, 1.0 }
		);

		Nova::Draw::Quad(
			Nova::mlb::vec2{ 0.0, 0.0 },
			Nova::mlb::vec2{ 0.75, 0.9 },
			texture
		);

		Nova::Render::Draw();

		gui->begin();

		// ### GUI ###

		if (Nova::gui::BeginMainMenuBar()) {
			if (Nova::gui::BeginMenu("File")) {
				if (Nova::gui::MenuItem("Quit")) {
					Nova::Event::WindowClose close;
					event_callback(close);
				}
				Nova::gui::EndMenu();
			} // File

			if (Nova::gui::BeginMenu("View")) {
				if (Nova::gui::MenuItem("Viewport", 0, windows.viewport)) {
					windows.viewport = !windows.viewport;
				}
				if (Nova::gui::MenuItem("Sol Settings", 0, windows.settings)) {
					windows.settings = !windows.settings;
				}
				if (Nova::gui::MenuItem("Stats", 0, windows.stats)) {
					windows.stats = !windows.stats;
				}
				Nova::gui::EndMenu();
			} // View
			Nova::gui::EndMainMenuBar();
		} // MainMenu

		// Create Dockspace
		Nova::gui::DockSpaceOverViewport(Nova::gui::GetMainViewport());

		if (windows.viewport) {
			if (Nova::gui::Begin("Viewport", &windows.viewport)) {
				const auto& focus_window = Nova::gui::IsWindowFocused();
				const auto& focus_hover = Nova::gui::IsWindowHovered();
				gui->block_events(!focus_window || !focus_hover);

				auto size = Nova::gui::GetContentRegionAvail();
				auto& tex = Nova::RenderState::Get().framebuffer->get_colour();
				auto x = (void*)(intptr_t)tex->id();
				Nova::gui::Image(x, size, { 0,1 }, { 1,0 });
				auto& fbsize = tex->size();
				if (size.x != fbsize.x || size.y != fbsize.y) {
					tex->bind();
					tex->resize(size.x, size.y);
					camera.set(size.x, size.y);
				}
			} Nova::gui::End();
		} // Viewport

		if (windows.settings) {
			if (Nova::gui::Begin("Sol Settings", &windows.settings)) {
				Nova::gui::Text("Viewer");
			} Nova::gui::End();
		} // Sol Settings

		if (windows.stats) {
			if (Nova::gui::Begin("Stats", &windows.stats)) {
				Nova::gui::Text("CPU Time: %f", Nova::DeltaTime::dt() * 1000.0f);
			} Nova::gui::End();
		} // Stats

		gui->end();

	}

	virtual void event(Nova::Event::Event& event) override {
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
			camera.zoom(off * Nova::DeltaTime::dt());
		}

	}

private:
	Nova::Camera::Ortho camera;
	Nova::Star<Nova::gui::App> gui;
	Nova::Star<Nova::Texture2D> texture;
	WindowState windows;
};

Nova::Application* Nova::Application::Create() {
	return new Sol();
}