#pragma once

#define EVENT_NAME static const event_name_t EventName
#define GET_EVENT_NAME virtual const event_name_t& GetEventName() const noexcept override { return EventName; }