// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StructUtils/InstancedStruct.h"
#include "UObject/Object.h"
#include "Items/Manifest/Inv_ItemManifest.h"
#include "Inv_InventoryItem.generated.h"

/**
 *  这个类，是一个实例身份，具体定义应该是 Manifest 结构体中，会被网络同步
 */
UCLASS()
class INVENTORY_API UInv_InventoryItem : public UObject
{
	GENERATED_BODY()

public:
	
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	// 必须：让这个UObject允许走网络复制（作为 Replicated Subobject）。
	// 不加的话：Dedicated/远端客户端收不到这个 InventoryItem 的数据/字段。
	virtual bool IsSupportedForNetworking() const override { return true;};

	void SetItemManifest(const FInv_ItemManifest& Manifest);
	const FInv_ItemManifest& GetItemManifest() const { return ItemManifest.Get<FInv_ItemManifest>(); }//只读
	FInv_ItemManifest& GetItemManifestMutable() { return ItemManifest.GetMutable<FInv_ItemManifest>(); }//可改

private:

	UPROPERTY(VisibleAnywhere, meta = (BaseStruct = "/Script/Inventory.Inv_ItemManifest"), Replicated)//该路径指，在这个模块中有这个结构体
	FInstancedStruct ItemManifest;//可多态、可派生，因为是个插件，所以需要指认模块地址
};
