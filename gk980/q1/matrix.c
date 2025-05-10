// Copyright 2023 NaturaZh (@NaturalZh)
// SPDX-License-Identifier: GPL-2.0-or-later
#include "matrix.h"
#include <string.h>
#include "atomic_util.h"

#define CLOCK_TIME 15
#define MATRIX_INPUT_PRESSED_STATE 0

#define HC595_ST_PIN A6
#define HC595_SH_PIN A5
#define HC595_DS_PIN A7

pin_t row_pins[MATRIX_ROWS] = MATRIX_ROW_PINS;

static inline void select_delay(uint16_t n) {
    while (n-- > 0) {
        asm volatile("nop" ::: "memory");
    };
}

static inline void gpio_set_pin_output_write_low(pin_t pin) {
    ATOMIC_BLOCK_FORCEON {
        gpio_set_pin_output(pin);
        gpio_write_pin_low(pin);
    }
}

static inline void gpio_set_pin_output_write_high(pin_t pin) {
    ATOMIC_BLOCK_FORCEON {
        gpio_set_pin_output(pin);
        gpio_write_pin_high(pin);
    }
}

static inline void gpio_set_pin_input_high_atomic(pin_t pin) {
    ATOMIC_BLOCK_FORCEON {
        gpio_set_pin_input_high(pin);
    }
}

static inline uint8_t gpio_read_matrix_pin(pin_t pin) {
    if (pin != NO_PIN) {
        return (gpio_read_pin(pin) == MATRIX_INPUT_PRESSED_STATE) ? 0 : 1;
    } else {
        return 1;
    }
}

static inline void clock_pulse(uint16_t n) {
    gpio_write_pin_high(HC595_SH_PIN);
    gpio_write_pin_high(HC595_ST_PIN);
    select_delay(n);
    gpio_write_pin_low(HC595_SH_PIN);
    gpio_write_pin_low(HC595_ST_PIN);
}

// matrix code

static bool select_col(uint8_t col) {
    gpio_set_pin_output_write_high(HC595_DS_PIN);
        for (uint8_t m = 0; m <= col; m++) {
           if(m == 0){
               gpio_write_pin_low(HC595_DS_PIN);
            }else{
               gpio_write_pin_high(HC595_DS_PIN);
            }
           clock_pulse(CLOCK_TIME);
        }
        return true;

}

static void unselect_col(uint8_t col) {
    uint8_t x = (MATRIX_COLS - col);
    gpio_set_pin_output_write_high(HC595_DS_PIN);
     for (uint8_t y = 0; y < x ; y++) {
        clock_pulse(CLOCK_TIME);
    }
}

static void unselect_cols(void) {
    gpio_set_pin_output_write_low(HC595_SH_PIN);
    gpio_set_pin_output_write_low(HC595_ST_PIN);
    gpio_set_pin_output_write_high(HC595_DS_PIN);
    for (uint8_t x = 0; x < MATRIX_COLS; x++) {
        clock_pulse(CLOCK_TIME);
    }
}

__attribute__((weak)) void matrix_init_pins(void) {
    unselect_cols();
    for (uint8_t x = 0; x < MATRIX_ROWS; x++) {
        if (row_pins[x] != NO_PIN) {
            gpio_set_pin_input_high_atomic(row_pins[x]);
        }
    }
}

void matrix_read_rows_on_col(matrix_row_t current_matrix[], uint8_t current_col, matrix_row_t row_shifter) {
    bool key_pressed = false;

    // Select col
    if (!select_col(current_col)) { // select col
        return;                     // skip NO_PIN col
    }
    matrix_output_select_delay();

    // For each row...
    for (uint8_t row_index = 0; row_index < MATRIX_ROWS; row_index++) {
        // Check row pin state
        if (gpio_read_matrix_pin(row_pins[row_index]) == 0) {
            // Pin LO, set col bit
            current_matrix[row_index] |= row_shifter;
            key_pressed = true;
        } else {
            // Pin HI, clear col bit
            current_matrix[row_index] &= ~row_shifter;
        }
    }

    // Unselect col
    unselect_col(current_col);
    matrix_output_unselect_delay(current_col, key_pressed); // wait for all Row signals to go HIGH
}

void matrix_init_custom(void) {
    // initialize key pins
    matrix_init_pins();
}

bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    matrix_row_t curr_matrix[MATRIX_ROWS] = {0};

    // Set col, read rows
    matrix_row_t row_shifter = MATRIX_ROW_SHIFTER;
    for (uint8_t current_col = 0; current_col < MATRIX_COLS; current_col++, row_shifter <<= 1) {
        matrix_read_rows_on_col(curr_matrix, current_col, row_shifter);
    }

    bool changed = memcmp(current_matrix, curr_matrix, sizeof(curr_matrix)) != 0;
    if (changed) memcpy(current_matrix, curr_matrix, sizeof(curr_matrix));
    return (uint8_t)changed;
}
