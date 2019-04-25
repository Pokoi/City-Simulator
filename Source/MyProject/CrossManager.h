///
///Created by Jesus pokoidevVillar, jesusferminvillar@gmail.com (www.pokoidev.com) 
/// Copyright © 2019 Pokoidev. Creative Commons License:
/// Attribution 4.0 International (CC BY 4.0)
///

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Components/SceneComponent.h"
#include "Car.h"
#include "Walker.h"
#include "TrafficLight.h"
#include "CrossManager.generated.h"


UENUM()
enum class FlowTurn : uint8
{
	North_South,
	Western_East,
};

UCLASS()
class MYPROJECT_API ACrossManager : public AActor
{
	GENERATED_BODY()
	
public:

	//Root
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Root")
		class USceneComponent* root;

	//Timers
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Traffic Light Timer")
		float maximum_seconds_on        = 5;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Traffic Light Timer")
		float seconds_remaing_in_orange = 2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Colliders")
		class UBoxComponent* car_box_collider;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Colliders")
		class UBoxComponent* crosswalk_1_collider;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Colliders")
		class UBoxComponent* crosswalk_2_collider;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Colliders")
		class UBoxComponent* crosswalk_3_collider;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Colliders")
		class UBoxComponent* crosswalk_4_collider;

	//Lists
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Traffic Lights")
	TArray<ATrafficLight*> cross_traffic_lights;

	
	

	// Sets default values for this actor's properties
	ACrossManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Traffic control
	void TurnOnTrafficLight(int index);
	void TurnOffTrafficLight(int index);
	void TurnOffWalkTraffic(int index);
	void TurnOnWalkTraffic(int index);
	void TurnOrangeTrafficLight();

	//Timer control
	void ChangeFlow();



private:
	float remaining_seconds;
	FlowTurn current_turn;

	
	TArray<ACar*>    passing_cars;
	TArray<AWalker*> passing_walkers;

	//Trigger Enter
	UFUNCTION()
		void CrossWalkTriggerEnter(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	UFUNCTION()
		void CarTriggerEnter(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	//Trigger Exit
	UFUNCTION()
		void CrossWalkTriggerExit(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	UFUNCTION()
		void CarTriggerExit(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
		bool EmptyRoad();
	
};
