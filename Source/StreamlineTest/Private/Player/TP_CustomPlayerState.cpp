// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/TP_CustomPlayerState.h"

ATP_CustomPlayerState::ATP_CustomPlayerState()
{
	SetScore(0.0f);
	bHasRifle = false;
	bHasGravGun = false;
	bHasJetPack = false;
}

void ATP_CustomPlayerState::SetHasJetPack(bool value, UTP_JetPackComponent* Jetpack)
{
	bHasJetPack = value;
	JetPackRef = Jetpack;
	OnPickDropJetPack.Broadcast(value,Jetpack);
}
