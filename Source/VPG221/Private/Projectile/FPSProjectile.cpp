// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile/FPSProjectile.h"

// Sets default values
AFPSProjectile::AFPSProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent")); // Add component "Instantiate"
	CollisionComponent->InitSphereRadius(15.0f);
	CollisionComponent->BodyInstance.SetCollisionProfileName(TEXT("Projectile"));
	CollisionComponent->OnComponentHit.AddDynamic(this, &AFPSProjectile::OnHitCalled);
	RootComponent = CollisionComponent;

	ProjectileMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMeshComponent"));

	// 1. Get asset from UE
	//static ConstructorHelpers::FObjectFinder<UStaticMesh> ProjectileMeshAsset(TEXT("/Engine/BasicShapes/Sphere"));

	// 2. Get asset we imported or made
	static ConstructorHelpers::FObjectFinder<UStaticMesh> ProjectileMeshAsset(TEXT("/Game/Models/Sphere.Sphere")); // Copy Object Path

	if (ProjectileMeshAsset.Succeeded()) {
		ProjectileMeshComponent->SetStaticMesh(ProjectileMeshAsset.Object);
	} // World's most complicated WaitForChild()

	// 3. Set up material using only C++
	static ConstructorHelpers::FObjectFinder<UMaterial> ProjectileMaterialAsset(TEXT("/Game/Material/M_Projectile.M_Projectile"));
	if (ProjectileMaterialAsset.Succeeded()) {
		ProjectileMeshComponent->SetMaterial(0, ProjectileMaterialAsset.Object);
	}

	ProjectileMeshComponent->SetRelativeScale3D(FVector(0.09f, 0.09f, 0.09f));
	ProjectileMeshComponent->SetupAttachment(RootComponent);

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovementComponent->SetUpdatedComponent(CollisionComponent);
	ProjectileMovementComponent->InitialSpeed = BulletSpeed;
	ProjectileMovementComponent->MaxSpeed = BulletSpeed;
	ProjectileMovementComponent->bRotationFollowsVelocity = true;
	ProjectileMovementComponent->bShouldBounce = true;
	ProjectileMovementComponent->Bounciness = 0.3f;
	ProjectileMovementComponent->ProjectileGravityScale = 0.0f; // No gravity

	InitialLifeSpan = 3.0f; // Debris()
}

// Called when the game starts or when spawned
void AFPSProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFPSProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFPSProjectile::FireInDirection(const FVector& ShootDirection)
{
	// 1. FVector ShootDirection: Pass by value, least efficient. Makes copy of vector.
	// 2. FVector* ShootDirection: Pass by pointer, efficient but can be null.
	// 3. FVector& ShootDirection: Pass by reference, efficience since it refers to memory address. No dereferencing, no null - can manipulate
	// 4. const FVector& ShootDirection: Pass by const reference, cannot modify the original vector. Read only.
	// 
	//ShootDirection->GetAbs(); *
	//ShootDirection.GetAbs(); &
	ProjectileMovementComponent->Velocity = ShootDirection * ProjectileMovementComponent->InitialSpeed;
}

void AFPSProjectile::OnHitCalled(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	// If physics, add impulse then destroy projectile
	if (OtherActor != this && OtherComponent->IsSimulatingPhysics()) {
		OtherComponent->AddImpulseAtLocation(ProjectileMovementComponent->Velocity * 100.0f, Hit.ImpactPoint);
		Destroy();
	}

	UE_LOG(LogTemp, Warning, TEXT("Projectile hit: %s"), *OtherActor->GetName());
}
