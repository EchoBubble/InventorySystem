// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Inv_HUDWidget.generated.h"

/**
 * 
 */
UCLASS()
class INVENTORY_API UInv_HUDWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	// 搭配 Inv_ItemComponent 使用，蓝图中显示和关闭 UI 消息
	UFUNCTION(BlueprintImplementableEvent)
	void ShowPickupMessage(const FString& Message);
	
	UFUNCTION(BlueprintImplementableEvent)
	void HidePickupMessage();
};
