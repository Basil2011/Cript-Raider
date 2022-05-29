// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabber.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"


// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	UPhysicsHandleComponent *Handle = GetPhyisicsHandle();

	if (Handle == nullptr)
	{
		return;
	}



	FVector TargetL = GetComponentLocation() + GetForwardVector() * HodDist;

	Handle->SetTargetLocationAndRotation(TargetL, GetComponentRotation());

}

void UGrabber::Grab()
{

	UPhysicsHandleComponent* Handle = GetPhyisicsHandle();


if (Handle == nullptr)
{
	return;
}


	FVector start = GetComponentLocation();
	FVector end = start + GetForwardVector() * MGrabDist;
	FHitResult HitR;

	FCollisionShape Shere = FCollisionShape::MakeSphere(GR);
	bool HasHit = GetWorld()->SweepSingleByChannel(HitR, start, end, FQuat::Identity, ECC_GameTraceChannel2, Shere);

	if(HasHit)
	{

		UPrimitiveComponent* HitCompenent = HitR.GetComponent();
		HitCompenent->SetSimulatePhysics(true);
		HitCompenent->WakeAllRigidBodies();
		AActor* HItactor = HitR.GetActor();
		HItactor->Tags.Add("Grabbed");
		HItactor->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		Handle->GrabComponentAtLocationWithRotation(HitCompenent,NAME_None,HitR.ImpactPoint,GetComponentRotation());

		
	}

}



	

void UGrabber::Release()
{

	UPhysicsHandleComponent* PhysicsH = GetPhyisicsHandle();
	if(PhysicsH == nullptr)
	{
		return;
	}

	if(PhysicsH->GetGrabbedComponent() != nullptr)
	{
		AActor* GrabbedA = PhysicsH->GetGrabbedComponent()->GetOwner();
		GrabbedA->Tags.Remove("Grabbed");
		PhysicsH->ReleaseComponent();
	}

}







UPhysicsHandleComponent*  UGrabber::GetPhyisicsHandle() const
{
	return GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	

}






	