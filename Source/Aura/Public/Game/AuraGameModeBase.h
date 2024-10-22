// Copyright LaadieYao

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "AuraGameModeBase.generated.h"


class ULoadScreenSaveGame;
class UMVVM_LoadSlot;
class USaveGame;
class UCharacterClassInfo;
/**
 * 
 */
UCLASS()
class AURA_API AAuraGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, Category="Character Class Defaults")
	TObjectPtr<UCharacterClassInfo> CharacterClassInfo;
	

	void SaveSlotData(UMVVM_LoadSlot* LoadSlot, int32 SlotIndex);

	ULoadScreenSaveGame* GetSaveSlotData(const FString& SlotName, int32 SlotIndex) const;
	static void DeletelSot(const FString& SlotName, int32 SlotIndex);

	void TravelToMap(UMVVM_LoadSlot* Slot);
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<USaveGame> LoadScreenSaveGameClass;

	UPROPERTY(EditDefaultsOnly)
	FString DefaultMapName;
	
	UPROPERTY(EditDefaultsOnly)
	TSoftObjectPtr<UWorld> DefaultMap;

	UPROPERTY(EditDefaultsOnly)
	TMap<FString, TSoftObjectPtr<UWorld>> Maps;
protected:
	virtual void BeginPlay() override;
};
