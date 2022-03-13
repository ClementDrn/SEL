#pragma once

#include <mutex>
#include <shared_mutex>
#include <thread>


namespace sel {

	using Mutex = std::shared_mutex;

	using ReadLock = std::shared_lock<Mutex>;

	using WriteLock = std::unique_lock<Mutex>;

}
