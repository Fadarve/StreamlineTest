// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interaction/InteractInterface.h"
#include "StreamlineTest/StreamlineTestCharacter.h"
#include "Weapons/LaunchableActor.h"
#include "Interaction/InteractInterface.h"
#include "TP_CustomCharacter.generated.h"

class UInputAction;
class ATP_CustomPC;
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

private:
	bool bHasJectpack;

	ATP_CustomPC* PC;
public:
	//Constructor
	ATP_CustomCharacter();

	bool GetHasJetPack() const {return bHasJectpack;}

	void SetHasJetPack(bool value) {bHasJectpack = value; }

	ATP_CustomPC* GetPC() const {return PC;}
	void SetPC(ATP_CustomPC* PcRef) {PC = PcRef;}
	
protected:
	//Overriden function to add the dash input action
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

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
};
