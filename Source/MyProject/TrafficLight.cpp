///
///Created by Jesus pokoidevVillar, jesusferminvillar@gmail.com (www.pokoidev.com) 
/// Copyright © 2019 Pokoidev. Creative Commons License:
/// Attribution 4.0 International (CC BY 4.0)
///

#include "TrafficLight.h"



// Sets default values
ATrafficLight::ATrafficLight()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Create the mesh
	mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	
	//Create the lights
	red_light      = CreateDefaultSubobject<UPointLightComponent>("Red Light");
	orange_light   = CreateDefaultSubobject<UPointLightComponent>("Orange Light");
	green_light    = CreateDefaultSubobject<UPointLightComponent>("Green Light");
	walker_light   = CreateDefaultSubobject<UPointLightComponent>("Walker Light");
	

	//Create the colliders and set an initial shape size
	car_detector_trigger           = CreateDefaultSubobject<UBoxComponent>("Car Collider");
	walker_detector_trigger = CreateDefaultSubobject<UBoxComponent>("Nearby Walker Collider");	

	car_detector_trigger          ->SetBoxExtent(FVector(50, 50, 50));
	walker_detector_trigger->SetBoxExtent(FVector(50, 50, 50));	

	//Organize the hierarchy
	SetRootComponent(mesh);
	car_detector_trigger          ->AttachToComponent(mesh, FAttachmentTransformRules::SnapToTargetIncludingScale);
	walker_detector_trigger->AttachToComponent(mesh, FAttachmentTransformRules::SnapToTargetIncludingScale);
	red_light                     ->AttachToComponent(mesh, FAttachmentTransformRules::SnapToTargetIncludingScale);
	orange_light                  ->AttachToComponent(mesh, FAttachmentTransformRules::SnapToTargetIncludingScale);
	green_light                   ->AttachToComponent(mesh, FAttachmentTransformRules::SnapToTargetIncludingScale);
	walker_light                  ->AttachToComponent(mesh, FAttachmentTransformRules::SnapToTargetIncludingScale);

	


}

// Called when the game starts or when spawned
void ATrafficLight::BeginPlay()
{
	Super::BeginPlay();	

	//Subscribe to on trigger enter events
	car_detector_trigger   ->OnComponentBeginOverlap.AddDynamic(this, &ATrafficLight::CarTriggerEnter);
	walker_detector_trigger->OnComponentBeginOverlap.AddDynamic(this, &ATrafficLight::WalkTriggerEnter);
	
	//Subscribe to on trigger exit events
	car_detector_trigger   ->OnComponentEndOverlap.AddDynamic(this, &ATrafficLight::CarTriggerExit);
	walker_detector_trigger->OnComponentEndOverlap.AddDynamic(this, &ATrafficLight::WalkTriggerExit);
	

	//Add local position to the lights
	red_light   ->SetRelativeLocation(initial_position_red_light);
	orange_light->SetRelativeLocation(initial_position_orange_light);
	green_light ->SetRelativeLocation(initial_position_green_light);
	walker_light->SetRelativeLocation(initial_position_walker_light);

	//Add color to the lights
	red_light   ->SetLightColor(red_light_color);
	orange_light->SetLightColor(orange_light_color);
	green_light ->SetLightColor(green_light_color);
	walker_light->SetLightColor(red_light_color);
} 

// Called every frame
void ATrafficLight::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//Trigger Enter
void ATrafficLight::CarTriggerEnter(UPrimitiveComponent * HitComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherActor != nullptr && (OtherActor != this) && OtherComp != nullptr)
	{		
		ACar* car = Cast<ACar>(OtherActor);
		if (car != nullptr && !cars_can_pass)
		{
			waiting_cars.Add(car);
			car->Stop();
		}
		
	}
}

//Trigger Enter
void ATrafficLight::WalkTriggerEnter(UPrimitiveComponent * HitComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherActor != nullptr && (OtherActor != this) && OtherComp != nullptr)
	{		
		AWalker* walker = Cast<AWalker>(OtherActor);
		if (walker != nullptr && !walkers_can_pass)
		{
			waiting_walkers.Add(walker);
			walker->Stop();
		}
		
	}
}

//Trigger Exit
void ATrafficLight::CarTriggerExit(UPrimitiveComponent * HitComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
	ACar* car = Cast<ACar>(OtherActor);
	if (car != nullptr) waiting_cars.Remove(car);	
}

//Trigger Exit
void ATrafficLight::WalkTriggerExit(UPrimitiveComponent * HitComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{	
	AWalker* walker = Cast<AWalker>(OtherActor);
	if (walker != nullptr) waiting_walkers.Remove(walker);
	
}

//Light control
void ATrafficLight::TurnOnRedLight()     { red_light->SetVisibility(true); }

void ATrafficLight::TurnOnOrangeLight()  { orange_light->SetVisibility(true);}

void ATrafficLight::TurnOnGreenLight()   
{ 
	green_light->SetVisibility(true);
	for (ACar* car : waiting_cars) car->Move();
}

void ATrafficLight::TurnOnWalkerLight()  
{ 
	walker_light->SetLightColor(green_light_color);
	for (AWalker* walker : waiting_walkers) walker->Move();
}

void ATrafficLight::TurnOffRedLight()    { red_light->SetVisibility(false);}

void ATrafficLight::TurnOffOrangeLight() { orange_light->SetVisibility(false);}

void ATrafficLight::TurnOffGreenLight()  { green_light->SetVisibility(false); }

void ATrafficLight::TurnOffWalkerLight() { walker_light->SetLightColor(red_light_color); }

#if WITH_EDITOR
void ATrafficLight::PostEditChangeProperty(struct FPropertyChangedEvent& e)
{
	Super::PostEditChangeProperty(e);

	UWorld* currentWorld = GetWorld();

	if (currentWorld != nullptr && !currentWorld->IsPlayInEditor())
	{
		BeginPlay();
		check_to_apply_changes = false;
	}

}
#endif
