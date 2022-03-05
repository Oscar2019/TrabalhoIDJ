#pragma once


class Timer{
    public:
        Timer();

        void update(float dt);
        void Restart();
        float Get();
    private:
        float time;
};