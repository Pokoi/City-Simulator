///
///Created by Jesus pokoidevVillar, jesusferminvillar@gmail.com (www.pokoidev.com) 
/// Copyright © 2019 Pokoidev. Creative Commons License:
/// Attribution 4.0 International (CC BY 4.0)
///

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Car.h"
#include "Walker.h"
#include "Components/PointLightComponent.h"
#include "TrafficLight.generated.h"


UCLASS()
class MYPROJECT_API ATrafficLight : public AActor
{
	GENERATED_BODY()
	
public:	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Apply Changes")
		bool check_to_apply_changes = false;

	//Mesh
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
		class UStaticMeshComponent* mesh;

	//Detector colliders
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collider")
		class UBoxComponent* car_detector_trigger;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collider")
		class UBoxComponent* walker_detector_trigger;

	//Lights
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Traffic Lights")
		class UPointLightComponent* red_light;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Traffic Lights")
		class UPointLightComponent* orange_light;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Traffic Lights")
		class UPointLightComponent* green_light;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Traffic Lights")
		class UPointLightComponent* walker_light;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Traffic Lights")
		FVector initial_position_red_light = { -245.0, 60, 306.0 };

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Traffic Lights")
		FVector initial_position_orange_light = { -245.0, 60, 286.0 };

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Traffic Lights")
		FVector initial_position_green_light = { -245.0, 60, 266.0 };

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Traffic Lights")
		FVector initial_position_walker_light = { 20.0, 10, 106.0 };

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Traffic Lights")
		FColor  red_light_color   = { 255, 0, 0, 1 };

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Traffic Lights")
		FColor  orange_light_color = { 255, 125, 0, 1 };

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Traffic Lights")
		FColor  green_light_color  = { 0, 255, 0, 1 };



	//Access
	bool cars_can_pass;
	bool walkers_can_pass;

	   	  
	//Lists of movables actors
	TArray<ACar*>    waiting_cars;
	TArray<AWalker*> waiting_walkers;	

	// Sets default values for this actor's properties
	ATrafficLight();

	//Trigger Enter
	UFUNCTION()
		void CarTriggerEnter(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	UFUNCTION()
		void WalkTriggerEnter(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	//Trigger Exit
	UFUNCTION()
		void CarTriggerExit(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	UFUNCTION()
		void WalkTriggerExit(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
	//Light Control
	UFUNCTION()
		void TurnOnRedLight();
	UFUNCTION()
		void TurnOnOrangeLight();
	UFUNCTION()
		void TurnOnGreenLight();
	UFUNCTION()
		void TurnOnWalkerLight();	
	UFUNCTION()
		void TurnOffRedLight();
	UFUNCTION()
		void TurnOffOrangeLight();
	UFUNCTION()
		void TurnOffGreenLight();
	UFUNCTION()
		void TurnOffWalkerLight();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
private:
	void PostEditChangeProperty(struct FPropertyChangedEvent& e);
};
