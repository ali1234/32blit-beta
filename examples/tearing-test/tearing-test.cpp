// Draws horizontal and vertical lines moving exactly 1 pixel per frame.
// This should make it very easy to see if there is any tearing or stuttering.

#include "32blit.hpp"

enum Mode {Up, Down, Left, Right};

uint16_t screen_width = 160;
uint16_t screen_height = 120;
Mode mode = Left;
#define SPACING 32

void init() {
	blit::set_screen_mode(blit::screen_mode::lores);
}


void render(uint32_t time_ms) {
	static uint32_t frame = 0;
	uint32_t x = frame % SPACING;

	blit::fb.pen(blit::rgba(0, 0, 0));
	blit::fb.clear();
	blit::fb.pen(blit::rgba(255, 255, 255));

	switch (mode) {
		case Up:
		case Down:
			for (int y = 0; y < screen_height; y += SPACING) {
				blit::fb.rectangle(blit::rect(0, x + y, screen_width, 1));
			}
			break;
		case Left:
		case Right:
			for (int y = 0; y < screen_width; y += SPACING) {
				blit::fb.rectangle(blit::rect(x + y, 0, 1, screen_height));
			}
			break;
	}

	switch (mode) {
		case Up:
		case Left:
			frame--;
			break;
		case Down:
		case Right:
			frame++;
			break;
	}
}


void update(uint32_t time_ms) {
	if (blit::buttons & blit::button::A) {
		blit::set_screen_mode(blit::screen_mode::hires);
		screen_width = 320;
		screen_height = 240;
	}
	if (blit::buttons & blit::button::B) {
		blit::set_screen_mode(blit::screen_mode::lores);
		screen_width = 160;
		screen_height = 120;
	}
	if (blit::buttons & blit::button::DPAD_UP) {
		mode = Up;
	}
	if (blit::buttons & blit::button::DPAD_DOWN) {
		mode = Down;
	}
	if (blit::buttons & blit::button::DPAD_LEFT) {
		mode = Left;
	}
	if (blit::buttons & blit::button::DPAD_RIGHT) {
		mode = Right;
	}
}