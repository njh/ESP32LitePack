#ifndef __M5StackAXP192_H__
#define __M5StackAXP192_H__

#include <I2C_AXP192.h>

class M5StackAXP192 {
  public:
    void begin(bool disableLDO2 = false, bool disableLDO3 = false, bool disableRTC = false, bool disableDCDC1 = false, bool disableDCDC3 = false) {
      if (!enable) {
        return;
      }

      I2C_AXP192_InitDef initDef = {
        .EXTEN  = true,
        .BACKUP = true,
        .DCDC1  = disableDCDC1 ? -1 : 3300,
        .DCDC2  = 0,
        .DCDC3  = disableDCDC3 ? -1 : -1,
        .LDO2   = disableLDO2  ? -1 : 3000,
        .LDO3   = disableLDO3  ? -1 : 3000,
        .GPIO0  = disableRTC   ? -1 : 2800,
        .GPIO1  = -1,
        .GPIO2  = -1,
        .GPIO3  = -1,
        .GPIO4  = -1,
      };
      _axp192->begin(initDef);
    }

    void setAXP192(I2C_AXP192 *axp192) {
      _axp192 = axp192;
    }

    void ScreenBreath(uint8_t brightness) {
      if (!enable) {
        return;
      }

      if (brightness > 12) {
        brightness = 12;
      }
      _axp192->setLDO2(1800 + brightness * 100);
    }

    bool GetBatState() {
      // TODO
      return true;
    }

    uint8_t GetInputPowerStatus();
    uint8_t GetBatteryChargingStatus();

    void DisableAllIRQ(void);
    void ClearAllIRQ(void);
    void EnablePressIRQ(bool short_press, bool long_press);
    void GetPressIRQ(bool *short_press, bool* long_press);
    void ClearPressIRQ(bool short_press, bool long_press);

    void EnableCoulombcounter(void);
    void DisableCoulombcounter(void);
    void StopCoulombcounter(void);
    void ClearCoulombcounter(void);
    uint32_t GetCoulombchargeData(void);
    uint32_t GetCoulombdischargeData(void);
    float GetCoulombData(void);

    uint16_t GetVbatData(void) __attribute__((deprecated));
    uint16_t GetIchargeData(void) __attribute__((deprecated));
    uint16_t GetIdischargeData(void) __attribute__((deprecated));
    uint16_t GetTempData(void) __attribute__((deprecated));
    uint32_t GetPowerbatData(void) __attribute__((deprecated));
    uint16_t GetVinData(void) __attribute__((deprecated));
    uint16_t GetIinData(void) __attribute__((deprecated));
    uint16_t GetVusbinData(void) __attribute__((deprecated));
    uint16_t GetIusbinData(void) __attribute__((deprecated));
    uint16_t GetVapsData(void) __attribute__((deprecated));
    uint8_t GetBtnPress(void); // Use BtnC
    /*{
      if (!enable) {
        return 0;
      }

      return _axp192->getPekPress();
      }*/

    void SetSleep(void);
    void DeepSleep(uint64_t time_in_us = 0);
    void LightSleep(uint64_t time_in_us = 0);

    uint8_t GetWarningLeve(void) __attribute__((deprecated)) {
      // TODO
      return 0;
    }

    void SetChargeVoltage(uint8_t);
    void SetChargeCurrent(uint8_t);
    void SetVOff(uint8_t voltage);

    float GetBatVoltage() {
      if (!enable) {
        return 0;
      }
      return _axp192->getBatteryVoltage() / 1000.0;
    }
    float GetBatCurrent() {
      if (!enable) {
        return 0;
      }
      return _axp192->getBatteryChargeCurrent() - _axp192->getBatteryDischargeCurrent();
    }
    float GetVinVoltage() {
      if (!enable) {
        return 0;
      }
      return _axp192->getAcinVolatge() / 1000.0;
    }
    float GetVinCurrent() {
      if (!enable) {
        return 0;
      }
      return _axp192->getAcinCurrent();
    }
    float GetVBusVoltage() {
      if (!enable) {
        return 0;
      }
      return _axp192->getVbusVoltage() / 1000.0;
    }
    float GetVBusCurrent() {
      if (!enable) {
        return 0;
      }
      return _axp192->getVbusCurrent();
    }
    float GetTempInAXP192() {
      if (!enable) {
        return 0;
      }
      return _axp192->getInternalTemperature();
    }
    float GetBatPower() {
      if (!enable) {
        return 0;
      }
      return _axp192->getBatteryPower();
    }
    float GetBatChargeCurrent() {
      if (!enable) {
        return 0;
      }
      return _axp192->getBatteryChargeCurrent();
    }
    float GetAPSVoltage() {
      if (!enable) {
        return 0;
      }
      return _axp192->getApsVoltage() / 1000.0;
    }
    float GetBatCoulombInput();
    float GetBatCoulombOut();
    uint8_t GetWarningLevel(void) {
      // TODO
      return 0;
    }
    void SetCoulombClear()  __attribute__((deprecated));
    void SetLDO2(bool State);
    void SetLDO3(bool State);
    void SetGPIO0(bool State);
    void SetAdcState(bool State);
    void SetAdcRate(uint8_t rate);

    void PowerOff() {
      if (!enable) {
        return;
      }
      _axp192->powerOff();
    }

    void Read6BytesStorage(uint8_t *bufPtr);
    void Write6BytesStorage(uint8_t *bufPtr);

    int enable = 0;

  private:
    I2C_AXP192 *_axp192;
};

#endif
