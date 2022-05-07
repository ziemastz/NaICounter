#include "naicounter.h"

NaICounter::NaICounter()
{
    hif = hifInvalid;
    _deviceName = "CmodS6";
}

void NaICounter::setDeviceName(const std::string &deviceName)
{
    _deviceName = deviceName;
}

bool NaICounter::connect()
{
    if( hif != hifInvalid )
        return true;

    char szDvc[30];
    for (unsigned int i=0; i < sizeof(_deviceName); i++) {
        szDvc[i] = _deviceName[i];
    }
    // DMGR API Call: DmgrOpen
    if(!DmgrOpen(&hif, szDvc)) {
        //qWarning() << "DmgrOpen failed (check the device name you provided)";
        _lastError = "DmgrOpen failed (check the device name you provided)";
        return false;
    }

    // DEPP API call: DeppEnable
    if(!DeppEnable(hif)) {
        //qWarning() << "DeppEnable failed";
        _lastError = "DeppEnable failed";
        return false;
    }
    //qDebug() << "DEPP connected";
    return true;
}

void NaICounter::disconnect()
{
    if( hif != hifInvalid ) {
      // DEPP API Call: DeppDisable
        DeppDisable(hif);

      // DMGR API Call: DmgrClose
        DmgrClose(hif);
        //qDebug() << "DEPP disconnected";
    }
}

bool NaICounter::setEnable(const PORT &id, const bool &enable)
{
    switch (id) {
    case PORT_A :
    {
        if(!putReg(ENABLE_PORT_A,static_cast<BYTE>(enable))){
            //warning
            return false;
        }
        break;
    }
    case PORT_B :
    {
        if(!putReg(ENABLE_PORT_B,static_cast<BYTE>(enable))){
            //warning
            return false;
        }
        break;
    }
    case PORT_C :
    {
        if(!putReg(ENABLE_PORT_C,static_cast<BYTE>(enable))){
            //warning
            return false;
        }
        break;
    }
    case PORT_D :
    {
        if(!putReg(ENABLE_PORT_D,static_cast<BYTE>(enable))){
            //warning
            return false;
        }
        break;
    }
    }
    return true;
}

int NaICounter::isEnable(const PORT &id)
{
    BYTE reg;
    switch (id) {
    case PORT_A :
    {
        if(!getReg(ENABLE_PORT_A,&reg)){
            //warning
            return -1;
        }
        break;
    }
    case PORT_B :
    {
        if(!getReg(ENABLE_PORT_B,&reg)){
            //warning
            return -1;
        }
        break;
    }
    case PORT_C :
    {
        if(!getReg(ENABLE_PORT_C,&reg)){
            //warning
            return -1;
        }
        break;
    }
    case PORT_D :
    {
        if(!getReg(ENABLE_PORT_D,&reg)){
            //warning
            return -1;
        }
        break;
    }
    }
    return static_cast<int>(reg);
}

bool NaICounter::setReset(const PORT &id, const bool &reset)
{
    switch (id) {
    case PORT_A :
    {
        if(!putReg(RESET_PORT_A,static_cast<BYTE>(reset))){
            //warning
            return false;
        }
        break;
    }
    case PORT_B :
    {
        if(!putReg(RESET_PORT_B,static_cast<BYTE>(reset))){
            //warning
            return false;
        }
        break;
    }
    case PORT_C :
    {
        if(!putReg(RESET_PORT_C,static_cast<BYTE>(reset))){
            //warning
            return false;
        }
        break;
    }
    case PORT_D :
    {
        if(!putReg(RESET_PORT_D,static_cast<BYTE>(reset))){
            //warning
            return false;
        }
        break;
    }
    }
    return true;
}

int NaICounter::isReset(const PORT &id)
{
    BYTE reg;
    switch (id) {
    case PORT_A :
    {
        if(!getReg(RESET_PORT_A,&reg)){
            //warning
            return -1;
        }
        break;
    }
    case PORT_B :
    {
        if(!getReg(RESET_PORT_B,&reg)){
            //warning
            return -1;
        }
        break;
    }
    case PORT_C :
    {
        if(!getReg(RESET_PORT_C,&reg)){
            //warning
            return -1;
        }
        break;
    }
    case PORT_D :
    {
        if(!getReg(RESET_PORT_D,&reg)){
            //warning
            return -1;
        }
        break;
    }
    }
    return static_cast<int>(reg);
}

