#pragma once

#include "CoreMinimal.h"
#include "Net/Serialization/FastArraySerializer.h"
#include "Inv_FastArray.generated.h"

class UInv_ItemComponent;
class UInv_InventoryComponent;
class UInv_InventoryItem;

/* A single entry in an inventory */
// 元素层，就是单项的增删查改的追踪，两个结构体类型都是 FastArray 的标准用法
USTRUCT(BlueprintType)
struct FInv_InventoryEntry : public FFastArraySerializerItem
{
	GENERATED_BODY()
	
public:

	FInv_InventoryEntry(){};
private:

	friend UInv_InventoryComponent;
	friend struct FInv_InventoryFastArray;
	
	UPROPERTY()
	TObjectPtr<UInv_InventoryItem> Item = nullptr;
};

// 容器层，整个列表怎么做 Delta 同步，对整组元素进行同步
USTRUCT(BlueprintType)
struct FInv_InventoryFastArray : public FFastArraySerializer
{
	GENERATED_BODY()

public:
	FInv_InventoryFastArray(){};
	FInv_InventoryFastArray(UActorComponent* InOwnerComponent) : OwnerComponent(InOwnerComponent){};

	TArray<UInv_InventoryItem*> GetAllItems() const;

	// FFastArraySerializer contract ,处理网络时，有这两个函数会自动调用
	void PreReplicatedRemove(const TArrayView<int32> RemovedIndices, int32 FinalSize);
	void PostReplicatedAdd(const TArrayView<int32> AddedIndices, int32 FinalSize);
	// End of FFastArraySerializer contract

	bool NetDeltaSerialize(FNetDeltaSerializeInfo& DeltaParams)//必写， FastArray 的序列化核心
	{
		return FastArrayDeltaSerialize<FInv_InventoryEntry,	FInv_InventoryFastArray>(Entries,DeltaParams, *this);
	}

	UInv_InventoryItem* AddEntry(UInv_ItemComponent* ItemComponent);
	UInv_InventoryItem* AddEntry(UInv_InventoryItem* Item);
	void RemoveEntry(UInv_InventoryItem* Item);
	
private:

	friend UInv_InventoryComponent;
	
	// Replicated list of items
	UPROPERTY()
	TArray<FInv_InventoryEntry> Entries;

	UPROPERTY(NotReplicated)
	TObjectPtr<UActorComponent> OwnerComponent;
};

template<>
struct TStructOpsTypeTraits<FInv_InventoryFastArray> : public TStructOpsTypeTraitsBase2<FInv_InventoryFastArray>
{
	enum { WithNetDeltaSerializer = true };
};



