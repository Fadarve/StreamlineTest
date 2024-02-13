// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/TP_CustomCharacter.h"

#include "EnhancedInputComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PawnMovementComponent.h"

ATP_CustomCharacter::ATP_CustomCharacter()
{
	CurrentIntActor = LastIntActor = nullptr;
	bHasJectpack = false;
}

void ATP_CustomCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		//Dash
		EnhancedInputComponent->BindAction(DashAction, ETriggerEvent::Triggered, this, &ATP_CustomCharacter::Dash);
		//Interact
		EnhancedInputComponent->BindAction(InteractAction,ETriggerEvent::Triggered,this,&ATP_CustomCharacter::Interact);
	}
}

void ATP_CustomCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	CameraTrace();
}

void ATP_CustomCharacter::CameraTrace()
{
	FHitResult CameraHit;
	const FVector TraceStart = GetFirstPersonCameraComponent()->GetComponentLocation();
	const FVector TraceEnd = TraceStart + (GetFirstPersonCameraComponent()->GetForwardVector()*CameraTraceDistance);
	
	GetWorld()->LineTraceSingleByChannel(CameraHit,TraceStart,TraceEnd,ECC_Visibility);

	LastIntActor = CurrentIntActor;
	CurrentIntActor = Cast<IInteractInterface>(CameraHit.GetActor());
}

void ATP_CustomCharacter::Dash()
{
	if(GetCharacterMovement()->Velocity.Length()>0 && bCanDash && !GetCharacterMovement()->IsFalling())
	{
		//Calculates the dash duration based on distance and velocity and the dash direction
		const float DashTime = DashDistance/DashSpeed;
		const FVector DashDirection = GetCharacterMovement()->Velocity.GetSafeNormal();

		//Dash loop timer
		Delegate.BindUFunction(this,"DashLoop",DashDirection);
		GetWorldTimerManager().SetTimer(DashLoopTimerHandle, Delegate, loopTime,true);
		
		//Finish dash and delay timers
		GetWorldTimerManager().SetTimer(DashEndTimerHandle,this,&ATP_CustomCharacter::OnDashFinished,DashTime,false);
		GetWorldTimerManager().SetTimer(DashDelayTimerHandle, this, &ATP_CustomCharacter::OnDashDelayFinished, DashDelay, false);
		
		bCanDash = false;
	}
}

void ATP_CustomCharacter::OnDashFinished()
{
	GetWorldTimerManager().ClearTimer(DashLoopTimerHandle);
}

void ATP_CustomCharacter::OnDashDelayFinished()
{
	bCanDash = true;
}

void ATP_CustomCharacter::DashLoop(FVector DashDirection) const
{
	GetCharacterMovement()->Velocity = DashSpeed*DashDirection;
}

void ATP_CustomCharacter::Interact()
{
	if(CurrentIntActor == nullptr)
	{
		return;
	}

	CurrentIntActor->Interact(this);
}





