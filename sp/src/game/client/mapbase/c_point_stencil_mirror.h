#ifndef C_BASIC_STENCIL_WINDOW_H
#define C_BASIC_STENCIL_WINDOW_H

#include "cbase.h"

class C_PointStencilMirror : public C_BaseEntity {
	DECLARE_CLASS(C_PointStencilMirror, C_BaseEntity);
	DECLARE_CLIENTCLASS();
public:
	C_PointStencilMirror();

	void DrawStencil();
	virtual void SpawnClientEntity(void);
	virtual void Simulate();
public:
	bool m_bActive;
	EHANDLE m_hFriend;
	float m_fHalfWidth, m_fHalfHeight;
};

#endif