//
// Layer.h
//

#pragma once

class Layer {
public:
    virtual ~Layer() = default;
    virtual void OnAttach() {}
    virtual void OnDettach() {}

    virtual void Update(float dt) {}
    virtual void GUIRender() {}
};