// Fill out your copyright notice in the Description page of Project Settings.


#include "Gadgets/TP_JetPackComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player/TP_CustomPlayerState.h"
#include "StreamlineTest/Public/Character/TP_CustomCharacter.h"
#include "StreamlineTest/Public/Weapons/LaunchableActor.h"

// Sets default values for this component's properties
UTP_JetPackComponent::UTP_JetPackComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	bIsActive = false;
	RechargeFuel(StartFuelAmount);
}

void UTP_JetPackComponent::BeginPlay()
{
	Super::BeginPlay();
	SetComponentTickEnabled(false);
	bShouldAddForce = false;
}

void UTP_JetPackComponent::TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	if(bShouldAddForce && RemainingFuel>0.0f)
	{
		const float appliedForce = ImpulseForce*ForceMultiplier*DeltaTime*DeltaTime;
		
		//Avoid the player to keep accelerating beyond the max speed limit
		if(appliedForce>MaxForce)
		{
			Character->GetCharacterMovement()->AddForce(MaxForce*FVector::UpVector);
		}else
		{
			Character->GetCharacterMovement()->AddForce(appliedForce*FVector::UpVector);
		}
		RemainingFuel-=FuelUsedByTick;
	}
}


void UTP_JetPackComponent::RechargeFuel(float amount)
{
	RemainingFuel+=amount;
	if (RemainingFuel>MaxFuel)
	{
		RemainingFuel = MaxFuel;
	}
}

//Called from the manage interaction method in Launchable actor
void UTP_JetPackComponent::AttachJetPack(ATP_CustomCharacter* TargetCharacter)
{
	Character = TargetCharacter;
	if (Character == nullptr)
	{
		return;
	}
	
	//Disable physics before attachment
	if(ALaunchableActor* owner = Cast<ALaunchableActor>(GetOwner()))
	{
		owner->MeshComponent->SetSimulatePhysics(false);
		owner->MeshComponent->SetEnableGravity(false);
		owner->MeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
	
	// Attach the jetpack to the First Person Character
	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
	GetOwner()->AttachToComponent(Character->GetMesh1P(), AttachmentRules,FName(TEXT("JetPackSocket")));
	
	// switch bHasJetPack
	if (ATP_CustomPlayerState* PlayerState = Cast<ATP_CustomPlayerState>(Character->GetPlayerState()))
	{
		PlayerState->SetHasJetPack(true,this);
	}

	// Set up action bindings
	if (APlayerController* PlayerController = Cast<APlayerController>(Character->GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			
			Subsystem->AddMappingContext(JetPackMappingContext, 1);
		}

		if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerController->InputComponent))
		{
			// Start flying mode, called when the player press space after jumping
			EnhancedInputComponent->BindAction(StartJetPAckAction, ETriggerEvent::Triggered, this, &UTP_JetPackComponent::ActivateJP);

			//Add force once on air
			EnhancedInputComponent->BindAction(PropelAction, ETriggerEvent::Triggered,this, &UTP_JetPackComponent::StartEngine);
			
			//Stop adding force when button released
			EnhancedInputComponent->BindAction(PropelAction, ETriggerEvent::Completed,this, &UTP_JetPackComponent::StopEngine);
		}
	}
}

void UTP_JetPackComponent::ActivateJP() 
{
	bIsActive = true;
	SetComponentTickEnabled(true);
}

//Sets bShouldAddForce on true so the Tick method can add a force when pressing space
void UTP_JetPackComponent::StartEngine()
{
	if(Character->GetCharacterMovement()->IsFalling() && bIsActive)
	{
		if (RemainingFuel>0.0f)
		{
			const FString Message = "Activated";

			if(GEngine)
			{
				GEngine->AddOnScreenDebugMessage(-1,1.0f,FColor::Cyan,FString::Printf(TEXT("%s"),*Message));
			}
			
			bShouldAddForce = true;
			Character->GetCharacterMovement()->AirControl = JetPackAirControl;
			OnEngineOn.Broadcast();
		}
	}
}

//Stop adding force to the player when the space key is released
void UTP_JetPackComponent::StopEngine()
{
	bShouldAddForce = false;
	Character->GetCharacterMovement()->AirControl = FallingAirControl;
	OnEngineOff.Broadcast();
}

//Turns off the jetpack so the player can jump on ground normally without activating it
void UTP_JetPackComponent::DeActivateJP()
{
	bIsActive = false;
	bShouldAddForce = false;
	Character->GetCharacterMovement()->AirControl = FallingAirControl;
}

