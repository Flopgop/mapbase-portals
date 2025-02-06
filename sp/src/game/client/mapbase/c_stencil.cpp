
#include "cbase.h"
#include "c_stencil.h"

static StencilTool s_StencilTool;
StencilTool* g_pStencilTool = &s_StencilTool;

CON_COMMAND(r_dump_portal_info, "Dumps misc debug info about all portals.") {
	for (int i = 0; i < g_pStencilTool->m_Windows.Size(); ++i) {
		C_PointStencilMirror* window = g_pStencilTool->m_Windows[i];
		Msg("Portal %d:\n", i);
		Msg("\tPosition: %f %f %f\n", window->GetAbsOrigin().x, window->GetAbsOrigin().y, window->GetAbsOrigin().z);
		Msg("\tActive: %s\n", window->m_bActive ? "true" : "false");
		Msg("\tLinked: %p\n", window->m_hFriend);
		Msg("\tHalfWidth: %f, HalfHeight: %f\n", window->m_fHalfWidth, window->m_fHalfHeight);
	}
}


void StencilTool::SetupInitialStencilRendering(IMatRenderContext* pRenderContext, int ref)
{
	pRenderContext->SetStencilEnable(true);
	pRenderContext->SetStencilCompareFunction(STENCILCOMPARISONFUNCTION_ALWAYS);
	pRenderContext->SetStencilPassOperation(STENCILOPERATION_REPLACE); // pass = replace pixel
	pRenderContext->SetStencilFailOperation(STENCILOPERATION_KEEP); // fail (not possible with comparison ALWAYS) = keep pixel
	pRenderContext->SetStencilZFailOperation(STENCILOPERATION_KEEP); // fail (not possible with comparison ALWAYS) = keep depth
	pRenderContext->SetStencilTestMask(0xFF);
	pRenderContext->SetStencilWriteMask(0xFF);
	pRenderContext->SetStencilReferenceValue(ref);
}

void StencilTool::SetStencilReferenceValue(IMatRenderContext* pRenderContext, int ref)
{
	pRenderContext->SetStencilCompareFunction(STENCILCOMPARISONFUNCTION_EQUAL);
	pRenderContext->SetStencilPassOperation(STENCILOPERATION_INCR);
	pRenderContext->SetStencilFailOperation(STENCILOPERATION_KEEP);
	pRenderContext->SetStencilZFailOperation(STENCILOPERATION_KEEP);
	pRenderContext->SetStencilReferenceValue(ref);
}

void StencilTool::ClearDepthBuffer(IMatRenderContext* pRenderContext, int ref) 
{
	pRenderContext->SetStencilPassOperation(STENCILOPERATION_KEEP);
	pRenderContext->SetStencilReferenceValue(ref);
	pRenderContext->ClearBuffersObeyStencil(false, true);
}

void StencilTool::RestoreStencilMask(IMatRenderContext* pRenderContext, int ref)
{
	pRenderContext->SetStencilReferenceValue(ref);
	pRenderContext->SetStencilCompareFunction(STENCILCOMPARISONFUNCTION_EQUAL);
	pRenderContext->SetStencilPassOperation(STENCILOPERATION_DECR);
	pRenderContext->SetStencilFailOperation(STENCILOPERATION_KEEP);
	pRenderContext->SetStencilZFailOperation(STENCILOPERATION_KEEP);
	pRenderContext->PerformFullScreenStencilOperation();
}

void StencilTool::DisableInitialStencilRendering(IMatRenderContext* pRenderContext) {
	pRenderContext->SetStencilEnable(false);
	pRenderContext->SetStencilCompareFunction(STENCILCOMPARISONFUNCTION_NEVER);
	pRenderContext->SetStencilPassOperation(STENCILOPERATION_KEEP);
	pRenderContext->SetStencilFailOperation(STENCILOPERATION_KEEP);
	pRenderContext->SetStencilZFailOperation(STENCILOPERATION_KEEP);
	pRenderContext->SetStencilTestMask(0xFF);
	pRenderContext->SetStencilWriteMask(0xFF);
	pRenderContext->SetStencilReferenceValue(0);
}
