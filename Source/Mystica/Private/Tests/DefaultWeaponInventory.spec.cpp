#include "Mystica/DefaultWeaponInventory.h"
#include "GameplayTagsManager.h"
#include "Mystica/MysticaGameplayTags.h"
#include "Mystica/WeaponComponent.h"
#include "Templates/SharedPointer.h"

UE_DEFINE_GAMEPLAY_TAG_STATIC(Weapon_TestWeapon, "Weapon.TestWeapon");

BEGIN_DEFINE_SPEC(FDefaultWeaponInventorySpec,
                  "Project.Specs.FDefaultWeaponInventory",
                  EAutomationTestFlags::EditorContext |
                      EAutomationTestFlags::ProductFilter)

private:
TUniquePtr<FDefaultWeaponInventory> DefaultWeaponInventoryFixture;
const FGameplayTag WeaponTagFixture = Weapon_TestWeapon;

UWeaponComponent *GetRegisteredWeaponWithTagHelper(FGameplayTag InTag) const;

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
            UWeaponComponent *WeaponComponent =
                GetRegisteredWeaponWithTagHelper(WeaponTagFixture);

            TestTrue("GetWeaponByTag(WeaponTag) == WeaponActor",
                     DefaultWeaponInventoryFixture->GetWeaponByTag(
                         WeaponTagFixture) == WeaponComponent);
        });

        It("Should not start with weapon equipped", [this]() {
            TestFalse("EquippedWeaponTag is valid",
                      DefaultWeaponInventoryFixture->GetEquippedWeaponTag()
                          .IsValid());

            TestNull(
                "EquippedWeaponActor",
                DefaultWeaponInventoryFixture->GetEquippedWeapon().GetObject());
        });

        It("Should be able to equip registered weapons", [this]() {
            UWeaponComponent *WeaponComponent =
                GetRegisteredWeaponWithTagHelper(WeaponTagFixture);

            TestTrue(
                "EquipWeapon() return value",
                DefaultWeaponInventoryFixture->EquipWeapon(WeaponTagFixture));

            TestTrue("EquippedWeaponTag is the test WeaponTag",
                     DefaultWeaponInventoryFixture->GetEquippedWeaponTag() ==
                         WeaponTagFixture);

            TestTrue("EquippedWeaponActor is the test WeaponActor",
                     DefaultWeaponInventoryFixture->GetEquippedWeapon() ==
                         WeaponComponent);
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
                        DefaultWeaponInventoryFixture
                            ->GetWeaponByTag(FGameplayTag::EmptyTag)
                            .GetObject());
           });

        It("CheckHasWeapon.Should have Weapon when providing a registered "
           "Weapon Tag",
           [this]() {
               TestTrue("CheckHasWeapon(Registered Tag))",
                        DefaultWeaponInventoryFixture->CheckHasWeapon(
                            WeaponTagFixture));
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

UWeaponComponent *FDefaultWeaponInventorySpec::GetRegisteredWeaponWithTagHelper(
    FGameplayTag InTag) const {
    UWeaponComponent *WeaponComponent = NewObject<UWeaponComponent>();
    DefaultWeaponInventoryFixture->RegisterWeapon(InTag, WeaponComponent,
                                                  false);

    return WeaponComponent;
}
