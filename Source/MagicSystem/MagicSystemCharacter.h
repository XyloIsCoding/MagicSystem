// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "InstancedStruct.h"
#include "XMSTypes.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "SpellEditor/XMSSpellEditorInterface.h"
#include "MagicSystemCharacter.generated.h"

class UXMSProgramNode;
class UXMSStringProviderNode;
class IXMSIntegerProviderNodeInterface;
class UXMSNode;
class UXMSStringValueNode;
class UXMSValueNode;
class IXMSStringValueNodeInterface;
class UXMSPrintInstructionNode;
class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config=Game)
class AMagicSystemCharacter : public ACharacter, public IXMSSpellEditorInterface
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;
	
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

public:
	AMagicSystemCharacter();
	

protected:

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);
			

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	// To add mapping context
	virtual void BeginPlay();

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
	
	

	
	UPROPERTY()
	TObjectPtr<UXMSProgramNode> TestNode;
	UPROPERTY()
	TObjectPtr<UXMSProgramNode> TestNodeDeserialized;

	UFUNCTION(BlueprintCallable)
	void CreateNode();
	
	UFUNCTION(BlueprintCallable)
	void ExecuteTestNode();

	UFUNCTION(BlueprintCallable)
	void SerializeTestNode(const FString& Path);

	UFUNCTION(BlueprintCallable)
	void CollectGarbage();

public:
	virtual UXMSSpellEditorComponent* GetSpellEditorComponent() override { return SpellEditorComponent; }
protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr<UXMSSpellEditorComponent> SpellEditorComponent;

}; 

