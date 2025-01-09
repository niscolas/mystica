#include "Mystica/DefaultWeaponInventory.h"
#include "Mystica/MysticaGameplayTags.h"

BEGIN_DEFINE_SPEC(FDefaultWeaponInventorySpec,
                  "Project.Specs.FDefaultWeaponInventory",
                  EAutomationTestFlags::EditorContext |
                      EAutomationTestFlags::ProductFilter)
TUniquePtr<FDefaultWeaponInventory> DefaultWeaponInventoryFixture;
END_DEFINE_SPEC(FDefaultWeaponInventorySpec)

void FDefaultWeaponInventorySpec::Define() {
    Describe("Main", [this]() {
        BeforeEach([this]() {
            DefaultWeaponInventoryFixture =
                MakeUnique<FDefaultWeaponInventory>();
        });

        AfterEach([this]() {
            DefaultWeaponInventoryFixture.Reset();
        });

        It("Should register weapons properly", [this]() {
            AActor *WeaponActor = NewObject<AActor>();
            FGameplayTag WeaponTag = MysticaGameplayTags::Player_Weapon_Sword;
            DefaultWeaponInventoryFixture->RegisterWeapon(WeaponTag,
                                                          WeaponActor, false);

            TestTrue("GetWeaponByTag(WeaponTag) == WeaponActor",
                     DefaultWeaponInventoryFixture->GetWeaponByTag(WeaponTag) ==
                         WeaponActor);
        });

        It("Should not start with weapon equipped", [this]() {
            TestFalse("EquippedWeaponTag is valid",
                      DefaultWeaponInventoryFixture->GetEquippedWeaponTag()
                          .IsValid());

            TestNull("EquippedWeaponActor",
                     DefaultWeaponInventoryFixture->GetEquippedWeapon());
        });

        It("Should be able to equip registered weapons", [this]() {
            AActor *WeaponActor = NewObject<AActor>();
            FGameplayTag WeaponTag = MysticaGameplayTags::Player_Weapon_Sword;
            DefaultWeaponInventoryFixture->RegisterWeapon(WeaponTag,
                                                          WeaponActor, false);

            TestTrue("EquipWeapon() return value",
                     DefaultWeaponInventoryFixture->EquipWeapon(WeaponTag));

            TestTrue("EquippedWeaponTag is the test WeaponTag",
                     DefaultWeaponInventoryFixture->GetEquippedWeaponTag() ==
                         WeaponTag);

            TestTrue("EquippedWeaponActor is the test WeaponActor",
                     DefaultWeaponInventoryFixture->GetEquippedWeapon() ==
                         WeaponActor);
        });

        It("Should be not able to equip weapon with invalid tag", [this]() {
            TestFalse("EquipWeapon() return value",
                      DefaultWeaponInventoryFixture->EquipWeapon(
                          FGameplayTag::EmptyTag));
        });

        It("Should be not able to equip weapon that's not registered",
           [this]() {
               TestFalse("EquipWeapon() return value",
                         DefaultWeaponInventoryFixture->EquipWeapon(
                             MysticaGameplayTags::Player_Weapon_Sword));
           });

        It("Should get an invalid actor when getting a non registered weapon",
           [this]() {
               TestNull("GetWeaponByTag() return value",
                        DefaultWeaponInventoryFixture->GetWeaponByTag(
                            FGameplayTag::EmptyTag));
           });

        It("CheckHasWeapon.Should have Weapon when providing a registered "
           "Weapon Tag",
           [this]() {
               AActor *WeaponActor = NewObject<AActor>();
               FGameplayTag WeaponTag =
                   MysticaGameplayTags::Player_Weapon_Sword;
               DefaultWeaponInventoryFixture->RegisterWeapon(
                   WeaponTag, WeaponActor, false);

               TestTrue(
                   "CheckHasWeapon(Registered Tag))",
                   DefaultWeaponInventoryFixture->CheckHasWeapon(WeaponTag));
           });

        It("CheckHasWeapon.Should not have Weapon when providing an invalid "
           "Weapon Tag",
           [this]() {
               TestFalse("CheckHasWeapon(Invalid Tag))",
                         DefaultWeaponInventoryFixture->CheckHasWeapon(
                             FGameplayTag::EmptyTag));
           });

        It("CheckHasWeapon.Should not have Weapon when providing a "
           "unregistered Weapon Tag",
           [this]() {
               TestFalse("CheckHasWeapon(Valid Tag))",
                         DefaultWeaponInventoryFixture->CheckHasWeapon(
                             MysticaGameplayTags::Player_Weapon_Sword));
           });
    });
}
