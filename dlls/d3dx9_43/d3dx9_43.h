#ifndef QEMU_D3D9_H
#define QEMU_D3D9_H

#include <stdlib.h>

#include "d3d9_wrapper.h"

enum d3dx9_43_calls
{
    CALL_D3DXVEC3TRANSFORMCOORD = 0,
};

#ifdef QEMU_DLL_GUEST

#else

extern const struct qemu_ops *qemu_ops;

void qemu_D3DXVec3TransformCoord(struct qemu_syscall *call);

#endif

#endif
