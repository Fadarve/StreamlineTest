// Fill out your copyright notice in the Description page of Project Settings.


#include "Gadgets/TP_JetPackComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "StreamlineTest/Public/Character/TP_CustomCharacter.h"

// Sets default values for this component's properties
UTP_JetPackComponent::UTP_JetPackComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	RemainingFuel = StartFuelAmount;
}

void UTP_JetPackComponent::RechargeFuel(float amount)
{
	RemainingFuel+=amount;
	if (RemainingFuel>MaxFuel)
	{
		RemainingFuel = MaxFuel;
	}
}


void UTP_JetPackComponent::AttachJetPack(ATP_CustomCharacter* TargetCharacter)
{
	Character = TargetCharacter;
	if (Character == nullptr)
	{
		return;
	}

	// Attach the jetpack to the First Person Character
	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
	AttachToComponent(Character->GetMesh1P(), AttachmentRules, FName(TEXT("JetPackSocket")));
	
	// switch bHasJetPack
	Character->SetHasJetPack(true);

	// Set up action bindings
	if (APlayerController* PlayerController = Cast<APlayerController>(Character->GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			// Set the priority of the mapping to 1, so that it overrides the Jump action with the Fire action when using touch input
			Subsystem->AddMappingContext(JetPackMappingContext, 1);
		}

		if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerController->InputComponent))
		{
			// Fly
			EnhancedInputComponent->BindAction(FlyAction, ETriggerEvent::Triggered, this, &UTP_JetPackComponent::Fly);
		}
	}
}

// Called when the game starts
void UTP_JetPackComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UTP_JetPackComponent::Fly()
{
	const FString Message = "Flying";

	if(GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1,0.1f,FColor::Cyan,FString::Printf(TEXT("%s"),*Message));
	}
}

