#ifndef ABILITYRESPONCE_H
#define ABILITYRESPONCE_H

#include <iostream>

class AbilityResponce {
public:
    enum class DoubleDamageStatus {
        activated,
        disable
    };

    enum class ScannerStatus {
        detected,
        empty
    };

    enum class Ability {
        DoubleDamage,
        Scanner,
        Bombardment
    };

private:
    DoubleDamageStatus double_damage_status;
    ScannerStatus scanner_status;
    Ability last_ability_used;

public:
    AbilityResponce();

    void DoubleDamageActivated();
    void DoubleDamageDisable();
    void ScanSuccessful();
    void ScanEmpty();

    DoubleDamageStatus GetDoubleDamageStatus() const;
    void SetLastAbility(Ability ability);
    void GetAbilityResult() const;
};

#endif // ABILITYRESPONCE_H
