// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "C_Element.h"
#include "HUDLibrary.generated.h"

class UPrimitiveComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ELECTRONICS2_API UHUDLibrary : public UActorComponent
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
		TArray<AC_Element*> Elements;

public:	

	UFUNCTION(BlueprintCallable)
	void GetConnectedElement(FVector InLocation, AC_Element* &Element, UPrimitiveComponent* &Component) {
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

	UHUDLibrary()	{
		PrimaryComponentTick.bCanEverTick = true;
		Elements.Empty();
	}

	void BeginPlay()	{
		Super::BeginPlay();

	}

	void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)	{
		Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	}

	UFUNCTION(BlueprintCallable)
		void RegisterElement(AC_Element* Element) {
		Elements.Add(Element);
	}


		
	
};
