#pragma once

namespace cbr {
	class Action {
	public:
		virtual void initialize() = 0;
		virtual void deinitialize() = 0;
		virtual void update() = 0;
		virtual bool condition() = 0;
		bool* m_hasFiredOnce = false;
	};
} // namespace cbr