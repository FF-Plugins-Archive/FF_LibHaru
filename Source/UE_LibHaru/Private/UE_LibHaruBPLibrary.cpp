// Copyright Epic Games, Inc. All Rights Reserved.

#include "UE_LibHaruBPLibrary.h"
#include "UE_LibHaru.h"

// UE Includes.
#include "Kismet/KismetStringLibrary.h"
#include "ImageUtils.h"
#include "Engine/TextureRenderTarget2D.h"

THIRD_PARTY_INCLUDES_START
#include <iostream>
#include <sstream>
// LibHaru Includes
#include "hpdf_u3d.h"
THIRD_PARTY_INCLUDES_END

FString Dec_To_Hex(HPDF_STATUS Result)
{
	std::stringstream ss;
	ss << std::hex << Result;
	std::string String(ss.str());

	return String.c_str();
}

UUE_LibHaruBPLibrary::UUE_LibHaruBPLibrary(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{

}

bool UUE_LibHaruBPLibrary::LibHaru_Create_Doc(ULibHaruDoc*& Out_PDF)
{
	HPDF_Doc PDF_Document = HPDF_New(NULL, NULL);
	PDF_Document->pdf_version = HPDF_VER_17;
	
	HPDF_SetCompressionMode(PDF_Document, HPDF_COMP_NONE);
	HPDF_SetPageMode(PDF_Document, HPDF_PAGE_MODE_USE_OUTLINE);
	HPDF_UseUTFEncodings(PDF_Document);
	HPDF_SetCurrentEncoder(PDF_Document, "UTF-8");

	ULibHaruDoc* LibHaru_Object = NewObject<ULibHaruDoc>();
	LibHaru_Object->Document = PDF_Document;
	
	Out_PDF = LibHaru_Object;

	return true;
}

bool UUE_LibHaruBPLibrary::LibHaru_Add_Pages(UPARAM(ref)ULibHaruDoc*& In_PDF, TArray<FVector2D> Pages, bool bInsertInstead, int32 InsertAfter)
{
	if (IsValid(In_PDF) == false)
	{
		return false;
	}

	if (!In_PDF->Document)
	{
		return false;
	}

	HPDF_Page Start_Page = NULL;

	if (bInsertInstead == true)
	{
		Start_Page = HPDF_GetPageByIndex(In_PDF->Document, InsertAfter);
	}

	for (int32 Index_Pages = 0; Index_Pages < Pages.Num(); Index_Pages++)
	{
		HPDF_Page New_Page;

		if (bInsertInstead == true)
		{
			
			New_Page = HPDF_InsertPage(In_PDF->Document, Start_Page);
		}

		else
		{
			New_Page = HPDF_AddPage(In_PDF->Document);
		}

		HPDF_Page_SetWidth(New_Page, Pages[Index_Pages].X);
		HPDF_Page_SetHeight(New_Page, Pages[Index_Pages].Y);
	}

	return true;
}

bool UUE_LibHaruBPLibrary::LibHaru_Load_Font_Standart(ULibHaruFont*& Out_Font, UPARAM(ref)ULibHaruDoc*& In_PDF, EStandartFonts Font_Name, EFontEncodings Font_Encoding)
{
	if (IsValid(In_PDF) == false)
	{
		return false;
	}

	if (!In_PDF->Document)
	{
		return false;
	}

	FString Name_String;
	switch (Font_Name)
	{
	case EStandartFonts::Helvetica:
		Name_String = "Helvetica";
		break;
	case EStandartFonts::Helvetica_Italic:
		Name_String = "Helvetica-Italic";
		break;
	case EStandartFonts::Helvetica_Bold:
		Name_String = "Helvetica-Bold";
		break;
	case EStandartFonts::Helvetica_BoldItalic:
		Name_String = "Helvetica-BoldItalic";
		break;
	case EStandartFonts::Times_Roman:
		Name_String = "Times-Roman";
		break;
	case EStandartFonts::Times_Bold:
		Name_String = "Times-Bold";
		break;
	case EStandartFonts::Times_BoldItalic:
		Name_String = "Times-BoldItalic";
		break;
	case EStandartFonts::Times_Italic:
		Name_String = "Times-Italic";
		break;
	case EStandartFonts::Courier:
		Name_String = "Courier";
		break;
	case EStandartFonts::Courier_Bold:
		Name_String = "Courier-Bold";
		break;
	case EStandartFonts::Courier_Oblique:
		Name_String = "Courier-Oblique";
		break;
	case EStandartFonts::Courier_BoldOblique:
		Name_String = "Courier-BoldOblique";
		break;
	case EStandartFonts::Symbol:
		Name_String = "Symbol";
		break;
	case EStandartFonts::ZapfDingbats:
		Name_String = "ZapfDingbats";
		break;
	default:
		Name_String = "Helvetica";
		break;
	}

	FString Encoding_String;
	switch (Font_Encoding)
	{
	case EFontEncodings::FONT_SPECIFIC:
		Encoding_String = HPDF_ENCODING_FONT_SPECIFIC;
		break;
	case EFontEncodings::STANDARD:
		Encoding_String = HPDF_ENCODING_STANDARD;
		break;
	case EFontEncodings::MAC_ROMAN:
		Encoding_String = HPDF_ENCODING_MAC_ROMAN;
		break;
	case EFontEncodings::WIN_ANSI:
		Encoding_String = HPDF_ENCODING_WIN_ANSI;
		break;
	case EFontEncodings::ISO8859_2:
		Encoding_String = HPDF_ENCODING_ISO8859_2;
		break;
	case EFontEncodings::ISO8859_3:
		Encoding_String = HPDF_ENCODING_ISO8859_3;
		break;
	case EFontEncodings::ISO8859_4:
		Encoding_String = HPDF_ENCODING_ISO8859_4;
		break;
	case EFontEncodings::ISO8859_5:
		Encoding_String = HPDF_ENCODING_ISO8859_5;
		break;
	case EFontEncodings::ISO8859_6:
		Encoding_String = HPDF_ENCODING_ISO8859_6;
		break;
	case EFontEncodings::ISO8859_7:
		Encoding_String = HPDF_ENCODING_ISO8859_7;
		break;
	case EFontEncodings::ISO8859_8:
		Encoding_String = HPDF_ENCODING_ISO8859_8;
		break;
	case EFontEncodings::ISO8859_9:
		Encoding_String = HPDF_ENCODING_ISO8859_9;
		break;
	case EFontEncodings::ISO8859_10:
		Encoding_String = HPDF_ENCODING_ISO8859_10;
		break;
	case EFontEncodings::ISO8859_11:
		Encoding_String = HPDF_ENCODING_ISO8859_11;
		break;
	case EFontEncodings::ISO8859_13:
		Encoding_String = HPDF_ENCODING_ISO8859_13;
		break;
	case EFontEncodings::ISO8859_14:
		Encoding_String = HPDF_ENCODING_ISO8859_14;
		break;
	case EFontEncodings::ISO8859_15:
		Encoding_String = HPDF_ENCODING_ISO8859_15;
		break;
	case EFontEncodings::ISO8859_16:
		Encoding_String = HPDF_ENCODING_ISO8859_16;
		break;
	case EFontEncodings::CP1250:
		Encoding_String = HPDF_ENCODING_CP1250;
		break;
	case EFontEncodings::CP1251:
		Encoding_String = HPDF_ENCODING_CP1251;
		break;
	case EFontEncodings::CP1252:
		Encoding_String = HPDF_ENCODING_CP1252;
		break;
	case EFontEncodings::CP1253:
		Encoding_String = HPDF_ENCODING_CP1253;
		break;
	case EFontEncodings::CP1254:
		Encoding_String = HPDF_ENCODING_CP1254;
		break;
	case EFontEncodings::CP1255:
		Encoding_String = HPDF_ENCODING_CP1255;
		break;
	case EFontEncodings::CP1256:
		Encoding_String = HPDF_ENCODING_CP1256;
		break;
	case EFontEncodings::CP1257:
		Encoding_String = HPDF_ENCODING_CP1257;
		break;
	case EFontEncodings::CP1258:
		Encoding_String = HPDF_ENCODING_CP1258;
		break;
	case EFontEncodings::KOI8_R:
		Encoding_String = HPDF_ENCODING_KOI8_R;
		break;
	default:
		Encoding_String = HPDF_ENCODING_STANDARD;
		break;
	}

	HPDF_Font Font = HPDF_GetFont(In_PDF->Document, TCHAR_TO_UTF8(*Name_String), TCHAR_TO_UTF8(*Encoding_String));
	if (!Font == true)
	{
		return false;
	}

	ULibHaruFont* Font_Object = NewObject<ULibHaruFont>();
	Font_Object->Font = Font;

	Out_Font = Font_Object;

	return true;
}

bool UUE_LibHaruBPLibrary::LibHaru_Load_Font_External(ULibHaruFont*& Out_Font, UPARAM(ref)ULibHaruDoc*& In_PDF, FString In_Path)
{
	if (IsValid(In_PDF) == false)
	{
		return false;
	}

	if (!In_PDF->Document)
	{
		return false;
	}

	if (In_Path.IsEmpty() == true)
	{
		return false;
	}

	FPaths::MakeStandardFilename(In_Path);
	if (FPaths::FileExists(In_Path) == false)
	{
		return false;
	}

	FPaths::MakePlatformFilename(In_Path);

	const char* Font_Chars = HPDF_LoadTTFontFromFile(In_PDF->Document, TCHAR_TO_UTF8(*In_Path), HPDF_TRUE);
	HPDF_Font Font = HPDF_GetFont(In_PDF->Document, Font_Chars, "UTF-8");

	if (!Font == true)
	{
		return false;
	}

	ULibHaruFont* Font_Object = NewObject<ULibHaruFont>();
	Font_Object->Font = Font;

	Out_Font = Font_Object;

	return true;
}

void UUE_LibHaruBPLibrary::LibHaru_Add_Texts(FDelegateLibharu DelegateAddObject, UPARAM(ref)ULibHaruDoc*& In_PDF, UPARAM(ref)ULibHaruFont*& In_Font, FString In_Texts, FLinearColor Text_Color, FVector2D Position, FVector2D Size, FVector2D Rotation, FVector2D Border, int32 FontSize, int32 PageIndex)
{
	if (IsValid(In_PDF) == false)
	{
		DelegateAddObject.Execute(false, "PDF object is not valid.");
	}

	if (!In_PDF->Document)
	{
		DelegateAddObject.Execute(false, "PDF document is not valid.");
	}

	if (In_Texts.IsEmpty() == true)
	{
		DelegateAddObject.Execute(false, "Text is empty.");
	}

	if (IsValid(In_Font) == false)
	{
		DelegateAddObject.Execute(false, "Font object is invalid.");
	}

	if (!In_Font->Font)
	{
		DelegateAddObject.Execute(false, "PDFium font is invalid.");
	}

	AsyncTask(ENamedThreads::AnyBackgroundThreadNormalTask, [DelegateAddObject, In_PDF, In_Font, In_Texts, Text_Color, Position, Size, Rotation, Border, FontSize, PageIndex]()
		{
			HPDF_Page First_Page = HPDF_GetPageByIndex(In_PDF->Document, PageIndex);
			TArray<HPDF_Page> Array_Pages;
			Array_Pages.Add(First_Page);

			int32 Acceptable_Horizontal = 2 * ((HPDF_Page_GetWidth(First_Page) - Position.X - Border.X) / FontSize);
			int32 Acceptable_Vertical = (Position.Y - Border.Y) / FontSize;

			// Generate paragraphs.
			TArray<FString> Array_Paragraphs;
			if (In_Texts.Contains(LINE_TERMINATOR_ANSI) == true)
			{
				Array_Paragraphs = UKismetStringLibrary::ParseIntoArray(In_Texts, LINE_TERMINATOR_ANSI, false);
			}

			else
			{
				Array_Paragraphs.Add(In_Texts);
			}

			// Generate lines for text wrapping.
			TArray<FString> Array_Lines;
			for (int32 Index_Paragraphs = 0; Index_Paragraphs < Array_Paragraphs.Num(); Index_Paragraphs++)
			{
				FString Each_Paragraph = Array_Paragraphs[Index_Paragraphs];

				if (Each_Paragraph.IsEmpty())
				{
					Array_Lines.Add(" ");

					continue;
				}

				if (Each_Paragraph.Len() < Acceptable_Horizontal)
				{
					Array_Lines.Add(Each_Paragraph);

					continue;
				}

				bool bAllowChop = true;
				while (bAllowChop)
				{
					FString Each_Line = UKismetStringLibrary::Left(Each_Paragraph, Acceptable_Horizontal);
					Each_Paragraph = UKismetStringLibrary::RightChop(Each_Paragraph, Acceptable_Horizontal);

					if (UKismetStringLibrary::Left(Each_Line, 2) == "  ")
					{
						Array_Lines.Add(Each_Line.TrimEnd());
					}

					else
					{
						Array_Lines.Add(Each_Line.TrimStartAndEnd());
					}

					if (Each_Paragraph.Len() < Acceptable_Horizontal)
					{
						if (UKismetStringLibrary::Left(Each_Paragraph, 2) == "  ")
						{
							Array_Lines.Add(Each_Paragraph.TrimEnd());
						}

						else
						{
							Array_Lines.Add(Each_Paragraph.TrimStartAndEnd());
						}

						bAllowChop = false;
					}
				}
			}

			// Check if new pages are required or not.
			if (Array_Lines.Num() > Acceptable_Vertical)
			{
				FVector2D Page_Resolution = FVector2D(HPDF_Page_GetWidth(First_Page), HPDF_Page_GetHeight(First_Page));
				int32 Extra_Page_Count = (Array_Lines.Num() / Acceptable_Vertical);
				for (int32 Index_Extra_Page = 0; Index_Extra_Page < Extra_Page_Count; Index_Extra_Page++)
				{
					HPDF_Page New_Page = HPDF_AddPage(In_PDF->Document);
					HPDF_Page_SetWidth(New_Page, Page_Resolution.X);
					HPDF_Page_SetHeight(New_Page, Page_Resolution.Y);
					Array_Pages.Add(New_Page);
				}
			}

			// Generate text objects.
			int32 ActivePage = 0;
			for (int32 Index_Lines = 0; Index_Lines < Array_Lines.Num(); Index_Lines++)
			{
				FString Each_Line = Array_Lines[Index_Lines];
				HPDF_Page Target_Page = Array_Pages[ActivePage];

				HPDF_Page_BeginText(Target_Page);
				HPDF_Page_SetRGBFill(Target_Page, Text_Color.R, Text_Color.G, Text_Color.B);
				HPDF_Page_SetTextRenderingMode(Target_Page, HPDF_FILL);
				HPDF_Page_SetFontAndSize(Target_Page, In_Font->Font, FontSize);
				HPDF_Page_MoveTextPos(Target_Page, Position.X, ((Position.Y * (ActivePage + 1)) - (FontSize * Index_Lines)));
				HPDF_Page_ShowText(Target_Page, TCHAR_TO_UTF8(*Each_Line));
				HPDF_Page_EndText(Target_Page);

				// We need counts not index.
				if (((Index_Lines + 1) / (ActivePage + 1)) == Acceptable_Vertical)
				{
					ActivePage += 1;
				}
			}
			
			AsyncTask(ENamedThreads::GameThread, [DelegateAddObject]()
				{
					DelegateAddObject.ExecuteIfBound(true, "Text objects successfully added.");
				}
			);
		}
	);
}

HPDF_Image PDF_Image_Callback(UPARAM(ref)ULibHaruDoc*& In_PDF, UTexture2D* Target_Image, FColor TransparentColor)
{
	int32 Texture_Width = Target_Image->GetSizeX();
	int32 Texture_Height = Target_Image->GetSizeY();

	FImage Image;
	FImageUtils::GetTexture2DSourceImage(Target_Image, Image);

	TArray<FColor> Array_Colors;
	Array_Colors.SetNum(Texture_Width * Texture_Height);
	FMemory::Memcpy(Array_Colors.GetData(), Image.RawData.GetData(), static_cast<SIZE_T>(Image.RawData.Num()));

	HPDF_BYTE* Buffer = (unsigned char*)malloc(static_cast<size_t>(Array_Colors.Num()) * 3);
	
	for (int32 Index_Colors = 0; Index_Colors < Array_Colors.Num(); Index_Colors++)
	{
		if (Array_Colors[Index_Colors].A == 0)
		{
			Buffer[Index_Colors * 3] = TransparentColor.R;
			Buffer[(Index_Colors * 3) + 1] = TransparentColor.G;
			Buffer[(Index_Colors * 3) + 2] = TransparentColor.B;
		}

		else
		{
			Buffer[Index_Colors * 3] = Array_Colors[Index_Colors].R;
			Buffer[(Index_Colors * 3) + 1] = Array_Colors[Index_Colors].G;
			Buffer[(Index_Colors * 3) + 2] = Array_Colors[Index_Colors].B;
		}
	}

	HPDF_Image PDF_Image = HPDF_LoadRawImageFromMem(In_PDF->Document, Buffer, Texture_Width, Texture_Height, HPDF_ColorSpace::HPDF_CS_DEVICE_RGB, 8);

	return PDF_Image;
}

bool UUE_LibHaruBPLibrary::LibHaru_Add_Image(UPARAM(ref)ULibHaruDoc*& In_PDF, UTexture2D* Target_Image, FColor TransparentColor, FVector2D Position, int32 Page_Index)
{
	if (IsValid(In_PDF) == false)
	{
		return false;
	}

	if (!In_PDF->Document)
	{
		return false;
	}

	if (IsValid(Target_Image) == false)
	{
		return false;
	}

	HPDF_Image PDF_Image = PDF_Image_Callback(In_PDF, Target_Image, TransparentColor);
	HPDF_Page Target_Page = HPDF_GetPageByIndex(In_PDF->Document, Page_Index);
	HPDF_STATUS Result = HPDF_Page_DrawImage(Target_Page, PDF_Image, Position.X, Position.Y, Target_Image->GetSizeX(), Target_Image->GetSizeY());

	if (Result == 0)
	{
		return true;
	}

	else
	{
		return false;
	}
}

bool UUE_LibHaruBPLibrary::LibHaru_Add_U3D(UPARAM(ref)ULibHaruDoc*& In_PDF, FString Model_Path, FVector2D Position, FVector2D Size, int32 Zoom, FLinearColor BG_Color, int32 Page_Index)
{
	if (IsValid(In_PDF) == false)
	{
		return false;
	}

	if (!In_PDF->Document)
	{
		return false;
	}

	FPaths::MakeStandardFilename(Model_Path);
	if (FPaths::FileExists(Model_Path) == false)
	{
		return false;
	}

	FPaths::MakePlatformFilename(Model_Path);

	HPDF_Page Target_Page = HPDF_GetPageByIndex(In_PDF->Document, Page_Index);

	HPDF_U3D U3D_Model = HPDF_LoadU3DFromFile(In_PDF->Document, TCHAR_TO_UTF8(*Model_Path));
	
	HPDF_Rect U3D_Rectangle = { 0,0,0,0 };
	U3D_Rectangle.top = Position.Y;
	U3D_Rectangle.bottom = Position.Y - Size.Y;
	U3D_Rectangle.left = Position.X;
	U3D_Rectangle.right = Position.X + Size.X;
	
	HPDF_Annotation U3D_Annot = HPDF_Page_Create3DAnnot(Target_Page, U3D_Rectangle, HPDF_TRUE, HPDF_FALSE, U3D_Model, NULL);
	HPDF_Dict DefaultView = HPDF_Page_Create3DView(Target_Page, U3D_Model, U3D_Annot, "DefaultView");
	
	HPDF_3DView_SetCamera(DefaultView, 0, 0, 0, 0, 0, 1, 3, 0);
	HPDF_3DView_SetOrthogonalProjection(DefaultView, Zoom);
	
	HPDF_3DView_SetBackgroundColor(DefaultView, BG_Color.R, BG_Color.G, BG_Color.B);
	HPDF_STATUS Result = HPDF_U3D_Add3DView(U3D_Model, DefaultView);

	if (Result != 0)
	{
		return false;
	}

	Result = HPDF_U3D_SetDefault3DView(U3D_Model, "DefaultView");

	if (Result == 0)
	{
		return true;
	}

	else
	{
		return false;
	}
}

bool UUE_LibHaruBPLibrary::LibHaru_Add_Line(UPARAM(ref)ULibHaruDoc*& In_PDF, FVector2D Start, FVector2D End, int32 Width, FLinearColor Line_Color, int32 Page_Index)
{
	if (IsValid(In_PDF) == false)
	{
		return false;
	}

	if (!In_PDF->Document)
	{
		return false;
	}
	
	HPDF_Page Target_Page = HPDF_GetPageByIndex(In_PDF->Document, Page_Index);
	HPDF_Page_SetLineWidth(Target_Page, Width);
	HPDF_Page_SetRGBStroke(Target_Page, Line_Color.R, Line_Color.G, Line_Color.B);
	HPDF_Page_MoveTo(Target_Page, Start.X, Start.Y);
	HPDF_Page_LineTo(Target_Page, End.X, End.Y);
	HPDF_Page_Stroke(Target_Page);
	
	return true;
}

bool UUE_LibHaruBPLibrary::LibHaru_Add_Rectangle(UPARAM(ref)ULibHaruDoc*& In_PDF, FVector2D Location, FVector2D Dimensions, int32 Width, FLinearColor Line_Color, int32 Page_Index)
{
	if (IsValid(In_PDF) == false)
	{
		return false;
	}

	if (!In_PDF->Document)
	{
		return false;
	}

	HPDF_Page Target_Page = HPDF_GetPageByIndex(In_PDF->Document, Page_Index);
	HPDF_Page_SetLineWidth(Target_Page, Width);
	HPDF_Page_SetRGBStroke(Target_Page, Line_Color.R, Line_Color.G, Line_Color.B);
	HPDF_Page_Rectangle(Target_Page, Location.X, Location.Y, Dimensions.X, Dimensions.Y);
	HPDF_Page_Stroke(Target_Page);

	return true;
}

bool UUE_LibHaruBPLibrary::LibHaru_Add_Arc(UPARAM(ref)ULibHaruDoc*& In_PDF, FVector2D Location, FVector2D Angles, double Radius, int32 Width, FLinearColor Line_Color, int32 Page_Index)
{
	if (IsValid(In_PDF) == false)
	{
		return false;
	}

	if (!In_PDF->Document)
	{
		return false;
	}

	HPDF_Page Target_Page = HPDF_GetPageByIndex(In_PDF->Document, Page_Index);
	HPDF_Page_SetLineWidth(Target_Page, Width);
	HPDF_Page_SetRGBStroke(Target_Page, Line_Color.R, Line_Color.G, Line_Color.B);
	HPDF_Page_Arc(Target_Page, Location.X, Location.Y, Radius, Angles.X, Angles.Y);
	HPDF_Page_Stroke(Target_Page);

	return true;
}

bool UUE_LibHaruBPLibrary::LibHaru_Add_Circle(UPARAM(ref)ULibHaruDoc*& In_PDF, FVector2D Location, double Radius, int32 Width, FLinearColor Line_Color, int32 Page_Index)
{
	if (IsValid(In_PDF) == false)
	{
		return false;
	}

	if (!In_PDF->Document)
	{
		return false;
	}

	HPDF_Page Target_Page = HPDF_GetPageByIndex(In_PDF->Document, Page_Index);
	HPDF_Page_SetLineWidth(Target_Page, Width);
	HPDF_Page_SetRGBStroke(Target_Page, Line_Color.R, Line_Color.G, Line_Color.B);
	HPDF_Page_Circle(Target_Page, Location.X, Location.Y, Radius);
	HPDF_Page_Stroke(Target_Page);

	return true;
}

bool UUE_LibHaruBPLibrary::LibHaru_Add_Ellipse(UPARAM(ref)ULibHaruDoc*& In_PDF, FVector2D Location, FVector2D Radii, int32 Width, FLinearColor Line_Color, int32 Page_Index)
{
	if (IsValid(In_PDF) == false)
	{
		return false;
	}

	if (!In_PDF->Document)
	{
		return false;
	}

	HPDF_Page Target_Page = HPDF_GetPageByIndex(In_PDF->Document, Page_Index);
	HPDF_Page_SetLineWidth(Target_Page, Width);
	HPDF_Page_SetRGBStroke(Target_Page, Line_Color.R, Line_Color.G, Line_Color.B);
	HPDF_Page_Ellipse(Target_Page, Location.X, Location.Y, Radii.X, Radii.Y);
	HPDF_Page_Stroke(Target_Page);

	return true;
}

bool UUE_LibHaruBPLibrary::LibHaru_Save_File(UPARAM(ref)ULibHaruDoc*& In_PDF, FString& OutCode, FString Export_Path)
{
	if (IsValid(In_PDF) == false)
	{
		return false;
	}

	if (!In_PDF->Document)
	{
		return false;
	}

	if (Export_Path.IsEmpty() == true)
	{
		return false;
	}

	HPDF_STATUS Result = HPDF_SaveToFile(In_PDF->Document, TCHAR_TO_UTF8(*Export_Path));
	OutCode = Dec_To_Hex(Result);

	if (Result == 0)
	{
		return true;
	}

	else
	{
		return false;
	}
}

bool UUE_LibHaruBPLibrary::LibHaru_Save_Bytes(UPARAM(ref)ULibHaruDoc*& In_PDF, UBytesObject_64*& Out_Bytes)
{
	if (IsValid(In_PDF) == false)
	{
		return false;
	}

	if (!In_PDF->Document)
	{
		return false;
	}
	
	HPDF_STATUS Stream_Status = HPDF_SaveToStream(In_PDF->Document);
	
	// 0 is true for LibHaru.
	if (Stream_Status != 0)
	{
		return false;
	}

	HPDF_UINT32 Buffer_Size = HPDF_GetStreamSize(In_PDF->Document);
	HPDF_BYTE* Buffer = (unsigned char*)malloc(Buffer_Size);
	HPDF_ReadFromStream(In_PDF->Document, Buffer, &Buffer_Size);
	
	TArray64<uint8> Array_Bytes;
	Array_Bytes.SetNum(Buffer_Size);
	FMemory::Memcpy(Array_Bytes.GetData(), Buffer, Buffer_Size);

	UBytesObject_64* BytesObject = NewObject<UBytesObject_64>();
	BytesObject->ByteArray = Array_Bytes;

	Out_Bytes = BytesObject;
	
	return true;
}

bool UUE_LibHaruBPLibrary::LibHaru_Close_Document(UPARAM(ref)ULibHaruDoc*& In_PDF)
{
	if (IsValid(In_PDF) == false)
	{
		return false;
	}

	if (!In_PDF->Document)
	{
		return false;
	}

	HPDF_Free(In_PDF->Document);
	In_PDF = nullptr;

	return true;
}