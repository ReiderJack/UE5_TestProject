

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "HealthAttributeSet.generated.h"

// Uses macros from AttributeSet.h
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

/**
 * 
 */
UCLASS()
class TESTPROJECTALSV4_API UHealthAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
	
protected:
    /** Sample "Health" Attribute */
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    FGameplayAttributeData Health;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayAttributeData HealthMax;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayAttributeData Damage;

    //~ ... Other Gameplay Attributes here ...

public:
    //~ Helper functions for "Health" attributes

   virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;

	// Called everytime an effect is applied to the ability system
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

    // Static function, returns the FGameplayAttribute struct from the engine's reflection system
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(UHealthAttributeSet, Health);

    // Returns the current value of the "Health" Gameplay Attribute
    float GetHealth() const;

    // Sets the "Health" Gameplay Attribute's value to NewVal
    void SetHealth(float NewVal);

    // Initializes the "Health" Gameplay Attribute's value to NewVal
   // GAMEPLAYATTRIBUTE_VALUE_INITTER(Health);

	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(UHealthAttributeSet, HealthMax);
	GAMEPLAYATTRIBUTE_VALUE_GETTER(HealthMax);
	GAMEPLAYATTRIBUTE_VALUE_INITTER(HealthMax);

	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(UHealthAttributeSet, Damage);
	GAMEPLAYATTRIBUTE_VALUE_GETTER(Damage);
	GAMEPLAYATTRIBUTE_VALUE_SETTER(Damage);
	GAMEPLAYATTRIBUTE_VALUE_INITTER(Damage);
};
