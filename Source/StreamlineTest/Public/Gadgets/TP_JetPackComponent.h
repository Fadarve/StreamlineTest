// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "TP_JetPackComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class STREAMLINETEST_API UTP_JetPackComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTP_JetPackComponent();

	UFUNCTION(BlueprintCallable)
	void RechargeFuel(float amount);

	UFUNCTION(BlueprintCallable)
	void SetStartFuelAmount(float fuel){StartFuelAmount = fuel;}

	/** Attaches the actor to a FirstPersonCharacter */
	UFUNCTION(BlueprintCallable, Category="Weapon")
	void AttachJetPack(ATP_CustomCharacter* TargetCharacter);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
private:
	
	void ActivateJP();

	void StartEngine();

	void StopEngine();

	UFUNCTION(BlueprintCallable)
	void DeActivateJP();
public:	

	/** Sound to when activated */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
	USoundBase* ActiveSound;

	/** Sound to when no fuel left */
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
	bool bIsActive;
};
