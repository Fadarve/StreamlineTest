// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/LaunchableActor.h"
#include "NavigationSystemTypes.h"
#include "Components/SphereComponent.h"

// Sets default values
ALaunchableActor::ALaunchableActor()
{
	PrimaryActorTick.bCanEverTick = true;
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	RootComponent = MeshComponent;

	//Start with physics enabled by default
	MeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	MeshComponent->SetEnableGravity(true);
	MeshComponent->SetSimulatePhysics(true);
}

// Called when the game starts or when spawned
void ALaunchableActor::BeginPlay()
{
	Super::BeginPlay();
}

//Called when focused by player
FString ALaunchableActor::GetInteractMessage()
{
	DecideInteractionMessage();
	return InteractionMessage;
}

//Implements the custom interaction for each objet in blueprints
void ALaunchableActor::Interact(ATP_CustomCharacter* character)
{
	ManageInteraction(character);
}

// Called every frame
void ALaunchableActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

