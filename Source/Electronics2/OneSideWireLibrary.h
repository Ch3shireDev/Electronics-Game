// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "OneSideWireLibrary.generated.h"

UCLASS()
class ELECTRONICS2_API UOneSideWireLibrary : public UActorComponent
{
	GENERATED_BODY()

		TArray<FVector> NodePositions;

	UOneSideWireLibrary() {}

protected:
	virtual void BeginPlay() override{}

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override{}


	UFUNCTION(BlueprintCallable)

		void AddWireLocation(FVector InLocation) {
		if (NodePositions.Num() != 0 && FVector::Dist(NodePositions.Last(), InLocation) < 50)return;

		int n = -1;
		for (int i = 0; i < NodePositions.Num(); i++) {
			FVector Node = NodePositions.Last(i);
			if (FVector::Dist(Node, InLocation) < 50) {
				n = i;
				break;
			}
		}
		
		if (n != -1) {
			for (int i = 0; i < n; i++)NodePositions.Pop();
		}
		else {
			NodePositions.Add(InLocation);
		}
		

	}
	
	UFUNCTION(BlueprintCallable)
	int GetArraySize() { return NodePositions.Num(); }
	
	UFUNCTION(BlueprintCallable)
		void DrawPoints() {
		if (NodePositions.Num() < 2)return;
		for (int i = 1; i < NodePositions.Num(); i++) {
			
			FVector p0 = NodePositions[i - 1];
			FVector p1 = NodePositions[i];

			UKismetSystemLibrary::DrawDebugLine(this, p0, p1, FLinearColor::Red, 0, 5);
		}
	}
};
