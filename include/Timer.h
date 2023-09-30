#ifndef Timer_h_
#define Timer_h_

class Timer {
    private: 
        float time;
    
    public:
        Timer();

        void Update(float dt);
        void Restart();
        float Get();
};

#endif