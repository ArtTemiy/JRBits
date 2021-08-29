//
// Created by Artemiy Shvedov on 03.07.21.
//

#pragma once

#include <_gen/actors_creator_helper_list.hpp>

#include <TopDownEngine/object/actor.hpp>

#include <string>

namespace ActorsCreatorHelper {
    class ActorsCreatorHelper {
        static const std::string kPathToConfig;
    public:
        static void CreateActor(ActorsList actor_id);
    };

    inline const std::string ActorsCreatorHelper::kPathToConfig = "configs/actor_cfg.yaml";
}
