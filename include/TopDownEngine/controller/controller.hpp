//
// Created by Artemiy Shvedov on 01.04.21.
//

#pragma once

#include <TopDownEngine/object/dynamic_object.hpp>

#include <SFML/Window/Event.hpp>

#include <memory>

namespace Engine::Controller {
    /// Class decide what to do
    class IController {
    protected:
        DynamicObject *object_ptr_;
    public:
        explicit IController() : object_ptr_(nullptr) {}

        /// Initialise with slave Object
        void Init(DynamicObject *object_ptr);

        virtual void Tick(double time_delta) = 0;

        /// Make some decisions depend on event
        /// @param [in] event Event to process
        /// @return Event was processed
        virtual bool ProcessEvent(const sf::Event& event) = 0;
    };

    using ControllerPtr = std::shared_ptr<IController>;
}