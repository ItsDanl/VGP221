// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSProjectGameMode.h" // must be first
#include "Logging/StructuredLog.h"

void AFPSProjectGameMode::StartPlay()
{
	Super::StartPlay();

	check(GEngine != nullptr);

	// Pointer CHEAT SHEET!

	// 1. Print to screen
	// Display a debug message for five seconds.
	// The -1 "Key" value argument prevents the message from being updated or refreshed.
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Hello World, this is FPSGameMode! This is with editor open - Dan :3"));

	// 2. Print to log
	UE_LOG(LogTemp, Warning, TEXT("Hello World"));

	// 3. Printing values using specifiers
	int TestNumber = 5;
	bool TestBool = true;
	UE_LOG(LogTemp, Warning, TEXT("Test Number: %i, Test Bool: %i"), TestNumber,TestBool);

	// 4. Pointers
	int* TestNumberPtr = &TestNumber; // Memory address of TestNumber
	bool* TestBoolPtr = &TestBool;

	UE_LOG(LogTemp, Warning, TEXT("Test Number Ref: %p, Test Bool Ref: %p"), TestNumberPtr, TestBoolPtr);

	// If we don't use 'p' it will be really large number
	UE_LOG(LogTemp, Warning, TEXT("Test Number Ref: %i, Test Bool Ref: %i"), TestNumberPtr, TestBoolPtr);

	// Derefencing the pointer to get the value it points to
	UE_LOG(LogTemp, Warning, TEXT("Test Number: %i"), *TestNumberPtr);

	// 5. References - Can't be blank
	int& NicknameTestNumber = TestNumber;

	UE_LOG(LogTemp, Warning, TEXT("Test Number: %i"), TestNumber);
	NicknameTestNumber = 10;
	UE_LOG(LogTemp, Warning, TEXT("Test Number: %i"), TestNumber);
	UE_LOG(LogTemp, Warning, TEXT("Test Nickname Number: %i"), NicknameTestNumber);

	// 6. Printing a string
	FString TestString = TEXT("This is a test string"); // Strings ARE tables!!

	UE_LOG(LogTemp, Warning, TEXT("Test String: %s"), *TestString);

	// 7. Structed Logging
	UE_LOGFMT(LogTemp, Warning, "Structured Logging: Test Number: {0}, Test Bool: {1}, Test String: '{2}'", TestNumber, TestBool, TestString);

	// ---------------------------- Crash Test ------------------------------
	int* CrashPointer = nullptr;
	UE_LOG(LogTemp, Warning, TEXT("This is the memory addy: %p"), CrashPointer)
	//UE_LOG(LogTemp, Warning, TEXT("This will crash the engine: %i"), *CrashPointer)
}