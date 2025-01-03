#include "MysticaGameplayTags.h"

namespace MysticaGameplayTags {
UE_DEFINE_GAMEPLAY_TAG(Input_Move, "Input.Move");
UE_DEFINE_GAMEPLAY_TAG(Input_Look, "Input.Look");
UE_DEFINE_GAMEPLAY_TAG(Input_Equip_Sword, "Input.Equip.Sword");
UE_DEFINE_GAMEPLAY_TAG(Input_Unequip_Sword, "Input.Unequip.Sword");
UE_DEFINE_GAMEPLAY_TAG(Input_LightAttack_Sword, "Input.LightAttack.Sword");
UE_DEFINE_GAMEPLAY_TAG(Input_HeavyAttack_Sword, "Input.HeavyAttack.Sword");

UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Equip_Sword,
                       "Player.Ability.Equip.Sword");
UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Unequip_Sword,
                       "Player.Ability.Unequip.Sword");

UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Attack_Light_Sword,
                       "Player.Ability.Attack.Light.Sword");
UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Attack_Heavy_Sword,
                       "Player.Ability.Attack.Heavy.Sword");

UE_DEFINE_GAMEPLAY_TAG(Player_Weapon_Sword, "Player.Weapon.Sword");

UE_DEFINE_GAMEPLAY_TAG(Player_Event_Equip_Sword, "Player.Event.Equip.Sword");
UE_DEFINE_GAMEPLAY_TAG(Player_Event_Unequip_Sword,
                       "Player.Event.Unequip.Sword");

UE_DEFINE_GAMEPLAY_TAG(Player_Effect_HeavyAttackFinisherReady_Sword,
                       "Player.Effect.HeavyAttackFinisherReady.Sword");
} // namespace MysticaGameplayTags
