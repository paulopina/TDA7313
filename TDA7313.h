#ifndef _TDA7313_H_
#define _TDA7313_H_

#ifdef ARDUINO
#include "Wire.h"
#endif

#include <vector>

const unsigned char OPT_VOLUME = 0b10000000,
					OPT_SWITCH = 0b01000000,
					OPT_BASS   = 0b00100000,
					OPT_TREBLE = 0b00010000,
					OPT_ATTENUATORS = 0b00001000,
					OPT_ALL = 0xFF;


class TDA7313 {
	private:
		unsigned char	temp_memory[4];
		unsigned char	vol_ctrl_data,
						switch_data,
						bass_data,
						treble_data,
						lf_att_data,
						rf_att_data,
						lr_att_data,
						rr_att_data;

		unsigned char *get_attenuator(int input);
	public:
		TDA7313();

		/* select one of three inputs, starting from 0 */
		void set_input(int num);
		int get_input(void);

		/* audio switch functions */
		void set_loudness(bool on);
		bool get_loudness(void);
		void set_gain(int num);
		int get_gain(void);

		/* volume related functions */
		unsigned char get_volume(void);
		void set_volume(unsigned char vol);
		void increase_volume(void);
		void decrease_volume(void);
		bool is_volume_at_min(void);
		bool is_volume_at_max(void);

		/* mute is attenuator's lowest level for all output channels */
		void mute(void);
		void unmute(void);

		/* attenuators */
		void attenuator_set_value(int input, unsigned char value);
		unsigned char attenuator_get_value(int input);
		void attenuator_decrease(int input);
		void attenuator_increase(int input);

		/* bass */
		unsigned char get_bass_value(void);
		void set_bass_value(unsigned char val);
		void increase_bass(void);
		void decrease_bass(void);
		bool is_bass_at_max(void);
		bool is_bass_at_min(void);

		/* treble */
		unsigned char get_treble_value(void);
		void set_treble_value(unsigned char val);
		void increase_treble(void);
		void decrease_treble(void);
		bool is_treble_at_max(void);
		bool is_treble_at_min(void);

		/* returns bytes that can be written to I2C channel,
		 * options used to determine what should be sent
		 */
		std::vector<unsigned char>* get_i2c_sequence(int options);

		/* write to I2C */
		void write(int options);
};

#endif
