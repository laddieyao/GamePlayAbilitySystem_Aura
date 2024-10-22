// Copyright LaddieYao

#pragma once

#include "CoreMinimal.h"
#include "MVVMViewModelBase.h"
#include "Game/LoadScreenSaveGame.h"
#include "Templates/SubclassOf.h"
#include "MVVM_LoadSlot.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSetWidgetSwitcherIndex, int32, widgetSwithcerIndex);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FEnableSelectSlotButton, bool, bEnable);

/**
 * 
 */
UCLASS()
class AURA_API UMVVM_LoadSlot : public UMVVMViewModelBase
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable)
	FSetWidgetSwitcherIndex SetWidgetSwitcherIndex;

	UPROPERTY(BlueprintAssignable)
	FEnableSelectSlotButton EnableSelectSlotButton;

	void InitializeSlot();
	
	UPROPERTY()
	int32 SlotIndex;

	UPROPERTY()
	TEnumAsByte<ESaveSlotStatus> SlotStatus;

	/** Field Notifies */
	
	void SetLoadSlotName(const FString& SlotName);
	void SetPlayerName(const FString& InPlayerName);
	void SetMapName(const FString& InMapName);
	
	FString GetLoadSlotName() const { return LoadSlotName; };
	FString GetPlayerName() const { return PlayerName; }
	FString GetMapName() const { return MapName; }

private:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, FieldNotify, Setter, Getter, meta = (AllowPrivateAccess="true"))
	FString PlayerName;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, FieldNotify, Setter, Getter, meta = (AllowPrivateAccess="true"))
	FString LoadSlotName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, FieldNotify, Setter, Getter, meta = (AllowPrivateAccess="true"))
	FString MapName;
	
};
