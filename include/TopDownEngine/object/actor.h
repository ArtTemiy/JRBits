//
// Created by Artemiy Shvedov on 01.04.21.
//

#pragma once

#include <TopDownEngine/Core.h>
#include <TopDownEngine/controller/controller.h>
#include <TopDownEngine/Drawable.hpp>
#include "dynamic_object.h"

namespace Engine {
    /// Actor - dynamic object with controller
    class Actor : public DynamicObject, Drawable {
        ControllerPtr controller_;

    public:
        Actor(DynamicObject object, ControllerPtr controller)
                : DynamicObject(std::move(object)),
                  controller_(std::move(controller)) {
            controller_->Init(this);
        }

        void Tick(double time_delta) override;
    };
}