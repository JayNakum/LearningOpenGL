#include "Yarn.h"

class TestLayer : public Yarn::Layer
{
public:
	TestLayer()
		: Layer("Example") {}

	void onUpdate() override
	{
		// YARN_TRACE("TestLayer::Update");
	}

	void onEvent(Yarn::Event& event) override
	{
		// YARN_INFO("{0}", event);
	}
};

class SandBox : public Yarn::Application
{
public:
	SandBox()
	{
		// pushLayer(new TestLayer());
		pushOverlay(new Yarn::ImGuiLayer());
	}
	~SandBox()
	{

	}
};

Yarn::Application* Yarn::createApplication()
{
	return new SandBox();
}