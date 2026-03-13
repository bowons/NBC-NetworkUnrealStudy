// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/CXGameModeBase.h"

#include "Game/CXGameStateBase.h"

void ACXGameModeBase::OnPostLogin(AController* NewPlayer)
{
	Super::OnPostLogin(NewPlayer);
	
	ACXGameStateBase* CXGameStateBase = GetGameState<ACXGameStateBase>();
	if (IsValid(CXGameStateBase) == true)
	{
		CXGameStateBase->MulticastRPCBroadcastLoginMessage(TEXT("XXXXXX"));
	}
}
