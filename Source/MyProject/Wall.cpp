///
///Created by Jesus pokoidevVillar, jesusferminvillar@gmail.com (www.pokoidev.com) 
/// Copyright © 2019 Pokoidev. Creative Commons License:
/// Attribution 4.0 International (CC BY 4.0)
///

#include "Wall.h"


// Sets default values
AWall::AWall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Create the collider and set an initial shape size
	box_collider = CreateDefaultSubobject<UBoxComponent>("Collider");
	box_collider->SetBoxExtent(FVector(50, 50, 50));

	//Create the exit position
	exit_position_scene_component = CreateDefaultSubobject<USceneComponent>("Exit");

	//Organize the hierarchy
	SetRootComponent(box_collider);
	exit_position_scene_component ->AttachToComponent(box_collider, FAttachmentTransformRules::SnapToTargetIncludingScale);
}

// Called when the game starts or when spawned
void AWall::BeginPlay()
{
	Super::BeginPlay();
	
	//Subscribe to on trigger enter events
	box_collider->OnComponentBeginOverlap.AddDynamic(this, &AWall::TriggerEnter);
	//Subscribe to on trigger exit events
	box_collider->OnComponentEndOverlap.AddDynamic(this, &AWall::TriggerExit);

	exit_position = exit_position_scene_component->GetComponentLocation();
}

// Called every frame
void AWall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//Trigger Enter
void AWall::TriggerEnter(UPrimitiveComponent * HitComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherActor != nullptr && (OtherActor != this) && OtherComp != nullptr)
	{
		AMovableActor* movable = Cast<AMovableActor>(OtherActor);
		if (movable != nullptr)
		{
			movable->ChangeDirection();
			movable->ChangePosition({ exit_position.X + FMath::RandRange(-100.0f, 100.0f) , exit_position.Y, movable-> GetActorLocation().Z});
		}
	}
}

//Trigger Exit
void AWall::TriggerExit(UPrimitiveComponent * HitComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
	//Sin implementar
}


