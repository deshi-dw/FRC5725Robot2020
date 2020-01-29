#pragma once

namespace events {
	class Event {
		public:
			virtual bool condition() = 0;
			virtual void initialize() = 0;
			virtual void deinitialize() = 0;
			virtual void update() = 0;

			bool isEnabled = true;
			bool hasFiredOnce = false;
	};
}