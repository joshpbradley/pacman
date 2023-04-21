/// <author>
/// Joshua Bradley
/// </author>

#include "Timer.h"

Timer::Timer(unsigned int initial_time, bool loop)
    : kMaximumTime(initial_time),
      kLoop(loop),
      millis_remaining_(initial_time),
      paused_(false) {}

void Timer::Pause(void) {
  paused_ = true;
}

void Timer::Reset(void) {
  millis_remaining_ = kMaximumTime;
}

void Timer::Resume(void) {
  paused_ = false;
}

bool Timer::Update(unsigned int elapsed_millis) {
  if (!paused_) {
    if ((millis_remaining_ -= elapsed_millis) <= 0) {
      if (kLoop) {
        Reset();
      } else {
        Pause();
      }

      return true;
    }
  }

  return false;
}