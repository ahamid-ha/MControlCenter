/* Copyright (C) 2022  Dmitry Serov
 *
 * This file is part of MControlCenter.
 *
 * MControlCenter is free software: you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation, either version 3 of
 * the License, or (at your option) any later version.
 *
 * MControlCenter is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with MControlCenter. If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef OPERATE_H
#define OPERATE_H


#include <string>
#include <QString>

enum class charging_state {
    battery_charging,
    battery_discharging,
    battery_not_charging,
    battery_fully_charged,
    battery_fully_charged_no_power,
    battery_unknown
};

enum class user_mode {
    performance_mode,
    balanced_mode,
    silent_mode,
    super_battery_mode,
    extreme_mode,
    unknown_mode
};

enum class fan_mode {
    auto_fan_mode,
    silent_fan_mode,
    basic_fan_mode,
    advanced_fan_mode,
    unknown_fan_mode
};

const int speedsControlCount = 7;
struct FanSpeedProfile {
    int speeds[speedsControlCount];

    void load(const QString &speedsStr);
};

struct FansSpeedProfile {
    FanSpeedProfile cpu;
    FanSpeedProfile gpu;

    void load(const QString &speedsStr);
};

class Operate {
public:
    Operate();
    void closeHelperApp() const;
    [[nodiscard]] bool isEcSysModuleLoaded() const;
    [[nodiscard]] bool loadEcSysModule() const;
    [[nodiscard]] bool updateEcData() const;
    [[nodiscard]] bool doProbe() const;
    [[nodiscard]] std::string getEcVersion() const;
    [[nodiscard]] std::string getEcBuild() const;
    [[nodiscard]] int getBatteryCharge() const;
    [[nodiscard]] int getBatteryThreshold() const;
    [[nodiscard]] charging_state getChargingStatus() const;
    [[nodiscard]] int getCpuTemp() const;
    [[nodiscard]] int getGpuTemp() const;
    [[nodiscard]] int getFan1Speed() const;
    [[nodiscard]] int getFan2Speed() const;

    [[nodiscard]] int getKeyboardBacklightMode() const;
    [[nodiscard]] int getKeyboardBrightness() const;
    [[nodiscard]] bool getUsbPowerShareState() const;
    [[nodiscard]] bool getWebCamState() const;
    [[nodiscard]] bool getFnSuperSwapState() const;
    [[nodiscard]] bool getCoolerBoostState() const;
    [[nodiscard]] user_mode getUserMode() const;
    [[nodiscard]] fan_mode getFanMode() const;

    void setBatteryThreshold(int value) const;
    void setKeyboardBacklightMode(int value) const;
    void setKeyboardBrightness(int value) const;
    void setUsbPowerShareState(bool enabled) const;
    void setWebCamState(bool enabled) const;
    void setFnSuperSwapState(bool enabled) const;
    void setCoolerBoostState(bool enabled) const;
    void setUserMode(user_mode userMode) const;

    void setFanSpeedProfile(const QString &profileName) const;

    [[nodiscard]] int getValue(int address) const;
    void setValue(int address, int value) const;

    [[nodiscard]] bool isBatteryThresholdSupport() const;
    [[nodiscard]] bool isKeyboardBacklightSupport() const;
    [[nodiscard]] bool isUsbPowerShareSupport() const;
    [[nodiscard]] bool isWebCamOffSupport() const;

    void loadSettings() const;

    void putSuperBatteryModeValue(bool enabled) const;
private:
    int detectFan1Address() const;
    int detectBatteryThresholdAddress() const;
    int detectFanModeAddress() const;
};

#endif // OPERATE_H
