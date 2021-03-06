///
///Created by Jesus pokoidev Villar, jesusferminvillar@gmail.com (www.pokoidev.com) 
/// Copyright © 2019 Pokoidev. Creative Commons License:
/// Attribution 4.0 International (CC BY 4.0)
///

#include "StreetSpawn.h"


// Sets default values
AStreetSpawn::AStreetSpawn()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	street_collider = CreateDefaultSubobject<UBoxComponent>("Street collider");


}

// Called when the game starts or when spawned
void AStreetSpawn::BeginPlay()
{
	Super::BeginPlay();
	
	//Set z position
	walker_prefab_position = walker_prefab->GetActorLocation();
	car_prefab_position    = car_prefab   ->GetActorLocation();

	//Set extents	
	FVector collider_bounds_extent = street_collider ->GetScaledBoxExtent();
	
	max_x_position = (collider_bounds_extent.X) + street_collider->GetComponentLocation().X;
	max_y_position = (collider_bounds_extent.Y) + street_collider->GetComponentLocation().Y;
	min_x_position = street_collider->GetComponentLocation().X - (collider_bounds_extent.X);
	min_y_position = street_collider->GetComponentLocation().Y - (collider_bounds_extent.Y);
		 
	if(walker_spawner) spawn_walkers();
	if (car_spawner)   spawn_cars();
}

// Called every frame
void AStreetSpawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AStreetSpawn::spawn_walkers()
{
	walker_prefab->SetActorHiddenInGame(false);
	walker_prefab->SetActorEnableCollision(true);

	for (int i = 0; i < walkers_amount; i++)
	{
		FRotator rotation = {
							0,
							(north_south_flow) ? ((FMath::RandRange(0.0f, 10.0f) > 5.0f) ? -north_south_yaw : north_south_yaw) : (FMath::RandRange(0.0f, 1.0f) > 0.5f) ? 0 : west_east_yaw,
							0
		};

		FActorSpawnParameters spawn_info;
		spawn_info.Template = walker_prefab;
		GetWorld()->SpawnActor<AWalker>(GetRandomPositionInsideCollider(), rotation - walker_prefab->GetActorRotation(), spawn_info);
	}
	
	walker_prefab->SetActorHiddenInGame(true);
	walker_prefab->SetActorEnableCollision(false);
}

void AStreetSpawn::spawn_cars()
{
	car_prefab->SetActorHiddenInGame(false);
	car_prefab->SetActorEnableCollision(true);

	for (int i = 0; i < cars_amount; i++)
	{
		FRotator                   rotation = { 0,                0,0 };;
		if(north_south_flow)       rotation = { 0, -north_south_yaw,0 };
		else if(south_north_flow)  rotation = { 0,  north_south_yaw,0 };
		else if(east_west_flow)    rotation = { 0,                0,0 };
		else if(west_east_flow)    rotation = { 0,    west_east_yaw,0 };

		FActorSpawnParameters spawn_info;
		spawn_info.Template = car_prefab;
		GetWorld()->SpawnActor<ACar>(GetRandomPositionInsideCollider(), rotation - car_prefab->GetActorRotation(), spawn_info);
	}

	car_prefab->SetActorHiddenInGame(true);
	car_prefab->SetActorEnableCollision(false);
}

FVector AStreetSpawn::GetRandomPositionInsideCollider() {
	
	return { FMath::RandRange(min_x_position, max_x_position), FMath::RandRange(min_y_position, max_y_position) ,0 };
}

