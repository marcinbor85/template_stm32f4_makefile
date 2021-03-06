/*
MIT License

Copyright (c) 2020 Marcin Borowicz

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#ifndef HW_UART_H
#define HW_UART_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>

#include "utils/fifo.h"

struct uart_descriptor {
        void *reg;

        uint32_t baudrate;

        uint8_t *buf_rx;
        uint32_t buf_rx_size;
        uint8_t *buf_tx;
        uint32_t buf_tx_size;
};

struct uart {
        struct uart_descriptor const *desc;

        struct fifo fifo_rx;
        struct fifo fifo_tx;
};

void uart_init(struct uart *self, const struct uart_descriptor *desc);

bool uart_read_byte(struct uart *self, uint8_t *byte);
bool uart_write_byte(struct uart *self, uint8_t byte);
bool uart_write_buf(struct uart *self, uint8_t *buf, uint32_t size);

extern void uart_port_init(struct uart *self);
extern void uart_port_disable_rx_interrupt(struct uart *self);
extern void uart_port_enable_rx_interrupt(struct uart *self);
extern void uart_port_disable_tx_interrupt(struct uart *self);
extern void uart_port_enable_tx_interrupt(struct uart *self);

extern void uart_port_rx_isr(struct uart *self);
extern void uart_port_tx_isr(struct uart *self);

#ifdef __cplusplus
}
#endif

#endif /* HW_UART_H */
