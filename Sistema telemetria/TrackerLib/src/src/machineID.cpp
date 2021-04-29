#include "machineID.h"

#include <Windows.h>
#include "Iphlpapi.h"

//Returns the forst MAC adress as a string
std::string machineHash()
{
    char data[4096];
    ZeroMemory(data, 4096);
    unsigned long  len = 4000;
    PIP_ADAPTER_INFO pinfo = (PIP_ADAPTER_INFO)data;
    char sbuf[20];
    std::string sret;

    DWORD ret = GetAdaptersInfo(pinfo, &len);
    if (ret != ERROR_SUCCESS)
        return std::string("**ERROR**");

    for (int k = 0; k < 5; k++) {
        sprintf_s(sbuf, "%02X-", pinfo->Address[k]);
        sret += sbuf;
    }
    sprintf_s(sbuf, "%02X", pinfo->Address[5]);
    sret += sbuf;

    return(sret);
}
