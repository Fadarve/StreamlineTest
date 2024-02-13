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

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	//Declare blueprint callable on implementations
	virtual FString GetInteractMessage() = 0;
	//declare Blueprint implementable
	virtual void Interact(ATP_CustomCharacter* character) = 0;
};
