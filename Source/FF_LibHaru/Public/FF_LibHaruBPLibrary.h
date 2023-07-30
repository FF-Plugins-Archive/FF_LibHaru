// Copyright Epic Games, Inc. All Rights Reserved.

/*
* LibHaru Source Code
* https://github.com/libharu/libharu
*/

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"

THIRD_PARTY_INCLUDES_START
#include "hpdf.h"
THIRD_PARTY_INCLUDES_END

#include "ExtendedVarsBPLibrary.h"

#include "FF_LibHaruBPLibrary.generated.h"

UCLASS(BlueprintType)
class FF_LIBHARU_API ULibHaruDoc : public UObject
{
	GENERATED_BODY()

public:

	HPDF_Doc Document;
};

UCLASS(BlueprintType)
class FF_LIBHARU_API ULibHaruFont : public UObject
{
	GENERATED_BODY()

public:

	HPDF_Font Font;
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FDelegateLibharu, bool, bIsSuccessfull, FString, OutCode);

UCLASS()
class UFF_LibHaruBPLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()


	UFUNCTION(BlueprintCallable, meta = (DisplayName = "LibHaru - Create Document", ToolTip = "", Keywords = "libharu, pdf, create, doc, document"), Category = "LibHaru|Write")
	static bool LibHaru_Create_Doc(ULibHaruDoc*& Out_PDF);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "LibHaru - Add Pages", ToolTip = "", Keywords = "libharu, pdf, add, doc, document, page, pages"), Category = "LibHaru|Write")
	static bool LibHaru_Add_Pages(UPARAM(ref)ULibHaruDoc*& In_PDF, TArray<FVector2D> Pages, bool bInsertInstead, int32 InsertAfter);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "LibHaru - Load Standart Font", Keywords = "libharu, pdf, load, font, standart"), Category = "LibHaru|Write")
	static bool LibHaru_Load_Font_Standart(ULibHaruFont*& Out_Font, UPARAM(ref)ULibHaruDoc*& In_PDF, EStandartFonts Font_Name = EStandartFonts::Helvetica, EFontEncodings Font_Encoding = EFontEncodings::STANDARD);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "LibHaru - Load External Font", Keywords = "libharu, pdf, load, font, external"), Category = "LibHaru|Write")
	static bool LibHaru_Load_Font_External(ULibHaruFont*& Out_Font, UPARAM(ref)ULibHaruDoc*& In_PDF, FString In_Path);

	/*
	* @param Position X value starts from left, Y value starts from bottom.
	*/
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "LibHaru - Add Texts", Keywords = "libharu, pdf, create, doc, document, add, texts"), Category = "LibHaru|Write")
	static void LibHaru_Add_Texts(FDelegateLibharu DelegateAddObject, UPARAM(ref)ULibHaruDoc*& In_PDF, UPARAM(ref)ULibHaruFont*& In_Font, FString In_Texts, FLinearColor Text_Color = FLinearColor::Black, FVector2D Position = FVector2D(0.0f, 0.0f), FVector2D Size = FVector2D(1.0f, 1.0f), FVector2D Rotation = FVector2D(0.0f, 0.0f), FVector2D Border = FVector2D(10.0f, 10.0f), int32 FontSize = 12, int32 PageIndex = 0);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "LibHaru - Add Image", ToolTip = "", Keywords = "libharu, pdf, add, draw, doc, document, image, images"), Category = "LibHaru|Write")
	static bool LibHaru_Add_Image(UPARAM(ref)ULibHaruDoc*& In_PDF, UObject* Target_Image, FColor TransparentColor, FVector2D Position, int32 Page_Index);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "LibHaru - Add U3D Model", ToolTip = "", Keywords = "libharu, pdf, add, draw, doc, document, 3d, model, models, u3d"), Category = "LibHaru|Write")
	static bool LibHaru_Add_U3D(UPARAM(ref)ULibHaruDoc*& In_PDF, FString Model_Path, FVector2D Position, FVector2D Size, int32 Zoom = 1000, FLinearColor BG_Color = FLinearColor::White, int32 Page_Index = 0);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "LibHaru - Add Line", ToolTip = "", Keywords = "libharu, pdf, add, draw, doc, document, line, lines"), Category = "LibHaru|Write")
	static bool LibHaru_Add_Line(UPARAM(ref)ULibHaruDoc*& In_PDF, FVector2D Start, FVector2D End, int32 Width = 1, FLinearColor Line_Color = FLinearColor::Black, int32 Page_Index = 0);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "LibHaru - Add Rectangle", ToolTip = "", Keywords = "libharu, pdf, add, draw, doc, document, rectangle, rectangles"), Category = "LibHaru|Write")
	static bool LibHaru_Add_Rectangle(UPARAM(ref)ULibHaruDoc*& In_PDF, FVector2D Location, FVector2D Dimensions, int32 Width = 1, FLinearColor Line_Color = FLinearColor::Black, int32 Page_Index = 0);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "LibHaru - Add Arc", ToolTip = "", Keywords = "libharu, pdf, add, draw, doc, document, arc, arcs"), Category = "LibHaru|Write")
	static bool LibHaru_Add_Arc(UPARAM(ref)ULibHaruDoc*& In_PDF, FVector2D Location, FVector2D Angles, double Radius, int32 Width = 1, FLinearColor Line_Color = FLinearColor::Black, int32 Page_Index = 0);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "LibHaru - Add Circle", ToolTip = "", Keywords = "libharu, pdf, add, draw, doc, document, circle, circles"), Category = "LibHaru|Write")
	static bool LibHaru_Add_Circle(UPARAM(ref)ULibHaruDoc*& In_PDF, FVector2D Location, double Radius, int32 Width = 1, FLinearColor Line_Color = FLinearColor::Black, int32 Page_Index = 0);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "LibHaru - Add Ellipse", ToolTip = "", Keywords = "libharu, pdf, add, draw, doc, document, ellipse, ellipses"), Category = "LibHaru|Write")
	static bool LibHaru_Add_Ellipse(UPARAM(ref)ULibHaruDoc*& In_PDF, FVector2D Location, FVector2D Radii, int32 Width = 1, FLinearColor Line_Color = FLinearColor::Black, int32 Page_Index = 0);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "LibHaru - Save File", ToolTip = "You can find list of error codes in here. https://github.com/libharu/libharu/wiki/Error-handling", Keywords = "libharu, pdf, doc, document, save"), Category = "LibHaru|Write")
	static bool LibHaru_Save_File(UPARAM(ref)ULibHaruDoc*& In_PDF, FString& OutCode, FString Export_Path);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "LibHaru - Save Bytes", ToolTip = "", Keywords = "libharu, pdf, doc, document, save, as, bytes"), Category = "LibHaru|Write")
	static bool LibHaru_Save_Bytes(UPARAM(ref)ULibHaruDoc*& In_PDF, UBytesObject_64*& Out_Bytes);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "LibHaru - Close Document", ToolTip = "", Keywords = "libharu, pdf, doc, document, close"), Category = "LibHaru|System")
	static bool LibHaru_Close_Document(UPARAM(ref)ULibHaruDoc*& In_PDF);

};