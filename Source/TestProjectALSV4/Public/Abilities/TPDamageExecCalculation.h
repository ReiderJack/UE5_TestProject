

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "TPDamageExecCalculation.generated.h"


UCLASS()
class TESTPROJECTALSV4_API UTPDamageExecCalculation : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()
		
public:
	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;

};
