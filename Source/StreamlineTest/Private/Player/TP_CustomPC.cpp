// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/TP_CustomPC.h"
#include "Camera/CameraComponent.h"

//Save a reference to the character on possesion
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

void ATP_CustomPC::CameraTrace()
{
	FHitResult CameraHit;
	
	const FVector TraceStart = Character->GetFirstPersonCameraComponent()->GetComponentLocation();
	const FVector TraceEnd = TraceStart + (Character->GetFirstPersonCameraComponent()->GetForwardVector()*CameraTraceDistance);
	
	GetWorld()->LineTraceSingleByChannel(CameraHit,TraceStart,TraceEnd,ECC_Visibility);

	LastIntActor = CurrentIntActor;
	CurrentIntActor = Cast<IInteractInterface>(CameraHit.GetActor());

	// --- Interacton Messages / Optional, final ----------

	/*
	 * Casos:
	 *	A. Last y Current Nulos
	 *		Nada
	 *	B. Last es null y current es valido
	 *		Resaltar a Current
	 *		Mostrar mensaje de current
	 *	C. Last es valido y current es null
	 *		Quitar resaltado a Last
	 *		Ocultar mensaje
	 *	D. Ambos validos y mismo valor
	 *		Nada
	 *	E. Ambos validos pero dif valor
	 *		Quitar resaltado a Last y resaltar current
	 *		Cambiar valor de mensaje
	 */

	
	
	if(LastIntActor == nullptr)
	{
		if(CurrentIntActor != nullptr)
		{
			//Caso B
			HUDMessage = CurrentIntActor->GetInteractMessage();
			UpdateHUDMessage();
			ShowInteractionMessage();
		}
	}else
	{
		if(CurrentIntActor == nullptr)
		{
			//Caso C
			HideInteractionMessage();
		}
		else
		{
			if(CurrentIntActor != LastIntActor)
			{
				//Caso E
				HUDMessage = CurrentIntActor->GetInteractMessage();
				UpdateHUDMessage();
			}
		}
	}
}


