/* --------------------------------------------------------------------------
 *
 * Little Board Application Kit
 * Copyright (C) 2018, Anthony Lee, All Rights Reserved
 *
 * This software is a freeware; it may be used and distributed according to
 * the terms of The MIT License.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR
 * IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * File: LBAppDefs.h
 * Description:
 *
 * --------------------------------------------------------------------------*/

#ifndef __LBK_APP_DEFS_H__
#define __LBK_APP_DEFS_H__

#ifdef __cplusplus
#include <be/Be.h>
#else // for using C on HaikuOS
#include <stdlib.h>
#include <string.h>
#include <be/support/SupportDefs.h>
#endif // __cplusplus

#define LBK_DEVICE_DETACHED		'lBKd'
#define LBK_EVENT_PENDING		'lBKe'
#define LBK_QUIT_REQUESTED		'lBKq'
#define LBK_APP_SETTINGS_UPDATED	'lBKs'
#define LBK_VIEW_STOOD_BACK		'lBKb'


#ifndef ETK_MAJOR_VERSION

#include <bsd_mem.h>

#ifndef _EXPORT
#define _EXPORT		__declspec(dllexport)
#endif

#ifdef __cplusplus /* Just for C++ */

// e_cast_as(): like cast_as(), but NULL accepted, implemented by ETK++
template<class C, typename B> inline C* etk_cast_as(B *ptr)
{
	return (ptr ? dynamic_cast<C*>(ptr) : (C*)0);
}
#define e_cast_as(ptr, class)		etk_cast_as<class>(ptr)

#endif /* __cplusplus */

#endif /* !ETK_MAJOR_VERSION */

#endif /* __LBK_APP_DEFS_H__ */

