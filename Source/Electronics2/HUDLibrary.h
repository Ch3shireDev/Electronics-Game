// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "C_Element.h"
#include "HUDLibrary.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ELECTRONICS2_API UHUDLibrary : public UActorComponent
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
		TArray<AC_Element*> Elements;

public:	
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
