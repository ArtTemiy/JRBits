//
// Created by Artemiy Shvedov on 01.04.21.
//

#pragma once

#include <TopDownEngine/object/dynamic_object.hpp>

#include <SFML/Window/Event.hpp>
#include <glog/logging.h>

#include <memory>
#include <exception>

namespace Engine::Controller {

    /// Class that controls actor (decides what to do depending
    /// on what is happening)
    class IController {
    protected:
    public:
        virtual ~IController() = default;

        virtual void SetControllable(Object*) = 0;

        virtual void Tick(double time_delta) = 0;

        /// Make some decisions depend on event
        /// @param [in] event Event to process
        /// @return Event was processed and shouldn't be thrown further
        virtual bool ProcessEvent(const sf::Event& event) = 0;
    };

    template <class Controllable = Object>
    class Controller : public IController {
    protected:
        Controllable* object_ = nullptr;

    public:
        void SetControllable(Object* object) override;
    };

    template<class Controllable>
    void Controller<Controllable>::SetControllable(Object* object) {
        Object* a;
        DynamicObject* b = dynamic_cast<DynamicObject*>(a);

        object_ = dynamic_cast<Controllable*>(object);
        if (!object_) {
            throw std::runtime_error("Could not cast point to type");
        }
    }

    using ControllerPtr = std::shared_ptr<IController>;
}