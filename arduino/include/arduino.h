#ifndef TJLUTILS_ARDUINO_H
#define TJLUTILS_ARDUINO_H

#include <list>
#include <string>
#include <memory>
#include <mutex>
#include <algorithm>
#include "serialport.h"
#include "generalutilities.h"
#include "eventtimer.h"

enum class ArduinoType { UNO, NANO, MEGA };
enum IOType { DIGITAL_INPUT, DIGITAL_OUTPUT, ANALOG_INPUT, ANALOG_OUTPUT, DIGITAL_INPUT_PULLUP, UNSPECIFIED };
enum class CanMaskType { POSITIVE, NEGATIVE, ALL };
enum IOStatus { OPERATION_SUCCESS, OPERATION_FAILURE };
enum IOState { PIN_NUMBER, STATE, RETURN_CODE };
enum ArduinoTypeEnum { RETURN_STATE, OPERATION_RESULT };
enum IOReportEnum { IO_PIN_NUMBER, IO_TYPE, IO_STATE };
enum CanIOStatus { MESSAGE_ID, BYTE_0, BYTE_1, BYTE_2, BYTE_3, BYTE_4, BYTE_5, BYTE_6, BYTE_7 , CAN_IO_OPERATION_RESULT};
enum CanEnabledStatus { CAN_RETURN_STATE, CAN_OPERATION_RESULT };
enum ADThresholdReq { AD_RETURN_STATE, AD_OPERATION_RESULT };
enum CanMask { CAN_MASK_RETURN_STATE, CAN_MASK_OPERATION_RESULT };

class GPIO;
class CanMessage;
class CanReport;
class SerialReport;
class IOReport;

#include "canmessage.h"
#include "candatapacket.h"

#include "gpio.h"
#include "protectedserialport.h"

#ifndef HIGH
#define HIGH 0x1
#endif

#ifndef LOW
#define LOW 0x0
#endif

#ifndef HIGH
    #define HIGH true
#endif
#ifndef LOW
    #define LOW false
#endif

class Arduino
{
    friend class ArduinoFactory;

public:
    virtual std::pair<IOStatus, bool> digitalRead(int pinNumber, int serialPortIndex);
    virtual std::pair<IOStatus, bool> digitalWrite(int pinNumber, bool state, int serialPortIndex);
    virtual std::pair<IOStatus, double> analogRead(int pinNumber, int serialPortIndex);
    virtual std::pair<IOStatus, int> analogReadRaw(int pinNumber, int serialPortIndex);
    virtual std::pair<IOStatus, double> analogWrite(int pinNumber, double state, int serialPortIndex);
    virtual std::pair<IOStatus, int> analogWriteRaw(int pinNumber, int state, int serialPortIndex);
    virtual std::pair<IOStatus, bool> softDigitalRead(int pinNumber, int serialPortIndex);
    virtual std::pair<IOStatus, double> softAnalogRead(int pinNumber, int serialPortIndex);
    virtual std::pair<IOStatus, int> softAnalogReadRaw(int pinNumber, int serialPortIndex);
    virtual std::pair<IOStatus, IOType> pinMode(int pinNumber, IOType ioType, int serialPortIndex);
    virtual std::pair<IOStatus, IOType> currentPinMode(int pinNumber, int serialPortIndex);
    virtual std::pair<IOStatus, int> changeAnalogToDigitalThreshold(int threshold, int serialPortIndex);
    virtual std::pair<IOStatus, uint32_t> addCanMask(CanMaskType canMaskType, const std::string &mask, int serialPortIndex);
    virtual std::pair<IOStatus, uint32_t> removeCanMask(CanMaskType canMaskType, const std::string &mask, int serialPortIndex);
    virtual std::pair<IOStatus, bool> removeAllCanMasks(CanMaskType canMaskType, int serialPortIndex);

    virtual std::pair<IOStatus, std::string> getArduinoType(int serialPortIndex);
    static std::pair<IOStatus, int> getAnalogToDigitalThreshold(std::shared_ptr<SerialPort> serialPort);

