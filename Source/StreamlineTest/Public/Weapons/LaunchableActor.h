// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interaction/InteractInterface.h"
#include "LaunchableActor.generated.h"

class UTP_GravityGunComponent;

UCLASS()
class STREAMLINETEST_API ALaunchableActor : public AActor, public IInteractInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALaunchableActor();

	//Mesh component, object's root component
	UPROPERTY(Editanywhere,BlueprintReadOnly, Category = "Mesh")
	TObjectPtr<UStaticMeshComponent> MeshComponent;
protected:
	//The message that will be displayed when the object is focused
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString InteractionMessage;

	/*
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FTransform GunHoldTransform;
	*/

	//A reference to the Weapon holding this item
	UPROPERTY(BlueprintReadWrite)
	UTP_GravityGunComponent* HolderComponent;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UTP_GravityGunComponent* GetHolderComponent() const {return HolderComponent;}

	/*
	FTransform GetGunHoldTransform() const { return GunHoldTransform;}
	*/

	//Defined in BPs, used to attach to the weapon disabling physics
	UFUNCTION(BlueprintImplementableEvent)
	void AttachToWeapon(UTP_GravityGunComponent* GravGunComponent);

	//Defined in BPs, used to detach from the weapon enabling physics
	UFUNCTION(BlueprintImplementableEvent)
	void DetachFromGun();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//Returns the interaction message
	UFUNCTION(BlueprintCallable)
	virtual FString GetInteractMessage() override;

	UFUNCTION(BlueprintImplementableEvent)
	void ManageInteraction(ATP_CustomCharacter* character);
	
	//Defined in BPs, custom interaction per object
	virtual void Interact(ATP_CustomCharacter* character) override;

	//Sets the interaction message based on player state
	UFUNCTION(BlueprintImplementableEvent)
	void DecideInteractionMessage();
};
