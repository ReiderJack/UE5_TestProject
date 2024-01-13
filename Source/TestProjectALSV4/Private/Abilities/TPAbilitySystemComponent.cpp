


#include "Abilities/TPAbilitySystemComponent.h"

void UTPAbilitySystemComponent::ReceiveDamage(UTPAbilitySystemComponent * SourceASC, float Damage)
{
	ReceivedDamage.Broadcast(SourceASC, Damage);
}