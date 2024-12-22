#include "AbilityResponce.h"

AbilityResponce::AbilityResponce() 
    : double_damage_status(DoubleDamageStatus::disable), 
      scanner_status(ScannerStatus::empty), 
      last_ability_used(Ability::DoubleDamage) {}

void AbilityResponce::DoubleDamageActivated() {
    double_damage_status = DoubleDamageStatus::activated;
}

void AbilityResponce::DoubleDamageDisable() {
    double_damage_status = DoubleDamageStatus::disable;
}

void AbilityResponce::ScanSuccessful() {
    scanner_status = ScannerStatus::detected;
}

void AbilityResponce::ScanEmpty() {
    scanner_status = ScannerStatus::empty;
}

AbilityResponce::DoubleDamageStatus AbilityResponce::GetDoubleDamageStatus() const {
    return double_damage_status;
}

void AbilityResponce::SetLastAbility(Ability ability) {
    last_ability_used = ability;
}

void AbilityResponce::GetAbilityResult() const {
    switch (last_ability_used) {
        case Ability::DoubleDamage:
            std::cout << "использован дд" << "\n";
            break;
        case Ability::Scanner:
            if (scanner_status == ScannerStatus::detected) {
                std::cout << "в области есть корабль" << "\n";
            } else {
                std::cout << "в области нет корабля" << "\n";
            }
            break;
        case Ability::Bombardment:
            std::cout << "использован Обстрел" << "\n";
            break;
        default:
            break;
    }
}
