// Example PwmIn class to detect PWM inputs, sford
//  - Note: uses InterruptIn, so not available on p19/p20

#include "mbed.h"

class PwmIn {
public:
    PwmIn(PinName p) : _p(p) {
        _p.rise(this, &PwmIn::rise);
        _p.fall(this, &PwmIn::fall);
        _period = 0.0;
        _pulsewidth = 0.0;
        _t.start();
    }
    
    void rise() {
        _period = _t.read();
        _t.reset();
    }
    
    void fall() {
        _pulsewidth = _t.read();
    }
    
    float period() { return _period; }
    float pulsewidth() { return _pulsewidth; }
    float dutycycle() { return _pulsewidth / _period; }

protected:        
    InterruptIn _p;
    Timer _t;
    float _pulsewidth, _period;
};

PwmOut x(p21);
PwmOut y(p22);

PwmIn a(p5);
PwmIn b(p6);

int main() {
    x = 0.5;
    y = 0.2;
    while(1) {
        printf("a: pw = %f, period = %f\n", a.pulsewidth(), a.period());
        printf("b: pw = %f, period = %f\n", b.pulsewidth(), b.period());
        wait(2);
    }
}
