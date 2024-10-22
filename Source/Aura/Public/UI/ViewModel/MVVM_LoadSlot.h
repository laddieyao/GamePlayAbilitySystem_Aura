// Copyright LaddieYao

#pragma once

#include "CoreMinimal.h"
#include "MVVMViewModelBase.h"
#include "Templates/SubclassOf.h"
#include "MVVM_LoadSlot.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSetWidgetSwitcherIndex, int32, widgetSwithcerIndex);

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

	void InitializeSlot();
	
	UPROPERTY()
	FString SlotIndex;

	void SetLoadSlotName(const FString& SlotName);

	FString GetLoadSlotName() const { return LoadSlotName; };

	/** Field Notifies */
	
	void SetPlayerName(const FString& InPlayerName);
	FString GetPlayerName() const { return PlayerName; }

private:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, FieldNotify, Setter, Getter, meta = (AllowPrivateAccess="true"))
	FString PlayerName;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, FieldNotify, Setter, Getter, meta = (AllowPrivateAccess="true"))
	FString LoadSlotName;
	
};