bool NaICounter::setDeadTime(const PORT &id, const unsigned short &value)
{
    BYTE data0,data1;
    unsigned short val0,val1;

    val1 = value/static_cast<unsigned short>(256);
    val0 = value - val1*static_cast<unsigned short>(256);

    data0 = static_cast<BYTE>(val0);
    data1 = static_cast<BYTE>(val1);

    switch (id) {
    case PORT_A :
    {
        if(!putReg(DEAT_TIME_A0,data0)){
            //warning
            return false;
        }
        if(!putReg(DEAT_TIME_A1,data1)){
            //warning
            return false;
        }

        break;
    }
    case PORT_B :
    {
        if(!putReg(DEAT_TIME_B0,data0)){
            //warning
            return false;
        }
        if(!putReg(DEAT_TIME_B1,data1)){
            //warning
            return false;
        }

        break;
    }
    case PORT_C :
    {
        if(!putReg(DEAT_TIME_C0,data0)){
            //warning
            return false;
        }
        if(!putReg(DEAT_TIME_C1,data1)){
            //warning
            return false;
        }

        break;
    }
    case PORT_D :
    {
        if(!putReg(DEAT_TIME_D0,data0)){
            //warning
            return false;
        }
        if(!putReg(DEAT_TIME_D1,data1)){
            //warning
            return false;
        }

        break;
    }
    }
    return true;
}

unsigned short NaICounter::deadTime(const PORT &id)
{
    BYTE data0,data1;
    unsigned short ret = -1;

    switch (id) {
    case PORT_A :
    {
        getReg(DEAT_TIME_A0,&data0);
        getReg(DEAT_TIME_A1,&data1);

        unsigned short val0 = static_cast<unsigned short>(data0);
        unsigned short val1 = static_cast<unsigned short>(data1);

        ret = val0 + val1*static_cast<unsigned short>(256);

        break;
    }
    case PORT_B :
    {
        getReg(DEAT_TIME_B0,&data0);
        getReg(DEAT_TIME_B1,&data1);

        unsigned short val0 = static_cast<unsigned short>(data0);
        unsigned short val1 = static_cast<unsigned short>(data1);

        ret = val0 + val1*static_cast<unsigned short>(256);

        break;
    }
    case PORT_C :
    {
        getReg(DEAT_TIME_C0,&data0);
        getReg(DEAT_TIME_C1,&data1);

        unsigned short val0 = static_cast<unsigned short>(data0);
        unsigned short val1 = static_cast<unsigned short>(data1);

        ret = val0 + val1*static_cast<unsigned short>(256);

        break;
    }
    case PORT_D :
    {
        getReg(DEAT_TIME_D0,&data0);
        getReg(DEAT_TIME_D1,&data1);

        unsigned short val0 = static_cast<unsigned short>(data0);
        unsigned short val1 = static_cast<unsigned short>(data1);

        ret = val0 + val1*static_cast<unsigned short>(256);

        break;
    }
    }
    return ret;
}

