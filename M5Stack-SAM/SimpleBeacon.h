#ifndef _SIMPLE_BEACON_H_
#define _SIMPLE_BEACON_H_


#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "bt.h"

#include "Arduino.h"

struct ble_gap_adv_params_s;

class SimpleBeacon {
    public:

        SimpleBeacon(void);
        ~SimpleBeacon(void);

        /**
         * Start BLE Advertising
         *
         * @param[in] localName  local name to advertise
         *
         * @return true on success
         *
         */

        bool iBeacon(uint16_t inMajor, uint16_t inMinor, uint8_t inPWR);
        bool EddystoneTLM(uint16_t inVoltage, uint16_t inTemp, uint32_t inCount, uint32_t inTime);
        bool EddystoneURIPlain(uint8_t inPrefix, String inURI, uint8_t inPWR);
        bool AltBeacon(void);

        /**
         * Stop BLE Advertising
         *
         * @return none
         */
        void end(void);

    private:
        struct ble_gap_adv_params_s * _ble_adv_param;
        String local_name;
        void _ble_send_adv_param(void);
        void _ble_send_ibeacon(uint16_t, uint16_t, uint8_t);
        void _ble_send_EddystoneTLM(uint16_t, uint16_t, uint32_t, uint32_t);
        void _ble_send_EddystoneURIPlain(uint8_t, String, uint8_t);
        void _ble_send_AltBeacon();
    private:

};

#endif
