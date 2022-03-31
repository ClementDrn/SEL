#pragma once

#include <queue>


namespace sel {

	/// @brief Allows to gain acces to a std::priority_queue container.
	/// 
	/// @param q is the std::priority_queue where the wanted container is.
	/// 
	/// @return The std::priority_queue container.
	/// 
	template <class T, class S, class C>
	S& container(std::priority_queue<T, S, C>& q) {
		// stackoverflow.com/questions/4484767/how-to-iterate-over-a-priority-queue
		struct HackedQueue : private std::priority_queue<T, S, C> {
			static S& container(std::priority_queue<T, S, C>& q) {
				return q.* & HackedQueue::c;
			}
		};
		return HackedQueue::container(q);
	}

}
