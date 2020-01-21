#pragma once

namespace Events {
	class Event {
		public:
			bool Condition();
			void Initialize();
			void Update();

			bool isEnabled = true;
			bool hasFiredOnce = false;
	};
}