    virtual std::pair<IOStatus, bool> canAutoUpdate(bool state, int serialPortIndex);
    virtual std::pair<IOStatus, bool> initializeCanBus(int serialPortIndex);
    virtual std::pair<IOStatus, CanMessage> canRead(int serialPortIndex);
    virtual std::pair<IOStatus, CanMessage> canWrite(const CanMessage &message, int serialPortIndex);
    virtual IOReport ioReportRequest(int serialPortIndex);
    virtual SerialReport serialReportRequest(int serialPortIndex, const std::string &delimiter = "");
    virtual CanReport canReportRequest(int serialPortIndex);
    virtual void writeRawString(const std::string &str, int serialPortIndex);
    virtual std::string readRawString(int serialPortIndex);
    virtual void flushRX(int serialPortIndex);
    virtual void flushTX(int serialPortIndex);
    virtual void flushRXTX(int serialPortIndex);
    virtual void flushTXRX(int serialPortIndex);

    virtual bool parseToDigitalState(const std::string &state) const;
    virtual double parseToAnalogState(const std::string &state) const;
    virtual int parseToAnalogStateRaw(const std::string &state) const;
    virtual bool isValidDigitalStateIdentifier(const std::string &state) const;
    virtual bool isValidAnalogStateIdentifier(const std::string &state) const;
    virtual bool isValidAnalogRawStateIdentifier(const std::string &state) const;

    std::pair<IOStatus, bool> digitalRead(const std::string &pinAlias);
    std::pair<IOStatus, bool> digitalWrite(const std::string &pinAlias, bool state);
    std::pair<IOStatus, double> analogRead(const std::string &pinAlias);
    std::pair<IOStatus, int> analogReadRaw(const std::string &pinAlias);
    std::pair<IOStatus, double> analogWrite(const std::string &pinAlias, double state);
    std::pair<IOStatus, int> analogWriteRaw(const std::string &pinAlias, int state);
    std::pair<IOStatus, bool> softDigitalRead(const std::string &pinAlias);
    std::pair<IOStatus, double> softAnalogRead(const std::string &pinAlias);
    std::pair<IOStatus, int> softAnalogReadRaw(const std::string &pinAlias);
    std::pair<IOStatus, IOType> pinMode(const std::string &pinAlias, IOType ioType);
    std::pair<IOStatus, IOType> currentPinMode(const std::string &pinAlias);

    std::pair<IOStatus, bool> digitalRead(const GPIO &gpio);
    std::pair<IOStatus, bool> digitalWrite(const GPIO &gpio, bool state);
    std::pair<IOStatus, double> analogRead(const GPIO &gpio);
    std::pair<IOStatus, int> analogReadRaw(const GPIO &gpio);
    std::pair<IOStatus, double> analogWrite(const GPIO &gpio, double state);
    std::pair<IOStatus, int> analogWriteRaw(const GPIO &gpio, int state);
    std::pair<IOStatus, bool> softDigitalRead(const GPIO &gpio);
    std::pair<IOStatus, double> softAnalogRead(const GPIO &gpio);
    std::pair<IOStatus, int> softAnalogReadRaw(const GPIO &gpio);
    std::pair<IOStatus, IOType> pinMode(GPIO &gpio, IOType ioType);
    std::pair<IOStatus, IOType> currentPinMode(const GPIO &gpio);
    void writeRawString(const std::string &str);
    std::string readRawString();
    void flushRX();
    void flushTX();
    void flushRXTX();
    void flushTXRX();

    std::pair<IOStatus, bool> digitalRead(std::shared_ptr<GPIO> gpioPtr);
    std::pair<IOStatus, bool> digitalWrite(std::shared_ptr<GPIO> gpioPtr, bool state);
    std::pair<IOStatus, double> analogRead(std::shared_ptr<GPIO> gpioPtr);
    std::pair<IOStatus, int> analogReadRaw(std::shared_ptr<GPIO> gpioPtr);
    std::pair<IOStatus, double> analogWrite(std::shared_ptr<GPIO> gpioPtr, double state);
    std::pair<IOStatus, int> analogWriteRaw(std::shared_ptr<GPIO> gpioPtr, int state);
    std::pair<IOStatus, bool> softDigitalRead(std::shared_ptr<GPIO> gpioPtr);
    std::pair<IOStatus, double> softAnalogRead(std::shared_ptr<GPIO> gpioPtr);
    std::pair<IOStatus, int> softAnalogReadRaw(std::shared_ptr<GPIO> gpioPtr);
    std::pair<IOStatus, IOType> pinMode(std::shared_ptr<GPIO> gpioPtr, IOType ioType);
    std::pair<IOStatus, IOType> currentPinMode(std::shared_ptr<GPIO> gpioPtr);

