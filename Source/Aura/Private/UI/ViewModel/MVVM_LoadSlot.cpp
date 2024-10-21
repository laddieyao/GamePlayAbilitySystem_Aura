// Copyright LaddieYao


#include "UI/ViewModel/MVVM_LoadSlot.h"


void UMVVM_LoadSlot::InitializeSlot()
{
	// TODO: Check slot status based on loaded data
	SetWidgetSwitcherIndex.Broadcast(1);
}

void UMVVM_LoadSlot::SetLoadSlotName(const FString& SlotName)
{
	UE_MVVM_SET_PROPERTY_VALUE(LoadSlotName, SlotName);
}
