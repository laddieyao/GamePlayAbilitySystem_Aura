// Copyright LaddieYao


#include "UI/ViewModel/MVVM_LoadSlot.h"


void UMVVM_LoadSlot::InitializeSlot()
{
	// TODO: Check slot status based on loaded data
	const int32 WidgetSwitcherIndex = SlotStatus.GetValue();
	SetWidgetSwitcherIndex.Broadcast((WidgetSwitcherIndex));
}

void UMVVM_LoadSlot::SetLoadSlotName(const FString& SlotName)
{
	UE_MVVM_SET_PROPERTY_VALUE(LoadSlotName, SlotName);
}

void UMVVM_LoadSlot::SetMapName(const FString& InMapName)
{
	UE_MVVM_SET_PROPERTY_VALUE(MapName, InMapName);
}

void UMVVM_LoadSlot::SetPlayerName(const FString& InPlayerName)
{
	UE_MVVM_SET_PROPERTY_VALUE(PlayerName, InPlayerName);
}


