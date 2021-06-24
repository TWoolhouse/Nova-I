#pragma once
#include "npch.h"
#include "../component.h"

#include "phys/lib.h"
#include "parent.h"

namespace Nova::ecs::Components {

	struct Transform : public Component {
		mlb::vec3 pos, rot, scl;

		Transform(const Transform&) = default;
		Transform(
			const mlb::vec3& pos = mlb::vec3{ 0.0f },
			const mlb::vec3& rot = mlb::vec3{ 0.0f },
			const mlb::vec3& scl = mlb::vec3{ 1.0f })
			: pos(pos), rot(rot), scl(scl) {}

		mlb::mat4 transform() {
			auto rot_mat = mlb::toMat4(mlb::quat(rot));
			return glm::translate(pos)
				* rot_mat
				* glm::scale(scl);
		}

		operator mlb::mat4& () { return transform(); }
		void combine(const Transform& other) {
			pos += other.pos;
			rot += other.rot;
			scl *= other.scl;
		}

		Transform global(Entity& entity) {
			Transform comp{ *this };
			global(entity, comp);
			return comp;
		}
	protected:
		void global(Entity& entity, Transform& transform) {
			auto pcomp = entity.try_get<Parent>();
			if (pcomp) {
				Entity parent{ entity.registry(), pcomp->entity };
				auto& pt = parent.get<Transform>();
				pt.global(parent, transform);
				transform.combine(pt);
			}
		}
	};

}