    std::string firmwareVersion();
    std::pair<bool, bool> canCapability();
    std::shared_ptr<SerialPort> serialPort() const;
    bool isValidAnalogPinIdentifier(const std::string &state) const;
    void eraseCanPin();
    bool isBluetooth() const;

    std::shared_ptr<GPIO> gpioPinByPinAlias(const std::string &pinAlias) const;
    std::shared_ptr<GPIO> gpioPinByPinNumber(int pinNumber) const;
    std::string gpioAliasByPinNumber(int number) const;
    void assignIOTypes(std::shared_ptr<GlobalLogger> globalLogger = nullptr);

    bool isValidDigitalOutputPin(int pinNumber) const;
    bool isValidDigitalInputPin(int pinNumber) const;
    bool isValidAnalogOutputPin(int pinNumber) const;
    bool isValidAnalogInputPin(int pinNumber) const;

    int parseAnalogPin(const std::string &pinAlias) const;
    std::string analogPinFromNumber(int pinNumber) const;
    static int staticParseAnalogPin(const std::string &pinAlias);
    static std::string staticAnalogPinFromNumber(int pinNumber);

    void setFirmwareVersion(const std::string &firmwareVersion);
    void setCanCapability(const std::pair<bool, bool> &capability);
    void setAnalogToDigitalThreshold(int state);
    int analogToDigitalThreshold();
    bool setPinAlias(int pinNumber, const std::string &newAlias);
    bool setPinAlias(const GPIO &gpio, const std::string &newAlias);
    bool setPinAlias(std::shared_ptr<GPIO> gpio, const std::string &newAlias);

    bool confirmValidAlias(const std::pair<int, std::string> &alias) const;
    bool confirmValidIOType(const std::pair<int, std::string> &io) const;
    bool confirmValidStates(const std::pair<int, std::string> &alias) const;

    std::set<int> AVAILABLE_ANALOG_PINS() const;
    std::set<int> AVAILABLE_PWM_PINS() const;
    std::set<int> AVAILABLE_PINS() const;
    int NUMBER_OF_DIGITAL_PINS() const;

    static std::vector<std::string> genericIOTask(const std::string &stringToSend, const std::string &header, int serialPortIndex, double delay = static_cast<double>(Arduino::BLUETOOTH_SERIAL_SEND_DELAY));
    static std::vector<std::string> genericIOTask(const std::string &stringToSend, const std::string &header, std::shared_ptr<SerialPort> serialPort, double delay = static_cast<double>(Arduino::BLUETOOTH_SERIAL_SEND_DELAY));
    static std::vector<std::string> genericIOReportTask(const std::string &stringToSend, const std::string &header, const std::string &endHeader, int serialPortIndex, double delay = static_cast<double>(Arduino::BLUETOOTH_SERIAL_SEND_DELAY));
    static std::vector<std::string> genericIOReportTask(const std::string &stringToSend, const std::string &header, const std::string &endHeader, std::shared_ptr<SerialPort> serialPort, double delay = static_cast<double>(Arduino::BLUETOOTH_SERIAL_SEND_DELAY));
    static unsigned int SERIAL_PORT_TRY_COUNT_HIGH_LIMIT();
    static std::pair<IOStatus, std::string> getArduinoType(std::shared_ptr<SerialPort> serialPort);
    static std::pair<IOStatus, std::string> getFirmwareVersion(std::shared_ptr<SerialPort> serialPort);
    static std::pair<IOStatus, bool> getCanCapability(std::shared_ptr<SerialPort> serialPort);
    static double analogToVoltage(int state);
    static int voltageToAnalog(double state);
    static std::string parseIOType(IOType ioType);
    static IOType parseIOTypeFromString(const std::string &ioType);
    static double bluetoothSendDelayMultiplier;

