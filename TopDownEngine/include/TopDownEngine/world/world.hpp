//
// Created by Artemiy Shvedov on 01.04.21.
//

#pragma once

#include <utility>
#include <TopDownEngine/world/world_fwd.hpp>

#include <TopDownEngine/core/core.hpp>
#include <TopDownEngine/drawable/drawable.hpp>
#include <TopDownEngine/map/map.hpp>
#include <TopDownEngine/object/actor.hpp>
#include <TopDownEngine/interface/interface.hpp>

#include <SFML/Window.hpp>

#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <memory>

namespace Engine {
    class World : public Tickable {
        using ActorSet = std::unordered_set<std::shared_ptr<Actor>>;

        Map map_;
        Drawable::CameraPtr camera_;
        ActorSet static_actors_;
        ActorSet dynamic_actors_;
        ActorSet non_collision_actors_;

        class ActorsIterable {
            std::vector<std::reference_wrapper<ActorSet>> actor_sets_;

            class AllActorsIterator {
                std::vector<std::reference_wrapper<ActorSet>> actor_sets_;
                ActorSet::iterator iterator_;
                size_t index_ = 0;

            public:
                explicit AllActorsIterator(std::vector<std::reference_wrapper<ActorSet>>  actor_sets, bool end = false) : actor_sets_(std::move(actor_sets)) {
                    index_ = end ? actor_sets_.size() : 0;
                    while (index_ < actor_sets_.size() && actor_sets_[index_].get().empty()) {
                        ++index_;
                    }
                    if (index_ < actor_sets_.size()) {
                        iterator_ = actor_sets_[index_].get().begin();
                    }
                }

                bool operator==(const AllActorsIterator& rhs) const {
                    // if end iterator
                    if (index_ >= actor_sets_.size() && index_ == rhs.index_) {
                        return true;
                    }
                    return iterator_ == rhs.iterator_ &&
                           index_ == rhs.index_;
                }

                bool operator!=(const AllActorsIterator& rhs) const {
                    return !(rhs == *this);
                }

                auto& operator++() {
                    ++iterator_;
                    while (iterator_ == actor_sets_[index_].get().end()) {
                        if (++index_ == actor_sets_.size()) {
                            break;
                        }
                        iterator_ = actor_sets_[index_].get().begin();
                    }
                    return *this;
                }

                auto& operator*() const {
                    return *iterator_;
                }
            };

            public:
            explicit ActorsIterable(std::vector<std::reference_wrapper<ActorSet>> actor_sets) : actor_sets_(std::move(actor_sets)) {}

            auto begin() {
                return AllActorsIterator(actor_sets_);
            }
            auto end() {
                return AllActorsIterator(actor_sets_, true);
            }
        };

        class ConstActorsIterable {
            std::vector<std::reference_wrapper<const ActorSet>> actor_sets_;

            class AllActorsIterator {
                std::vector<std::reference_wrapper<const ActorSet>> actor_sets_;
                ActorSet::const_iterator iterator_;
                size_t index_ = 0;

            public:
                explicit AllActorsIterator(std::vector<std::reference_wrapper<const ActorSet>>  actor_sets, bool end = false) : actor_sets_(std::move(actor_sets)) {
                    index_ = end ? actor_sets_.size() : 0;
                    while (index_ < actor_sets_.size() && actor_sets_[index_].get().empty()) {
                        ++index_;
                    }
                    if (index_ < actor_sets_.size()) {
                        iterator_ = actor_sets_[index_].get().begin();
                    }
                }

                bool operator==(const AllActorsIterator& rhs) const {
                    // if end iterator
                    if (index_ >= actor_sets_.size() && index_ == rhs.index_) {
                        return true;
                    }
                    return iterator_ == rhs.iterator_ &&
                           index_ == rhs.index_;
                }

                bool operator!=(const AllActorsIterator& rhs) const {
                    return !(rhs == *this);
                }

                auto& operator++() {
                    ++iterator_;
                    while (iterator_ == actor_sets_[index_].get().end()) {
                        if (++index_ == actor_sets_.size()) {
                            break;
                        }
                        iterator_ = actor_sets_[index_].get().begin();
                    }
                    return *this;
                }

                auto& operator*() const {
                    return *iterator_;
                }
            };

            public:
            explicit ConstActorsIterable(std::vector<std::reference_wrapper<const ActorSet>> actor_sets) : actor_sets_(std::move(actor_sets)) {}

            auto begin() {
                return AllActorsIterator(actor_sets_);
            }
            auto end() {
                return AllActorsIterator(actor_sets_, true);
            }
        };

    public:
        World() : map_(0, 0), camera_(nullptr) {}

        const Map& GetMap() const {
            return map_;
        }

        void SetMap(const Map &map);

        Drawable::CameraPtr GetCamera() {
            return camera_;
        }
        const Drawable::CameraPtr GetCamera() const {
            return camera_;
        }

        void SetCamera(const Drawable::CameraPtr camera) {
            camera_ = camera;
            camera_->GetView().setCenter(
                    map_.GetSize()[0] * GameTile::GetTileSize()[0] / 2,
                    map_.GetSize()[1] * GameTile::GetTileSize()[1] / 2);
        }

        void AddActor(const std::shared_ptr<Actor>& actor);

        void AddActor(Actor actor) { AddActor(std::make_shared<Actor>(std::move(actor))); }

        void RemoveActor(const std::shared_ptr<Actor>& actor);

        void ClearActors();

        void OnActorEdit(const std::shared_ptr<Actor>& actor);

        void Draw();

        void Tick(double time_delta) override;

        bool ProcessEvent(sf::Event& event);

        auto Actors() {
            return ActorsIterable({static_actors_, dynamic_actors_, non_collision_actors_});
        }

        auto Actors() const {
            return ConstActorsIterable({static_actors_, dynamic_actors_, non_collision_actors_});
        }

        /// Returns actors that are inside given box
        ActorSet ActorsInArea(const Object& box);
        ActorSet ActorsInArea(const Coordinates& center, const Size size) { return ActorsInArea(Object(center - size / 2, size)); }
    };
}
