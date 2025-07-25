// Copyright Epic Games, Inc. All Rights Reserved.

#include "MagicSystemCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "MagicSystemHud.h"
#include "XMSNodeStaticLibrary.h"
#include "Node/Runnable/XMSProgramNode.h"
#include "Node/Runnable/Instruction/XMSPrintInstructionNode.h"
#include "Node/Runnable/Instruction/XMSVariableSetterNode.h"
#include "Node/Types/Integer/XMSIntegerValueNode.h"
#include "Node/Types/String/XMSStringValueNode.h"
#include "Node/Types/Integer/XMSIntegerProviderNode.h"
#include "Node/Types/String/XMSStringProviderNode.h"
#include "Node/Types/Integer/Variable/XMSIntegerVarGetterNode.h"
#include "Node/Types/Integer/Variable/XMSIntegerVarSetterNode.h"
#include "Spell/XMSSpellActor.h"
#include "SpellEditor/XMSSpellEditorComponent.h"
#include "Blueprint/UserWidget.h"
#include "Node/Runnable/XMSRootInstructionNode.h"
#include "UI/XMSNodeCanvasWidget.h"
#include "UI/SubNode/XMSNodeContainerWidget.h"


DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// AMagicSystemCharacter

AMagicSystemCharacter::AMagicSystemCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)

	SpellEditorComponent = CreateDefaultSubobject<UXMSSpellEditorComponent>(TEXT("SpellEditorComponent"));
}

void AMagicSystemCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	CreateNode();
	CreateWidget();
}

void AMagicSystemCharacter::CreateWidget()
{
	if (!TestNode || !SpellEditorComponent) return;
	
	if (!NodeCanvasWidget)
	{
		NodeCanvasWidget = SpellEditorComponent->CreateNodeCanvas(GetController<APlayerController>(), TestNode);
		if (!NodeCanvasWidget) return;
		GetController<APlayerController>()->GetHUD<AMagicSystemHud>()->NodeCanvasWidget = NodeCanvasWidget;
	}

	if (!NodeCanvasWidget->IsInViewport())
	{
		NodeCanvasWidget->AddToPlayerScreen();
	}
	else
	{
		NodeCanvasWidget->SetFocus();
	}
	NodeCanvasWidget->SetVisibility(ESlateVisibility::Visible);
}

void AMagicSystemCharacter::CreateNode()
{
	TestNode = NewObject<UXMSRootInstructionNode>(this);
	UXMSProgramNode* Program = NewObject<UXMSProgramNode>(this);
	TestNode->Instruction.Set(Program);

	UXMSVariableDeclarationNode* Variable1Declaration = NewObject<UXMSVariableDeclarationNode>(this);
	Program->Instructions.Add(Variable1Declaration);
	UXMSValueTypeValueNode* Variable1Type = NewObject<UXMSValueTypeValueNode>(this);
	Variable1Declaration->VariableType.Set(Variable1Type);
	Variable1Type->SetValueType(XMSValueType::Integer);
	UXMSStringValueNode* Variable1Name = NewObject<UXMSStringValueNode>(this);
	Variable1Declaration->VariableName.Set(Variable1Name);
	Variable1Name->SetString("Pippo");

	UXMSVariableSetterNode* Variable1Setter = NewObject<UXMSVariableSetterNode>(this);
	Program->Instructions.Add(Variable1Setter);
	UXMSIntegerVarSetterNode* Variable1IntegerSetter = NewObject<UXMSIntegerVarSetterNode>(this);
	Variable1Setter->Setter.Set(Variable1IntegerSetter);
	UXMSVariableNameValueNode* Variable1NameGetter = NewObject<UXMSVariableNameValueNode>(this);
	Variable1IntegerSetter->VariableName.Set(Variable1NameGetter);
	Variable1NameGetter->SetName("Pippo"); // 0 is Pippo because it is the first int variable declared
	UXMSIntegerValueNode* Variable1Value = NewObject<UXMSIntegerValueNode>(this);
	Variable1IntegerSetter->IntegerValue.Set(Variable1Value);
	Variable1Value->SetInteger(10);

	UXMSPrintInstructionNode* PrintVariable1 = NewObject<UXMSPrintInstructionNode>(this);
	Program->Instructions.Add(PrintVariable1);
	UXMSIntegerProviderNode* Variable1IntegerProvider = NewObject<UXMSIntegerProviderNode>(this);
	PrintVariable1->OutputString.Set(Variable1IntegerProvider);
	UXMSIntegerVarGetterNode* Variable1IntegerGetter = NewObject<UXMSIntegerVarGetterNode>(this);
	Variable1IntegerProvider->IntegerNode.Set(Variable1IntegerGetter);
	UXMSVariableNameValueNode* Variable1NameGetterP2 = NewObject<UXMSVariableNameValueNode>(this);
	Variable1IntegerGetter->VariableName.Set(Variable1NameGetterP2);
	Variable1NameGetterP2->SetName("Pippo"); // 0 is Pippo because it is the first int variable declared

	UXMSVariableDeclarationNode* Variable2Declaration = NewObject<UXMSVariableDeclarationNode>(this);
	Program->Instructions.Add(Variable2Declaration);
	UXMSValueTypeValueNode* Variable2Type = NewObject<UXMSValueTypeValueNode>(this);
	Variable2Declaration->VariableType.Set(Variable2Type);
	Variable2Type->SetValueType(XMSValueType::Integer);
	UXMSStringValueNode* Variable2Name = NewObject<UXMSStringValueNode>(this);
	Variable2Declaration->VariableName.Set(Variable2Name);
	Variable2Name->SetString("Pluto");

	UXMSVariableSetterNode* Variable2Setter = NewObject<UXMSVariableSetterNode>(this);
	Program->Instructions.Add(Variable2Setter);
	UXMSIntegerVarSetterNode* Variable2IntegerSetter = NewObject<UXMSIntegerVarSetterNode>(this);
	Variable2Setter->Setter.Set(Variable2IntegerSetter);
	UXMSVariableNameValueNode* Variable2NameGetter = NewObject<UXMSVariableNameValueNode>(this);
	Variable2IntegerSetter->VariableName.Set(Variable2NameGetter);
	Variable2NameGetter->SetName("Pluto"); // 1 is Pluto because it is the second int variable declared
	UXMSIntegerValueNode* Variable2Value = NewObject<UXMSIntegerValueNode>(this);
	Variable2IntegerSetter->IntegerValue.Set(Variable2Value);
	Variable2Value->SetInteger(15);

	UXMSPrintInstructionNode* PrintVariable2 = NewObject<UXMSPrintInstructionNode>(this);
	Program->Instructions.Add(PrintVariable2);
	UXMSIntegerProviderNode* Variable2IntegerProvider = NewObject<UXMSIntegerProviderNode>(this);
	PrintVariable2->OutputString.Set(Variable2IntegerProvider);
	UXMSIntegerVarGetterNode* Variable2IntegerGetter = NewObject<UXMSIntegerVarGetterNode>(this);
	Variable2IntegerProvider->IntegerNode.Set(Variable2IntegerGetter);
	UXMSVariableNameValueNode* Variable2NameGetterP2 = NewObject<UXMSVariableNameValueNode>(this);
	Variable2IntegerGetter->VariableName.Set(Variable2NameGetterP2);
	Variable2NameGetterP2->SetName("Pluto"); // 1 is Pluto because it is the second int variable declared
}

