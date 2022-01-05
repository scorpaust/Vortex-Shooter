// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"


UENUM(BlueprintType)
enum class EItemRarity : uint8 {
	
	EIR_Damaged UMETA(DisplayName: "Damaged"),

	EIR_Common UMETA(DisplayName: "Common"),

	EIR_Uncommon UMETA(DisplayName: "Uncommon"),

	EIR_Rare UMETA(DisplayName: "Rare"),

	EIR_Legendary UMETA(DisplayName: "Legendary"),

	EIR_Max UMETA(DisplayName: "DefaultMax")
};

UENUM(BlueprintType)
enum class EItemState : uint8 
{

	EIS_Pickup UMETA(DisplayName: "Pickup"),

	EIS_EquipInterping UMETA(DisplayName: "EquipInterping"),

	EIS_PickedUp UMETA(DisplayName: "PickedUp"),

	EIS_Equipped UMETA(DisplayName: "Equipped"),

	EIS_Falling UMETA(DisplayName: "Falling"),

	EIS_Max UMETA(DisplayName: "DefaultMax")
};

UENUM(BlueprintType)
enum class EItemType : uint8 
{
	EIT_Ammo UMETA(DisplayName: "Ammo"),
	EIT_Weapon UMETA(DisplayName: "Weapon"),
	EIT_Max UMETA(DisplayName: "DefaultMax")
};

UCLASS()
class VORTEXSHOOTER_API AItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/** Called when overlapping area sphere */
	UFUNCTION()
	void OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	/** Called when end overlapping area sphere */
	UFUNCTION()
	void OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	/** Sets the active stars array of bools based on rarity */
	void SetActiveStars();

	/** Sets properties of the item's components based on state */
	virtual void SetItemProperties(EItemState State);

	/** Called when item interp timer is finished */
	void FinishInterping();

	/** Handles item interpolation within the equip interping state */
	void ItemInterp(float DeltaTime);

	/** Get interp location based on the item type */
	FVector GetInterpLocation();

	void PlayPickupSound(bool bForcePlaySound = false);

	virtual void InitializeCustomDepth();

	virtual void OnConstruction(const FTransform& transform) override;

	void EnableGlowMaterial();

	void UpdatePulse();

	void ResetPulseTimer();

	void StartPulseTimer();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	/** Skeletal mesh for the item */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item Properties", meta = (AllowPrivateAccess = true))
	USkeletalMeshComponent* ItemMesh;

	/** Line trace collides with box to show HUD widgets */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Properties", meta = (AllowPrivateAccess = true))
	class UBoxComponent* CollisionBox;

	/** Popup widget for when the player looks at the item */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Properties", meta = (AllowPrivateAccess = true))
	class UWidgetComponent* PickupWidget;

	/** Enables item tracing when overlapped */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Properties", meta = (AllowPrivateAccess = true))
	class USphereComponent* AreaSphere;

	/** Name that appears on the pickup widget */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Properties", meta = (AllowPrivateAccess = true))
	FString ItemName;

	/** Item Count (Ammo...etc...) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Properties", meta = (AllowPrivateAccess = true))
	int32 ItemCount;

	FGuid ID;

	/** Item rarity determines number of stars in pickup widget */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Properties", meta = (AllowPrivateAccess = true))
	EItemRarity ItemRarity;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item Properties", meta = (AllowPrivateAccess = true))
	TArray<bool> ActiveStars;

	/** State of the item */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item Properties", meta = (AllowPrivateAccess = true))
	EItemState ItemState;

	/** The curve asset to use for the item's z location when interping */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item Properties", meta = (AllowPrivateAccess = true))
	class UCurveFloat* ItemZCurve;

	/** Starting location when interping begins */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item Properties", meta = (AllowPrivateAccess = true))
	FVector ItemInterpStartLocation;

	/** Target interp location in front of the camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item Properties", meta = (AllowPrivateAccess = true))
	FVector CameraTargetLocation;

	/** True when interping */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item Properties", meta = (AllowPrivateAccess = true))
	bool bInterping;

	/** Plays when we start interping */
	FTimerHandle ItemInterpTimer;

	/** Duration of the curve and timer */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item Properties", meta = (AllowPrivateAccess = true))
	float ZCurveTime;

	/** Pointer to the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item Properties", meta = (AllowPrivateAccess = true))
	class AShooterCharacter* Character;

	/** X and Y for the item while interping in the equip interping state */
	float ItemInterpX;

	float ItemInterpY;

	/** Initial yaw offset between the camera and the interping item */
	float InterpInitialYawOffset;

	/** Curve used to scale the item when interping */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item Properties", meta = (AllowPrivateAccess = true))
	UCurveFloat* ItemScaleCurve;

	/** Sound played when the item is picked up */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Properties", meta = (AllowPrivateAccess = true))
	class USoundCue* PickupSound;

	/** Sound played when the item is equipped */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Properties", meta = (AllowPrivateAccess = true))
	class USoundCue* EquipSound;

	/** Enum for the type of item this item is */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Properties", meta = (AllowPrivateAccess = true))
	EItemType ItemType;

	/** Index of the interp location this item is interping to */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item Properties", meta = (AllowPrivateAccess = true))
	int32 InterpLocIndex;

	/** Index for the material we would like to change at runtime */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Properties", meta = (AllowPrivateAccess = true))
	int32 MaterialIndex;

	/** Dynamic instance that we can change at runtime */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item Properties", meta = (AllowPrivateAccess = true))
	UMaterialInstanceDynamic* DynamicMaterialInstance;

	/** Material instance used with the dynamic material instance */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Properties", meta = (AllowPrivateAccess = true))
	UMaterialInstance* MaterialInstance;

	bool bCanChangeCustomDepth;

	/** Curve to drive the dynamic material parameters */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item Properties", meta = (AllowPrivateAccess = true))
	class UCurveVector* PulseCurve;

	/** Curve to drive the dynamic material parameters */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item Properties", meta = (AllowPrivateAccess = true))
	UCurveVector* InterpPulseCurve;

	FTimerHandle PulseTimer;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item Properties", meta = (AllowPrivateAccess = true))
	float PulseCurveTime;

	UPROPERTY(VisibleAnywhere, Category = "Item Properties", meta = (AllowPrivateAccess = true))
	float GlowAmount;

	UPROPERTY(VisibleAnywhere, Category = "Item Properties", meta = (AllowPrivateAccess = true))
	float FresnelExponent;

	UPROPERTY(VisibleAnywhere, Category = "Item Properties", meta = (AllowPrivateAccess = true))
	float FresnelReflectFraction;

	/** Background in this item for the inventory */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory", meta = (AllowPrivateAccess = true))
	UTexture2D* IconBackground;

	/** Icon for this item in the inventory */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory", meta = (AllowPrivateAccess = true))
	UTexture2D* IconItem;

	/** Ammo icon for this item in the inventory */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory", meta = (AllowPrivateAccess = true))
	UTexture2D* AmmoIcon;

	/** Slot in the inventory array */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory", meta = (AllowPrivateAccess = true))
	int32 SlotIndex;

	/** True when the character's inventory is full */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory", meta = (AllowPrivateAccess = true))
	bool bCharacterInventoryFull;

