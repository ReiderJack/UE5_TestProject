

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "TPAbilitySystemComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FReceivedDamageDelegate, UTPAbilitySystemComponent*, SourceASC, float, Damage);

/**
 * 
 */
UCLASS()
class TESTPROJECTALSV4_API UTPAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
	
public:
	bool bCharacterAbilitiesGiven = false;
	bool bStartupEffectsApplied = false;

	FReceivedDamageDelegate ReceivedDamage;

	// Called from GDDamageExecCalculation. Broadcasts on ReceivedDamage whenever this ASC receives damage.
	virtual void ReceiveDamage(UTPAbilitySystemComponent* SourceASC, float Damage);
	
};
