// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LaunchableActor.h"
#include "StreamlineTest/TP_WeaponComponent.h"
#include "TP_GravityGunComponent.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class STREAMLINETEST_API UTP_GravityGunComponent : public UTP_WeaponComponent
{
	GENERATED_BODY()


public:
	UTP_GravityGunComponent();
	
	//AttachWeapon override
	void AttachWeapon(ATP_CustomCharacter* TargetCharacter) override;

	//Fires the Launchable Object
	void Fire() override;

	//Pick or Drop a picked LaunchableObject
	void PickDrop();
	
private:
	//Determines the relative location to be placed
	void CalculateHoldLocation();
	
public:
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputMappingContext* GravityMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* PickDropAction;

	//Attach to weapon location
	UPROPERTY(BlueprintReadOnly)
	FVector HoldLocation;

private:
	bool bIsHoldingItem;

	//A reference to the current item being held
	ALaunchableActor* HoldingItem;
	
	UPROPERTY(EditDefaultsOnly, Category = "Shooting")
	float ShootForce;

	//The distance from the camera the object will be placed when picked up
	UPROPERTY(EditDefaultsOnly, Category = "Shooting")
	float HoldDistance;
};
