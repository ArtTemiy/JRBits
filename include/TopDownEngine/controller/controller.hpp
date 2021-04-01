//
// Created by Artemiy Shvedov on 01.04.21.
//

#pragma once

#include <TopDownEngine/object/dynamic_object.hpp>
#include <memory>

namespace Engine {
    /// Class decide what to do
    class Controller {
        DynamicObject *object_ptr_;
    public:
        explicit Controller(DynamicObject *object_ptr = nullptr) : object_ptr_(object_ptr) {}

        /// Initialise with slave Object
        void Init(DynamicObject *object_ptr);

        virtual void Tick(double time_delta) = 0;

        /// Make some decisions depend on event
        virtual bool EventProcess() = 0;
    };

    using ControllerPtr = std::shared_ptr<Controller>;
}