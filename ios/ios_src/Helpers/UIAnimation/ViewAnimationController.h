// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <vector>

#include "ViewAnimatorBase.h"

namespace ExampleApp
{
    namespace Helpers
    {
        namespace UIAnimation
        {
            class ViewAnimationController
            {
            public:
                typedef void(^OnAnimationComplete)(UIView*);
                
            private:
                UIView* m_mainView;
                OnAnimationComplete m_forwardCompleteCallback;
                OnAnimationComplete m_reverseCompleteCallback;
                std::vector<ViewAnimatorBase*> m_animators;
                double m_totalDurationSeconds;
                double m_timerSeconds;
                bool m_isPlayingForward;
                
                void StartAnimators();
                
            public:
                ViewAnimationController(UIView* mainView,
                                        OnAnimationComplete forwardCompleteCallback,
                                        OnAnimationComplete reverseCompleteCallback);
                
                ~ViewAnimationController();
                
                void AddAnimator(ViewAnimatorBase* animator);
                
                void DeleteAnimatorsForView(UIView* view);
                
                void Play();
                
                void PlayReverse();
                
                void PlayWithNormalizedOffset(float offset);
                
                void PlayReverseWithNormalizedOffset(float offset);
                
                void SetToNormalizedOffset(float offset);
                
                void Update(double deltaSeconds);
                
                bool IsActive() const;
                
                float GetNormalizedLinearProgress() const;
            };
        }
    }
}
