#include "cbase.h"

class CPointStencilMirror : public CBaseEntity {
public:
	DECLARE_CLASS( CPointStencilMirror, CBaseEntity );
	DECLARE_SERVERCLASS();
	DECLARE_DATADESC();
	CPointStencilMirror();

	int UpdateTransmitState()	// always send to all clients
	{
		return SetTransmitState(FL_EDICT_ALWAYS);
	}

	virtual void Activate(void);
public:
	string_t m_iFriendName;
	CNetworkHandle(CPointStencilMirror, m_hFriend);
	CNetworkVar(bool, m_bActive);
	CNetworkVar(float, m_fHalfWidth);
	CNetworkVar(float, m_fHalfHeight);
};

LINK_ENTITY_TO_CLASS(point_stencil_mirror, CPointStencilMirror);

BEGIN_DATADESC(CPointStencilMirror)
DEFINE_KEYFIELD(m_iFriendName, FIELD_STRING, "friendwindow"),
DEFINE_FIELD(m_hFriend, FIELD_EHANDLE),
DEFINE_KEYFIELD(m_bActive, FIELD_BOOLEAN, "active"), /// If active is set and friend is not things will break!!
DEFINE_KEYFIELD(m_fHalfWidth, FIELD_FLOAT, "halfwidth"),
DEFINE_KEYFIELD(m_fHalfHeight, FIELD_FLOAT, "halfheight"),
END_DATADESC()

IMPLEMENT_SERVERCLASS_ST( CPointStencilMirror, DT_PointStencilMirror )
SendPropEHandle(SENDINFO(m_hFriend)),
SendPropBool(SENDINFO(m_bActive)),
SendPropFloat(SENDINFO(m_fHalfWidth)),
SendPropFloat(SENDINFO(m_fHalfHeight)),
END_SEND_TABLE()

CPointStencilMirror::CPointStencilMirror()
{
	DevMsg("Portal Created (SERVER)!!!\n");
}

void CPointStencilMirror::Activate(void) {
	BaseClass::Activate();

	CBaseEntity* entity = gEntList.FindEntityByName(NULL, m_iFriendName);
	if (CPointStencilMirror* mirror = dynamic_cast<CPointStencilMirror*>(entity)) {
		m_hFriend.Set(mirror);
	}
}