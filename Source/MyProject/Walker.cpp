///
///Created by Jesus pokoidevVillar, jesusferminvillar@gmail.com (www.pokoidev.com) 
/// Copyright © 2019 Pokoidev. Creative Commons License:
/// Attribution 4.0 International (CC BY 4.0)
///

#include "Walker.h"

AWalker::AWalker() 
{
	//Create the mesh
	mesh = CreateDefaultSubobject<USkeletalMeshComponent>("Mesh");
	
	//Organize the hierarchy
	mesh->AttachToComponent(box_collider, FAttachmentTransformRules::SnapToTargetIncludingScale);

}

void AWalker::BeginPlay()
{
	Super::BeginPlay();
	mesh->SetPosition(FMath::RandRange(0.0f, 1.0f));

}

void AWalker::HurryUp()
{
	current_speed *= speed_modificator;	
}

void AWalker::Relax()
{
	current_speed = initial_speed;
}

