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

	/** Attaches the actor to a FirstPersonCharacter */
	UFUNCTION(BlueprintCallable, Category="Weapon")
	void AttachJetPack(ATP_CustomCharacter* TargetCharacter);
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:

	void Fly();
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
	class UInputAction* FlyAction;
	
protected:
	/** The Character equiped with this*/
	ATP_CustomCharacter* Character;

	UPROPERTY(EditDefaultsOnly)
	float ImpulseForce;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float MaxFuel;

	UPROPERTY(EditDefaultsOnly)
	float StartFuelAmount;

	UPROPERTY(BlueprintReadOnly)
	float RemainingFuel;
	
private:
	
};
