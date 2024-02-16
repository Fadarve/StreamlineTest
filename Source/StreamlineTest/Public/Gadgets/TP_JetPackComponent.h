// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "TP_JetPackComponent.generated.h"

UDELEGATE(BlueprintCallable)
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEngineOnOff);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class STREAMLINETEST_API UTP_JetPackComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTP_JetPackComponent();

	//Adds fuel/batterie to the jetpack
	UFUNCTION(BlueprintCallable)
	void RechargeFuel(float amount);

	/** Attaches the actor to a FirstPersonCharacter */
	UFUNCTION(BlueprintCallable, Category="Weapon")
	void AttachJetPack(ATP_CustomCharacter* TargetCharacter);

	UPROPERTY(BlueprintAssignable)
	FOnEngineOnOff OnEngineOn;
	
	UPROPERTY(BlueprintAssignable)
	FOnEngineOnOff OnEngineOff;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
private:
	//Tick enabling/disabling
	
	void ActivateJP();

	UFUNCTION(BlueprintCallable)
	void DeActivateJP();

	//Turns on/off the jetpack
	void StartEngine();

	void StopEngine();
	
public:	
	/** Sound to play when activated */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
	USoundBase* ActiveSound;

	/** Sound to play when no fuel left */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
	USoundBase* NoFuelSound;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputMappingContext* JetPackMappingContext;

	/** Fly Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* StartJetPAckAction;

	/** Propel Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* PropelAction;
	
protected:
	/** The Character equiped with this*/
	ATP_CustomCharacter* Character;

	//----------------Movement / Force -----------------
	UPROPERTY(EditDefaultsOnly)
	float ImpulseForce;

	UPROPERTY(EditDefaultsOnly)
	float ForceMultiplier;

	UPROPERTY(EditDefaultsOnly)
	float JetPackAirControl;

	float FallingAirControl = 0.05f;

	UPROPERTY(EditDefaultsOnly)
	float MaxForce;

	bool bShouldAddForce;

	//-------------fuel----------------------------
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float MaxFuel;

	UPROPERTY(EditAnywhere)
	float StartFuelAmount;

	UPROPERTY(BlueprintReadOnly)
	float RemainingFuel;

	UPROPERTY(EditDefaultsOnly)
	float FuelUsedByTick;
	
private:
	//tells whether or not the jetpack should add a force to the player when pressing space
	bool bIsActive;
};
