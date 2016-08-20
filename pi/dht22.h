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

#ifndef __DHT22_H__
#define __DHT22_H__

#include <stdint.h>
#include <stdbool.h>


struct dht22 {
	uint8_t data[5];
	uint8_t pin;
};


/**
 * Initialization gpio and dht structure
 * @dht: dht structure pointer
 * @pin: reading pin
 */
void dht22_init(struct dht22 *dht, uint8_t pin);

/**
* Reading temperature and humidity
* @dht: dht structure pointer
* @temp: temperature pointer
* @hum: humidity pointer
*
* returns true: if complete reading data
* returns false: if fail reading data
*/
bool dht22_read_data(struct dht22 *dht, float *temp, float *hum);


#endif
