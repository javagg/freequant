#ifndef FQ_EXO_OTHERS_H
#define FQ_EXO_OTHERS_H

#include <memory>
#include <freequant/experiment/Indicator.h>

namespace FreeQuant { namespace Exp {

// Absolute Breadth Index
class ABI;

// Accumulation Swing Index
class ASI;

// Accumulation/Distribution Line
class ADL : public Indicator {
public:
    ADL();
    //Acc/Dist = ((Close – Low) – (High – Close)) / (High – Low) * Period's volume
};

class Alligator {

};

class Gator {
//    MEDIAN PRICE = (HIGH + LOW) / 2
//    ALLIGATORS JAW = SMMA (MEDIAN PRICE, 13, 8)
//    ALLIGATORS TEETH = SMMA (MEDIAN PRICE, 8, 5)
//    ALLIGATORS LIPS = SMMA (MEDIAN PRICE, 5, 3)
//    Where:
//    HIGH — is the maximum price;
//    LOW — is the minimum price;
//    SMMA (A, B, C) — smoothed moving average. Parameter А — smoothed data, В — period of smoothing, С — Shift in the future.
};

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
//    To find a Typical Price. You need to add the HIGH, the LOW, and the CLOSE prices of each bar and then divide the result by 3.
//    TP = (HIGH + LOW +CLOSE)/3
//    To calculate the n-period Simple Moving Average of typical prices.
//    SMA(TP, N) = SUM[TP, N]/N
//    To subtract the received SMA(TP, N) from Typical Prices.
//    D = TP — SMA(TP, N)
//    To calculate the n-period Simple Moving Average of absolute D values.
//    SMA(D, N) = SUM[D, N]/N
//    To multiply the received SMA(D, N) by 0,015.
//    M = SMA(D, N) * 0,015
//    To divide M by D
//    CCI = M/D
//Where:
//SMA — Simple Moving Average;
//N — number of periods, used for calculation.
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
//    DPO = CLOSE - SMA (CLOSE, (N / 2 + 1))
//    Where:
//    SMA — a simple moving average;
//    CLOSE — the closing price;
//    N — the period of the cycle (if N is equal to 12, DPO resembles the DiNapoli Detrend Oscillator).
};

// Dynamic Momentum Index
class DMI;

// Klinger Oscillator
class KO;

// Ease of Movement
class EMV : public Indicator {
public:
    EMV(int n = 9, double shift = 8, double percent = false);
};

class Envelope {

};

class SRA;
class TRIX;
class WAD;
class ROC {
//    You can find the speed of price change as a difference between current closing price and the closing price n periods ago.
//    ROC = ((CLOSE (i) - CLOSE (i - n)) / CLOSE (i - n)) * 100
//    Where:
//    CLOSE (i) — the closing price of the current bar;
//    CLOSE (i - n) — the closing price n bars ago;
//    ROC — the value of Price Rate of Change indicator.
};

class StochasticOscillator {
//    The Stochastic Oscillator has four variables:
//        %K periods. This is the number of time periods used in the stochastic calculation;
//        %K Slowing Periods. This value controls the internal smoothing of %K. A value of 1 is considered a fast stochastic; a value of 3 is considered a slow stochastic;
//        %D periods. his is the number of time periods used when calculating a moving average of %K;
//        %D method. The method (i.e., Exponential, Simple, Smoothed, or Weighted) that is used to calculate %D.
//    The formula for %K is:
//    %K = (CLOSE-LOW(%K))/(HIGH(%K)-LOW(%K))*100
//    Where:
//    CLOSE — is today’s closing price;
//    LOW(%K) — is the lowest low in %K periods;
//    HIGH(%K) — is the highest high in %K periods.

//    The %D moving average is calculated according to the formula:
//    %D = SMA(%K, N)
//    Where:
//    N — is the smoothing period;
//    SMA — is the Simple Moving Average.
};

// On Balance Volume
class OBV : public Indicator {
//    If today’s close is greater than yesterday’s close then:
//    OBV(i) = OBV(i-1)+VOLUME(i)
//    If today’s close is less than yesterday’s close then:
//    OBV(i) = OBV(i-1)-VOLUME(i)
//    If today’s close is equal to yesterday’s close then:
//    OBV(i) = OBV(i-1)
//    Where:
//    OBV(i) — is the indicator value of the current period;
//    OBV(i-1) — is the indicator value of the previous period;
//    VOLUME(i) — is the volume of the current bar.
};

// Relative Momentum Index
class RMI : public Indicator {
public:
//    RMI(int n) : _n(n) {}
//    void onCalculate(const Bar& bar) {
//        double close_n = 0;
//        double close_0 = 0;
//        double up = 0;
//        double dn = 0;
//        double rmi = 0;
//        if (size() > _n) {
//            if(close_0 > close_n) {
//                up = close_0 - close_n;
//            } else {
//                dn = close_n - close_0;
//            }
//            _upavg = (_upavg*(_n-1)+up)/_n;
//            _dnavg = (_dnavg*(_n-1)+up)/_n;
//            rmi = 100*(_upavg/(_upavg+_dnavg));
//        }
//        append(bar.dateTime(), rmi);
//    }
private:
    int _n;

