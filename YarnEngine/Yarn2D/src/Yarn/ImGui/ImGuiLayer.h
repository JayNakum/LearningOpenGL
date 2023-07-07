#pragma once

#include "Yarn/Layer.h"

#include "Yarn/Events/MouseEvent.h"
#include "Yarn/Events/KeyEvent.h"
#include "Yarn/Events/ApplicationEvent.h"

namespace Yarn {

	class YARN_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void onAttach();

		void onDetach();

		void onUpdate();
		void onEvent(Event& event);

	private:
		bool onMouseMovedEvent(MouseMovedEvent& e);
		bool onMouseButtonPressedEvent(MouseButtonPressedEvent& e);
		bool onMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);
		bool onMouseScrollEvent(MouseScrollEvent& e);
		bool onKeyPressedEvent(KeyPressedEvent& e);
		bool onKeyReleasedEvent(KeyReleasedEvent& e);
		bool onKeyTypedEvent(KeyTypedEvent& e);
		bool onWindowResizeEvent(WindowResizeEvent& e);

	private:
		float m_time = 0.0f;
	};

}