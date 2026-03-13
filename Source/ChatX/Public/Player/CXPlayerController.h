// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CXPlayerController.generated.h"

class UCXChatInput;
/**
 * 
 */
UCLASS()
class CHATX_API ACXPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
    virtual void BeginPlay() override;

    void SetChatMessageString(const FString& InChatMessageString);

    void PrintChatMessageString(const FString& InChatMessageString) const;

protected:
    UPROPERTY(EditDefaultsOnly)
    TSubclassOf<UCXChatInput> ChatInputWidgetClass;

    UPROPERTY()
    TObjectPtr<UCXChatInput> ChatInputWidgetInstance;
	
	UFUNCTION(Client, Reliable)
	void ClientRPCPrintChatMessageString(const FString& InChatMessageString);
	
	UFUNCTION(Server, Reliable)
	void ServerRPCPrintChatMessageString(const FString& InChatMessageString);
	
    FString ChatMessageString;

};
