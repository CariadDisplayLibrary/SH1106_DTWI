#ifndef _SH1106_DTWI_H
#define _SH1106_DTWI_H

#include <SH1106.h>

#include <DTWI.h>

class SH1106_DTWI : public SH1106 {
    private:
        DTWI *_dtwi;
        uint8_t _addr;
        uint8_t _res;

    public:
        SH1106_DTWI(DTWI &dtwi, uint8_t addr, uint8_t res = 255) :
            _dtwi(&dtwi), _addr(addr), _res(res), SH1106() {}
        SH1106_DTWI(DTWI *dtwi, uint8_t addr, uint8_t res = 255) :
            _dtwi(dtwi), _addr(addr), _res(res), SH1106() {}


        void command(uint8_t c);
        void command(uint8_t c, uint8_t p);
        void data(uint8_t d);
        void data(uint8_t *d, uint32_t l);

        void initializeDevice();

};
#endif
