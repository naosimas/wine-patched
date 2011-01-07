/*
 * Copyright 2011 Jacek Caban for CodeWeavers
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA
 */

#define COBJMACROS

#include <wine/test.h>
#include <stdarg.h>
#include <stdio.h>

#include "windef.h"
#include "winbase.h"
#include "ole2.h"
#include "exdisp.h"

static void test_InternetExplorer(void)
{
    IWebBrowser2 *wb;
    IUnknown *unk;
    ULONG ref;
    HRESULT hres;

    hres = CoCreateInstance(&CLSID_InternetExplorer, NULL, CLSCTX_SERVER,
            &IID_IUnknown, (void**)&unk);
    if(FAILED(hres)) {
        win_skip("Could not create InternetExplorer object\n");
        return;
    }

    hres = IUnknown_QueryInterface(unk, &IID_IWebBrowser2, (void**)&wb);
    ok(hres == S_OK, "Could not get IWebBrowser2 interface: %08x\n", hres);

    IWebBrowser2_Release(wb);
    ref = IUnknown_Release(unk);
    ok(!ref, "object not destroyed, ref=%u\n", ref);
}

START_TEST(ie)
{
    CoInitialize(NULL);

    test_InternetExplorer();

    CoUninitialize();
}
