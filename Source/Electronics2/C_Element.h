// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <cmath>
#include "Components/PrimitiveComponent.h"
#include "PaperSprite.h"
#include "PaperSpriteComponent.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "C_Element.generated.h"

UCLASS()
class ELECTRONICS2_API AC_Element : public AActor
{
	

	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere)
	TMap<UPrimitiveComponent*, FVector> Sockets;

	AC_Element(){
		PrimaryActorTick.bCanEverTick = true;
	}




protected:

	UFUNCTION(BlueprintCallable)
	void AddSocket(UPaperSpriteComponent *Socket) {
		if (!IsValid(Socket) || Socket == NULL)return;
		Sockets.Add(Socket, Socket->GetComponentLocation()-GetActorLocation());
		Socket->SetTranslucentSortPriority(1);
	}

	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool IsSocket(UPrimitiveComponent *Socket) {
		if (!IsValid(Socket))return false;
		auto *Paper = dynamic_cast<UPaperSpriteComponent*>(Socket);
		if (Paper == NULL)return false;
		if (!IsValid(Paper))return false;
		return Sockets.Contains(Socket);
	}

	UFUNCTION(BlueprintCallable, BlueprintPure)
		bool GetSocketStartingPosition(UPrimitiveComponent *Socket, FVector &StartingLocation) {
		if (!IsValid(Socket))return false;
		bool flag = Sockets.Contains(Socket);
		if (!flag)return false;		
		StartingLocation = Sockets[Socket] + GetActorLocation();
		return true;
	}


	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


#if WITH_EDITOR

	FVector PendingTranslation = FVector::ZeroVector;

	void PostActorCreated() {
		FVector Vec = GetActorLocation();
		int x = Vec.X / 50;
		int y = Vec.Y / 50;
		int z = Vec.Z / 50;
		auto lambda = [](int &x) {
			if (x != 0)	x = (x / abs(x))*((abs(x)) / 2 * 2);
		};
		lambda(x);
		lambda(y);
		lambda(z);
		SetActorLocation(FVector(0, y + 1, z + 1) * 50);
	}

	void EditorApplyTranslation(const FVector & DeltaTranslation,
		bool bAltDown, bool bShiftDown, bool bCtrlDown) {
		if (bShiftDown) {
			SetActorLocation(GetActorLocation() + DeltaTranslation);
			return;
		}
		PendingTranslation += DeltaTranslation;
		int x = PendingTranslation.X / 50;
		int y = PendingTranslation.Y / 50;
		int z = PendingTranslation.Z / 50;
		if (x == 0 && y == 0 && z == 0)return;

		auto lambda = [](int &x) {
			if (x != 0)	x = (x / abs(x))*((abs(x) + 1) / 2);
		};
		lambda(x);
		lambda(y);
		lambda(z);
		SetActorLocation(GetActorLocation() + FVector(0, y, z) * 100);
		PendingTranslation -= FVector(0, y, z) * 100;
	}

#endif

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector DeltaLocation = FVector(0, 50, 0);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector DeltaLocationSocket = FVector(0, 50, 0);

	UFUNCTION(BlueprintCallable)
		static FVector QuantizePosition(FVector InLocation, FVector Delta = FVector(0, 50, 0)) {

		float y = InLocation.Y;
		float z = InLocation.Z;

		bool bNegativeY = y < 0;
		bool bNegativeZ = z < 0;

		y = (int)std::abs(y + 25) / 100 * 100;
		z = (int)std::abs(z + 25) / 100 * 100 + 50;

		if (bNegativeY)y = -y;
		if (bNegativeZ)z = -z;


		return FVector(0, y, z) + Delta;
	}

	UFUNCTION(BlueprintCallable)
		virtual void SetElementPosition(FVector InLocation, UPrimitiveComponent *Component) {

		float y = InLocation.Y;
		float z = InLocation.Z;

		bool bNegativeY = y < 0;
		bool bNegativeZ = z < 0;

		y = (int)std::abs(y + 25) / 100 * 100;
		z = (int)std::abs(z + 25) / 100 * 100 + 50;

		if (bNegativeY)y = -y;
		if (bNegativeZ)z = -z;


		SetActorLocation(FVector(0, y, z) + DeltaLocation);

	}

	UFUNCTION(BlueprintCallable)
		void SetElementComponentLocalPosition(UPrimitiveComponent *Component, FTransform InTransform, FTransform &OutTransform) {

		float y = InTransform.GetLocation().Y;
		float z = InTransform.GetLocation().Z;

		bool bNegativeY = y < 0;
		bool bNegativeZ = z < 0;

		y = (int)abs(y + 25) / 100 * 100 + 50;
		z = (int)abs(z + 25) / 100 * 100 + 50;

		if (bNegativeY)y = -y;
		if (bNegativeZ)z = -z;

		FVector Loc = FVector(0, y, z) + DeltaLocationSocket;

		Component->SetWorldLocation(Loc);

		OutTransform = FTransform(Loc);


	}


};
