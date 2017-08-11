// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "C_Element.h"
#include "OneSideWireLibrary.generated.h"

UENUM(BlueprintType)
enum class EWireEndType : uint8
{
	VE_ElementA 		UMETA(DisplayName = "WireStart"),
	VE_ElementB			UMETA(DisplayName = "WireEnd")
};


UCLASS()
class ELECTRONICS2_API UOneSideWireLibrary : public UActorComponent
{
	GENERATED_BODY()

		TArray<FVector> NodePositions;

public:

	AC_Element *ElementA, *ElementB;

	bool bIsCurrentOn = false;
	float Current = 1;

	UFUNCTION(BlueprintCallable)
	void SetCurrentState(bool bNewCurrent = false) {
		bIsCurrentOn = bNewCurrent;
	}

	UFUNCTION(BlueprintCallable)
	void SetCurrentValue(float InCurrent = 1.0f) {
		Current = InCurrent;
	}

	UFUNCTION(BlueprintCallable)
	bool GetCurrentState() { return bIsCurrentOn; }

	UFUNCTION(BlueprintCallable)
	float GetCurrentValue() { return Current; }

	UFUNCTION(BlueprintCallable)
	void DrawCurrentFlow() {
		if (!bIsCurrentOn)return;

		for (int i = 0; i < NodePositions.Num()-1; i++) {
			FVector LocA = NodePositions[i], LocB = NodePositions[i + 1];

			FVector Position = NodePositions[i];

			double alpha = FPlatformTime::Seconds()/Current;
			alpha -= (int)alpha;

			Position = LocA + (LocB - LocA)*alpha;

			UKismetSystemLibrary::DrawDebugSphere(this, Position, 10, 10, FLinearColor::Black, 0, 0);
		}
	}


	UFUNCTION(BlueprintCallable)
		void SetConnectedElement(AC_Element *InElement, EWireEndType WireEnd) {
		if (!IsValid(InElement))return;
		if (WireEnd == EWireEndType::VE_ElementA) {
			GLog->Log("Wire A");
			if (!IsValid(ElementA))ElementA = InElement;
		}
		else {
			if (!IsValid(ElementB) && InElement != ElementA)ElementB = InElement;
		}
	}

	UFUNCTION(BlueprintCallable)
		bool IsTwoSidedConnected() {
		return IsValid(ElementA) && IsValid(ElementB) && ElementA != ElementB;
	}

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
