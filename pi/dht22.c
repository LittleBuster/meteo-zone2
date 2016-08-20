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
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dht22.h"
#include "gpio.h"

/* This is the only processor specific magic value, the maximum amount of time to
 * spin in a loop before bailing out and considering the read a timeout.  This should
 * be a high value, but if you're running on a much faster platform than a Raspberry
 * Pi or Beaglebone Black then it might need to be increased.
 */
#define DHT_MAXCOUNT 32000

/* Number of bit pulses to expect from the DHT.  Note that this is 41 because
 * the first pulse is a constant 50 microsecond pulse, with 40 pulses to represent
 * the dht->data afterwards.
 */
#define DHT_PULSES 41


void dht22_init(struct dht22 *dht, uint8_t pin)
{
    dht->pin = pin;
    memset(dht->data, 0x00, sizeof(uint8_t)*5);
}

bool dht22_read_data(struct dht22 *dht, float *temp, float *hum)
{
    uint32_t count = 0;
    uint32_t threshold = 0;
    uint32_t pulseCounts[DHT_PULSES*2] = {0};

    gpio_set_output(dht->pin);
    gpio_max_priority();
    gpio_set_high(dht->pin);
    gpio_sleep_millis(500);
    gpio_set_low(dht->pin);
    gpio_wait_millis(20);
    gpio_set_input(dht->pin);

    /*
     * Need a very short delay before reading pins or else value
     * is sometimes still low.
     */
    for (volatile uint8_t i = 0; i < 50; ++i) {}

    /* Wait for DHT to pull pin low. */
    while (gpio_read(dht->pin))
        if (++count >= DHT_MAXCOUNT) {
            gpio_default_priority();
            return false;
        }

    /* Record pulse widths for the expected result bits. */
    for (uint8_t i = 0; i < DHT_PULSES*2; i += 2) {
        while (!gpio_read(dht->pin))
            if (++pulseCounts[i] >= DHT_MAXCOUNT) {
                gpio_default_priority();
                return false;
            }

        while (gpio_read(dht->pin))
            if (++pulseCounts[i+1] >= DHT_MAXCOUNT) {
                gpio_default_priority();
                return false;
            }
    }
    gpio_default_priority();

    for (uint8_t i = 2; i < DHT_PULSES*2; i += 2)
        threshold += pulseCounts[i];

    threshold /= DHT_PULSES-1;

    /* Interpret each high pulse as a 0 or 1 by comparing it to the 50us reference.
     * If the count is less than 50us it must be a ~28us 0 pulse, and if it's higher
     * then it must be a ~70us 1 pulse.
     */
    for (uint8_t i = 3; i < DHT_PULSES*2; i += 2) {
        uint8_t index = (i-3)/16;

        dht->data[index] <<= 1;
        if (pulseCounts[i] >= threshold)
            dht->data[index] |= 1;
    }

    if (dht->data[4] == ((dht->data[0] + dht->data[1] + dht->data[2] + dht->data[3]) & 0xFF)) {
        *hum = (dht->data[0] * 256 + dht->data[1]) / 10.0f;
        *temp = ((dht->data[2] & 0x7F) * 256 + dht->data[3]) / 10.0f;
        if (dht->data[2] & 0x80)
            *temp *= -1.0f;
    } else
	return false;
    return true;
}
