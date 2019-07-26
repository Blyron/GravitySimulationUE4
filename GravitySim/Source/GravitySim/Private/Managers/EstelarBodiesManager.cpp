// Fill out your copyright notice in the Description page of Project Settings.


#include "EstelarBodiesManager.h"
#include "EngineUtils.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AEstelarBodiesManager::AEstelarBodiesManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEstelarBodiesManager::BeginPlay()
{
	TArray<AActor*> aux;
	Super::BeginPlay();
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEstelarBody::StaticClass(), aux);
	for (int i = 0; i < aux.Num(); ++i) {
		AEstelarBody* bodyToAdd = nullptr;
		bodyToAdd = Cast<AEstelarBody>(aux[i]);
		if (bodyToAdd->IsValidLowLevelFast()){
			bodies.Add(bodyToAdd);
		}
	}
}

// Called every frame
void AEstelarBodiesManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	for (int i = 0; i < bodies.Num(); ++i) {
		for (int j = 0; j < bodies.Num(); ++j) {
			if (i != j && bodies[i]->affectedByGravitatoryFields) {
				FVector distancebBodies = bodies[j]->GetActorLocation() - bodies[i]->GetActorLocation();
				double forcePower = 6.6738480 * pow(10, -11);
				//GEngine->AddOnScreenDebugMessage(-1, 2.0, FColor::Red, FString::Printf(TEXT("Force x: %LF, Vector Size y: %d"), forcePower, distancebBodies.Size()));
				forcePower = forcePower * bodies[i]->GetMass() * bodies[j]->GetMass();
				//GEngine->AddOnScreenDebugMessage(-1, 2.0, FColor::Red, FString::Printf(TEXT("Force x: %f, Vector Size y: %f"), forcePower, distancebBodies.Size()));
				forcePower = forcePower / ((distancebBodies.Size() / 2.0) *  (distancebBodies.Size() / 2.0));

				FVector forceAdder = distancebBodies * forcePower * forceMultiplier;
				
				bodies[i]->AddGravitationalForce(forceAdder);
			}
		}
	}

}

