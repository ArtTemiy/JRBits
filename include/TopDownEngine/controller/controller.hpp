//
// Created by Artemiy Shvedov on 01.04.21.
//

#pragma once

#include <TopDownEngine/object/dynamic_object.hpp>

#include <SFML/Window/Event.hpp>

#include <memory>

namespace Engine::Controller {

    /// Class that controls actor (decides what to do depending
    /// on what is happening)
    template <class ObjectType = DynamicObject>
    class IController {
    protected:
        /// object to control
        ObjectType& object_;
    public:
        explicit IController(DynamicObject& object) : object_(object) {}

        virtual void Tick(double time_delta) = 0;

        /// Make some decisions depend on event
        /// @param [in] event Event to process
        /// @return Event was processed and shouldn't be thrown further
        virtual bool ProcessEvent(const sf::Event& event) = 0;
    };

    template <class ObjectType = DynamicObject>
    using ControllerPtr = std::shared_ptr<IController<ObjectType>>;
}