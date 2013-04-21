/*
Copyright © 2011-2012 Clint Bellanger
Copyright © 2012 Stefan Beller

This file is part of FLARE.

FLARE is free software: you can redistribute it and/or modify it under the terms
of the GNU General Public License as published by the Free Software Foundation,
either version 3 of the License, or (at your option) any later version.

FLARE is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
PARTICULAR PURPOSE.  See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with
FLARE.  If not, see http://www.gnu.org/licenses/
*/

/**
 * class WidgetButton
 */

#include "WidgetSlot.h"
#include "SharedResources.h"
#include "SDL_gfxBlitFunc.h"
#include "Settings.h"

using namespace std;

WidgetSlot::WidgetSlot(SDL_Surface *_icons, int icon_id)
	: Widget()
	, icons(_icons)
	, icon_id(icon_id)
	, enabled(true)
	, pressed(false)
{
	focusable = true;
	pos.x = pos.y = 0;
	pos.w = ICON_SIZE;
	pos.h = ICON_SIZE;
}

void WidgetSlot::activate() {
	pressed = true;
}

bool WidgetSlot::checkClick() {
	return checkClick(inpt->mouse.x,inpt->mouse.y);
}

/**
 * Sets and releases the "pressed" visual state of the button
 * If press and release, activate (return true)
 */
bool WidgetSlot::checkClick(int x, int y) {
	Point mouse(x,y);

	// disabled buttons can't be clicked;
	if (!enabled) return false;

	// main button already in use, new click not allowed
	if (inpt->lock[MAIN1]) return false;
	if (inpt->lock[ACCEPT]) return false;

	// main click released, so the button state goes back to unpressed
	if (pressed && !inpt->lock[MAIN1] && !inpt->lock[ACCEPT]) {
		pressed = false;
		return true;
	}

	pressed = false;

	// detect new click
	if (inpt->pressing[MAIN1]) {
		if (isWithin(pos, mouse)) {

			inpt->lock[MAIN1] = true;
			pressed = true;

		}
	}
	return false;

}

void WidgetSlot::render(SDL_Surface *target) {
	if (target == NULL) {
		target = screen;
	}
	SDL_Rect src;

	int columns = icons->w / ICON_SIZE;
	src.x = (icon_id % columns) * ICON_SIZE;
	src.y = (icon_id / columns) * ICON_SIZE;
	
	src.w = pos.w;
	src.h = pos.h;

	if (render_to_alpha)
		SDL_gfxBlitRGBA(icons, &src, target, &pos);
	else
		SDL_BlitSurface(icons, &src, target, &pos);

	if (in_focus) {
		Point topLeft;
		Point bottomRight;
		Uint32 color;

		topLeft.x = pos.x;
		topLeft.y = pos.y;
		bottomRight.x = pos.x + pos.w;
		bottomRight.y = pos.y + pos.h;
		color = SDL_MapRGB(target->format, 0,191,255);

		if (target == screen) {
			SDL_LockSurface(screen);
			drawRectangle(target, topLeft, bottomRight, color);
			SDL_UnlockSurface(screen);
		}
		else
			drawRectangle(target, topLeft, bottomRight, color);
	}
}

WidgetSlot::~WidgetSlot() {
}
