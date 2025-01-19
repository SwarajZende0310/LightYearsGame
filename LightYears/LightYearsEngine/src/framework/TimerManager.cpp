#include"framework/TimerManager.h"

namespace ly
{
    Timer::Timer(weak<Object> weakRef, std::function<void()> callback, float duration, bool repeat)
        : mListener{weakRef,callback},
        mDuration{duration},
        mRepeat{repeat},
        mTimeCounter{0.f},
        mIsExpired{false}
    {

    }

    void Timer::TickTime(float deltaTime)
    {
        if(Expired())return;

        mTimeCounter += deltaTime;
        if(mTimeCounter >= mDuration)
        {
            mListener.second();

            if(mRepeat)mTimeCounter = 0.f;
            else SerExpired();
        }
    }

    bool Timer::Expired() const
    {
        return mIsExpired || mListener.first.expired() || mListener.first.lock()->IsPendingDestroy();
    }

    void Timer::SerExpired()
    {
        mIsExpired = true;
    }

    unique<TimerManager> TimerManager :: timerManager{ nullptr};

    void TimerManager::UpdateTimer(float deltaTime)
    {
        for(auto& timer : mTimers)
        {
            timer.TickTime(deltaTime);
        }
    }

    TimerManager::TimerManager():mTimers{}
    {

    }

    TimerManager &TimerManager::Get()
    {
        if(!timerManager)
        {
            timerManager = std::move(unique<TimerManager>(new TimerManager{}));
        }
        return *timerManager;
    }
}