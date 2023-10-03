#ifndef Timer_h_
#define Timer_h_

/// @brief A timer that can track how much tme has passed.
class Timer {
    private: 
        /// @brief Accumulated time.
        float time;
    
    public:
        /// @brief initializes the time as 0.
        Timer();

        /// @brief Accumulates the time in the time variable.
        /// @param dt Delta Time.
        void Update(float dt);
        /// @brief restarts the timer to 0.
        void Restart();
        /// @brief Getter for the current value of the Timer.
        /// @return second passes since started.
        float Get();
};

#endif