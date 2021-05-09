//
// Created by Artemiy Shvedov on 30.04.21.
//

#include <TopDownEngine/object/dynamic_object.hpp>

#include <SFML/Graphics.hpp>

namespace Engine::Drawable {
    /// Camera for world. Only objects that are inside camera borders
    /// will be drawn on the screen
    /// ICamera is a interface but defines all general fields and methods
    class ICamera : public DynamicObject {
        /// Game window
        sf::RenderWindow& window_;

        /// View to set
        sf::View view_;

    public:
        explicit ICamera(sf::RenderWindow &window, const Coordinates& coordinates = {0, 0});

        sf::View& GetView() {
            return view_;
        }

        void UpdateView();

        /// Draws sprite in given coordinates
        void DrawSprite(sf::Sprite& sprite);

        void Tick(double time_delta) override {
            UpdateView();
        }
    };

    /// Inplementation with controller
    template<class ControllerT>
    class Camera : public ICamera {
        ControllerT controller_;

    public:
        Camera(sf::RenderWindow &window, const Coordinates &coordinates)
        : ICamera(window, coordinates),
          controller_(*this) {
        }

        auto& GetController() {
            return controller_;
        }

        void Tick(double time_delta) override {
            controller_.Tick(time_delta);
            ICamera::Tick(time_delta);
        }
    };
}