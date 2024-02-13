// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/TP_CustomCharacter.h"
#include "GameFramework/PlayerController.h"
#include "TP_CustomPC.generated.h"

/**
 * 
 */
UCLASS()
class STREAMLINETEST_API ATP_CustomPC : public APlayerController
{
	GENERATED_BODY()
	
protected:
	
	//Interactible actors reference to manage on screen messages
	IInteractInterface* CurrentIntActor;
	IInteractInterface* LastIntActor;

	//Max interaction distance from camera, determines raycast lenght
	UPROPERTY(EditDefaultsOnly)
	float CameraTraceDistance;

	UPROPERTY(BlueprintReadOnly)
	FString HUDMessage;
	
public:
	ATP_CustomPC();
	
	UFUNCTION(BlueprintImplementableEvent)
	void HideInteractionMessage();
	
	UFUNCTION(BlueprintImplementableEvent)
	void ShowInteractionMessage();

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateHUDMessage();

	IInteractInterface* GetCurrentIntActor() const { return CurrentIntActor;}

protected:
	virtual void Tick(float DeltaSeconds) override;
	
private:
	void CameraTrace();

	virtual void AcknowledgePossession(APawn* P) override;

	ATP_CustomCharacter* Character; 
};
