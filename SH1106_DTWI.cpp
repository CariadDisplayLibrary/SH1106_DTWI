#include <SH1106_DTWI.h>

void SH1106_DTWI::initializeDevice() {
    _dtwi->beginMaster();
    if (_res != 255) {
        pinMode(_res, OUTPUT);
        digitalWrite(_res, HIGH);
        delay(10);
        digitalWrite(_res, LOW);
        delay(10);
        digitalWrite(_res, HIGH);
    }
    initDevice();
}

void SH1106_DTWI::command(uint8_t c) {
    uint8_t state = 0;
    uint32_t ts = millis();
    uint8_t data[2] = { 0x00, c }; // Only data bytes, data bytes are commands.
    while (1) {
        if (millis() - ts > 100) {
            _dtwi->stopMaster();
            return;
        }
        switch (state) {
            case 0: // begin write 
                if (_dtwi->startMasterWrite(_addr)) {
                    state = 1;
                }
                break;
            case 1: // Send data
                if (_dtwi->write(data, 2) == 2) {
                    state = 2;
                }
                break;
            case 2: // Stop Master
                if (_dtwi->stopMaster()) {
                    return;
                }
                break;
        }
    }
}

void SH1106_DTWI::command(uint8_t c, uint8_t p) {
    uint8_t state = 0;
    uint32_t ts = millis();
    uint8_t data[3] = { 0x00, c, p }; // Only data bytes, data bytes are commands.
    while (1) {
        if (millis() - ts > 100) {
            _dtwi->stopMaster();
            return;
        }
        switch (state) {
            case 0: // begin write 
                if (_dtwi->startMasterWrite(_addr)) {
                    state = 1;
                }
                break;
            case 1: // Send data
                if (_dtwi->write(data, 3) == 3) {
                    state = 2;
                }
                break;
            case 2: // Stop Master
                if (_dtwi->stopMaster()) {
                    return;
                }
                break;
        }
    }
}

void SH1106_DTWI::data(uint8_t d) {
    uint8_t state = 0;
    uint32_t ts = millis();
    uint8_t data[2] = { 0x40, d }; // Only data bytes, data bytes are RAM.
    while (1) {
        if (millis() - ts > 100) {
            _dtwi->stopMaster();
            return;
        }
        switch (state) {
            case 0: // begin write 
                if (_dtwi->startMasterWrite(_addr)) {
                    state = 1;
                }
                break;
            case 1: // Send data
                if (_dtwi->write(data, 2) == 2) {
                    state = 2;
                }
                break;
            case 2: // Stop Master
                if (_dtwi->stopMaster()) {
                    return;
                }
                break;
        }
    }
}

void SH1106_DTWI::data(uint8_t *d, uint32_t l) {
    uint8_t state = 0;
    uint32_t ts = millis();
    uint8_t data[l + 1];
    data[0] = 0x40;
    memcpy(&data[1], d, l);
    while (1) {
        if (millis() - ts > 100) {
            _dtwi->stopMaster();
            return;
        }
        switch (state) {
            case 0: // begin write 
                if (_dtwi->startMasterWrite(_addr)) {
                    state = 1;
                }
                break;
            case 1: // Send data
                if (_dtwi->write(data, l+1) == l+1) {
                    state = 2;
                }
                break;
            case 2: // Stop Master
                if (_dtwi->stopMaster()) {
                    return;
                }
                break;
        }
    }
}
