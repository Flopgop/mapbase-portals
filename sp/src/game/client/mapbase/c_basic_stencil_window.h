#ifndef C_BASIC_STENCIL_WINDOW_H
#define C_BASIC_STENCIL_WINDOW_H

#include "cbase.h"

class C_BasicStencilWindow : public C_BaseEntity {
	DECLARE_CLASS(C_BasicStencilWindow, C_BaseEntity);
	DECLARE_CLIENTCLASS();
public:
	C_BasicStencilWindow();

	void DrawStencil();
	virtual void SpawnClientEntity(void);
public:
	bool m_bActive;
	EHANDLE m_hFriend;
	float m_fHalfWidth, m_fHalfHeight;
};

#endif