#ifndef C_BASIC_STENCIL_WINDOW_H
#define C_BASIC_STENCIL_WINDOW_H

#include "cbase.h"

class BasicStencilWindow : public C_BaseEntity {
	DECLARE_CLASS(BasicStencilWindow, C_BaseEntity);
	DECLARE_CLIENTCLASS();
public:
	BasicStencilWindow();

	void DrawStencil();
	virtual void SpawnClientEntity(void);
public:
	bool m_bActive;
	EHANDLE m_hFriend;
	float m_fHalfWidth, m_fHalfHeight;
};

#endif