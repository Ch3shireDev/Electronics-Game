// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "C_ElectronicsHUD.generated.h"

/**
 * 
 */

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
	
	
public:

	
};
