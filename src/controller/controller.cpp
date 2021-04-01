//
// Created by Artemiy Shvedov on 01.04.21.
//

#include <TopDownEngine/controller/controller.hpp>

namespace Engine {
    void Controller::Init(DynamicObject *object_ptr) {
        object_ptr_ = object_ptr;
    }
}
