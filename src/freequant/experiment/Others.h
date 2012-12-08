#ifndef FQ_EXO_OTHERS_H
#define FQ_EXO_OTHERS_H

#include <freequant/experiment/Indicator.h>

namespace FreeQuant { namespace Exp {

class SMI : public Indicator {
public:
    SMI();
};

class Aroon : public Indicator {
public:
    Aroon(int n = 20);
};

// Commodity Channel Index
class CCI : public Indicator {
public:
    CCI(int n = 20, double c = 0.015);
};

// Chande Momentum Oscillator
class CMO : public Indicator {
public:
    CMO(int n = 14);
};

// Commodity Channel Index
class CSI;

// Cumulative Volume Index
class CVI;

// Detrended Price Oscillator
class DPO : public Indicator {
public:
    DPO(int n = 14, double shift = 8, double percent = false);
};

// Dynamic Momentum Index
class DMI;

// Klinger Oscillator
class KO;

class EMV : public Indicator {
public:
    EMV(int n = 9, double shift = 8, double percent = false);
};

class SRA;
class TRIX;
class WAD;
class ROC;
class OBV;
// Relative Momentum Index
class RMI;

// Relative Volatility Index
class RVI;

// Percentage Volume Oscillator
class PVO;

// Price and Volume Trend
class PVT;

// Market Facilitation Index
class MFI;

// Negative Volume Index
class NVI;

// Net Momentum Oscillator
class NMO;

// On Balance Open Interest
class OBOI;

class VHF;
class CMF;
class ADXR;
class RVI;
class ZigZag;
class ChaikinVolatility;

// r-squared
class RSquared;

// Vertical Horizontal Filter
class VHF;
}}
#endif // FQ_EXO_OTHERS_H
