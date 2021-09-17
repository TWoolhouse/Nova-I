#pragma once
#include "npch.h"
#include "../component.h"
#include "serial/cereal.h"

#include "phys/lib.h"
#include "parent.h"

namespace Nova::ecs::Components {

	struct Transform : public Component {
		glm::vec3 pos, rot, scl;

		Transform(const Transform&) = default;
		Transform(
			const glm::vec3& pos = glm::vec3{ 0.0f },
			const glm::vec3& rot = glm::vec3{ 0.0f },
			const glm::vec3& scl = glm::vec3{ 1.0f })
			: pos(pos), rot(rot), scl(scl) {}

		glm::mat4 transform() {
			auto rot_mat = glm::toMat4(glm::quat(rot));
			return glm::translate(pos)
				* rot_mat
				* glm::scale(scl);
		}

		operator glm::mat4 () { return transform(); }
		void combine(const Transform& other) {
			pos += other.pos;
			rot += other.rot;
			scl *= other.scl;
		}

		Transform global(const Entity& entity) {
			Transform comp{ *this };
			global(entity, comp);
			return comp;
		}
	protected:
		void global(const Entity& entity, Transform& transform) {
			auto pcomp = entity.try_get<Parent>();
			if (pcomp) {
				Entity parent{ entity.registry(), pcomp->entity };
				auto& pt = parent.get<Transform>();
				pt.global(parent, transform);
				transform.combine(pt);
			}
		}

		NovaCerealise { serialise(pos, rot, scl); }
	};

}