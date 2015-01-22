// GB Enhanced+ Copyright Daniel Baxter 2014
// Licensed under the GPLv2
// See LICENSE.txt for full license text

// File : mmu.h
// Date : April 22, 2014
// Description : Game Boy Advance memory manager unit
//
// Handles reading and writing bytes to memory locations

#ifndef GBA_MMU
#define GBA_MMU

#include <fstream>
#include <string>
#include <vector>
#include <iostream>

#include "common.h"
#include "gamepad.h"
#include "timer.h"
#include "lcd_data.h"

class MMU
{
	public:

	//Cartridge save-type enumerations
	enum backup_types
	{
		NONE,
		EEPROM,
		FLASH,
		SRAM
	};

	backup_types current_save_type;

	std::vector <u8> memory_map;

	//Memory access timings (Nonsequential and Sequential)
	u8 n_clock;
	u8 s_clock;

	bool bios_lock;

	//Structure to handle DMA transfers
	struct dma_controllers
	{
		bool enable;
		bool started;
		u32 start_address;
		u32 destination_address;
		u32 current_dma_position;
		u32 word_count;
		u8 word_type;
		u16 control;
		u8 dest_addr_ctrl;
		u8 src_addr_ctrl;
		u8 delay;
	} dma[4];

	//Structure to handle EEPROM reading and writing
	struct eeprom_controller
	{
		u8 bitstream_byte;
		u16 address;
		u32 dma_ptr;
		std::vector <u8> data;
		u16 size;
		bool size_lock;
	} eeprom;

	MMU();
	~MMU();

	void reset();

	void start_blank_dma();

	u8 read_u8(u32 address) const;
	u16 read_u16(u32 address) const;
	u32 read_u32(u32 address) const;

	u16 read_u16_fast(u32 address) const;
	u32 read_u32_fast(u32 address) const;

	void write_u8(u32 address, u8 value);
	void write_u16(u32 address, u16 value);
	void write_u32(u32 address, u32 value);

	void write_u16_fast(u32 address, u16 value);
	void write_u32_fast(u32 address, u32 value);

	bool read_file(std::string filename);
	bool read_bios(std::string filename);
	bool save_backup(std::string filename);
	bool load_backup(std::string filename);

	void eeprom_set_addr();
	void eeprom_read_data();
	void eeprom_write_data();

	void set_lcd_data(lcd_data* ex_lcd_stat);

	GamePad* g_pad;
	std::vector<gba_timer>* timer;

	private:

	//Only the MMU and LCD should communicate through this structure
	lcd_data* lcd_stat;
};

#endif // GBA_MMU


