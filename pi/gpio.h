/* DHT22 Raspberry Pi library
 *
 * Copyright (c) 2014 Adafruit Industries
 * Author: Tony DiCola
 * Rewrited by: Sergey Denisov aka LittleBuster (c) 2016
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef __PI_IO_H__
#define __PI_IO_H__

#include <stdint.h>
#include <stdbool.h>


enum io_errs {
    ERR_DEVMEM,
    ERR_MMAP
};

/**
 * IO library initialization
 *
 * returns 0 if succeful
 * returns ERR_DEVMEM if fail init (need root)
 * returns ERR_MMAP if fail reading mmap
 */
bool gpio_init(void);

/**
 * Set port in input mode
 * @gpio: port number
 */
void gpio_set_input(const int gpio);

/**
 * Set port in input mode
 * @gpio: port number
 */
void gpio_set_output(const int gpio);

/**
 * Set port in high level
 * @gpio: port number
 */
void gpio_set_high(const int gpio);

/**
 * Set port in low level
 * @gpio: port number
 */
void gpio_set_low(const int gpio);

/**
 * Reading data from port
 * @gpio: port number
 *
 * returns port value
 */
uint32_t gpio_read(const int gpio);

/**
 * Busy wait delay for most accurate timing, but high CPU usage.
 * Only use this for short periods of time (a few hundred milliseconds at most)!
 * @millis: wait milliseconds
 */
void gpio_wait_millis(uint32_t millis);

/**
 * General delay that sleeps so CPU usage is low,
 * but accuracy is potentially bad.
 * @millis: sleep milliseconds
 */
void gpio_sleep_millis(uint32_t millis);

/*
 * Increase scheduling priority and algorithm to try to get 'real time' results.
 */
void gpio_max_priority(void);

/*
 * Drop scheduling priority back to normal/default.
 */
void gpio_default_priority(void);


#endif