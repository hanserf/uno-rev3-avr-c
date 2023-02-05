

/**
 * \file
 *
 * \brief Tinymega Port related support
 *
 (c) 2020 Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms,you may use this software and
    any derivatives exclusively with Microchip products.It is your responsibility
    to comply with third party license terms applicable to your use of third party
    software (including open source software) that may accompany Microchip software.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 */

#ifndef PORT_INCLUDED
#define PORT_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

#include <compiler.h>
#include <stdbool.h>
#include <stdint.h>

enum port_pull_mode {
    PORT_PULL_OFF,
    PORT_PULL_UP,
};

enum port_dir {
    PORT_DIR_IN,
    PORT_DIR_OUT,
    PORT_DIR_OFF,
};

typedef enum {
    IO_Port_B = 0,
    IO_Port_C = 1,
    IO_Port_D = 2,
} Port_IO_TypeDef;
/**
 * \brief Set PORT pin pull mode
 *
 * Configure pin to pull up, down or disable pull mode, supported pull
 * modes are defined by device used
 *
 * \param[in] pin       The pin number
 * \param[in] port		The port number
 * \param[in] pull_mode Pin pull mode
 */
static inline void PORT_set_pin_pull_mode(const Port_IO_TypeDef port, const uint8_t pin, const enum port_pull_mode pull_mode) {
    switch (port) {
    case IO_Port_B:
        if (pull_mode == PORT_PULL_UP) {
            DDRB &= ~(1 << pin);
            PORTB |= 1 << pin;
        } else if (pull_mode == PORT_PULL_OFF) {
            PORTB &= ~(1 << pin);
        }
        break;
    case IO_Port_C:
        if (pull_mode == PORT_PULL_UP) {
            DDRC &= ~(1 << pin);
            PORTC |= 1 << pin;
        } else if (pull_mode == PORT_PULL_OFF) {
            PORTC &= ~(1 << pin);
        }
        break;
    case IO_Port_D:
        if (pull_mode == PORT_PULL_UP) {
            DDRD &= ~(1 << pin);
            PORTD |= 1 << pin;
        } else if (pull_mode == PORT_PULL_OFF) {
            PORTD &= ~(1 << pin);
        }
        break;
    default:
        break;
    }
}

/**
 * \brief Set PORT data direction
 *
 * Select if the port pins selected by mask data direction is input, output
 * or disabled.
 *
 * \param[in] mask      Bit mask where 1 means apply direction setting to the
 *                      corresponding pin
 * \param[in] port      port number
 *
 * \param[in] direction PORT_DIR_IN  = Data direction in
 *                      PORT_DIR_OUT = Data direction out
 *                      PORT_DIR_OFF = Disables the pin
 *                      (low power state)
 */
static inline void PORT_set_port_dir(const Port_IO_TypeDef port, const uint8_t mask, const enum port_dir direction) {
    switch (port) {
    case IO_Port_B:
        switch (direction) {
        case PORT_DIR_IN:
            DDRB &= ~mask;
            break;
        case PORT_DIR_OUT:
            DDRB |= mask;
            break;
        case PORT_DIR_OFF:
            DDRB &= ~mask;
            PORTB |= mask;
            break;
        default:
            break;
        }
        break;
    case IO_Port_C:
        switch (direction) {
        case PORT_DIR_IN:
            DDRC &= ~mask;
            break;
        case PORT_DIR_OUT:
            DDRC |= mask;
            break;
        case PORT_DIR_OFF:
            DDRC &= ~mask;
            PORTC |= mask;
            break;
        default:
            break;
        }
        break;
    case IO_Port_D:
        switch (direction) {
        case PORT_DIR_IN:
            DDRD &= ~mask;
            break;
        case PORT_DIR_OUT:
            DDRD |= mask;
            break;
        case PORT_DIR_OFF:
            DDRD &= ~mask;
            PORTD |= mask;
            break;
        default:
            break;
        }
        break;

    default:
        break;
    }
}

/**
 * \brief Set PORT single pin data direction
 *
 * Select if the pin data direction is input, output or disabled.
 * If disabled state is not possible, this function throws an assert.
 *
 * \param[in] port      The port number
 * \param[in] pin       The pin number within PORT (0..7)
 * \param[in] direction PORT_DIR_IN  = Data direction in
 *                      PORT_DIR_OUT = Data direction out
 *                      PORT_DIR_OFF = Disables the pin
 *                      (low power state)
 */
static inline void PORT_set_pin_dir(const Port_IO_TypeDef port, const uint8_t pin, const enum port_dir direction) {
    switch (port) {
    case IO_Port_B:
        switch (direction) {
        case PORT_DIR_IN:
            DDRB &= ~(1 << pin);
            break;
        case PORT_DIR_OUT:
            DDRB |= 1 << pin;
            break;
        case PORT_DIR_OFF:
            DDRB &= ~(1 << pin);
            PORTB |= 1 << pin;
            break;
        default:
            break;
        }
        break;
    case IO_Port_C:
        switch (direction) {
        case PORT_DIR_IN:
            DDRC &= ~(1 << pin);
            break;
        case PORT_DIR_OUT:
            DDRC |= 1 << pin;
            break;
        case PORT_DIR_OFF:
            DDRC &= ~(1 << pin);
            PORTC |= 1 << pin;
            break;
        default:
            break;
        }
        break;
    case IO_Port_D:
        switch (direction) {
        case PORT_DIR_IN:
            DDRD &= ~(1 << pin);
            break;
        case PORT_DIR_OUT:
            DDRD |= 1 << pin;
            break;
        case PORT_DIR_OFF:
            DDRD &= ~(1 << pin);
            PORTD |= 1 << pin;
            break;
        default:
            break;
        }
        break;

    default:
        break;
    }
}

