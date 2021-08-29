//
// Created by Artemiy Shvedov on 24.08.21.
//

/**
 * Maybe it will bw needed in future,
 * but for now it's totally useless.
 * However don't delete it.
 */

#pragma once

namespace Engine {
    using Id = uint32_t;

    class GarbageCollector {
    public:
        virtual void AddObjectToGarbage(Id id) = 0;
    };

    class BasicObject {
        inline static uint32_t next_id = 0;
        uint32_t id_;
        bool should_be_deleted_ = false;
        GarbageCollector* garbage_collector_;

    public:
        BasicObject(GarbageCollector* garbage_collector) : id_(next_id++), garbage_collector_(garbage_collector) {}
        Id GetId() const { return id_; }

        bool ShouldBeDeleted() const {
            return should_be_deleted_;
        }

        void SetShouldBeDeleted(bool should_be_deleted) {
            should_be_deleted_ = should_be_deleted;
            if (garbage_collector_) {
                garbage_collector_->AddObjectToGarbage(id_);
            }
        }
        /// called every frame
        /// @param [in] time_delta Time passed form precious frame
        virtual void Tick(double time_delta) {};
    };
}