unsigned int NaICounter::getCounts(PORT id)
{
    BYTE data0,data1,data2,data3;
    unsigned int ret = 0;

    switch (id) {
    case PORT_A :
    {
        getReg(COUNTS_A0,&data0);
        getReg(COUNTS_A1,&data1);
        getReg(COUNTS_A2,&data2);
        getReg(COUNTS_A3,&data3);

        unsigned short val0 = static_cast<unsigned short>(data0);
        unsigned short val1 = static_cast<unsigned short>(data1);
        unsigned short val2 = static_cast<unsigned short>(data2);
        unsigned short val3 = static_cast<unsigned short>(data3);

        ret = val0 + val1*static_cast<unsigned int>(256) + val2*static_cast<unsigned int>(65536)+ val3*static_cast<unsigned int>(16777216);

        break;
    }
    case PORT_B :
    {
        getReg(COUNTS_B0,&data0);
        getReg(COUNTS_B1,&data1);
        getReg(COUNTS_B2,&data2);
        getReg(COUNTS_B3,&data3);

        unsigned short val0 = static_cast<unsigned short>(data0);
        unsigned short val1 = static_cast<unsigned short>(data1);
        unsigned short val2 = static_cast<unsigned short>(data2);
        unsigned short val3 = static_cast<unsigned short>(data3);

        ret = val0 + val1*static_cast<unsigned int>(256) + val2*static_cast<unsigned int>(65536)+ val3*static_cast<unsigned int>(16777216);

        break;
    }
    case PORT_C :
    {
        getReg(COUNTS_C0,&data0);
        getReg(COUNTS_C1,&data1);
        getReg(COUNTS_C2,&data2);
        getReg(COUNTS_C3,&data3);

        unsigned short val0 = static_cast<unsigned short>(data0);
        unsigned short val1 = static_cast<unsigned short>(data1);
        unsigned short val2 = static_cast<unsigned short>(data2);
        unsigned short val3 = static_cast<unsigned short>(data3);

        ret = val0 + val1*static_cast<unsigned int>(256) + val2*static_cast<unsigned int>(65536)+ val3*static_cast<unsigned int>(16777216);

        break;
    }
    case PORT_D :
    {
        getReg(COUNTS_D0,&data0);
        getReg(COUNTS_D1,&data1);
        getReg(COUNTS_D2,&data2);
        getReg(COUNTS_D3,&data3);

        unsigned short val0 = static_cast<unsigned short>(data0);
        unsigned short val1 = static_cast<unsigned short>(data1);
        unsigned short val2 = static_cast<unsigned short>(data2);
        unsigned short val3 = static_cast<unsigned short>(data3);

        ret = val0 + val1*static_cast<unsigned int>(256) + val2*static_cast<unsigned int>(65536)+ val3*static_cast<unsigned int>(16777216);

        break;
    }
    }
    return ret;
}

unsigned int NaICounter::getLiveTime(PORT id)
{
    BYTE data0,data1,data2,data3;
    unsigned int ret = 0;

    switch (id) {
    case PORT_A :
    {
        getReg(LIVE_TIME_A0,&data0);
        getReg(LIVE_TIME_A1,&data1);
        getReg(LIVE_TIME_A2,&data2);
        getReg(LIVE_TIME_A3,&data3);

        unsigned short val0 = static_cast<unsigned short>(data0);
        unsigned short val1 = static_cast<unsigned short>(data1);
        unsigned short val2 = static_cast<unsigned short>(data2);
        unsigned short val3 = static_cast<unsigned short>(data3);

        ret = val0 + val1*static_cast<unsigned int>(256) + val2*static_cast<unsigned int>(65536)+ val3*static_cast<unsigned int>(16777216);

        break;
    }
    case PORT_B :
    {
        getReg(LIVE_TIME_B0,&data0);
        getReg(LIVE_TIME_B1,&data1);
        getReg(LIVE_TIME_B2,&data2);
        getReg(LIVE_TIME_B3,&data3);

        unsigned short val0 = static_cast<unsigned short>(data0);
        unsigned short val1 = static_cast<unsigned short>(data1);
        unsigned short val2 = static_cast<unsigned short>(data2);
        unsigned short val3 = static_cast<unsigned short>(data3);

        ret = val0 + val1*static_cast<unsigned int>(256) + val2*static_cast<unsigned int>(65536)+ val3*static_cast<unsigned int>(16777216);

        break;
    }
    case PORT_C :
    {
        getReg(LIVE_TIME_C0,&data0);
        getReg(LIVE_TIME_C1,&data1);
        getReg(LIVE_TIME_C2,&data2);
        getReg(LIVE_TIME_C3,&data3);

        unsigned short val0 = static_cast<unsigned short>(data0);
        unsigned short val1 = static_cast<unsigned short>(data1);
        unsigned short val2 = static_cast<unsigned short>(data2);
        unsigned short val3 = static_cast<unsigned short>(data3);

        ret = val0 + val1*static_cast<unsigned int>(256) + val2*static_cast<unsigned int>(65536)+ val3*static_cast<unsigned int>(16777216);

        break;
    }
    case PORT_D :
    {
        getReg(LIVE_TIME_D0,&data0);
        getReg(LIVE_TIME_D1,&data1);
        getReg(LIVE_TIME_D2,&data2);
        getReg(LIVE_TIME_D3,&data3);

        unsigned short val0 = static_cast<unsigned short>(data0);
        unsigned short val1 = static_cast<unsigned short>(data1);
        unsigned short val2 = static_cast<unsigned short>(data2);
        unsigned short val3 = static_cast<unsigned short>(data3);

        ret = val0 + val1*static_cast<unsigned int>(256) + val2*static_cast<unsigned int>(65536)+ val3*static_cast<unsigned int>(16777216);

        break;
    }
    }
    return ret;
}

