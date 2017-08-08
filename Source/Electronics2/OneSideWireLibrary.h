// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "OneSideWireLibrary.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class ELECTRONICS2_API UOneSideWireLibrary : public UActorComponent
{
	GENERATED_BODY()

		TArray<FVector> NodePositions;

	UFUNCTION(BlueprintCallable)

		void AddWireLocation(FVector InLocation) {
		if (NodePositions.Num() == 0){
			NodePositions.Add(InLocation);
			return;
		}

		int i = 0;
		for (; i < NodePositions.Num(); i++) {
			if (FVector::Distance(NodePositions[i], InLocation) < 50)break;
		}
		while (i + 1 < NodePositions.Num())NodePositions.Pop();
		NodePositions.Add(InLocation);
	}
	
	int GetArraySize() { return NodePositions.Num(); }
	
};
