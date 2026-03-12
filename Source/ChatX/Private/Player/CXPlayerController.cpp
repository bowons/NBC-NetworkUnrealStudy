// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/CXPlayerController.h"
#include "UI/CXChatInput.h"
#include "Kismet/KismetSystemLibrary.h"
#include "ChatX.h"

void ACXPlayerController::BeginPlay()
{
    Super::BeginPlay();
    
    if (IsLocalController() == false)
    {
        return;
    }

    FInputModeUIOnly InputModeUIOnly;
    SetInputMode(InputModeUIOnly);

    if (IsValid(ChatInputWidgetClass) == true)
    {
        ChatInputWidgetInstance = CreateWidget<UCXChatInput>(this, ChatInputWidgetClass);
        if (IsValid(ChatInputWidgetInstance) == true)
        {
            ChatInputWidgetInstance->AddToViewport();
        }
    }

}

void ACXPlayerController::SetChatMessageString(const FString& InChatMessageString)
{
    ChatMessageString = InChatMessageString;
    PrintChatMessageString(ChatMessageString);
}

void ACXPlayerController::PrintChatMessageString(const FString& InChatMessageString) const
{
    ChatXFunctionLibrary::MyPrintString(this, InChatMessageString, 10.f);
}
