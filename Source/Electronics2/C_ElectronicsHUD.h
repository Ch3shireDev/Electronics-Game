// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "C_Element.h"
#include "C_ElectronicsHUD.generated.h"

UENUM(BlueprintType)
enum class EHoldType : uint8
{
	VE_Free 		UMETA(DisplayName = "Free"),
	VE_HoldGlobal 	UMETA(DisplayName = "Hold Global"),
	VE_HoldLocal	UMETA(DisplayName = "Hold Local")
};

UCLASS()
class ELECTRONICS2_API AC_ElectronicsHUD : public AHUD
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
		TArray<AC_Element*> Elements;

public:

	AC_ElectronicsHUD() {
		Elements.Empty();
	}

	UFUNCTION(BlueprintCallable)
		virtual void GetConnectedElement(FVector InLocation, AC_Element* &Element, UPrimitiveComponent* &Component) {
		for (int i = 0; i < Elements.Num(); i++) {
			if (!IsValid(Elements[i]))continue;
			Component = Elements[i]->GetSocketOnLocation(InLocation);
			if (Component != NULL) {
				Element = Elements[i];
				return;
			}
		}
		Element = NULL;
		Component = NULL;
		return;
	}

	UFUNCTION(BlueprintCallable)
		void RegisterElement(AC_Element* Element) {
		Elements.Add(Element);
	}

	
};
