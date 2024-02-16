// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/TP_CustomCharacter.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Player/TP_CustomPC.h"

ATP_CustomCharacter::ATP_CustomCharacter()
{
	//CurrentIntActor = LastIntActor = nullptr;
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

//Stops the loop of the DashLoop method
void ATP_CustomCharacter::OnDashFinished()
{
	GetWorldTimerManager().ClearTimer(DashLoopTimerHandle);
}

//Set bCanDash en true after de cooldown time so the player can dash again
void ATP_CustomCharacter::OnDashDelayFinished()
{
	bCanDash = true;
}

//Sets the velocity on a fixed direction and value
void ATP_CustomCharacter::DashLoop(FVector DashDirection) const
{
	GetCharacterMovement()->Velocity = DashSpeed*DashDirection;
}

//Calls the interaction action of the current interactible actor in sight 
void ATP_CustomCharacter::Interact()
{
	if(PC->GetCurrentIntActor() != nullptr)
	{
		PC->GetCurrentIntActor()->Interact(this);
	}
}






