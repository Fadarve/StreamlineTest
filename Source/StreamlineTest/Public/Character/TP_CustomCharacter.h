// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interaction/InteractInterface.h"
#include "StreamlineTest/StreamlineTestCharacter.h"
#include "Weapons/LaunchableActor.h"
#include "Interaction/InteractInterface.h"
#include "TP_CustomCharacter.generated.h"

class UInputAction;
/**
 * 
 */
UCLASS()
class STREAMLINETEST_API ATP_CustomCharacter : public AStreamlineTestCharacter
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input)
	UInputAction* DashAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* InteractAction;
protected:
	//Timer handles to manage events' delays
	FTimerHandle DashEndTimerHandle;
	FTimerHandle DashLoopTimerHandle;
	FTimerHandle DashDelayTimerHandle;
	FTimerDelegate Delegate;

	//Determines whether the player can dash or not
	bool bCanDash = true;

	//Time span to call DashLoop
	float loopTime = 0.02f;
	
	UPROPERTY(EditAnywhere, Category = Dash)
	float DashDistance;
	
	UPROPERTY(EditAnywhere, Category = Dash)
	float DashSpeed;

	//Dash cooldown time
	UPROPERTY(EditAnywhere, Category = Dash)
	float DashDelay;

	//Interactible actors reference to manage on screen messages
	IInteractInterface* CurrentIntActor;
	IInteractInterface* LastIntActor;

	//Max interaction distance from camera, determines raycast lenght
	UPROPERTY(EditDefaultsOnly)
	float CameraTraceDistance;
	
private:
	bool bHasJectpack;
public:
	//Constructor
	ATP_CustomCharacter();

	bool GetHasJetPack() const {return bHasJectpack;}

	void SetHasJetPack(bool value) {bHasJectpack = value; }
	
	IInteractInterface* GetCurrentIntActor() const { return CurrentIntActor;}
	
protected:
	//Overriden function to add the dash input action
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	//Tick override used to check for interactible actors
	virtual void Tick(float DeltaSeconds) override;

	//Dash input action bind function
	void Dash();

	//Called once dash finished
	void OnDashFinished();

	//Called once dash delay finished
	void OnDashDelayFinished();

	//Called once every 'loopTime' seconds to set the CharacterMovement velocity
	UFUNCTION()
	void DashLoop(FVector DashDir) const;
	
	void Interact();

private:
	//Creates a raycast and check for interactible actors
	void CameraTrace();
};
