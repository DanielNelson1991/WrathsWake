// Text.h: interface for the CText class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TEXT_H__E78C250F_6677_4D5D_A8DF_1535A7265EBE__INCLUDED_)
#define AFX_TEXT_H__E78C250F_6677_4D5D_A8DF_1535A7265EBE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CText  
{
public:
	CText();
	virtual ~CText();
	static void RenderBitmapString(float x, float y,  char *string); 
	static void Render2DImage(float x_,float y_, float w_,float h_,float textureID_);
};

#endif // !defined(AFX_TEXT_H__E78C250F_6677_4D5D_A8DF_1535A7265EBE__INCLUDED_)
