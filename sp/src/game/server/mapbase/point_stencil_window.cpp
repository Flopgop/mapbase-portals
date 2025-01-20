#include "cbase.h"

class CPointStencilWindow : public CBaseEntity {
public:
	DECLARE_CLASS(CPointStencilWindow, CBaseEntity);
	DECLARE_SERVERCLASS();
	DECLARE_DATADESC();
	CPointStencilWindow();

	int UpdateTransmitState()	// always send to all clients
	{
		return SetTransmitState(FL_EDICT_ALWAYS);
	}

	virtual void Activate(void);
public:
	string_t m_iFriendName;
	CNetworkHandle(CPointStencilWindow, m_hFriend);
	CNetworkVar(bool, m_bActive);
	CNetworkVar(float, m_fHalfWidth);
	CNetworkVar(float, m_fHalfHeight);
};

LINK_ENTITY_TO_CLASS(point_stencil_window, CPointStencilWindow);

BEGIN_DATADESC(CPointStencilWindow)
DEFINE_KEYFIELD(m_iFriendName, FIELD_STRING, "friendwindow"),
DEFINE_FIELD(m_hFriend, FIELD_EHANDLE),
DEFINE_KEYFIELD(m_bActive, FIELD_BOOLEAN, "active"), /// If active is set and friend is not things will break!!
DEFINE_KEYFIELD(m_fHalfWidth, FIELD_FLOAT, "halfwidth"),
DEFINE_KEYFIELD(m_fHalfHeight, FIELD_FLOAT, "halfheight"),
END_DATADESC()

IMPLEMENT_SERVERCLASS_ST(CPointStencilWindow, DT_BasicStencilWindow)
SendPropEHandle(SENDINFO(m_hFriend)),
SendPropBool(SENDINFO(m_bActive)),
SendPropFloat(SENDINFO(m_fHalfWidth)),
SendPropFloat(SENDINFO(m_fHalfHeight)),
END_SEND_TABLE()

CPointStencilWindow::CPointStencilWindow()
{
	DevMsg("Portal Created (SERVER)!!!\n");
}

void CPointStencilWindow::Activate(void) {
	BaseClass::Activate();

	CBaseEntity* entity = gEntList.FindEntityByName(NULL, m_iFriendName);
	if (CPointStencilWindow* window = dynamic_cast<CPointStencilWindow*>(entity)) {
		m_hFriend.Set(window);
	}
}