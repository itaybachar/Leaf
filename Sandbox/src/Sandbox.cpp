#include <Leaf.h>

class ExampleLayer : public Leaf::Layer {
public:
	ExampleLayer(const std::string name)
		: Leaf::Layer(name)
	{

	}

	virtual void OnAttach() override {
		LF_INFO("{0} Attached", GetName());
	}
	virtual void OnDetach() override {
		LF_INFO("{0} Detached", GetName());
	}

	virtual void OnUpdate() override {
		//LF_INFO("{0} Updated", GetName());
	}
	
	virtual void OnEvent(Leaf::IEvent& e) override {
		LF_TRACE("{0}", e);
	}
};

class Sandbox : public Leaf::Application
{
public:
	Sandbox() {
		PushLayer(new ExampleLayer("Layer1"));
		PushOverlay(new ExampleLayer("Overlay1"));
	}
	~Sandbox() {}
};

Leaf::Application* Leaf::CreateLeaf() {
	
	return new Sandbox();
}