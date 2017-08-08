// Fill out your copyright notice in the Description page of Project Settings.

#include "WireLibrary.h"
#include "GameFramework/Actor.h"
#include "CoreMinimal.h"
#include "PaperSpriteComponent.h"
#include "PaperSprite.h"
#include "Components/SplineMeshComponent.h"
#include "Kismet/KismetSystemLibrary.h"


void UWireLibrary::CreateWireParts(AActor *Actor, USceneComponent *SceneComponent, UStaticMesh *SplineMesh) {

	//horizontal - y, vertical - z

	if (!IsValid(Actor))return;
	if (!IsValid(SceneComponent))return;
	if (!IsValid(SplineMesh))return;

	auto Array = GetAllPoints();

	for (int i = 1; i < Array.Num(); i++) {

		//GLog->Log(it->ToString());

		FVector p1 = Array[i - 1];
		FVector p2 = Array[i];

		FVector Location = (p1+p2) / 2;

		FString str = FString();
		str.AppendInt(i);
		
		auto *Component = NewObject<USplineMeshComponent>(this, FName(*str));
		Component->SetStaticMesh(SplineMesh);
		Component->SetMobility(EComponentMobility::Movable);
		Component->SetupAttachment(SceneComponent);
		Component->SetForwardAxis(ESplineMeshAxis::Z, true);
		Component->SetStartPosition(FVector(-50, 0, 0));
		Component->SetStartTangent(FVector(50, 0, 0));
		Component->SetEndPosition(FVector(50, 0, 0));
		Component->SetEndTangent(FVector(50, 0, 0));
		Component->SetWorldLocation(Location + Actor->GetActorLocation());

		bool IsHorizontal = abs(p1.Z - p2.Z) < 1;
		bool IsVertical = abs(p1.Y - p2.Y) < 1;

		if(IsHorizontal)
			Component->SetRelativeRotation(FRotator(0, 180, 0));
		else
			Component->SetRelativeRotation(FRotator(90, 180, 0));

		Component->RegisterComponent();

	}
}



void UWireLibrary::DrawPoints(AActor *Actor) {
	if (PointsList.size() < 2)return;

	//std::list<FVector>::iterator it1, it2;
	//it1 = PointsList.begin();
	//it2 = PointsList.begin();
	//it2++;
	//
	//while (it2 != PointsList.end()) {
	//	UKismetSystemLibrary::DrawDebugArrow(this, *it1 + Actor->GetActorLocation(), *it2 + Actor->GetActorLocation(), 5, FLinearColor::Red, 0, 10);
	//	it1++;
	//	it2++;
	//}
	//
}



// Sets default values for this component's properties
UWireLibrary::UWireLibrary()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UWireLibrary::BeginPlay()
{
	Super::BeginPlay();
	
}


// Called every frame
void UWireLibrary::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}



void UWireLibrary::UpdateSocketPosition(FTransform InTransform, AActor *InActor, UActorComponent *InComponent, UActorComponent *SocketA, UActorComponent *SocketB) {
	int Ending = 0;
	if (InComponent == SocketA) Ending = 0;
	else if (InComponent == SocketB) Ending = 1;
	else return;
	USceneComponent *Primitive = dynamic_cast<USceneComponent*>(InComponent);
	AddNewPoint(Primitive->GetComponentLocation() - InActor->GetActorLocation(), Ending);

	GLog->Log(Primitive->RelativeLocation.ToString());
}

template <typename It, typename List> void AddAux(FVector Point, int Ending, List PointsList) {
	PointsList.begin();
}


void UWireLibrary::AddNewPoint(FVector Point, int Ending) {

	//probably i could write it better, but frankly i don't give a fuck

	FVector BeginPoint, EndPoint;
	if (Ending) {
		BeginPoint = *PointsList.begin();
		EndPoint = *PointsList.rbegin();
	}
	else {
		BeginPoint = *PointsList.rbegin();
		EndPoint = *PointsList.begin();
	}


	//I add points at the front of the list

	bool flag = false;
	int n = 0;

	if ((FVector::Dist(EndPoint, Point) < 90))return;

	if (Ending == 0) {
		TList::iterator beg, end, it;
		beg = PointsList.begin();
		end = PointsList.end();
		it = beg;
		if (PointsList.size() > 0) {
			while (it != end) {
				if (FVector::Dist(*it++, Point) < 90) {
					if(it!=end)
						flag=true; 
					break; 
				}
				n++;
			}
			
		}
	}

	//I add points at the end of the list

	if (Ending) {
		TList::reverse_iterator beg, end, it;
		beg = PointsList.rbegin();
		end = PointsList.rend();
		it = beg;
		if (PointsList.size() > 0) {
			while (it != end) {
				if (FVector::Dist(*it++, Point) < 90) {
					if(it!=end)
						flag = true; 
					break;
				}
				n++;
			}

		}
	}

	if (flag) {
		for (int i = 0; i < n; i++) {
			if (Ending)PointsList.pop_back();
			else PointsList.pop_front();
		}
		return;
	}


	if (Ending) PointsList.push_back(Point);
	else PointsList.push_front(Point);
}

