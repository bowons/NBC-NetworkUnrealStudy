// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/CXPawn.h"

#include "ChatX.h"


// Called when the game starts or when spawned
void ACXPawn::BeginPlay()
{
	Super::BeginPlay();
	
	FString NetRoleString = ChatXFunctionLibrary::GetRoleString(this);
	FString CombinedString  = FString::Printf(TEXT("CXPawn::BeginPlay() %s [%s]"), 
								*ChatXFunctionLibrary::GetNetModeString(this), *NetRoleString);
	ChatXFunctionLibrary::MyPrintString(this, CombinedString, 10.f);
}

void ACXPawn::PossessedBy(AController* NetController)
{
	Super::PossessedBy(NetController);
	
	FString NetRoleString = ChatXFunctionLibrary::GetRoleString(this);
	FString CombinedString  = FString::Printf(TEXT("CXPawn::PossessedBy() %s [%s]"), 
								*ChatXFunctionLibrary::GetNetModeString(this), *NetRoleString);
	ChatXFunctionLibrary::MyPrintString(this, CombinedString, 10.f);
}
