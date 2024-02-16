// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "TP_CustomPlayerState.generated.h"

class UTP_JetPackComponent;
class UTP_WeaponComponent;
class UTP_GravityGunComponent;

/**
 * 
 */
UDELEGATE(BlueprintCallable)
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHasJetPackChanged,bool,value,UTP_JetPackComponent*,Jetpack);

UCLASS()
class STREAMLINETEST_API ATP_CustomPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	ATP_CustomPlayerState();

	//Variables to check the state of the player anywhere
	bool GetHasRifle() const {return bHasRifle;}

	bool GetHasGravGun() const {return bHasGravGun;}

	bool GetHasJetPack() const {return bHasJetPack;}

	void SetHasRifle(bool value){ bHasRifle = value;}

	void SetHasGravGun(bool value){ bHasGravGun = value;}

	void SetHasJetPack(bool value, UTP_JetPackComponent* Jetpack);

	UPROPERTY(BlueprintAssignable)
	FOnHasJetPackChanged OnPickDropJetPack;

	UPROPERTY(BlueprintReadOnly)
	UTP_JetPackComponent* JetPackRef;

protected:
	UPROPERTY(BlueprintReadOnly)
	bool bHasRifle;
	
	UPROPERTY(BlueprintReadOnly)
	bool bHasGravGun;
	
	UPROPERTY(BlueprintReadOnly)
	bool bHasJetPack;

	
};
