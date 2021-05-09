//
// Created by Artemiy Shvedov on 06.05.21.
//

#pragma once
namespace Engine {
    /// Class with tick function that called every frame
    class Tickable {
    public:
        /// called every frame
        /// @param [in] time_delta Time passed form precious frame
        virtual void Tick(double time_delta) = 0;
    };
}