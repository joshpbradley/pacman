/// <author>
/// Joshua Bradley
/// </author>

#pragma once

/// <summary>
/// Handles the timing of events throughout the game.
/// </summary>
class Timer {
 public:
  /// <summary>
  /// Constructor for the TImer class.
  /// </summary>
  /// <param name="maximum_time">
  /// Determines whether the timer should act on a loop (i.e., reset as soon as the timer has expired).
  /// True if the timer should loop, else false.
  /// </param>
  /// <param name="loop">
  /// Determines whether the timer should act on a loop (i.e., reset as soon as the timer has expired).
  /// True if the timer should loop, else false.
  /// </param>
  Timer(unsigned int maximum_time, bool loop);
  /// <summary>
  /// Pauses the timer.
  /// </summary>
  void Pause(void);
  /// <summary>
  /// Resets the timer. This is called automatically when the timer expires if it has been set to loop.
  /// </summary>
  void Reset(void);
  /// <summary>
  /// Resumes a paused timer.
  /// </summary>
  void Resume(void);
  /// <summary>
  /// Decreases the time remaining on the timer.
  /// </summary>
  /// <param name="elapsed_millis">The amount of time in milliseconds to deduct from the timer.</param>
  /// <returns>True if the timer has expired, else false. It always returns false if the timer is paused.</returns>
  bool Update(unsigned int elapsed_millis);

 private:
  /// <summary>
  /// The initial time of the timer in milliseconds, upon starting or reset.
  /// </summary>
  const unsigned int kMaximumTime;
  /// <summary>
  /// Determines whether the timer should act on a loop (i.e., reset as soon as the timer has expired).
  /// True if the timer should loop, else false.
  /// </summary>
  const bool kLoop;
  /// <summary>
  /// The number of milliseconds till the timer expires.
  /// </summary>
  int millis_remaining_;
  /// <summary>
  /// Determines whether the timer should be active.
  /// True if the timer should be inactive, else false.
  /// </summary>
  bool paused_;
};