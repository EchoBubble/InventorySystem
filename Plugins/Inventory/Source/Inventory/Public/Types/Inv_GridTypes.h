#pragma once

#include "Inv_GridTypes.generated.h"

class UInv_InventoryItem;

UENUM(BlueprintType)
enum class EInv_ItemCategory : uint8
{
	Equippable,
	Consumable,
	Craftable,
	None
};

/* 该结构体为单个格子的信息*/
USTRUCT()
struct FInv_SlotAvailability
{
	GENERATED_BODY()

	FInv_SlotAvailability(){};
	FInv_SlotAvailability(int32 ItemIndex, int32 Amount, bool bHasItem){Index = ItemIndex; AmountToFill = Amount; bItemAtIndex = bHasItem;};

	int32 Index{INDEX_NONE};//格子索引

	int32 AmountToFill{0};//单个格子能塞多少

	bool bItemAtIndex{false};//原本是否已经存在物品
};

/* 该结构体保存了具体的物品信息、背包空间信息*/
USTRUCT()
struct FInv_SlotAvailabilityResult
{
	GENERATED_BODY()

	FInv_SlotAvailabilityResult(){};

	TWeakPtr<UInv_InventoryItem> Item;

	int32 TotalRoomToFill{0};//当前物品总共能塞多少

	int32 Remainder{0};//剩余的空间

	bool bStackable{false};//是否可堆叠

	TArray<FInv_SlotAvailability> SlotAvailabilities;
};



