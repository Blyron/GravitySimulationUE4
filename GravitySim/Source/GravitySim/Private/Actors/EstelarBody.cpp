// Fill out your copyright notice in the Description page of Project Settings.

#include "Actors/EstelarBody.h"
#include "..\..\Public\Actors\EstelarBody.h"

// Sets default values
AEstelarBody::AEstelarBody()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Arrow = CreateDefaultSubobject<UArrowComponent>("Arrow");
	RootComponent = Mesh;
	Arrow->SetupAttachment(Mesh);

}

// Called when the game starts or when spawned
void AEstelarBody::BeginPlay()
{
	Super::BeginPlay();
	Init();
}

// Called every frame
void AEstelarBody::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector nextColor = Mesh->GetComponentVelocity();
	Arrow->SetWorldRotation(nextColor.Rotation());
	nextColor += FVector(1);
	nextColor.X /= 2;
	nextColor.Y /= 2;
	nextColor.Z /= 2;
	nextColor += FVector(1);
	material_->SetVectorParameterValue("BaseColor", nextColor);

	//UE4 works in cm , but velocity is m/s 
	// m/s * 100cm / 1m = 100cm/s
	
}

void AEstelarBody::AddGravitationalForce(FVector forceToAdd) {
	Mesh->AddForce(forceToAdd);
}

float AEstelarBody::GetMass()
{
	return Mesh->GetMass();
}

void AEstelarBody::Init()
{
	Mesh->SetSimulatePhysics(true);
	Mesh->SetEnableGravity(false);
	float tmass = Mesh->GetMass();
	tmass = tmass / (4 * PI * density);
	radius = pow(tmass, 1.0f / 3.0f);

	SetActorScale3D(FVector(2 * radius));

	AddGravitationalForce(initialForce);
	material_ = UMaterialInstanceDynamic::Create(material, this);
	Mesh->SetMaterial(0, material_);
	material_->SetScalarParameterValue("AffectsFields", affectedByGravitatoryFields);
	material_->SetVectorParameterValue("BaseColor", initialForce);
	Arrow->SetHiddenInGame(!affectedByGravitatoryFields);
}