    static bool isBluetooth(int serialPortIndex);
    static bool isBluetooth(const std::string &name);
    static bool isBluetooth(std::shared_ptr<SerialPort> serialPort);

    static const char *HEARTBEAT_HEADER;
    static const char *IO_REPORT_HEADER;
    static const char *IO_REPORT_END_HEADER;
    static const char *INVALID_HEADER;
    static const char *DIGITAL_READ_HEADER;
    static const char *ANALOG_READ_HEADER;
    static const char *DIGITAL_WRITE_HEADER;
    static const char *ANALOG_WRITE_HEADER;
    static const char *SOFT_DIGITAL_READ_HEADER;
    static const char *SOFT_ANALOG_READ_HEADER;
    static const char *PIN_TYPE_HEADER;
    static const char *PIN_TYPE_CHANGE_HEADER;
    static const char *ARDUINO_TYPE_HEADER;
    static const char *CAN_BUS_ENABLED_HEADER;
    static const unsigned int CAN_READ_BLANK_RETURN_SIZE;
    static const unsigned int REMOVE_CAN_MASKS_RETURN_SIZE;
    static const char *FIRMWARE_VERSION_HEADER;
    static const char *DIGITAL_INPUT_IDENTIFIER;
    static const char *DIGITAL_OUTPUT_IDENTIFIER;
    static const char *ANALOG_INPUT_IDENTIFIER;
    static const char *ANALOG_OUTPUT_IDENTIFIER;
    static const char *DIGITAL_INPUT_PULLUP_IDENTIFIER;
    static const char *OPERATION_FAILURE_STRING;
    static const char *ADD_POSITIVE_CAN_MASK_HEADER;
    static const char *ADD_NEGATIVE_CAN_MASK_HEADER;
    static const char *REMOVE_POSITIVE_CAN_MASK_HEADER;
    static const char *REMOVE_NEGATIVE_CAN_MASK_HEADER;
    static const char *REMOVE_ALL_POSITIVE_CAN_MASKS_HEADER;
    static const char *REMOVE_ALL_NEGATIVE_CAN_MASKS_HEADER;
    static const char *REMOVE_ALL_CAN_MASKS_HEADER;

    static const char *UNO_A0_STRING;
    static const char *UNO_A1_STRING;
    static const char *UNO_A2_STRING;
    static const char *UNO_A3_STRING;
    static const char *UNO_A4_STRING;
    static const char *UNO_A5_STRING;
    static const char *UNO_A0_EQUIVALENT_STRING;
    static const char *UNO_A1_EQUIVALENT_STRING;
    static const char *UNO_A2_EQUIVALENT_STRING;
    static const char *UNO_A3_EQUIVALENT_STRING;
    static const char *UNO_A4_EQUIVALENT_STRING;
    static const char *UNO_A5_EQUIVALENT_STRING;
    static const char *NANO_A0_STRING;
    static const char *NANO_A1_STRING;
    static const char *NANO_A2_STRING;
    static const char *NANO_A3_STRING;
    static const char *NANO_A4_STRING;
    static const char *NANO_A5_STRING;
    static const char *NANO_A6_STRING;
    static const char *NANO_A7_STRING;
    static const char *NANO_A0_EQUIVALENT_STRING;
    static const char *NANO_A1_EQUIVALENT_STRING;
    static const char *NANO_A2_EQUIVALENT_STRING;
    static const char *NANO_A3_EQUIVALENT_STRING;
    static const char *NANO_A4_EQUIVALENT_STRING;
    static const char *NANO_A5_EQUIVALENT_STRING;
    static const char *NANO_A6_EQUIVALENT_STRING;
    static const char *NANO_A7_EQUIVALENT_STRING;
    static const char *MEGA_A0_STRING;
    static const char *MEGA_A1_STRING;
    static const char *MEGA_A2_STRING;
    static const char *MEGA_A3_STRING;
    static const char *MEGA_A4_STRING;
    static const char *MEGA_A5_STRING;
    static const char *MEGA_A6_STRING;
    static const char *MEGA_A7_STRING;
    static const char *MEGA_A8_STRING;
    static const char *MEGA_A9_STRING;
    static const char *MEGA_A10_STRING;
    static const char *MEGA_A11_STRING;
    static const char *MEGA_A12_STRING;
    static const char *MEGA_A13_STRING;
    static const char *MEGA_A14_STRING;
    static const char *MEGA_A15_STRING;
    static const char *MEGA_A0_EQUIVALENT_STRING;
    static const char *MEGA_A1_EQUIVALENT_STRING;
    static const char *MEGA_A2_EQUIVALENT_STRING;
    static const char *MEGA_A3_EQUIVALENT_STRING;
    static const char *MEGA_A4_EQUIVALENT_STRING;
    static const char *MEGA_A5_EQUIVALENT_STRING;
    static const char *MEGA_A6_EQUIVALENT_STRING;
    static const char *MEGA_A7_EQUIVALENT_STRING;
    static const char *MEGA_A8_EQUIVALENT_STRING;
    static const char *MEGA_A9_EQUIVALENT_STRING;
    static const char *MEGA_A10_EQUIVALENT_STRING;
    static const char *MEGA_A11_EQUIVALENT_STRING;
    static const char *MEGA_A12_EQUIVALENT_STRING;
    static const char *MEGA_A13_EQUIVALENT_STRING;
    static const char *MEGA_A14_EQUIVALENT_STRING;
    static const char *MEGA_A15_EQUIVALENT_STRING;

