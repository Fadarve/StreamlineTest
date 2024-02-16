// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/TP_CustomPC.h"
#include "Camera/CameraComponent.h"

//Save a reference to the character on possession
void ATP_CustomPC::AcknowledgePossession(APawn* P)
{
	Super::AcknowledgePossession(P);

	if(ATP_CustomCharacter* CustomChar = Cast<ATP_CustomCharacter>(P))
	{
		Character = CustomChar;
		Character->SetPC(this);
	}
}

ATP_CustomPC::ATP_CustomPC()
{
	CurrentIntActor = LastIntActor = nullptr;
}

void ATP_CustomPC::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	CameraTrace();
}

//Traces a Raycast to look for interactive objects in sight
void ATP_CustomPC::CameraTrace()
{
	FHitResult CameraHit;
	
	const FVector TraceStart = Character->GetFirstPersonCameraComponent()->GetComponentLocation();
	const FVector TraceEnd = TraceStart + (Character->GetFirstPersonCameraComponent()->GetForwardVector()*CameraTraceDistance);
	
	GetWorld()->LineTraceSingleByChannel(CameraHit,TraceStart,TraceEnd,ECC_Visibility);

	LastIntActor = CurrentIntActor;
	CurrentIntActor = Cast<IInteractInterface>(CameraHit.GetActor());

	// --- Interaction Messages ----------

	/*
	 * Cases:
	 *	A. Last and Current null
	 *		Nothing
	 *	B. Last is null and current is valid
	 *		Show current message
	 *	C. Last is valid and current is null
	 *		Hide message
	 *	D. Both are valid and have the same value
	 *		Nothing
	 *	E. Both are valid but different values
	 *		Change message value
	 */
	
	if(LastIntActor == nullptr)
	{
		if(CurrentIntActor != nullptr)
		{
			//Case B
			HUDMessage = CurrentIntActor->GetInteractMessage();
			UpdateHUDMessage();
			ShowInteractionMessage();
		}
	}else
	{
		if(CurrentIntActor == nullptr)
		{
			//Case C
			HideInteractionMessage();
		}
		else
		{
			if(CurrentIntActor != LastIntActor)
			{
				//Case E
				HUDMessage = CurrentIntActor->GetInteractMessage();
				UpdateHUDMessage();
			}
		}
	}
}


