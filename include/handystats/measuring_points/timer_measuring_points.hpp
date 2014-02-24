#ifndef HANDYSTATS_TIMER_MEASURING_POINTS_H_
#define HANDYSTATS_TIMER_MEASURING_POINTS_H_

#include "handystats/message_queue_impl.hpp"
#include "handystats/events/timer_events.hpp"

inline void HANDY_TIMER_INIT(
		const std::string timer_name,
		const uint64_t instance_id = -1,
		handystats::metrics::timer::time_point timestamp = handystats::metrics::timer::clock::now()
		)
{
	auto message = handystats::events::timer_init_event(timer_name, instance_id, timestamp);
	handystats::message_queue::push_event_message(message);
}

inline void HANDY_TIMER_START(
		const std::string timer_name,
		const uint64_t instance_id = -1,
		handystats::metrics::timer::time_point timestamp = handystats::metrics::timer::clock::now()
		)
{
	auto message = handystats::events::timer_start_event(timer_name, instance_id, timestamp);
	handystats::message_queue::push_event_message(message);
}

inline void HANDY_TIMER_STOP(
		const std::string timer_name,
		const uint64_t instance_id = -1,
		handystats::metrics::timer::time_point timestamp = handystats::metrics::timer::clock::now()
		)
{
	auto message = handystats::events::timer_stop_event(timer_name, instance_id, timestamp);
	handystats::message_queue::push_event_message(message);
}

inline void HANDY_TIMER_DISCARD(
		const std::string timer_name,
		const uint64_t instance_id = -1,
		handystats::metrics::timer::time_point timestamp = handystats::metrics::timer::clock::now()
		)
{
	auto message = handystats::events::timer_discard_event(timer_name, instance_id, timestamp);
	handystats::message_queue::push_event_message(message);
}

inline void HANDY_TIMER_HEARTBEAT(
		const std::string timer_name,
		const uint64_t instance_id = -1,
		handystats::metrics::timer::time_point timestamp = handystats::metrics::timer::clock::now()
		)
{
	auto message = handystats::events::timer_heartbeat_event(timer_name, instance_id, timestamp);
	handystats::message_queue::push_event_message(message);
}

#endif // HANDYSTATS_TIMER_MEASURING_POINTS_H_
