


#include "TestProjectALSV4/Public/Abilities/TPDamageExecCalculation.h"

#include "TestProjectALSV4/Public/Abilities/TPAbilitySystemComponent.h"
#include "TestProjectALSV4/Public/Abilities/AttributeSets/TPAttributeSetBase.h"

// Declare the attributes to capture and define how we want to capture them from the Source and Target.
struct TPDamageStatics
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(Damage);

	TPDamageStatics()
	{
		// Capture optional Damage set on the damage GE as a CalculationModifier under the ExecutionCalculation
		DEFINE_ATTRIBUTE_CAPTUREDEF(UTPAttributeSetBase, Damage, Source, true);
	}
};

static const TPDamageStatics& DamageStatics()
{
	static TPDamageStatics DStatics;
	return DStatics;
}

void UTPDamageExecCalculation::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
	FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	
	Super::Execute_Implementation(ExecutionParams, OutExecutionOutput);

	UAbilitySystemComponent* TargetAbilitySystemComponent = ExecutionParams.GetTargetAbilitySystemComponent();
	UAbilitySystemComponent* SourceAbilitySystemComponent = ExecutionParams.GetSourceAbilitySystemComponent();

	const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();

	// Gather the tags from the source and target as that can affect which buffs should be used
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;

	float Damage = 0.0f;
	// Capture optional damage value set on the damage GE as a CalculationModifier under the ExecutionCalculation
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().DamageDef, EvaluationParameters, Damage);
	// Add SetByCaller damage if it exists
	Damage += FMath::Max<float>(Spec.GetSetByCallerMagnitude(FGameplayTag::RequestGameplayTag(FName("Data.Damage")), false, -1.0f), 0.0f);

	if (Damage > 0.f)
	{
		// Set the Target's damage meta attribute
		OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(DamageStatics().DamageProperty, EGameplayModOp::Additive, Damage));
	}

	// Broadcast damages to Target ASC
	UTPAbilitySystemComponent* TargetASC = Cast<UTPAbilitySystemComponent>(TargetAbilitySystemComponent);
	if (TargetASC)
	{
		UTPAbilitySystemComponent* SourceASC = Cast<UTPAbilitySystemComponent>(SourceAbilitySystemComponent);
		TargetASC->ReceiveDamage(SourceASC, Damage);
	}

}