/**
 * \brief Set PORT level
 *
 * Sets output level on the pins defined by the bit mask
 *
 * \param[in] port  IO Bank port for pin
 * \param[in] mask  Bit mask where 1 means apply port level to the corresponding
 *                  pin(0..7)
 * \param[in] level true  = Pin levels set to "high" state
 *                  false = Pin levels set to "low" state
 */
static inline void PORT_set_port_level(const Port_IO_TypeDef port, const uint8_t mask, const bool level) {
    switch (port) {
    case IO_Port_B:
        if (level) {
            PORTB |= mask;
        } else {
            PORTB &= ~mask;
        }
        break;
    case IO_Port_C:
        if (level) {
            PORTC |= mask;
        } else {
            PORTC &= ~mask;
        }
        break;
    case IO_Port_D:
        if (level) {
            PORTD |= mask;
        } else {
            PORTD &= ~mask;
        }
        break;
    default:
        break;
    }
}

/**
 * \brief Set PORT level
 *
 * Sets output level on a pin
 *
 * \param[in] port
 * \param[in] pin       The pin number for device
 * \param[in] level true  = Pin level set to "high" state
 *                  false = Pin level set to "low" state
 */
static inline void PORT_set_pin_level(const Port_IO_TypeDef port, const uint8_t pin, const bool level) {
    switch (port) {
    case IO_Port_B:
        if (level) {
            PORTB |= 1 << pin;
        } else {
            PORTB &= ~(1 << pin);
        }
        break;
    case IO_Port_C:
        if (level) {
            PORTC |= 1 << pin;
        } else {
            PORTC &= ~(1 << pin);
        }
        break;
    case IO_Port_D:
        if (level) {
            PORTD |= 1 << pin;
        } else {
            PORTD &= ~(1 << pin);
        }
        break;

    default:
        break;
    }
}

/**
 * \brief Toggle out level on pins
 *
 * Toggle the pin levels on pins defined by bit mask
 *
 * \param[in] port
 * \param[in] mask  Bit mask where 1 means toggle pin level to the corresponding
 *                  pin
 */
static inline void PORT_toggle_port_level(const Port_IO_TypeDef port, const uint8_t mask) {
    switch (port) {
    case IO_Port_B:
        PINB = mask;
        break;
    case IO_Port_C:
        PINC = mask;
        break;
    case IO_Port_D:
        PIND = mask;
        break;

    default:
        break;
    }
}

/**
 * \brief Toggle output level on pin
 *
 * Toggle the pin levels on pin
 *
 * \param[in] port
 * \param[in] pin       The pin number for device
 */
static inline void PORT_toggle_pin_level(const Port_IO_TypeDef port, const uint8_t pin) {
    switch (port) {
    case IO_Port_B:
        PINB = 1 << pin;
        break;
    case IO_Port_C:
        PINC = 1 << pin;
        break;
    case IO_Port_D:
        PIND = 1 << pin;
        break;
    default:
        break;
    }
}

/**
 * \brief Get input level on pins
 *
 * Read the input level on pins connected to a port, 0xFF indicates error
 *
 * \param[in] port
 */
static inline uint8_t PORT_get_port_level(const Port_IO_TypeDef port) {
    switch (port) {
    case IO_Port_B:
        return PINB;
    case IO_Port_C:
        return PINC;
    case IO_Port_D:
        return PIND;
    default:
        return 0xFF;
    }
}

/**
 * \brief Get level on pin
 *
 * Reads the level on a pin connected to a port
 *
 * \param[in] port
 * \param[in] pin       The pin number for device
 */
static inline bool PORT_get_pin_level(const Port_IO_TypeDef port, const uint8_t pin) {
    bool level;
    switch (port) {
    case IO_Port_B:
        level = PINB & (1 << pin);
        break;
    case IO_Port_C:
        level = PINC & (1 << pin);
        break;
    case IO_Port_D:
        level = PIND & (1 << pin);
        break;
    default:
        break;
    }
    return level;
}

/**
 * \brief Write value to PORT
 *
 * Write directly to the entire port register.
 *
 * \param[in] value   Value to write
 */
static inline void PORT_write_port(const Port_IO_TypeDef port, const uint8_t value) {
    switch (port) {
    case IO_Port_B:
        PORTB = value;
        break;
    case IO_Port_C:
        PORTC = value;
        break;
    case IO_Port_D:
        PORTD = value;
        break;
    default:
        break;
    }
}

#ifdef __cplusplus
}
#endif

#endif /* PORT_INCLUDED */
