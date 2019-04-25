///
///Created by Jesus pokoidevVillar, jesusferminvillar@gmail.com (www.pokoidev.com) 
/// Copyright © 2019 Pokoidev. Creative Commons License:
/// Attribution 4.0 International (CC BY 4.0)
///

#include "Car.h"

ACar::ACar() 
{
	//Create the mesh
	mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");	

	//Create the lights
	front_right_light = CreateDefaultSubobject<USpotLightComponent>("Front Right Light");
	front_left_light  = CreateDefaultSubobject<USpotLightComponent>("Front Left Light");
	back_right_light  = CreateDefaultSubobject<USpotLightComponent>("Back Right Light");
	back_left_light   = CreateDefaultSubobject<USpotLightComponent>("Back Left Light");

	//Organize the hierarchy
	mesh             ->AttachToComponent(box_collider, FAttachmentTransformRules::SnapToTargetIncludingScale);
	front_right_light->AttachToComponent(mesh, FAttachmentTransformRules::SnapToTargetIncludingScale);
	front_left_light ->AttachToComponent(mesh, FAttachmentTransformRules::SnapToTargetIncludingScale);
	back_right_light ->AttachToComponent(mesh, FAttachmentTransformRules::SnapToTargetIncludingScale);
	back_left_light  ->AttachToComponent(mesh, FAttachmentTransformRules::SnapToTargetIncludingScale);

	//Add the lights to the lists
	front_lights.Add(front_right_light);
	front_lights.Add(front_left_light);
	back_lights.Add(back_right_light);
	back_lights.Add(back_left_light);

}

void ACar::BeginPlay() 
{
	Super::BeginPlay();

	//Add local position to the lights
	front_right_light->SetRelativeLocation(initial_position_front_right_light);
	front_left_light->SetRelativeLocation(initial_position_front_left_light);
	back_right_light->SetRelativeLocation(initial_position_back_right_light);
	back_left_light->SetRelativeLocation(initial_position_back_left_light);

	//Set values of front lights
	for (USpotLightComponent* spot : front_lights)
	{
		spot->SetRelativeRotation(front_lights_rotator);
		spot->SetLightColor(front_lights_color);
		spot->SetIntensity(light_intensity);
		spot->SetInnerConeAngle(lights_inner_cone_angle);
		spot->SetOuterConeAngle(lights_outer_cone_angle);
		spot->SetAttenuationRadius(attenuation_radius);
	}

	//Set values of back lights
	for (USpotLightComponent* spot : back_lights)
	{
		spot->SetRelativeRotation(back_lights_rotator);
		spot->SetLightColor(back_lights_color);
		spot->SetIntensity(light_intensity);
		spot->SetInnerConeAngle(lights_inner_cone_angle);
		spot->SetOuterConeAngle(lights_outer_cone_angle);
		spot->SetAttenuationRadius(attenuation_radius);
	}
}

#if WITH_EDITOR
void ACar::PostEditChangeProperty(struct FPropertyChangedEvent& e)
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


