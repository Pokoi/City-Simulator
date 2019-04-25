///
///Created by Jesus pokoidevVillar, jesusferminvillar@gmail.com (www.pokoidev.com) 
/// Copyright © 2019 Pokoidev. Creative Commons License:
/// Attribution 4.0 International (CC BY 4.0)
///

#include "CrossManager.h"
#include "Engine.h"


// Sets default values
ACrossManager::ACrossManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	current_turn = FlowTurn::North_South;

	//Create root
	root = CreateDefaultSubobject<USceneComponent>("Root");

	//Create colliders
	car_box_collider     = CreateDefaultSubobject<UBoxComponent>("Car Box Collider");
	crosswalk_1_collider = CreateDefaultSubobject<UBoxComponent>("Crosswalk 1 Collider");
	crosswalk_2_collider = CreateDefaultSubobject<UBoxComponent>("Crosswalk 2 Collider");
	crosswalk_3_collider = CreateDefaultSubobject<UBoxComponent>("Crosswalk 3 Collider");
	crosswalk_4_collider = CreateDefaultSubobject<UBoxComponent>("Crosswalk 4 Collider");

	//Organize hierarchy
	SetRootComponent(root);
	car_box_collider    ->AttachToComponent(root, FAttachmentTransformRules::SnapToTargetIncludingScale);
	crosswalk_1_collider->AttachToComponent(root, FAttachmentTransformRules::SnapToTargetIncludingScale);
	crosswalk_2_collider->AttachToComponent(root, FAttachmentTransformRules::SnapToTargetIncludingScale);
	crosswalk_3_collider->AttachToComponent(root, FAttachmentTransformRules::SnapToTargetIncludingScale);
	crosswalk_4_collider->AttachToComponent(root, FAttachmentTransformRules::SnapToTargetIncludingScale);
	
	//Subscribe to on trigger events
	car_box_collider    ->OnComponentBeginOverlap.AddDynamic(this, &ACrossManager::CarTriggerEnter);
	crosswalk_1_collider->OnComponentBeginOverlap.AddDynamic(this, &ACrossManager::CrossWalkTriggerEnter);
	crosswalk_2_collider->OnComponentBeginOverlap.AddDynamic(this, &ACrossManager::CrossWalkTriggerEnter);
	crosswalk_3_collider->OnComponentBeginOverlap.AddDynamic(this, &ACrossManager::CrossWalkTriggerEnter);
	crosswalk_4_collider->OnComponentBeginOverlap.AddDynamic(this, &ACrossManager::CrossWalkTriggerEnter);
	car_box_collider    ->OnComponentEndOverlap.AddDynamic(this, &ACrossManager::CarTriggerExit);
	crosswalk_1_collider->OnComponentEndOverlap.AddDynamic(this, &ACrossManager::CrossWalkTriggerExit);
	crosswalk_2_collider->OnComponentEndOverlap.AddDynamic(this, &ACrossManager::CrossWalkTriggerExit);
	crosswalk_3_collider->OnComponentEndOverlap.AddDynamic(this, &ACrossManager::CrossWalkTriggerExit);
	crosswalk_4_collider->OnComponentEndOverlap.AddDynamic(this, &ACrossManager::CrossWalkTriggerExit);
}

// Called when the game starts or when spawned
void ACrossManager::BeginPlay()
{
	Super::BeginPlay();
	
}
// Called every frame
void ACrossManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (remaining_seconds > 0.0)
	{
		remaining_seconds -= DeltaTime;

		if (remaining_seconds < seconds_remaing_in_orange) TurnOrangeTrafficLight();
	}
	else ChangeFlow();

}

void ACrossManager::TurnOnTrafficLight(int index) 
{ 
	cross_traffic_lights[index]->cars_can_pass = true;
	cross_traffic_lights[index]->TurnOnGreenLight();

	cross_traffic_lights[index]->TurnOffRedLight();
	cross_traffic_lights[index]->TurnOffOrangeLight();
}

