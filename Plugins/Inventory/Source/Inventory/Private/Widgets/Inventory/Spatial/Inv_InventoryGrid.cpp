// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Inventory/Spatial/Inv_InventoryGrid.h"

#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "InventoryManagement/Components/Inv_InventoryComponent.h"
#include "InventoryManagement/Utils/Inv_InventoryStatics.h"
#include "Items/Inv_InventoryItem.h"
#include "Widgets/Inventory/GridSlots/Inv_GridSlot.h"
#include "Widgets/Utils/Inv_WidgetUtils.h"

void UInv_InventoryGrid::NativeConstruct()
{
	Super::NativeConstruct();

	ConstructGrid();

	Rows = 4;
	Columns = 7;
	TileSize = 50;

	InventoryComponent = UInv_InventoryStatics::GetInventoryComponent(GetOwningPlayer());
	InventoryComponent->OnItemAdded.AddDynamic(this, &ThisClass::AddItem);
}

void UInv_InventoryGrid::AddItem(UInv_InventoryItem* Item)
{
	if (!MatchesCategory(Item)) return;

	UE_LOG(LogTemp, Warning, TEXT("InventoryGrid::AddItem"));
}

void UInv_InventoryGrid::ConstructGrid()
{
	GridSlots.Reserve(Rows * Columns);//提前申请好内存大小，等于创建一个空箱子
	for (int32 j = 0; j < Rows; ++j)//先遍历行，因为要从左到右得到每列的 Index，然后在算下一行的
	{
		for (int32 i = 0; i < Columns; ++i)
		{
			UInv_GridSlot* GridSlot = CreateWidget<UInv_GridSlot>(this, GridSlotClass);
			CanvasPanel->AddChildToCanvas(GridSlot);

			FIntPoint Position = FIntPoint(i, j);//j*Columns 可理解为 j 行前面有 j 行放完了，每行有 columns 个格子
			GridSlot->SetTileIndex(UInv_WidgetUtils::GetIndexFromPosition(Position, Columns));

			UCanvasPanelSlot* CanvasSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot(GridSlot);
			CanvasSlot->SetSize(FVector2D(TileSize));
			CanvasSlot->SetPosition(Position * TileSize);

			GridSlots.Add(GridSlot);
		}
	}
}

bool UInv_InventoryGrid::MatchesCategory(const UInv_InventoryItem* Item) const
{
	return Item->GetItemManifest().GetItemCategory() == ItemCategory;
}
