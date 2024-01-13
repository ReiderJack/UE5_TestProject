


#include "HealthAttributeSet.h"
#include "GameplayEffectExtension.h"

void UHealthAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
    Super::PreAttributeChange(Attribute, NewValue);

    if(Attribute == GetHealthAttribute())
    {
        NewValue = FMath::Clamp(NewValue, 0.f, GetHealthMax());
    }
}

void UHealthAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
    Super::PostGameplayEffectExecute(Data);
    
    if (Data.EvaluatedData.Attribute == GetDamageAttribute())
    {
        const float LocalDamageDone = GetDamage();
        SetDamage(0.f);

        if (LocalDamageDone > 0.0f)
        {
            const float NewHealth = GetHealth() - LocalDamageDone;
            SetHealth(FMath::Clamp(NewHealth, 0.0f, GetHealthMax()));
        }
    }
}

float UHealthAttributeSet::GetHealth() const
{
    // Return Health's current value, but never return a value lower than zero.
    // This is the value after all modifiers that affect Health have been considered.
    return FMath::Max(Health.GetCurrentValue(), 0.0f);
}

void UHealthAttributeSet::SetHealth(float NewVal)
{
    // Do not accept values lower than zero.
    NewVal = FMath::Max(NewVal, 0.0f);

}
