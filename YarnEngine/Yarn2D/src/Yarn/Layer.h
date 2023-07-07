#pragma once

#include "Yarn/Core.h"
#include "Yarn/Events/Event.h"

namespace Yarn {

	class YARN_API Layer
	{
	// TODO: enable and disable a layer
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void onAttach() {}
		virtual void onDetach() {}
		virtual void onUpdate() {}
		virtual void onEvent(Event& event) {}

		inline const std::string& getName() const { return m_debugName; }

	protected:
		std::string m_debugName;
	};

}