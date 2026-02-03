// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Inv_PlayerController.generated.h"

/**
 * 
 */

class UInv_InventoryComponent;
class UInv_HUDWidget;
class UInputAction;
class UInputMappingContext;

UCLASS(PrioritizeCategories=("Inventory"))
class INVENTORY_API AInv_PlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	AInv_PlayerController();
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category="Inventory")
	void ToggleInventory();
protected:
	virtual void BeginPlay() override;

	virtual void SetupInputComponent() override;
private:
	void PrimaryInteract();//拾取按键回调函数
	void CreateHUDWidget();
	void TraceForItem();

	TWeakObjectPtr<UInv_InventoryComponent> InventoryComponent;//对蓝图组件的弱引用
	
	UPROPERTY(EditDefaultsOnly, Category = "Inventory")
	TArray<TObjectPtr<UInputMappingContext>> DefaultIMCs;

	UPROPERTY(EditDefaultsOnly, Category = "Inventory")
	TObjectPtr<UInputAction> PrimaryInteractAction;

	UPROPERTY(EditDefaultsOnly, Category = "Inventory")
	TObjectPtr<UInputAction> ToggleInventoryAction;

	UPROPERTY(EditDefaultsOnly, Category = "Inventory")
	TSubclassOf<UInv_HUDWidget> HUDWidgetClass;

	UPROPERTY()
	TObjectPtr<UInv_HUDWidget> HUDWidget;

	UPROPERTY(EditDefaultsOnly, Category = "Inventory")
	double TraceLength;

	UPROPERTY(EditDefaultsOnly, Category = "Inventory")
	TEnumAsByte<ECollisionChannel> ItemTraceChannel;//自定义检测通道，这里必须用 TEnumAsByte ，不然无法使用 UPROPERTY

	TWeakObjectPtr<AActor> LastActor;
	TWeakObjectPtr<AActor> ThisActor;
};
