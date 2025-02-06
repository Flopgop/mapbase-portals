#ifndef C_STENCIL_H
#define C_STENCIL_H
#include <materialsystem/imaterialsystem.h>
#include "c_point_stencil_mirror.h"

class StencilTool {
public:
	int m_iRecursionLevel;
	CUtlVector<C_PointStencilMirror*> m_Windows;
	void SetupInitialStencilRendering(IMatRenderContext* pRenderContext, int ref);
	void SetStencilReferenceValue(IMatRenderContext* pRenderContext, int ref);
	void ClearDepthBuffer(IMatRenderContext* pRenderContext, int ref);
	void RestoreStencilMask(IMatRenderContext* pRenderContext, int ref);
	void DisableInitialStencilRendering(IMatRenderContext* pRenderContext);
};

static ConVar r_max_stencil_recursion("r_max_stencil_recursion", "1", FCVAR_DEVELOPMENTONLY, "(BROKEN) Shows portals through portals, if it worked properly");
extern StencilTool* g_pStencilTool;
#endif