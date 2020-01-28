#pragma once

namespace Events {
	class Event {
		public:
			virtual bool Condition() = 0;
			virtual void Initialize() = 0;
			virtual void Update() = 0;

			bool isEnabled = true;
			bool hasFiredOnce = false;
	};
}