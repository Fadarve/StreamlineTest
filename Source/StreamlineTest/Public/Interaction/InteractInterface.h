// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InteractInterface.generated.h"

class ATP_CustomCharacter;

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInteractInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class STREAMLINETEST_API IInteractInterface
{
	GENERATED_BODY()

	// Objects implementing this interface can be "seen" by the player and implement a custom function for interaction
public:
	virtual FString GetInteractMessage() = 0;
	virtual void Interact(ATP_CustomCharacter* character) = 0;
};
