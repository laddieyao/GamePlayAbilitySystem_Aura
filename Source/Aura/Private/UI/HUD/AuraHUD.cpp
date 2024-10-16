// Copyright LaadieYao


#include "UI/HUD/AuraHUD.h"

#include "Blueprint/UserWidget.h"
#include "Engine/Engine.h"
#include "UI/WidgetController/AttributeMenuWidgetController.h"
#include "UI/WidgetController/OverlayWidgetController.h"

/**
 * 获取OverlayWidget对应的OverlayWidgetController，类似单例的实现形式
 * @param WCParams 
 * @return 
 */
UOverlayWidgetController* AAuraHUD::GetOverlayWidgetController(const FWidgetControllerParams& WCParams)
{
	if (OverlayWidgetController == nullptr)
	{
		OverlayWidgetController = NewObject<UOverlayWidgetController>(this, OverlayWidgetControllerClass);
		OverlayWidgetController->SetWidgetControllerParams(WCParams);
		OverlayWidgetController->BindCallbacksToDependencies();
		return OverlayWidgetController;
	}
	return OverlayWidgetController;
}


/**
 * 初始化OverlayWidget
 * @param PC 
 * @param PS 
 * @param ASC 
 * @param AS 
 */
void AAuraHUD::InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS)
{
	checkf(OverlayWidgetClass, TEXT("Overlay Widget Class uninitialized, please fill out BP_AuraHUD"));
	checkf(OverlayWidgetControllerClass, TEXT("Overlay Widget Controller Class uninitialized, please fill out BP_AuraHUD"));

	// 初始化OverlayWidget
	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass);
	OverlayWidget = Cast<UAuraUserWidget>(Widget);

	// 初始化OverlayWidgetController配置并构造OverlayWidgetController
	const FWidgetControllerParams WidgetControllerParams(PC, PS, ASC, AS);
	UOverlayWidgetController* WidgetController = GetOverlayWidgetController(WidgetControllerParams);
	
	OverlayWidget->SetWidgetController(WidgetController);

	// 这时可以广播初始值
	WidgetController->BroadcastInitialValues();
	Widget->AddToViewport();
}

UAttributeMenuWidgetController* AAuraHUD::GetAttributeMenuWidgetController(const FWidgetControllerParams& WCParams)
{
	if(AttributeMenuWidgetController == nullptr)
	{
		AttributeMenuWidgetController = NewObject<UAttributeMenuWidgetController>(this, AttributeMenuWidgetControllerClass);
		AttributeMenuWidgetController->SetWidgetControllerParams(WCParams);
		// AttributeMenuWidgetController->BroadcastInitialValues();
		AttributeMenuWidgetController->BindCallbacksToDependencies();
	}
	return AttributeMenuWidgetController;
}

void AAuraHUD::InitAttributeMenuWidget(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS)
{
	checkf(AttributeMenuWidgetClass, TEXT("AttributeMenu Widget Class uninitialized, please fill out BP_AuraHUD"));
	checkf(AttributeMenuWidgetControllerClass, TEXT("AttributeMenu Widget Controller Class uninitialized, please fill out BP_AuraHUD"));

	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), AttributeMenuWidgetClass);
	AttributeMenuWidget = Cast<UAuraUserWidget>(Widget);

	// 初始化OverlayWidgetController配置并构造OverlayWidgetController
	const FWidgetControllerParams WidgetControllerParams(PC, PS, ASC, AS);
	UAttributeMenuWidgetController* WidgetController = GetAttributeMenuWidgetController(WidgetControllerParams);
	
	AttributeMenuWidget->SetWidgetController(WidgetController);

	// 这时可以广播初始值
	WidgetController->BroadcastInitialValues();
	UE_LOG(LogTemp, Warning, TEXT("InitAttributeMenuWidget"));
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("InitAttributeMenuWidget"));
	// Widget->AddToViewport();
}
