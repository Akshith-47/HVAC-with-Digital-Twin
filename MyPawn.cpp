// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPawn.h"
#include "MyProject3/WebSocketGameInstance.h"

// Sets default values
AMyPawn::AMyPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	MeshComponent->SetupAttachment(GetRootComponent());
	GhostMesh = CreateDefaultSubobject<UStaticMesh>(TEXT("GhostMesh0"));
	GhostMesh1 = CreateDefaultSubobject<UStaticMesh>(TEXT("GhostMesh1"));
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	FollowCamera = CreateDefaultSubobject<UCameraComponent>("Camera");
	RootComponent = MeshComponent;
	_RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	CameraBoom->SetupAttachment(MeshComponent);
	FollowCamera->SetupAttachment(CameraBoom);
	//OnClicked.AddUniqueDynamic(this, &AAirConditioner::OnSelected);
	static ConstructorHelpers::FObjectFinder<UStaticMesh>MeshAsset(TEXT("/Game/AirConditioningPack/Meshes/SM_AC_Int_Wall_On"));
	if (MeshAsset.Succeeded())
	{
		GhostMesh = MeshAsset.Object;
	}
	static ConstructorHelpers::FObjectFinder<UStaticMesh>MeshAsset1(TEXT("/Game/AirConditioningPack/Meshes/SM_AC_Int_Wall_Off"));
	if (MeshAsset.Succeeded())
	{
		GhostMesh1 = MeshAsset1.Object;
	}
}

// Called when the game starts or when spawned
void AMyPawn::BeginPlay()
{
	Super::BeginPlay();


}

// Called every frame
void AMyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UWebSocketGameInstance* GameInstance = Cast<UWebSocketGameInstance>(GetGameInstance());
	if (GameInstance)
	{
		//GameInstance->c = 1;
		if (GameInstance->c == 1)
		{
			//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Cyan, "Ac is ON: " + GameInstance->c);
			//UStaticMesh* Asset = MeshAsset.Object;
			MeshComponent->SetStaticMesh(GhostMesh);
			//FString AssetPathName = "/Content/AirConditioningPack/Meshes/SM_AC_Int_Wall_On.uasset";
			//AMyPawn::MeshComponent->SetStaticMesh(Cast<UStaticMesh>(StaticLoadObject(USkeletalMesh::StaticClass(), NULL, *AssetPathName)));

			//static ConstructorHelpers::FObjectFinder<UStaticMesh>MeshAsset(TEXT("/Content/AirConditioningPack/Meshes/SM_AC_Int_Wall_On.uasset"));
			//UStaticMesh* Asset = MeshAsset.Object;

			//GhostMesh->SetStaticMesh(Asset);
		}
		else if (GameInstance->c == 0)
		{
			MeshComponent->SetStaticMesh(GhostMesh1);
		}
	}


}
/*void AMyPawn::Press()
{
	FString AssetPathName = "/Content/AirConditioningPack/Meshes/SM_AC_Int_Wall_On.uasset";
	AMyPawn::MeshComponent->SetStaticMesh(Cast<UStaticMesh>(StaticLoadObject(USkeletalMesh::StaticClass(), NULL, *AssetPathName)));
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, "Pressed");
	UE_LOG(LogTemp, Warning, TEXT("Press"));
}*/


// Called to bind functionality to input
void AMyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	//PlayerInputComponent->BindAction("Press", IE_Pressed, this, &AMyPawn::Press);

}


