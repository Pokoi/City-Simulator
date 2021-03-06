///
///Created by Jesus pokoidev Villar, jesusferminvillar@gmail.com (www.pokoidev.com) 
/// Copyright © 2019 Pokoidev. Creative Commons License:
/// Attribution 4.0 International (CC BY 4.0)
///

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Walker.h"
#include "Car.h"
#include "StreetSpawn.generated.h"

UCLASS()
class MYPROJECT_API AStreetSpawn : public AActor
{
	GENERATED_BODY()
	
public:	

	//Object collider
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collider")
		class UBoxComponent* street_collider;

	//Available Directions in this street 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flow Direction")
		bool north_south_flow;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flow Direction")
		bool south_north_flow;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flow Direction")
		bool east_west_flow;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flow Direction")
		bool west_east_flow;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crowd")
		bool car_spawner;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crowd")
		bool walker_spawner;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crowd")
		int walkers_amount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crowd")
		int cars_amount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crowd")
		class AWalker* walker_prefab;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crowd")
		class ACar*    car_prefab;

	// Sets default values for this actor's properties
	AStreetSpawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	float    north_south_yaw =  90.0f;
	float    west_east_yaw   = 180.0f;
	float    max_x_position;
	float    max_y_position;
	float    min_x_position;
	float    min_y_position;

	void     spawn_walkers();
	void     spawn_cars();

	FVector  walker_prefab_position;
	FVector  car_prefab_position;		
	FVector  GetRandomPositionInsideCollider();
};
