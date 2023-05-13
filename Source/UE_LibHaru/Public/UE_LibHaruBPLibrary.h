// Copyright Epic Games, Inc. All Rights Reserved.

/*
* LibHaru Source Code
* https://github.com/libharu/libharu
*/

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"

#ifdef _WIN64
THIRD_PARTY_INCLUDES_START
#include "hpdf.h"
THIRD_PARTY_INCLUDES_END
#endif

#include "Extended_Enums.h"

#include "UE_LibHaruBPLibrary.generated.h"

UCLASS(BlueprintType)
class UE_LIBHARU_API ULibHaruDoc : public UObject
{
	GENERATED_BODY()

public:

#ifdef _WIN64
	HPDF_Doc Document;
#endif
};

UCLASS(BlueprintType)
class UE_LIBHARU_API ULibHaruFont : public UObject
{
	GENERATED_BODY()

public:

#ifdef _WIN64
	HPDF_Font Font;
#endif
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FDelegateLibharu, bool, bIsSuccessfull, FString, OutCode);

UCLASS()
class UUE_LibHaruBPLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()


	UFUNCTION(BlueprintCallable, meta = (DisplayName = "LibHaru - Create Document", ToolTip = "", Keywords = "libharu, pdf, create, doc, document"), Category = "PDF_Reader|LibHaru|Write")
	static bool LibHaru_Create_Doc(ULibHaruDoc*& Out_PDF);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "LibHaru - Add Pages", ToolTip = "", Keywords = "libharu, pdf, add, doc, document, page, pages"), Category = "PDF_Reader|LibHaru|Write")
	static bool LibHaru_Add_Pages(UPARAM(ref)ULibHaruDoc*& In_PDF, TArray<FVector2D> Pages, bool bInsertInstead, int32 InsertAfter);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "LibHaru - Load Standart Font", Keywords = "libharu, pdf, load, font, standart"), Category = "PDF_Reader|LibHaru|Write")
	static bool LibHaru_Load_Font_Standart(ULibHaruFont*& Out_Font, UPARAM(ref)ULibHaruDoc*& In_PDF, EStandartFonts Font_Name = EStandartFonts::Helvetica, EFontEncodings Font_Encoding = EFontEncodings::STANDARD);

	/*
	* @param Position X value starts from left, Y value starts from bottom.
	*/
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "LibHaru - Add Texts", Keywords = "libharu, pdf, create, doc, document, add, texts"), Category = "PDF_Reader|LibHaru|Write")
	static void LibHaru_Add_Texts(FDelegateLibharu DelegateAddObject, UPARAM(ref)ULibHaruDoc*& In_PDF, UPARAM(ref)ULibHaruFont*& In_Font, FString In_Texts, FLinearColor Text_Color = FLinearColor::Black, FVector2D Position = FVector2D(0.0f, 0.0f), FVector2D Size = FVector2D(1.0f, 1.0f), FVector2D Rotation = FVector2D(0.0f, 0.0f), FVector2D Border = FVector2D(10.0f, 10.0f), int32 FontSize = 12, int32 PageIndex = 0);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "LibHaru - Add Image", ToolTip = "", Keywords = "libharu, pdf, add, doc, document, image, images"), Category = "PDF_Reader|LibHaru|Write")
	static bool LibHaru_Add_Image(UPARAM(ref)ULibHaruDoc*& In_PDF, UTexture2D* Target_Image, FVector2D Position, int32 Page_Index);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "LibHaru - Save PDF", ToolTip = "", Keywords = "libharu, pdf, doc, document, save"), Category = "PDF_Reader|LibHaru|Write")
	static bool LibHaru_Save_PDF(UPARAM(ref)ULibHaruDoc*& In_PDF, FString Export_Path);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "LibHaru - Save as Bytes", ToolTip = "", Keywords = "libharu, pdf, doc, document, save, as, bytes"), Category = "PDF_Reader|LibHaru|Write")
	static bool LibHaru_Save_As_Bytes(UPARAM(ref)ULibHaruDoc*& In_PDF, TArray<uint8>& Export_Bytes);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "LibHaru - Close Document", ToolTip = "", Keywords = "libharu, pdf, doc, document, close"), Category = "PDF_Reader|LibHaru|System")
	static bool LibHaru_Close_Document(UPARAM(ref)ULibHaruDoc*& In_PDF);
};
