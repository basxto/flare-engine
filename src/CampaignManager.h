/*
Copyright © 2011-2012 Clint Bellanger

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
 * class CampaignManager
 *
 * Contains data for story mode
 */


#pragma once
#ifndef CAMPAIGN_MANAGER_H
#define CAMPAIGN_MANAGER_H

#include "CommonIncludes.h"
#include "ItemManager.h"

class StatBlock;
class MenuItemStorage;

class CampaignManager {
public:
	CampaignManager();
	~CampaignManager();

	void clearAll();
	void setAll(std::string s);
	std::string getAll();
	bool checkStatus(std::string s);
	void setStatus(std::string s);
	void unsetStatus(std::string s);
	bool checkCurrency(int quantity);
	bool checkItem(int item_id);
	void removeCurrency(int quantity);
	void removeItem(int item_id);
	void rewardItem(ItemStack istack);
	void rewardCurrency(int amount);
	void rewardXP(int amount, bool show_message);
	void restoreHPMP(std::string s);
	void addMsg(const std::string& msg);

	std::vector<std::string> status;
	std::string log_msg;
	std::queue<ItemStack> drop_stack;

	// pointers to various info that can be changed
	MenuItemStorage *carried_items;
	int *currency;
	StatBlock *hero;

	bool quest_update;
	float bonus_xp;		// Fractional XP points not yet awarded (e.g. killing 1 XP enemies with a +25% ring)
};


#endif
