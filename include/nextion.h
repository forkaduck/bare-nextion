/** @file
 *  @brief Contains most of the user facing functions for use with the displays.
*/
#pragma once

#include <stdint.h>
#include <stddef.h>

#include "queue.h"

#define DISPLAY_EVENT_SIZE 10
#define DISPLAY_LAST_ERR D_VAR_NAME_TOOLONG

/**
 * @brief Return codes dependent on bkcmd.
 *
 * Contains returned error codes.
 */
enum {
	/** Returned when instruction sent by user has failed. */
	D_INVALID = 0x00,

	/** Returned when instruction sent by user was successful. */
	D_SUCCESSFUL = 0x01,

	/** Returned when invalid Component ID or name was used. */
	D_INVALID_COMP_ID = 0x02,

	/** Returned when invalid Page ID or name was used. */
	D_INVALID_PAGE_ID = 0x03,

	/** Returned when invalid Picture ID was used. */
	D_INVALID_PIC_ID = 0x04,

	/** Returned when invalid Font ID was used. */
	D_INVALID_FONT_ID = 0x05,

	/** Returned when File operation fails. */
	D_INVALID_FILE_OP = 0x06,

	/** Returned when Instructions with CRC validation fails their CRC check. */
	D_INVALID_CRC = 0x09,

	/** Returned when invalid Baud rate was used. */
	D_INVALID_BAUD = 0x11,

	/** Returned when invalid Waveform ID or Channel # was used. */
	D_INVALID_WAFEFORM_CH_ID = 0x12,

	/** Returned when invalid Variable name or invalid attribute was used. */
	D_INVALID_VAR_NAME = 0x1a,

	/** Returned when Operation of Variable is invalid. */
	D_INVALID_VAR_OP = 0x1b,

	/** Returned when attribute assignment failed to assign. */
	D_INVALID_ASSIGN_FAILED = 0x1c,

	/** Returned when an EEPROM Operation has failed. */
	D_INVALID_EEPROM_FAILED = 0x1d,

	/** Returned when the number of instruction parameters is invalid. */
	D_INVALID_QUANTITY_PARAMETER = 0x1e,

	/** Returned when an IO operation has failed. */
	D_IO_OP = 0x1f,

	/** Returned when an unsupported escape character is used. */
	D_ESCAPE_CHAR = 0x20,

	/** Returned when an unsupported escape character is used. */
	D_VAR_NAME_TOOLONG = 0x23,
};

/**
 * @brief Return codes valid in all cases.
 *
 * Contains some events.
 */
enum {
	D_NEXT_STARTUP = 0x000000,
	D_SERIAL_OVERFLOW = 0x24,

	D_TOUCH_EVENT = 0x65,
	D_CURR_PAGE = 0x66,
	D_TOUCH_CORD_AWAKE = 0x67,
	D_TOUCH_CORD_SLEEP = 0x68,
	D_STRING = 0x70,
	D_NUM = 0x71,

	D_AUTO_SLEEP = 0x86,
	D_AUTO_WAKE = 0x87,
	D_READY = 0x88,
	D_SD_UPGRADE = 0x89,
	D_TRANSPARENT_DATA_FIN = 0xfd,
	D_TRANSPARENT_DATA_READY = 0xfe,
};

enum {
	D_PRESS = 0x01,
	D_RELEASE = 0x00,
};

/**
 * @brief Represents one event.
 *
 * Don't use this struct directly. There is a global array called d_events
 * where you can add your events.
 *
 * The handler is a function pointer to the function which should be called if
 * the event in event_type is received.
 */
struct display_event {
	void (*handler)(char[], size_t size);
	uint8_t event_type;
};

extern struct display_event g_devents[DISPLAY_EVENT_SIZE];

struct D_TOUCH_EVENT {
	uint8_t page_num;
	uint8_t component_id;
	uint8_t event;
};

struct D_CURR_PAGE {
	uint8_t current_page;
};

struct coordinate {
	uint16_t x;
	uint16_t y;
};

struct D_TOUCH_CORD {
	struct coordinate cord;
	uint8_t event;
};

struct D_STRING {
	char string[QUEUE_SIZE];
};

struct D_NUM {
	uint32_t num;
};

/**
 * @brief Read raw returned messages.
 * @param out A string to which the returned event or code is written.
 * @param out_size The size of the string.
 * @return The size of the read chars backfilled in the out parameter.
 */
size_t display_read(char out[], const size_t out_size);

/**
 * @brief Sends a string with the termination characters attached.
 * @param instruction The string to send to the display.
 * @param size The size of the string.
 */
void display_send(const char instruction[], size_t size);

/**
 * @brief Initialize the event array.
 */
void display_event_init();

/**
 * @brief Reads the oldest event and calls the appropriate handler.
 * This function needs to be called repeatably to be able to handle all incoming events
 * at nearly real time. Like in the main function.
 * @return The first error code received or 0xff if no error has been received.
 */
uint8_t display_event_loop();
