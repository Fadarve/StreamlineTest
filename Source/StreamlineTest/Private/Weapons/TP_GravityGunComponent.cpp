// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/TP_GravityGunComponent.h"
#include "StreamlineTest/Public/Character/TP_CustomCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "Player/TP_CustomPC.h"

UTP_GravityGunComponent::UTP_GravityGunComponent()
{
	bIsHoldingItem = false;
}

void UTP_GravityGunComponent::AttachWeapon(ATP_CustomCharacter* TargetCharacter)
{
	Character = TargetCharacter;
	if (Character == nullptr)
	{
		return;
	}

	// Attach the weapon to the First Person Character
	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true);
	AttachToComponent(Character->GetMesh1P(), AttachmentRules, FName(TEXT("GripPoint")));
	
	// switch bHasRifle so the animation blueprint can switch to another animation set
	Character->SetHasRifle(true);

	// Set up action bindings
	if (APlayerController* PlayerController = Cast<APlayerController>(Character->GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			// Set the priority of the mapping to 1, so that it overrides the Jump action with the Fire action when using touch input
			Subsystem->AddMappingContext(GravityMappingContext, 1);
		}

		if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerController->InputComponent))
		{
			//PickDrop
			EnhancedInputComponent->BindAction(PickDropAction,ETriggerEvent::Triggered, this, &UTP_GravityGunComponent::PickDrop);
			
			// Fire
			EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Triggered, this, &UTP_WeaponComponent::Fire);
		}
	}
}

//Launches the object being held
void UTP_GravityGunComponent::Fire()
{
	if(bIsHoldingItem)
	{
		const FVector ShootDirection = Character->GetFirstPersonCameraComponent()->GetForwardVector();
		HoldingItem->DetachFromGun();
		HoldingItem->MeshComponent->AddImpulse(ShootDirection*ShootForce);
	}
}

//Picks up or drops a Launchable Object
void UTP_GravityGunComponent::PickDrop()
{
	if(!bIsHoldingItem)
	{
		//PickUp if Launchable
		if(ALaunchableActor* LaunchActor = Cast<ALaunchableActor>(Character->GetPC()->GetCurrentIntActor()))
		{
			CalculateHoldLocation();
			LaunchActor->AttachToWeapon(this);
			bIsHoldingItem = true;
			HoldingItem = LaunchActor;
		}
	}else
	{
		//Drop the item if is holding one
		HoldingItem->DetachFromGun();
		bIsHoldingItem = false;
		HoldingItem = nullptr;
	}
}

void UTP_GravityGunComponent::CalculateHoldLocation()
{
	const FVector View = Character->GetFirstPersonCameraComponent()->GetForwardVector().GetSafeNormal()*HoldDistance;
	const FVector CameraGun = GetComponentLocation()-Character->GetFirstPersonCameraComponent()->GetComponentLocation();
	HoldLocation = View - CameraGun;
}