    static const std::vector<const char *> VALID_DIGITAL_STATE_IDENTIFIERS;
    static const std::vector<char> VALID_ANALOG_STATE_IDENTIFIERS;
    static const unsigned int IO_STATE_RETURN_SIZE;
    static const unsigned int ARDUINO_TYPE_RETURN_SIZE;
    static const unsigned int PIN_TYPE_RETURN_SIZE;
    static const unsigned int IO_REPORT_RETURN_SIZE;
    static const unsigned int CAN_ID_WIDTH;
    static const unsigned int CAN_BYTE_WIDTH;
    static const int OPERATION_FAILURE;
    static const int OPERATION_SUCCESS;
    static const int INVALID_PIN;
    static const int STATE_FAILURE;
    static const int ANALOG_MAX;
    static const int CAN_BUS_PIN;
    static const unsigned int RAW_CAN_MESSAGE_SIZE;
    static const unsigned char CAN_MESSAGE_LENGTH;
    static const unsigned char CAN_FRAME;
    static const double VOLTAGE_MAX;
    static const int IO_TRY_COUNT;
    static const char *CAN_INIT_HEADER;
    static const char *CAN_READ_HEADER;
    static const char *CAN_WRITE_HEADER;
    static const char *CAN_LIVE_UPDATE_HEADER;
    static const char *CAN_CLEAR_MESSAGE_HEADER;
    static const char *CHANGE_A_TO_D_THRESHOLD_HEADER;
    static const char *CURRENT_A_TO_D_THRESHOLD_HEADER;
    static const unsigned int CAN_READ_RETURN_SIZE;
    static const unsigned int CAN_WRITE_RETURN_SIZE;
    static const unsigned int CAN_BUS_ENABLED_RETURN_SIZE;
    static const unsigned int CAN_AUTO_UPDATE_RETURN_SIZE;
    static const unsigned int A_TO_D_THRESHOLD_RETURN_SIZE;
    static const unsigned int CAN_INIT_RETURN_SIZE;
    static const unsigned int ADD_CAN_MASK_RETURN_SIZE;
    static const unsigned int REMOVE_CAN_MASK_RETURN_SIZE;
    static const unsigned int RETURN_SIZE_HIGH_LIMIT;
    static const double BOOTLOADER_BOOT_TIME;
    static const double SERIAL_TIMEOUT;
    static const int BLUETOOTH_RETRY_COUNT;
    static const double BLUETOOTH_SERIAL_SEND_DELAY;
    static const double DEFAULT_BLUETOOTH_SEND_DELAY_MULTIPLIER;
    static const unsigned int SERIAL_REPORT_REQUEST_TIME_LIMIT;
    static const unsigned int SERIAL_REPORT_OVERALL_TIME_LIMIT;
    static const double ANALOG_TO_VOLTAGE_SCALE_FACTOR;
    static const std::vector<const char *> DIGITAL_STATE_HIGH_IDENTIFIERS;
    static const std::vector<const char *> DIGITAL_STATE_LOW_IDENTIFIERS;