void ACrossManager::TurnOffTrafficLight(int index)
{
	cross_traffic_lights[index]->cars_can_pass = false;
	cross_traffic_lights[index]->TurnOnRedLight();

	cross_traffic_lights[index]->TurnOffGreenLight();
	cross_traffic_lights[index]->TurnOffOrangeLight();	
}

void ACrossManager::TurnOffWalkTraffic(int index) 
{
	cross_traffic_lights[index]->walkers_can_pass = false;
	cross_traffic_lights[index]->TurnOffWalkerLight();
}

void ACrossManager::TurnOnWalkTraffic(int index)
{
	cross_traffic_lights[index]->walkers_can_pass = true;
	cross_traffic_lights[index]->TurnOnWalkerLight();
}

void ACrossManager::ChangeFlow()
{
	switch (current_turn)
	{
		case FlowTurn::North_South :
			TurnOffTrafficLight(1);
			TurnOffTrafficLight(3);
			TurnOffWalkTraffic(0);
			TurnOffWalkTraffic(2);
		break;

		case FlowTurn::Western_East:
			TurnOffTrafficLight(0);
			TurnOffTrafficLight(2);
			TurnOffWalkTraffic(1);
			TurnOffWalkTraffic(3);
		break;

	}
	
	if (EmptyRoad()) 
	{
		switch (current_turn)
		{
			case FlowTurn::North_South:
				TurnOnTrafficLight(0);
				TurnOnTrafficLight(2);
				TurnOnWalkTraffic(1);
				TurnOnWalkTraffic(3);
			break;

			case FlowTurn::Western_East:
				TurnOnTrafficLight(1);
				TurnOnTrafficLight(3);
				TurnOnWalkTraffic(0);
				TurnOnWalkTraffic(2);
			break;
		}

		remaining_seconds = maximum_seconds_on;
		current_turn = current_turn == FlowTurn::North_South ? FlowTurn::Western_East : FlowTurn::North_South;
	}
	else 
	{
		for (AWalker* walker : passing_walkers) walker->HurryUp();
		
	}
}

void ACrossManager::TurnOrangeTrafficLight() 
{ 
	int initial_index = current_turn == FlowTurn::North_South ? 1 : 0;
	while (initial_index < (cross_traffic_lights.Num()))
	{
		cross_traffic_lights[initial_index]->TurnOnOrangeLight();
		cross_traffic_lights[initial_index]->TurnOffRedLight();
		cross_traffic_lights[initial_index]->TurnOffGreenLight();
		initial_index += 2;
	} 

}

void ACrossManager::CrossWalkTriggerEnter(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	
	if (OtherActor != nullptr && (OtherActor != this) && OtherComp != nullptr)
	{		
		AWalker* walker = Cast<AWalker>(OtherActor);
		if (walker != nullptr && !passing_walkers.Contains(walker)) passing_walkers.Add(walker);			
	}
}

void ACrossManager::CarTriggerEnter(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherActor != nullptr && (OtherActor != this) && OtherComp != nullptr)
	{	
		ACar* car = Cast<ACar>(OtherActor);
		if (car != nullptr && !passing_cars.Contains(car)) passing_cars.Add(car);		
	}
}

void ACrossManager::CrossWalkTriggerExit(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor != nullptr && (OtherActor != this) && OtherComp != nullptr)
	{
		AWalker* walker = Cast<AWalker>(OtherActor);
		if (walker != nullptr && passing_walkers.Contains(walker))
		{			
			walker->Relax();
			passing_walkers.Remove(walker);
		}
	}
}

void ACrossManager::CarTriggerExit(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

	if (OtherActor != nullptr && (OtherActor != this) && OtherComp != nullptr)
	{
		ACar* car = Cast<ACar>(OtherActor);
		if (car != nullptr && passing_cars.Contains(car)) passing_cars.Remove(car);
	}
}

bool ACrossManager::EmptyRoad() 
{
	return (passing_cars.Num() == 0 && passing_walkers.Num() == 0);
}
