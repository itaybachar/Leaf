#include "lfpch.h"
#include "Leaf/ImGui/ImGuiLayer.h"
#include "Leaf/Application.h"
#include "platforms/OpenGL/ImGuiRenderer.h"
#include "Leaf/Logger.h"
#include "Leaf/KeyCodes.h"
#include "Leaf/Inputs.h";

#include <glad/glad.h>
#include <GLFW\glfw3.h>

namespace Leaf {

	ImGuiLayer::~ImGuiLayer()
	{
	}

	void ImGuiLayer::OnAttach()
	{
		ImGui::CreateContext();
		ImGui::StyleColorsDark();

		ImGuiIO& io = ImGui::GetIO();
		io.BackendFlags |= ImGuiBackendFlags_::ImGuiBackendFlags_HasMouseCursors;
		io.BackendFlags |= ImGuiBackendFlags_::ImGuiBackendFlags_HasSetMousePos;
		io.KeyMap[ImGuiKey_Tab] = LF_KEY_SPACE;
		// Keyboard mapping.
		io.KeyMap[ImGuiKey_Tab] = LF_KEY_TAB;
		io.KeyMap[ImGuiKey_LeftArrow] = LF_KEY_LEFT;
		io.KeyMap[ImGuiKey_RightArrow] = LF_KEY_RIGHT;
		io.KeyMap[ImGuiKey_UpArrow] = LF_KEY_UP;
		io.KeyMap[ImGuiKey_DownArrow] = LF_KEY_DOWN;
		io.KeyMap[ImGuiKey_PageUp] = LF_KEY_PAGE_UP;
		io.KeyMap[ImGuiKey_PageDown] = LF_KEY_PAGE_DOWN;
		io.KeyMap[ImGuiKey_Home] = LF_KEY_HOME;
		io.KeyMap[ImGuiKey_End] = LF_KEY_END;
		io.KeyMap[ImGuiKey_Insert] = LF_KEY_INSERT;
		io.KeyMap[ImGuiKey_Delete] = LF_KEY_DELETE;
		io.KeyMap[ImGuiKey_Backspace] = LF_KEY_BACKSPACE;
		io.KeyMap[ImGuiKey_Space] = LF_KEY_SPACE;
		io.KeyMap[ImGuiKey_Enter] = LF_KEY_ENTER;
		io.KeyMap[ImGuiKey_Escape] = LF_KEY_ESCAPE;
		io.KeyMap[ImGuiKey_KeyPadEnter] = LF_KEY_KP_ENTER;
		io.KeyMap[ImGuiKey_A] = LF_KEY_A;
		io.KeyMap[ImGuiKey_C] = LF_KEY_C;
		io.KeyMap[ImGuiKey_V] = LF_KEY_V;
		io.KeyMap[ImGuiKey_X] = LF_KEY_X;
		io.KeyMap[ImGuiKey_Y] = LF_KEY_Y;
		io.KeyMap[ImGuiKey_Z] = LF_KEY_Z;

		ImGui_ImplOpenGL3_Init("#version 410");
	}

	void ImGuiLayer::OnDetach()
	{
	}

	void ImGuiLayer::OnUpdate()
	{
		ImGuiIO& io = ImGui::GetIO();
		auto& app = Application::Get();
		io.DisplaySize = ImVec2((float)app.GetWindow().GetWidth(), (float)app.GetWindow().GetHeight());

		double time = (double)glfwGetTime();
		io.DeltaTime = time > 0.0 ? (float)(time - m_Time) : (1.0f / 60.0f);
		m_Time = time;

		if (Inputs::IsKeyPressed(LF_KEY_TAB))
			LF_CORE_WARN("Tab is pressed!");

		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();
		
		static bool show = true;

		ImGui::ShowDemoWindow(&show);

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void ImGuiLayer::OnEvent(IEvent& e)
	{
		EventDispatcher disp(e);

		disp.DispatchEvent<MouseButtonPressEvent>(BIND_EVENT_FN(ImGuiLayer::OnMousePress));
		disp.DispatchEvent<MouseButtonReleaseEvent>(BIND_EVENT_FN(ImGuiLayer::OnMouseRelease));
		disp.DispatchEvent<MouseMoveEvent>(BIND_EVENT_FN(ImGuiLayer::OnMouseMove));
		disp.DispatchEvent<MouseScrollEvent>(BIND_EVENT_FN(ImGuiLayer::OnMouseScroll));

		disp.DispatchEvent<KeyPressEvent>(BIND_EVENT_FN(ImGuiLayer::OnKeyPress));
		disp.DispatchEvent<KeyReleaseEvent>(BIND_EVENT_FN(ImGuiLayer::OnKeyRelease));
		disp.DispatchEvent<KeyTypedEvent>(BIND_EVENT_FN(ImGuiLayer::OnKeyTyped));

		disp.DispatchEvent<WindowResizeEvent>(BIND_EVENT_FN(ImGuiLayer::OnResize));
	}

	bool ImGuiLayer::OnMousePress(MouseButtonPressEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseDown[e.GetMouseButton()] = true;

		return false;
	}
	bool ImGuiLayer::OnMouseRelease(MouseButtonReleaseEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseDown[e.GetMouseButton()] = false;

		return false;
	}
	bool ImGuiLayer::OnMouseMove(MouseMoveEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MousePos = ImVec2(e.GetX(),e.GetY());

		return false;
	}
	bool ImGuiLayer::OnMouseScroll(MouseScrollEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseWheel += e.GetYOffset();
		io.MouseWheel += e.GetXOffset();

		return false;
	}
	bool ImGuiLayer::OnKeyPress(KeyPressEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.KeysDown[e.GetKeycode()] = true;

		io.KeyCtrl = io.KeysDown[LF_KEY_LEFT_CONTROL] || io.KeysDown[LF_KEY_RIGHT_CONTROL];
		io.KeyShift = io.KeysDown[LF_KEY_LEFT_SHIFT] || io.KeysDown[LF_KEY_RIGHT_SHIFT];
		io.KeyAlt = io.KeysDown[LF_KEY_LEFT_ALT] || io.KeysDown[LF_KEY_RIGHT_ALT];
		io.KeySuper = io.KeysDown[LF_KEY_LEFT_SUPER] || io.KeysDown[LF_KEY_RIGHT_SUPER];
		return false;
	}

	bool ImGuiLayer::OnKeyRelease(KeyReleaseEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.KeysDown[e.GetKeycode()] = false;

		io.KeyCtrl = io.KeysDown[LF_KEY_LEFT_CONTROL] || io.KeysDown[LF_KEY_RIGHT_CONTROL];
		io.KeyShift = io.KeysDown[LF_KEY_LEFT_SHIFT] || io.KeysDown[LF_KEY_RIGHT_SHIFT];
		io.KeyAlt = io.KeysDown[LF_KEY_LEFT_ALT] || io.KeysDown[LF_KEY_RIGHT_ALT];
		io.KeySuper = io.KeysDown[LF_KEY_LEFT_SUPER] || io.KeysDown[LF_KEY_RIGHT_SUPER];
		return false;
	}

	bool ImGuiLayer::OnKeyTyped(KeyTypedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.AddInputCharacter(e.GetKeycode());

		return false;
	}

	bool ImGuiLayer::OnResize(WindowResizeEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.DisplaySize = ImVec2((float)e.GetWidth(), (float)e.GetHeight());
		io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);
		glViewport(0, 0, e.GetWidth(), e.GetHeight());

		return false;
	}
}