    static const BaudRate FIRMWARE_BAUD;
    static const DataBits FIRMWARE_DATA_BITS;
    static const StopBits FIRMWARE_STOP_BITS;
    static const Parity FIRMWARE_PARITY;
    int numberOfSerialPorts() const;
    static std::shared_ptr<SerialPort> serialPortAtIndex(unsigned int serialPortIndex);
    static std::shared_ptr<std::mutex> ioMutexAtIndex(unsigned int ioMutexIndex);
    int addSerialPort(std::shared_ptr<SerialPort> serialPort);

    std::pair<IOStatus, CanMessage> canListen(int screenIndex, double delay = Arduino::BLUETOOTH_SERIAL_SEND_DELAY);
private:

    Arduino(ArduinoType arduinoType, std::shared_ptr<SerialPort> serialPort);
    Arduino(ArduinoType arduinoType, std::shared_ptr<SerialPort> serialPort, bool canCapability);
    Arduino(ArduinoType arduinoType, std::shared_ptr<SerialPort> serialPort, const std::string &firmwareVersion);
    Arduino(ArduinoType arduinoType, std::shared_ptr<SerialPort> serialPort, const std::string &firmwareVersion, bool canCapability);

    std::map<std::string, std::shared_ptr<GPIO>> m_gpioPinsAlias;
    std::map<int, std::string> m_gpioPinIterationAliasMap;
    std::map<int, std::shared_ptr<GPIO>> m_gpioPins;
    int m_serialPortIndex;
    std::string m_firmwareVersion;
    std::pair<bool, bool> m_canCapability;
    std::string m_canPinAlias;
    std::set<int> m_availablePins;
    std::set<int> m_availablePwmPins;
    std::set<int> m_availableAnalogPins;
    int m_numberOfDigitalPins;
    int m_analogToDigitalThreshold;

    static std::vector<ProtectedSerialPort> s_serialPorts;
    static unsigned  int s_SERIAL_PORT_TRY_COUNT_HIGH_LIMIT;

    void initializeIO();
    void setArduinoType(ArduinoType arduinoType);
};




class IOReport
{
public:
    void addDigitalInputResult(const std::pair<int, bool> &result)
    {
        this->m_digitalInputResults.emplace_back(result);
    }

    void addDigitalOutputResult(const std::pair<int, bool> &result)
    {
        this->m_digitalOutputResults.emplace_back(result);
    }

    void addAnalogInputResult(const std::pair<int, int> &result)
    {
        this->m_analogInputResults.emplace_back(result);
    }

    void addAnalogOutputResult(const std::pair<int, int> &result)
    {
        this->m_analogOutputResults.emplace_back(result);
    }

    std::vector<std::pair<int, bool>> digitalInputResults() const
    {
        return this->m_digitalInputResults;
    }

    std::vector<std::pair<int, bool>> digitalOutputResults() const
    {
        return this->m_digitalOutputResults;
    }

    std::vector<std::pair<int, int>> analogInputResults() const
    {
        return this->m_analogInputResults;
    }
    
    std::vector<std::pair<int, int>> analogOutputResults() const
    {
        return this->m_analogOutputResults;
    }

private:
    std::vector<std::pair<int, bool>> m_digitalInputResults;
    std::vector<std::pair<int, bool>> m_digitalOutputResults;
    std::vector<std::pair<int, int>> m_analogInputResults;
    std::vector<std::pair<int, int>> m_analogOutputResults;
};

class CanReport
{
public:
    void addCanMessageResult(const CanMessage &result)
    {
        this->m_canMessageResults.emplace_back(result);
    }

    std::vector<CanMessage> canMessageResults() const
    {
        return this->m_canMessageResults;
    }

private:
    std::vector<CanMessage> m_canMessageResults;
};

class SerialReport
{
public:
    void addSerialResult(const std::string &result)
    {
        this->m_serialResults.emplace_back(result);
    }

    std::vector<std::string> serialResults() const
    {
        return this->m_serialResults;
    }

private:
    std::vector<std::string> m_serialResults;
};


#endif //TJLUTILS_ARDUINO_H