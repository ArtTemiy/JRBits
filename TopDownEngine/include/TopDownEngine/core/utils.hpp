//
// Created by Artemiy Shvedov on 03.08.21.
//

#pragma once

#include <glog/logging.h>

namespace Engine::Utils {
    inline void LogAndThrow(const std::string& message) {
        LOG(ERROR) << message;
        throw std::runtime_error(message);
    }
}