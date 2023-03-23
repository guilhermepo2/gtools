//
// Layer.h
//

#pragma once

namespace gtools {
	class Layer {
	public:
		virtual ~Layer() = default;
		virtual void OnAttach() {}
		virtual void OnDettach() {}

		virtual void Update(float dt) {}
		virtual void GUIRender() {}
	};
}