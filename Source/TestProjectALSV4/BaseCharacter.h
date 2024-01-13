

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "HealthAttributeSet.h"
#include "AbilitySet.h"
#include "BaseCharacter.generated.h"

USTRUCT()
struct FAbilityInputToInputActionBinding
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	UInputAction* InputAction;

	UPROPERTY(EditDefaultsOnly)
	EAbilityInput AbilityInput;
};

// The bridge between enhanced input system
// and gameplay ability input
USTRUCT()
struct FAbilityInputBindings
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category="Input")
	TArray<FAbilityInputToInputActionBinding> Bindings;
	
};

UCLASS()
class TESTPROJECTALSV4_API ABaseCharacter : public ACharacter, public IAbilitySystemInterface
{
private:
	GENERATED_BODY()
	
public:
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override { return AbilitySystemComponent; }
	
	// Sets default values for this character's properties
	ABaseCharacter();

protected:
	
	UPROPERTY(VisibleAnywhere, Category="Abilitites")
	UAbilitySystemComponent* AbilitySystemComponent { nullptr };

	UPROPERTY(VisibleAnywhere, Category="Abilitites")
	UHealthAttributeSet* HealthAttributes { nullptr };

	UPROPERTY(EditDefaultsOnly, Category="Abilities")
	UAbilitySet* InitialAbilitySet { nullptr };
	
	UPROPERTY(EditDefaultsOnly, Category="Abilities")
	TSubclassOf<UGameplayEffect> InitialGameplayEffect;

	UPROPERTY(EditDefaultsOnly, Category="Input|Binding")
	FAbilityInputBindings AbilityInputBindings;

	// Begin Input Bindings
	void AbilityInputBindingPressedHandler(EAbilityInput abilityInput);
	void AbilityInputBindingReleasedHandler(EAbilityInput abilityInput);
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	UPROPERTY(Transient)
	TArray<FGameplayAbilitySpecHandle> InitialliGrantedAbilitySpecHandles;

};
