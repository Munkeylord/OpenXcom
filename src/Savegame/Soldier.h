/*
 * Copyright 2010-2012 OpenXcom Developers.
 *
 * This file is part of OpenXcom.
 *
 * OpenXcom is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * OpenXcom is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with OpenXcom.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef OPENXCOM_SOLDIER_H
#define OPENXCOM_SOLDIER_H

#include <string>
#include <yaml-cpp/yaml.h>
#include "../Ruleset/Unit.h"

namespace OpenXcom
{

enum SoldierRank { RANK_ROOKIE, RANK_SQUADDIE, RANK_SERGEANT, RANK_CAPTAIN, RANK_COLONEL, RANK_COMMANDER};
enum SoldierGender { GENDER_MALE, GENDER_FEMALE };
enum SoldierLook { LOOK_BLONDE, LOOK_BROWNHAIR, LOOK_ORIENTAL, LOOK_AFRICAN };

class Craft;
class SoldierNamePool;
class Ruleset;
class RuleSoldier;
class Armor;
class Language;
class EquipmentLayoutItem;

/**
 * Represents a soldier hired by the player.
 * Soldiers have a wide variety of stats that affect
 * their performance during battles.
 */
class Soldier
{
private:
	std::wstring _name;
	int _id, _improvement;
	RuleSoldier *_rules;
	UnitStats _initialStats, _currentStats;
	SoldierRank _rank;
	Craft *_craft;
	SoldierGender _gender;
	SoldierLook _look;
	int _missions, _kills, _recovery;
	bool _recentlyPromoted, _psiTraining;
	Armor *_armor;
	std::vector<EquipmentLayoutItem*> _equipmentLayout;
public:
	/// Creates a new soldier.
	Soldier(RuleSoldier *rules, Armor *armor, const std::vector<SoldierNamePool*> *names = 0, int id = 0);
	/// Cleans up the soldier.
	~Soldier();
	/// Loads the soldier from YAML.
	void load(const YAML::Node& node, const Ruleset *rule);
	/// Saves the soldier to YAML.
	void save(YAML::Emitter& out) const;
	/// Gets the soldier's name.
	std::wstring getName() const;
	/// Sets the soldier's name.
	void setName(const std::wstring &name);
	/// Gets the soldier's craft.
	Craft *const getCraft() const;
	/// Sets the soldier's craft.
	void setCraft(Craft *craft);
	/// Gets the soldier's craft string.
	std::wstring getCraftString(Language *lang) const;
	/// Gets a string version of the soldier's rank.
	std::string getRankString() const;
	/// Gets a sprite version of the soldier's rank.
	int getRankSprite() const;
	/// Gets the soldier's rank.
	SoldierRank getRank() const;
	/// Increase the soldier's military rank.
	void promoteRank();
	/// Gets the soldier's missions.
	int getMissions() const;
	/// Gets the soldier's kills.
	int getKills() const;
	/// Gets the soldier's gender.
	SoldierGender getGender() const;
	/// Gets the soldier's look.
	SoldierLook getLook() const;
	/// Gets soldier rules.
	RuleSoldier *getRules() const;
	/// Gets the soldier's unique ID.
	int getId() const;
	/// Add a mission to the counter.
	void addMissionCount();
	/// Add a kill to the counter.
	void addKillCount(int count);
	/// Get pointer to initial stats.
	UnitStats *getInitStats();
	/// Get pointer to current stats.
	UnitStats *getCurrentStats();
	/// Get whether the unit was recently promoted.
	bool isPromoted();
	/// Gets the soldier armor.
	Armor *const getArmor() const;
	/// Sets the soldier armor.
	void setArmor(Armor *armor);
	/// Gets the soldier's wound recovery time.
	int getWoundRecovery() const;
	/// Sets the soldier's wound recovery time.
	void setWoundRecovery(int recovery);
	/// Heals wound recoveries.
	void heal();
	/// Gets the soldier's equipment-layout.
	std::vector<EquipmentLayoutItem*> *const getEquipmentLayout();
	/// Trains a soldier's psychic stats
	void trainPsi();
	/// Returns whether the unit is in psi training or not
	bool isInPsiTraining();
	/// set the psi training status
	void setPsiTraining();
	/// returns this soldier's psionic improvement score for this month.
	int getImprovement();
};

}

#endif
