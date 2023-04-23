/*
    This file is part of cAVRos - AVR C++ Framework - simple, fast, modern, type safe
    Copyright (C) 2023- Thomas Huxhorn

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301
    USA
*/

#ifndef ADC_HPP
#define ADC_HPP


/*
 * Begin Analog Digital Converter
 */

// undefine some AVR GCC symbols to reuse them in C++ context
#undef MUX0
#undef MUX1
#undef MUX2
#undef MUX3
#undef ADLAR
#undef REFS0
#undef REFS1
#undef ADPS0
#undef ADPS1
#undef ADPS2
#undef ADIE
#undef ADIF
#undef ADFR
#undef ADSC
#undef ADEN

/// ADC Voltage Reference Selections Bits
enum class REFS_t : uint8_t { REFS_zero=0, REFS0=1, REFS1=2 };
using enum REFS_t;

// Create bit manipulation functions for enum REFS_t
ENUM_FLAG_OPERATORS(REFS_t)

/// ADC Input Channel Selections Bits
enum class MUX_t : uint8_t { MUX_zero=0, MUX0=1, MUX1=2, MUX2=4, MUX3=8 };
using enum MUX_t;

// Create bit manipulation functions for enum MUX_t
ENUM_FLAG_OPERATORS(MUX_t)

/// ADC Multiplexer Selection Register
struct ADMUX_t {
  /// Analog Channel Selection Bit. The value of these bits selects which analog inputs are connected to the ADC.
  MUX_t MUX : 4;
  /// Reserved
  uint8_t R : 1;
  /// ADC Left Adjust Result. The ADLAR bit affects the presentation of the ADC conversion result in the ADC Data Register.
  uint8_t ADLAR : 1;
  /// Reference Selection Bit. These bits select the voltage reference for the ADC.
  REFS_t REFS : 2;

  void setChannel(uint8_t channel) volatile {
    assert(channel <= 7);
    // The bit mask of the channel variable is equal the the MUX bitnumber
    MUX = MUX_t(channel);
  }

};

static_assert(sizeof(ADMUX_t) == 1);

/// Type safe replacment register name for ADCSRA
volatile static ADMUX_t& AD_MUX = *(ADMUX_t*)&ADMUX;

/// ADC Prescaler Selections Bits
enum class ADPS_t : uint8_t { ADPS_zero=0, ADPS0=1, ADPS1=2, ADPS2=4};
using enum ADPS_t;

// Create bit manipulation functions for enum ADPS_t
ENUM_FLAG_OPERATORS(ADPS_t)

/// ADC Control and Status Register A
struct ADCSRA_t {
  // ADC Prescaler Select Bits These bits determine the division factor between the XTAL frequency and the input clock to theADC.
  ADPS_t ADPS : 3;
  /// ADC Interrupt Enable. When this bit is written to one and the I-bit in SREG is set, the ADC Conversion Complete Inter-rupt is activated.
  uint8_t ADIE : 1;
  /// ADC Interrupt Flag This bit is set when an ADC conversion completes and the Data Registers are updated.
  uint8_t ADIF : 1;
  /// ADC Free Running Select. When this bit is set (one) the ADC operates in Free Running mode.
  uint8_t ADFR : 1;
  /// ADC Start Conversion. In Single Conversion mode, write this bit to one to start each conversion
  uint8_t ADSC : 1;
  /// ADC Enable. Writing this bit to one enables the ADC.
  uint8_t ADEN : 1;
};

static_assert(sizeof(ADCSRA_t) == 1);

/// Type safe replacment register name for ADCSRA
volatile static ADCSRA_t& AD_CSRA = *(ADCSRA_t*)&ADCSRA;

struct ADC_t {

    /// Select the voltage reference for the ADC
    enum class Voltage : uint8_t { AREF=0, AVCC=1, R=2, internal=3 };

    /// Select division factor for the ADC, Prescaler
    enum class Prescaler : uint8_t { factor2=1, factor4=2, factor8=3, factor16=4, factor32=5, factor64=6, factor128=7 };

    void init(Voltage reference, Prescaler factor) {
        AD_MUX.REFS = REFS_t(reference);
        AD_CSRA.ADPS = ADPS_t(factor);
        AD_CSRA.ADEN = true;
    }

    //select ADC channel
    void set_channel(uint8_t channel) {
        AD_MUX.setChannel(channel);
    }

    // Start singlae conversion
    uint16_t start_conversion() {
        assert(AD_CSRA.ADEN)
        AD_CSRA.ADSC = true;

        // wait until conversion complete ADSC=0 -> Complete
        while (AD_CSRA.ADSC);

        return ADC;
    }
};

static_assert(sizeof(ADC_t) == 1);

inline ADC_t adc;

#endif // ADC_HPP
