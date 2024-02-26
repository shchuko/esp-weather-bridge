#pragma once

#include <lwip/apps/sntp.h>
#include <esp_sntp.h>
#include "weatherBridge/wifi/ap/WiFiAP.hpp"
#include "weatherBridge/wifi/ap/WiFiAPStatus.hpp"

#include "weatherBridge/wifi/client/WiFiClientStatus.hpp"

#include "weatherBridge/FSSettingStore.hpp"
#include "weatherBridge/WeatherBridgeContext.hpp"
#include "weatherBridge/WeatherBridgeSettings.hpp"
#include "weatherBridge/InputPullUpButton.hpp"
#include "weatherBridge/display/WeatherBridgeDisplay.hpp"
#include "weatherBridge/NTPTimeClient.hpp"
#include "weatherBridge/wifi/client/WiFiClientConnector.hpp"
#include "SettingsServer.hpp"

class WeatherBridge {
private:
    fs::FS &fs;
    InputPullUpButton configModeButton;

    bool isConfigurationMode = false;
    bool ntpTimeSyncOk = false;

    WeatherBridgeDisplay display = WeatherBridgeDisplay();

    SettingsServer settingsServer = SettingsServer();
    WiFiAPStatus wifiApStatus = WiFiAPStatus();

    WiFiClientConnector wifiClientConnector = WiFiClientConnector();
    WiFiClientStatus wifiConnectionStatus = WiFiClientStatus();

    FSSettingStore settingStore;
    WeatherBridgeSettings settingsSnapshot;

    WeatherBridgeContext context = WeatherBridgeContext(isConfigurationMode,
                                                        wifiApStatus,
                                                        settingsSnapshot,
                                                        ntpTimeSyncOk,
                                                        wifiConnectionStatus);

public:
    WeatherBridge(fs::FS &fs, int configModeButtonPin) noexcept;

    void begin();

    void loop();
};