void AMagicSystemCharacter::ExecuteTestNode()
{
	if (TestNode)
	{
		AXMSSpellActor* Spell = GetWorld()->SpawnActorDeferred<AXMSSpellActor>(AXMSSpellActor::StaticClass(), GetActorTransform(), this, this);
		Spell->Instruction.Set(UXMSNodeStaticLibrary::CopyNode<>(Spell, TestNode.Get()));
		Spell->FinishSpawning(GetActorTransform());
	}
}

void AMagicSystemCharacter::SerializeTestNode(const FString& Path)
{
	// Serialize node
	bool bSerializeSuccess;
	TSharedPtr<FJsonObject> NodeJson = TestNode->SerializeToJson(bSerializeSuccess);
	if (!bSerializeSuccess)
	{
		UE_LOG(LogTemp, Warning, TEXT("AMagicSystemCharacter::SerializeTestNode >> Failed to serialize node"));
		return;
	}

	// write to json
	bool bWriteJsonSuccess;
	FString WriteOutMessage;
	UXMSNodeStaticLibrary::WriteJson(Path, NodeJson, bWriteJsonSuccess, WriteOutMessage);
	if (!bWriteJsonSuccess)
	{
		UE_LOG(LogTemp, Warning, TEXT("AMagicSystemCharacter::SerializeTestNode >> Failed to write to json : %s"), *WriteOutMessage);
		return;
	}
	
	UE_LOG(LogTemp, Warning, TEXT("AMagicSystemCharacter::SerializeTestNode >> Sucessfully wrote to json"));

	// Test deserialization
	bool bReadJsonSuccess;
	FString ReadOutMessage;
	TSharedPtr<FJsonObject> NewNodeJson = UXMSNodeStaticLibrary::ReadJson(Path, bReadJsonSuccess, ReadOutMessage);
	if (!bReadJsonSuccess)
	{
		UE_LOG(LogTemp, Warning, TEXT("AMagicSystemCharacter::SerializeTestNode >> Failed to read from json : %s"), *ReadOutMessage);
		return;
	}
	
	UE_LOG(LogTemp, Warning, TEXT("AMagicSystemCharacter::SerializeTestNode >> Running TestNodeDeserialized ..."));
	AXMSSpellActor* Spell = GetWorld()->SpawnActorDeferred<AXMSSpellActor>(AXMSSpellActor::StaticClass(), GetActorTransform(), this, this);

	UXMSRootInstructionNode* DeserializedNode = NewObject<UXMSRootInstructionNode>(Spell);
	DeserializedNode->DeserializeFromJson(NewNodeJson);
	Spell->Instruction.Set(DeserializedNode);
	
	Spell->FinishSpawning(GetActorTransform());
}

void AMagicSystemCharacter::CollectGarbage()
{
	if (GEngine)
	{
		GEngine->ForceGarbageCollection();
	}
}

//////////////////////////////////////////////////////////////////////////
// Input

void AMagicSystemCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
	
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMagicSystemCharacter::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AMagicSystemCharacter::Look);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void AMagicSystemCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	
		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AMagicSystemCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}