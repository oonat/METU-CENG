
#ifndef ADC_H
#define	ADC_H

#ifdef	__cplusplus
extern "C" {
#endif


    
    void InitADC()
    {
        ADCON1bits.PCFG3=1; // RA0 = Analog, RA1=1 Analog, RA2 = Analog
        ADCON1bits.PCFG2=1;
        ADCON1bits.PCFG1=0;
        ADCON1bits.PCFG0=0;
        
        ADCON1bits.VCFG0 =0; //Vref+=5.0, Vref=0
        ADCON1bits.VCFG1=0;
        
        TRISAbits.RA0 = 1;
        TRISAbits.RA1 = 1;
        TRISAbits.RA2 = 1;
        
        // For 40 MHZ (Fosc) -> Tosc = 1/40 us (Tosc = 1 / Fosc)
        // Tad options (2xTosc, 4xTosc, 8xTosc, 16xTosc, 32xTosc, 64xTosc)
        // min Tad 0.7 us - max Tad 25 us (0.7 us <= Tad <= 25 us, Keep as short as possible)
        // The closest one to min Tad (64xTosc) hence Tad = 64xTosc = 1.6 us (ADCS2:ADCS0=110)
        // Acquisition time options (0xTad, 2xTad, 4xTad, 6xTad, 8xTad, 12xTad, 16xTad, 20xTad)
        // In order to increase the sampling rate (the number of samples that can be obtained by a ADC module in 1 second)
        // We can keep the acquisition time as short as possible without violating the minimum acquisition time
        // Min acquisition time = 2.4 us (the closest acquisition time we can set 2xTad = 3.2us) (ACQT2:ACQT0=001)
       
        ADCON2bits.ADCS2 = 1; //Tad (64xTOSC) -> 1.6 us
        ADCON2bits.ADCS1 = 1;
        ADCON2bits.ADCS0 = 0;
        
        ADCON2bits.ACQT2 = 0; //Acqusition time (2xTad) = 3.2 us
        ADCON2bits.ACQT1 = 0;
        ADCON2bits.ACQT0 = 1;
        
        ADCON2bits.ADFM = 1; // Right justified...
                
        ADCON0bits.ADON = 1; //ADC module is enabled....
           
    }

    
#ifdef	__cplusplus
}
#endif

#endif	/* ADC_H */

