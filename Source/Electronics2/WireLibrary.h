// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include <list>
#include "Containers/Map.h"
#include "Runtime/Engine/Classes/Engine/Texture2D.h"
#include "WireLibrary.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ELECTRONICS2_API UWireLibrary : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UWireLibrary();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	typedef std::list<FVector> TList;

	TList PointsList;

	UFUNCTION(BlueprintCallable)

		void AddNewPoint(FVector Point, int Ending = 0);

	UFUNCTION(BlueprintCallable)

		void DrawPoints(AActor *object);

	UFUNCTION(BlueprintCallable)

		void UpdateSocketPosition(FTransform InTransform, AActor *InActor, UActorComponent *InComponent, UActorComponent *SocketA, UActorComponent *SocketB);

	UFUNCTION(BlueprintCallable)

		int GetArraySize() { return (int)PointsList.size(); }

	UFUNCTION(BlueprintCallable)
		void ClearList() {PointsList.clear();}

	UFUNCTION(BlueprintCallable)
		void GetPair(int n, FVector &a, FVector &b) {
		std::list<FVector>::iterator it = PointsList.begin();
		for (int i = 0; i < n; i++)it++;
		a = *it;
		it++;
		b = *it;
	}

	UFUNCTION(BlueprintCallable)

	void CreateWireParts(AActor *Actor, USceneComponent *SceneComponent, UStaticMesh *SplineMesh);

	UFUNCTION(BlueprintCallable)
		TArray<FVector> GetAllPoints() {
		TArray<FVector> out;
		for (FVector p : PointsList) {
			out.Add(p);
		}
		return out;
	}
};
