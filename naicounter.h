#ifndef NAICOUNTER_H
#define NAICOUNTER_H
#include <string>
#include <QMutex>
#include <windows.h>
#include "dpcdecl.h"
#include "depp.h"
#include "dmgr.h"
/*!
 *\brief Biblioteka NaICounter umożliwia komunikacje z FPGA
 *\brief zaimplemtowanym kodem
 */
class NaICounter
{
public:
    enum ADDRESSREG {
        ENABLE_PORT_A = 0x01,
        RESET_PORT_A  = 0x02,
        ENABLE_PORT_B = 0x03,
        RESET_PORT_B  = 0x04,
        ENABLE_PORT_C = 0x05,
        RESET_PORT_C  = 0x06,
        ENABLE_PORT_D = 0x07,
        RESET_PORT_D  = 0x08,

        DEAT_TIME_A0  = 0xA0,
        DEAT_TIME_A1  = 0xA1,

        DEAT_TIME_B0  = 0xB0,
        DEAT_TIME_B1  = 0xB1,

        DEAT_TIME_C0  = 0xC0,
        DEAT_TIME_C1  = 0xC1,

        DEAT_TIME_D0  = 0xD0,
        DEAT_TIME_D1  = 0xD1,

        COUNTS_A3     = 0x11,
        COUNTS_A2     = 0x12,
        COUNTS_A1     = 0x13,
        COUNTS_A0     = 0x14,

        LIVE_TIME_A3  = 0x15,
        LIVE_TIME_A2  = 0x16,
        LIVE_TIME_A1  = 0x17,
        LIVE_TIME_A0  = 0x18,

        REAL_TIME_A3  = 0x19,
        REAL_TIME_A2  = 0x1A,
        REAL_TIME_A1  = 0x1B,
        REAL_TIME_A0  = 0x1C,

        COUNTS_B3     = 0x21,
        COUNTS_B2     = 0x22,
        COUNTS_B1     = 0x23,
        COUNTS_B0     = 0x24,

        LIVE_TIME_B3  = 0x25,
        LIVE_TIME_B2  = 0x26,
        LIVE_TIME_B1  = 0x27,
        LIVE_TIME_B0  = 0x28,

        REAL_TIME_B3  = 0x29,
        REAL_TIME_B2  = 0x2A,
        REAL_TIME_B1  = 0x2B,
        REAL_TIME_B0  = 0x2C,

        COUNTS_C3     = 0x31,
        COUNTS_C2     = 0x32,
        COUNTS_C1     = 0x33,
        COUNTS_C0     = 0x34,

        LIVE_TIME_C3  = 0x35,
        LIVE_TIME_C2  = 0x36,
        LIVE_TIME_C1  = 0x37,
        LIVE_TIME_C0  = 0x38,

        REAL_TIME_C3  = 0x39,
        REAL_TIME_C2  = 0x3A,
        REAL_TIME_C1  = 0x3B,
        REAL_TIME_C0  = 0x3C,

        COUNTS_D3     = 0x41,
        COUNTS_D2     = 0x42,
        COUNTS_D1     = 0x43,
        COUNTS_D0     = 0x44,

        LIVE_TIME_D3  = 0x45,
        LIVE_TIME_D2  = 0x46,
        LIVE_TIME_D1  = 0x47,
        LIVE_TIME_D0  = 0x48,

        REAL_TIME_D3  = 0x49,
        REAL_TIME_D2  = 0x4A,
        REAL_TIME_D1  = 0x4B,
        REAL_TIME_D0  = 0x4C,
    };
    enum PORT {
        PORT_A = 0,
        PORT_B = 1,
        PORT_C = 2,
        PORT_D = 3
    };
    NaICounter();
    /*!
     * \brief Funkcja służoca do ustawiania nazwy urządzenia
     * z którym będzie się komunikowało
     * \param deviceName - nazwa urządzenia Adept
     */
    void setDeviceName(const std::string &deviceName);
    bool connect();
    void disconnect();

    bool setEnable(const PORT &id, const bool &enable);
    int isEnable(const PORT &id);
    bool setReset(const PORT &id, const bool &reset);
    int isReset(const PORT &id);
    bool setDeadTime(const PORT &id, const unsigned short &value);
    unsigned short deadTime(const PORT &id);

    unsigned int getCounts(PORT id);
    unsigned int getLiveTime(PORT id);
    unsigned int getRealTime(PORT id);

    std::string lastError();
private:
    QMutex mutex;
    std::string _deviceName;
    std::string _lastError;
    HIF hif;

    bool putReg(ADDRESSREG addrReg, BYTE dReg);
    bool getReg(ADDRESSREG addrReg, BYTE *dReg);
};

#endif // NAICOUNTER_H
