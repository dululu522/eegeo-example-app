// Copyright eeGeo Ltd 2016, All Rights Reserved

#pragma once

#include <map>
#include <string>
#include <vector>
#include "Types.h"
#include "ScreenProperties.h"
#include "EegeoWorld.h"
#include "AppCameraController.h"
#include "IAppModeStatesFactory.h"
#include "IAppModeModel.h"
#include "ApplicationConfiguration.h"
#include "GpsGlobeCameraController.h"
#include "CameraFrustumStreamingVolume.h"
#include "IInitialExperienceModel.h"
#include "IWorldPinsInFocusController.h"
#include "ICallback.h"
#include "ICompassUpdateController.h"
#include "Module.h"

namespace ExampleApp
{
    class MobileExampleApp : private Eegeo::NonCopyable
    {
    private:
        const std::shared_ptr<Eegeo::EegeoWorld> m_world;
        const std::shared_ptr<AppCamera::SdkModel::IAppCameraController> m_cameraController;
        const std::shared_ptr<AppModes::SdkModel::IAppModeStatesFactory> m_appStatesFactory;
        const std::shared_ptr<AppModes::SdkModel::IAppModeModel> m_appModeModel;
        const std::shared_ptr<ExampleApp::ApplicationConfig::ApplicationConfiguration> m_appConfig;
        const std::shared_ptr<Eegeo::Camera::GlobeCamera::GpsGlobeCameraController> m_gpsCameraController;
        const std::shared_ptr<Eegeo::Streaming::CameraFrustumStreamingVolume> m_streamingVolume;
        const std::shared_ptr<InitialExperience::SdkModel::IInitialExperienceModel> m_initialExperienceModel;
        const std::shared_ptr<WorldPins::SdkModel::IWorldPinsInFocusController> m_worldPinsInFocusController;
        const std::shared_ptr<Compass::SdkModel::ICompassUpdateController> m_compassUpdateController;
        const std::shared_ptr<Eegeo::Location::NavigationService> m_navigationService;
        
        std::shared_ptr<Eegeo::Rendering::ScreenProperties> m_screenProperties;
        std::shared_ptr<Eegeo::Rendering::LoadingScreen> m_loadingScreen;
        
        Eegeo::Helpers::CallbackCollection0 m_loadingScreenCallbacks;
        
    public:
        MobileExampleApp(const std::shared_ptr<Eegeo::EegeoWorld>& world,
                         const std::shared_ptr<AppCamera::SdkModel::IAppCameraController>& appCameraController,
                         const std::shared_ptr<AppModes::SdkModel::IAppModeStatesFactory>& appStatesFactory,
                         const std::shared_ptr<AppModes::SdkModel::IAppModeModel>& appModeModel,
                         const std::shared_ptr<ExampleApp::ApplicationConfig::ApplicationConfiguration>& appConfig,
                         const std::shared_ptr<Eegeo::Camera::GlobeCamera::GpsGlobeCameraController>& gpsCameraController,
                         const std::shared_ptr<Eegeo::Streaming::CameraFrustumStreamingVolume>& cameraFrustumStreamingVolume,
                         const std::shared_ptr<Eegeo::Rendering::ScreenProperties>& screenProperties,
                         const std::shared_ptr<Eegeo::Rendering::LoadingScreen>& loadingScreen,
                         const std::shared_ptr<InitialExperience::SdkModel::IInitialExperienceModel>& initialExperienceModel,
                         const std::shared_ptr<WorldPins::SdkModel::IWorldPinsInFocusController>& worldPinsInFocusController,
                         const std::shared_ptr<Compass::SdkModel::ICompassUpdateController>& compassUpdateController,
                         const std::shared_ptr<Eegeo::Location::NavigationService>& navigationService);

        ~MobileExampleApp();

        void OnPause();

        void OnResume();

        void Update (float dt);

        void Draw (float dt);

        void NotifyScreenPropertiesChanged(const std::shared_ptr<Eegeo::Rendering::ScreenProperties>& screenProperties);

        bool IsRunning() const;
        
        void InitialiseApplicationViewState(const TContainer& container);
        
        void RegisterLoadingScreenComplete(Eegeo::Helpers::ICallback0& callback);
        
        void UnregisterLoadingScreenComplete(Eegeo::Helpers::ICallback0& callback);
    };
}