
#include "cbase.h"
#include "view_scene.h"
#include "c_point_stencil_mirror.h"
#include "c_stencil.h"

LINK_ENTITY_TO_CLASS(point_stencil_mirror, C_PointStencilMirror);

IMPLEMENT_CLIENTCLASS_DT(C_PointStencilMirror, DT_PointStencilMirror, CPointStencilMirror)
RecvPropEHandle(RECVINFO(m_hFriend)),
RecvPropBool(RECVINFO(m_bActive)),
RecvPropFloat(RECVINFO(m_fHalfWidth)),
RecvPropFloat(RECVINFO(m_fHalfHeight)),
END_RECV_TABLE()

C_PointStencilMirror::C_PointStencilMirror()
{
	DevMsg("Portal Created!!!");
	g_pStencilTool->m_Windows.AddToTail(this);
}

void C_PointStencilMirror::SpawnClientEntity(void)
{
	BaseClass::SpawnClientEntity();
}

void C_PointStencilMirror::Simulate()
{
	BaseClass::Simulate();

	// shadow clone jutsu
}

void C_PointStencilMirror::DrawStencil()
{
	float forwardOffset = 0.1;
	const IMaterial* pMaterial = materials->FindMaterial("", "", false); // literally just yoink an error texture, TODO: actually make this get a real material

	CMatRenderContextPtr pRenderContext(materials);
	pRenderContext->Bind((IMaterial*)pMaterial, GetClientRenderable());

	// This can depend on the Bind command above, so keep this after!
	UpdateFrontBufferTexturesForMaterial((IMaterial*)pMaterial);

	pRenderContext->MatrixMode(MATERIAL_MODEL); //just in case
	pRenderContext->PushMatrix();
	pRenderContext->LoadIdentity();

	Vector m_vForward, m_vRight, m_vUp;
	this->GetVectors(&m_vForward, &m_vRight, &m_vUp);
	
	Vector ptCenter = this->GetAbsOrigin() + m_vForward * forwardOffset;

	Vector verts[4];
	verts[0] = ptCenter + (m_vRight * m_fHalfWidth * 2.0f);
	verts[1] = ptCenter + (m_vRight * m_fHalfWidth * 2.0f) + (m_vUp * m_fHalfHeight * 2.0f);
	verts[2] = ptCenter;
	verts[3] = ptCenter + (m_vUp * m_fHalfHeight * 2.0f);

	CMeshBuilder meshBuilder;
	IMesh* pMesh = pRenderContext->GetDynamicMesh(false);
	meshBuilder.Begin(pMesh, MATERIAL_TRIANGLE_STRIP, 2);

	meshBuilder.Position3fv(&verts[3].x);
	meshBuilder.AdvanceVertex();

	meshBuilder.Position3fv(&verts[2].x);
	meshBuilder.AdvanceVertex();

	meshBuilder.Position3fv(&verts[1].x);
	meshBuilder.AdvanceVertex();

	meshBuilder.Position3fv(&verts[0].x);
	meshBuilder.AdvanceVertex();

	meshBuilder.End();
	pMesh->Draw();

	pRenderContext->MatrixMode(MATERIAL_MODEL);
	pRenderContext->PopMatrix();
}