    double _upavg;
    double _dnavg;
};

// Relative Volatility Index
class RVI;

// Percentage Volume Oscillator
class PVO;

// Price and Volume Trend
class PVT {
//    We get PVT by multiplying the current volume by the relative change of the share price and adding the result to the current cumulate value of the indicator.
//    PVT (i) = ((CLOSE (i) - CLOSE (i - 1)) / CLOSE (i - 1)) * VOLUME (i) + PVT (i - 1)
//    Where:
//    CLOSE (i) — the closing price of the current bar;
//    CLOSE (i - n) — the closing price n bars ago;
//    VOLUME (i) — the volume of the current bar;
//    PVT (i) — the current value of PVT indicator;
//    PVT (i - 1) — the value of PVT indicator on the previous bar.
};

// Market Facilitation Index

// Money Flow Index
class MFI : public Indicator {
//    TP = (HIGH + LOW + CLOSE)/3
//    MF = TP * VOLUME
//    MR = Positive Money Flow (PMF)/Negative Money Flow (NMF)
//    MFI = 100 - (100 / (1 + MR))
};

class MassInex {
//    MI = SUM (EMA (HIGH - LOW, 9) / EMA (EMA (HIGH - LOW, 9), 9), N)
//    Where:
//    SUM — means a sum;
//    HIGH — the maximum price of the current bar;
//    LOW — the minimum price of the current bar;
//    EMA — the exponential moving average;
//    N — the period of the indicator (the number of values added).
};

// Negative Volume Index
class NVI {
//    Mathematically, the NVI compares the day's volatility to its moving average:

//    If V < V-1, then NVI = NVI-1 + ((Px - Px-1) / Px-1)
//    If V > V-1, then NVI = NVI-1

//    where V = today's trading volume, V-1 = yesterday's trading volume, NVI-1 = yesterday's NVI, Px = today's closing price, and Px-1 = yesterday's closing price.

};

// Net Momentum Oscillator
class NMO;

// On Balance Open Interest
class OBOI;

// Volume Rate of Change
class VROC {
//    VROC = ((VOLUME (i) - VOLUME (i - n)) / VOLUME (i - n)) * 100
//    Where:
//    VOLUME (i) — is the current bar volume;
//    VOLUME (i - n) — the volume n bars ago;
//    VROC — the Volume Rate of Change indicator value.
};

//Positive Volume Index
class PVI;

class VHF;
class CMF;
class ADXR;
class RVI;
class ZigZag;

class VWAP {

};

class UltimateOscillator {
//    Define current "True Low" (TL) — the least of two values: the current minimum and the precious closing price.
//    TL (i) = MIN (LOW (i) || CLOSE (i - 1))
//    Find current "Buying Pressure" (BP). It is equal to the difference between current closing price and current True Low.
//    BP (i) = CLOSE (i) - TL (i)
//    Define the "True Range" (TR). It is the greatest of the following differences: current maximum and minimum; current maximum and previous closing price; current minimum and previous closing price.
//    TR (i) = MAX (HIGH (i) - LOW (i) || HIGH (i) - CLOSE (i - 1) || CLOSE (i - 1) - LOW (i))
//    Find the sum of BP values for all three periods of calculation:
//    BPSUM (N) = SUM (BP (i), i)
//    Find the sum of TR values for all three periods of calculation:
//    TRSUM (N) = SUM (TR (i), i)
//    Calculate the "Raw Ultimate Oscillator" (RawUO)
//    RawUO = 4 * (BPSUM (1) / TRSUM (1)) + 2 * (BPSUM (2) / TRSUM (2)) + (BPSUM (3) / TRSUM (3))
//    Calculate the "Ultimate Oscillator" (UO) value according to the formula:
//    UO = ( RawUO / (4 + 2 + 1)) * 100
//Where:
//MIN — means the minimum value;
//MAX — the maximum value;
//|| — a logical OR;
//LOW (i) — the minimum price of the current bar;
//HIGH (i) — the maximum price of the current bar;
//CLOSE (i) — the closing price of the current bar;
//CLOSE (i — 1) — the closing price of the previous bar;
//TL (i) — the True Low;
//BP (i) — the Buying Pressure;
//TR (i) — the True Range;
//BPSUM (N) — the mathematical sum of BP values for an n period (N equal to 1 corresponds with i=7 bars; N equal to 2 corresponds with i=14 bars; N equal to 3 corresponds with i=28 bars);
//TRSUM (N) — the mathematical sum of TR values for an n period (N equal to 1 corresponds with i=7 bars; N equal to 2 corresponds with i=14 bars; N equal to 3 corresponds with i=28 bars);
//RawUO — "Raw Ultimate Oscillator";
//UO — stands for Ultimate Oscillator.
};

class ChaikinOscillator {
//    To calculate the Chaikin's oscillator, you must subtract a 10-period exponential moving average of Accumulation/Distribution indicator from a 3-period exponential moving average of the same indicator.
//    CHO = EMA (A/D, 3) — EMA (A/D, 10)
//    Where:
//    EMA — exponential moving average;
//    A/D — Accumulation/Distribution indicator.
};

class ChaikinVolatility {
//    H-L (i) = HIGH (i) - LOW (i)
//    H-L (i - 10) = HIGH (i - 10) - LOW (i - 10)
//    CHV = (EMA (H-L (i), 10) - EMA (H-L (i - 10), 10)) / EMA (H-L (i - 10), 10) * 100
//    Where:
//    HIGH (i) — maximum price of current bar;
//    LOW (i) — minimum price of current bar;
//    HIGH (i - 10) — maximum price of the bar ten positions away from the current one;
//    LOW (i - 10) — minimum price of the bar ten positions away from the current one;
//    H-L (i) — difference between the maximum and the minimum price in the current bar;
//    H-L (i - 10) — difference between the maximum and the minimum price ten bars ago;
//    EMA — exponential moving average.
};

// r-squared
class RSquared;

// Vertical Horizontal Filter
class VHF;
}}
#endif // FQ_EXO_OTHERS_H