public:

	FORCEINLINE UWidgetComponent* GetPickupWidget() const { return PickupWidget; }

	FORCEINLINE FGuid GetGuid() const { return ID; }

	FORCEINLINE USphereComponent* GetAreaSphere() const { return AreaSphere; }

	FORCEINLINE UBoxComponent* GetCollisionBox() const { return CollisionBox; }

	FORCEINLINE EItemState GetItemState() const { return ItemState;  }

	FORCEINLINE USkeletalMeshComponent* GetItemMesh() const { return ItemMesh; }

	FORCEINLINE USoundCue* GetPickupSound() const { return PickupSound; }

	FORCEINLINE USoundCue* GetEquipSound() const { return EquipSound; }

	FORCEINLINE int32 GetItemCount() const { return ItemCount;  }

	FORCEINLINE int32 GetSlotIndex() const { return SlotIndex; }

	FORCEINLINE void SetSlotIndex(int32 Index) { SlotIndex = Index; }

	FORCEINLINE void SetCharacter(AShooterCharacter* Char) { Character = Char; }

	FORCEINLINE void SetCharacterInventoryFull(bool bFull) { bCharacterInventoryFull = bFull; }

	void SetItemState(EItemState State);

	/** Called from the AShooterCharacter class */
	void StartItemCurve(AShooterCharacter* Char, bool bForcePlaySound = false);

	/** Called in AShooterCharacter  */
	void PlayEquipSound(bool bForcePlaySound = false);

	virtual void EnableCustomDepth();

	virtual void DisableCustomDepth();

	void DisableGlowMaterial();

};
