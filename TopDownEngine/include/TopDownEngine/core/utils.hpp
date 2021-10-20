//
// Created by Artemiy Shvedov on 03.08.21.
//

#pragma once

#include <glog/logging.h>

namespace Engine {
    inline void LogAndThrow(const std::string& message) {
        LOG(ERROR) << message;
        throw std::runtime_error(message);
    }

    inline void CheckOrThrow(bool expr, const std::string& message) {
        if (!expr) {
            LogAndThrow(message);
        }
    }
}