unsigned int NaICounter::getRealTime(PORT id)
{
    BYTE data0,data1,data2,data3;
    unsigned int ret = 0;

    switch (id) {
    case PORT_A :
    {
        getReg(REAL_TIME_A0,&data0);
        getReg(REAL_TIME_A1,&data1);
        getReg(REAL_TIME_A2,&data2);
        getReg(REAL_TIME_A3,&data3);

        unsigned short val0 = static_cast<unsigned short>(data0);
        unsigned short val1 = static_cast<unsigned short>(data1);
        unsigned short val2 = static_cast<unsigned short>(data2);
        unsigned short val3 = static_cast<unsigned short>(data3);

        ret = val0 + val1*static_cast<unsigned int>(256) + val2*static_cast<unsigned int>(65536)+ val3*static_cast<unsigned int>(16777216);

        break;
    }
    case PORT_B :
    {
        getReg(REAL_TIME_B0,&data0);
        getReg(REAL_TIME_B1,&data1);
        getReg(REAL_TIME_B2,&data2);
        getReg(REAL_TIME_B3,&data3);

        unsigned short val0 = static_cast<unsigned short>(data0);
        unsigned short val1 = static_cast<unsigned short>(data1);
        unsigned short val2 = static_cast<unsigned short>(data2);
        unsigned short val3 = static_cast<unsigned short>(data3);

        ret = val0 + val1*static_cast<unsigned int>(256) + val2*static_cast<unsigned int>(65536)+ val3*static_cast<unsigned int>(16777216);

        break;
    }
    case PORT_C :
    {
        getReg(REAL_TIME_C0,&data0);
        getReg(REAL_TIME_C1,&data1);
        getReg(REAL_TIME_C2,&data2);
        getReg(REAL_TIME_C3,&data3);

        unsigned short val0 = static_cast<unsigned short>(data0);
        unsigned short val1 = static_cast<unsigned short>(data1);
        unsigned short val2 = static_cast<unsigned short>(data2);
        unsigned short val3 = static_cast<unsigned short>(data3);

        ret = val0 + val1*static_cast<unsigned int>(256) + val2*static_cast<unsigned int>(65536)+ val3*static_cast<unsigned int>(16777216);

        break;
    }
    case PORT_D :
    {
        getReg(REAL_TIME_D0,&data0);
        getReg(REAL_TIME_D1,&data1);
        getReg(REAL_TIME_D2,&data2);
        getReg(REAL_TIME_D3,&data3);

        unsigned short val0 = static_cast<unsigned short>(data0);
        unsigned short val1 = static_cast<unsigned short>(data1);
        unsigned short val2 = static_cast<unsigned short>(data2);
        unsigned short val3 = static_cast<unsigned short>(data3);

        ret = val0 + val1*static_cast<unsigned int>(256) + val2*static_cast<unsigned int>(65536)+ val3*static_cast<unsigned int>(16777216);

        break;
    }
    }
    return ret;
}

std::string NaICounter::lastError()
{
    std::string ret = _lastError;
    _lastError = "";
    return ret;
}

bool NaICounter::putReg(ADDRESSREG addrReg, BYTE dReg)
{
    mutex.lock();
    BYTE idReg;

    idReg = static_cast<BYTE>(addrReg);

    // DEPP API Call: DeppPutReg
    if(!DeppPutReg(hif, idReg, dReg, false)) {
        _lastError = "DeppPutReg failed";
        mutex.unlock();
        return false;
    }
    mutex.unlock();
    return true;
}

bool NaICounter::getReg(ADDRESSREG addrReg, BYTE *dReg)
{
    mutex.lock();
    BYTE idReg;
    idReg = static_cast<BYTE>(addrReg);

    // DEPP API Call: DeppGetReg
    if(!DeppGetReg(hif, idReg, dReg, false)) {
        _lastError = "DeppGetReg failed";
        mutex.unlock();
        return false;
    }
    mutex.unlock();
    return true;
}
