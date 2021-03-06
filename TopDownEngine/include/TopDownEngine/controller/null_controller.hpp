//
// Created by Artemiy Shvedov on 30.04.21.
//

#include <TopDownEngine/controller/controller.hpp>

namespace Engine::Controller {

    /// Simple controller what do nothing
    class NullController : public IController<> {
    public:
        explicit NullController(DynamicObject& object) : IController(object) {}

        /// Discards any event
        bool ProcessEvent(const sf::Event &event) override {
            return false;
        }

        void Tick(double time_delta) override {}
    };
}