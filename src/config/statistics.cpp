// Copyright (c) 2014 Yandex LLC. All rights reserved.

#include <handystats/statistics.hpp>

#include "config/statistics_impl.hpp"

namespace handystats { namespace config {

statistics::statistics()
	: moving_interval(1, chrono::time_unit::SEC)
	, histogram_bins(30)
	, tags(
		handystats::statistics::tag::value |
		handystats::statistics::tag::min | handystats::statistics::tag::max |
		handystats::statistics::tag::count | handystats::statistics::tag::sum | handystats::statistics::tag::avg |
		handystats::statistics::tag::moving_count | handystats::statistics::tag::moving_sum | handystats::statistics::tag::moving_avg |
		handystats::statistics::tag::timestamp
	)
	, rate_unit(chrono::time_unit::SEC)
{}

void apply(const rapidjson::Value& config, statistics& statistics_opts) {
	if (!config.IsObject()) {
		return;
	}

	if (config.HasMember("moving-interval")) {
		const rapidjson::Value& moving_interval = config["moving-interval"];
		if (moving_interval.IsUint64() && moving_interval.GetUint64() > 0) {
			statistics_opts.moving_interval = chrono::duration(moving_interval.GetUint64(), chrono::time_unit::MSEC);
		}
	}

	if (config.HasMember("histogram-bins")) {
		const rapidjson::Value& histogram_bins = config["histogram-bins"];
		if (histogram_bins.IsUint64() && histogram_bins.GetUint64() > 0) {
			statistics_opts.histogram_bins = histogram_bins.GetUint64();
		}
	}

	if (config.HasMember("tags")) {
		const rapidjson::Value& tags = config["tags"];

		if (tags.IsArray()) {
			statistics_opts.tags = handystats::statistics::tag::empty;
			for (size_t index = 0; index < tags.Size(); ++index) {
				const rapidjson::Value& tag = tags[index];
				if (tag.IsString()) {
					statistics_opts.tags |= handystats::statistics::tag::from_string(tag.GetString());
				}
			}
		}
	}

	if (config.HasMember("rate-unit")) {
		const rapidjson::Value& rate_unit = config["rate-unit"];

		if (rate_unit.IsString()) {
			try {
				statistics_opts.rate_unit = chrono::time_unit_from_string(rate_unit.GetString());
			}
			catch (const std::logic_error&) {
			}
		}
	}
}

}} // namespace handystats::config
