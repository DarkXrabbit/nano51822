#ifndef NEOPIXEL_H
#define NEOPIXEL_H

#include <class/object.h>
#include <class/list.h>
		
//extern void nrf_delay_us(uint32_t volatile number_of_us);
typedef union {
		struct {
			uint8_t g, r, b;
		}simple;
    uint8_t grb[3];
} color_t;

typedef struct {
	uint8_t pin_num;
	uint16_t num_leds;
	color_t *leds;
} neopixel_strip_t;


/**
 * @brief NeoPixel Class
 */
class CNeoPixel:CObject {
public:
	/**
	@brief Initialize GPIO and data location
	@param[in] pointer to Strip structure
	@param[in] pin number for GPIO
	*/
	void setup(uint8_t pin_num, uint16_t num_leds);
	
	/**
	@brief Turn all LEDs off
	*/
	void clear();

	/**
	@brief Update strip with structure data
	*/
	void show();

	/**
	  @brief Write RGB value to LED structure
		@param[in] red value
		@param[in] green value
		@param[in] blue value
		@param[in] LED number (starting at 1)
	  @retval 0 Successful write
	  @retval 1 LED number is out of bounds
	*/
	bool set_color(uint16_t index, uint8_t red, uint8_t green, uint8_t blue);

	/**
	 * @brief Retrieve pin number
	 */
	uint8_t pin();

	/**
	 * @brief Need to Show
	 */
	inline void needToShow() {
		m_needToShow = true;
	}

	/**
	  @brief Clears structure data
	  @param[in] pointer to Strip structure
	*/
	virtual ~CNeoPixel();

	CNeoPixel();
protected:
	neopixel_strip_t m_strip;
	bool			 m_needToShow;
};

#endif
