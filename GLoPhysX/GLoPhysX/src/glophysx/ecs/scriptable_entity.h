#pragma once

#include "entity.h"

namespace GLOPHYSX {

	namespace COMPONENTS {

		class ScriptableEntity
		{
		public:
			virtual ~ScriptableEntity() {};

			template<typename T>
			T& GetComponent() {
				return m_entity.GetComponent<T>();
			}

		protected:
			virtual void OnCreate() {}
			virtual void OnUpdate(DeltaTime dt) {}
			virtual void OnDestroy() {}

		private:
			Entity m_entity;

			friend class Scene;
		};
	}
}
