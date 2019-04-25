///
///Created by Jesus pokoidevVillar, jesusferminvillar@gmail.com (www.pokoidev.com) 
/// Copyright © 2019 Pokoidev. Creative Commons License:
/// Attribution 4.0 International (CC BY 4.0)
///

#include "MovableActor.h"


// Sets default values
AMovableActor::AMovableActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Create the colliders
	box_collider           = CreateDefaultSubobject<UBoxComponent>("Collider");
	front_proximity_sensor = CreateDefaultSubobject<UBoxComponent>("Front Proximity Sensor");

	//Organize the hierarchy
	RootComponent = box_collider;
	front_proximity_sensor->AttachToComponent(box_collider, FAttachmentTransformRules::SnapToTargetIncludingScale);

	//Add a local position to the front_proximity_sensor
	front_proximity_sensor->SetRelativeLocation({236, 0, 0});

	//Subscribe to on trigger events
	front_proximity_sensor->OnComponentBeginOverlap.AddDynamic(this, &AMovableActor::FrontSensorTriggerEnter);
	front_proximity_sensor->OnComponentEndOverlap.AddDynamic(this, &AMovableActor::FrontSensorTriggerExit);
	
}

// Called when the game starts or when spawned
void AMovableActor::BeginPlay()
{
	Super::BeginPlay();

	sensor_activated = false;
	current_speed += FMath::RandRange(-speed_random_offset, speed_random_offset);
	UpdateMovementDirectionVector();
	Move();
	initial_speed = current_speed;
}

// Called every frame
void AMovableActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if(movable && !sensor_activated) SetActorLocation(GetActorLocation() + movement_direction * DeltaTime * current_speed);
}

/*
Makes the actor facing backwards
*/
void AMovableActor::ChangeDirection() 
{ 	
	FRotator actor_rotation = GetActorRotation();
	SetActorRotation({ actor_rotation.Pitch, actor_rotation.Yaw - 180, actor_rotation.Roll});

	UpdateMovementDirectionVector();
}
/*
Teleports the actor to a given position
@param new_position - The position to teleport to
*/
void AMovableActor::ChangePosition(FVector new_position) { SetActorLocation(new_position); }
/*
Stops the actor
*/
void AMovableActor::Stop() { movable = false; }
/*
Moves the actor
*/
void AMovableActor::Move() { movable = true;  }
/*
Updates the value of the movement_direction value
*/
void AMovableActor::UpdateMovementDirectionVector() { movement_direction = GetActorForwardVector(); }

void AMovableActor::FrontSensorTriggerEnter(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherActor != nullptr && (OtherActor != this) && OtherComp != nullptr)
	{
		AMovableActor* movable = Cast<AMovableActor>(OtherActor);
		if (movable != nullptr)
		{
			sensor_activated = true;
			sensor_contacts++;
		}
	}
}

void AMovableActor::FrontSensorTriggerExit(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor != nullptr && (OtherActor != this) && OtherComp != nullptr)
	{
		AMovableActor* movable = Cast<AMovableActor>(OtherActor);
		if (movable != nullptr)
		{
			sensor_contacts--;
			if(sensor_contacts==0) sensor_activated = false;
		}
	}
}