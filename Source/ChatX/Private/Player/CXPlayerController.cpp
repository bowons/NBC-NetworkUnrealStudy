// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/CXPlayerController.h"
#include "UI/CXChatInput.h"
#include "Kismet/KismetSystemLibrary.h"
#include "ChatX.h"
#include "EngineUtils.h"
#include "Game/CXGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"
#include "Player/CXPlayerState.h"

ACXPlayerController::ACXPlayerController()
{
    bReplicates = true;
}

void ACXPlayerController::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(ThisClass, NotificationText);
}

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

    if (IsValid(NotificationTextWidgetClass) == true)
    {
        NotificationTextWidgetInstance = CreateWidget<UUserWidget>(this, NotificationTextWidgetClass);
        if (IsValid(NotificationTextWidgetInstance) == true)
        {
            NotificationTextWidgetInstance->AddToViewport();
        }
    }
}

void ACXPlayerController::SetChatMessageString(const FString& InChatMessageString)
{
    ChatMessageString = InChatMessageString;
    
    //PrintChatMessageString(ChatMessageString);
    if (IsLocalController() == true)
    {
        //ServerRPCPrintChatMessageString(InChatMessageString);
        
        ACXPlayerState* CXPS = GetPlayerState<ACXPlayerState>();
        if (IsValid(CXPS) == true)
        {
            //FString CombinedMessageString = CXPS->PlayerNameString + TEXT(": ") + InChatMessageString;
            FString CombinedMessageString = CXPS->GetPlayerInfoString() + TEXT(": ") + InChatMessageString;
            ServerRPCPrintChatMessageString(CombinedMessageString);
        }
    }
}

void ACXPlayerController::PrintChatMessageString(const FString& InChatMessageString) const
{
    ChatXFunctionLibrary::MyPrintString(this, InChatMessageString, 10.f);
}

// RPC 구현부 문법, Implementation을 붙여줘야 한다.
void ACXPlayerController::ClientRPCPrintChatMessageString_Implementation(const FString& InChatMessageString)
{
    PrintChatMessageString(InChatMessageString);
}

void ACXPlayerController::ServerRPCPrintChatMessageString_Implementation(const FString& InChatMessageString)
{
    // for (TActorIterator<ACXPlayerController> It(GetWorld()); It; ++It)
    // {
    //     ACXPlayerController* CXPlayerController = *It;
    //     if (IsValid(CXPlayerController))
    //     {
    //         // 호출부 문법, Implementation이 필요없다. (RPC)
    //         // 여기서 왜 ClientRPCPrintChatMessageString가 Multicast RPC가 아닌 Client RPC 이유?
    //         // -> CXPlayerController->... 와 같이 RPC 호출을 하는데, 다른 컴퓨터에서는 이 Controller 자체가 없기에 RPC를 보내는 것 조차 불가능하다!
    //         CXPlayerController->ClientRPCPrintChatMessageString(InChatMessageString);
    //     }
    // }
    
    AGameModeBase* GM = UGameplayStatics::GetGameMode(this);
    if (IsValid(GM) == true)
    {
        ACXGameModeBase* CXGM = Cast<ACXGameModeBase>(GM);
        if (IsValid(CXGM) == true)
        {
            CXGM->PrintChatMessageString(this, InChatMessageString);
        }
    }
}
