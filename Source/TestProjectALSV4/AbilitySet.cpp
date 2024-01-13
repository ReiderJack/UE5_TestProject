


#include "AbilitySet.h"

#include "AbilitySystemComponent.h"

TArray<FGameplayAbilitySpecHandle> UAbilitySet::GrantAbilitiesToAbilitySystem(
	UAbilitySystemComponent* AbilitySystemComponent) const
{

	check(AbilitySystemComponent);

	TArray<FGameplayAbilitySpecHandle> handles;

	// Go over all defined abilities in data asset
	// and give those abilities directly into the ability system
	// and binding the input ID
	for (const auto abilitySetItem : AbilitySetItems)
	{
		handles.AddUnique(AbilitySystemComponent->GiveAbility(
			FGameplayAbilitySpec(abilitySetItem.GameplayAbility,
				0,
				static_cast<uint32>(abilitySetItem.InputKey)
				)
				));
	}

	return handles;
}
