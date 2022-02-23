#pragma once

#include <queue>


namespace esl {

	// https://stackoverflow.com/questions/4484767/how-to-iterate-over-a-priority-queue
	template <class T, class S, class C>
	S& container(std::priority_queue<T, S, C>& q) {
		struct HackedQueue : private std::priority_queue<T, S, C> {
			static S& container(std::priority_queue<T, S, C>& q) {
				return q.* & HackedQueue::c;
			}
		};
		return HackedQueue::container(q);
	}

}
