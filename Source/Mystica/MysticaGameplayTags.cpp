#include "MysticaGameplayTags.h"

namespace MysticaGameplayTags {
UE_DEFINE_GAMEPLAY_TAG(Input_Move, "Input.Move");
UE_DEFINE_GAMEPLAY_TAG(Input_Look, "Input.Look");
UE_DEFINE_GAMEPLAY_TAG(Input_EquipWeapon, "Input.EquipWeapon");
UE_DEFINE_GAMEPLAY_TAG(Input_UnequipWeapon, "Input.UnequipWeapon");

UE_DEFINE_GAMEPLAY_TAG(Player_Weapon_Sword, "Player.Weapon.Sword");

UE_DEFINE_GAMEPLAY_TAG(Player_Event_Equip_Weapon, "Player.Event.Equip.Weapon");
UE_DEFINE_GAMEPLAY_TAG(Player_Event_Unequip_Weapon,
                       "Player.Event.Unequip.Weapon");
} // namespace MysticaGameplayTags
