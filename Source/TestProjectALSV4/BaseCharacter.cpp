


#include "BaseCharacter.h"


// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	HealthAttributes = CreateDefaultSubobject<UHealthAttributeSet>(TEXT("HealthAttributeSet"));

}

void ABaseCharacter::AbilityInputBindingPressedHandler(EAbilityInput abilityInput)
{
	AbilitySystemComponent->AbilityLocalInputPressed(static_cast<uint8>(abilityInput));
}

void ABaseCharacter::AbilityInputBindingReleasedHandler(EAbilityInput abilityInput)
{
	AbilitySystemComponent->AbilityLocalInputReleased(static_cast<uint8>(abilityInput));
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	if(IsValid(InitialAbilitySet))
	{
		InitialliGrantedAbilitySpecHandles.Append(InitialAbilitySet->GrantAbilitiesToAbilitySystem(AbilitySystemComponent));
	}

	if(IsValid(InitialGameplayEffect))
	{
		AbilitySystemComponent->ApplyGameplayEffectToSelf(InitialGameplayEffect->GetDefaultObject<UGameplayEffect>(), 0.f, AbilitySystemComponent->MakeEffectContext());
	}
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if(UEnhancedInputComponent* playerEnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		for(const FAbilityInputToInputActionBinding& binding : AbilityInputBindings.Bindings)
		{
			playerEnhancedInputComponent->BindAction(binding.InputAction, ETriggerEvent::Triggered, this, &ThisClass::AbilityInputBindingPressedHandler, binding.AbilityInput);
			playerEnhancedInputComponent->BindAction(binding.InputAction, ETriggerEvent::Completed, this, &ThisClass::AbilityInputBindingReleasedHandler, binding.AbilityInput);
		}
	}
}

