/****************************************************************************/
// Eclipse SUMO, Simulation of Urban MObility; see https://eclipse.dev/sumo
// Copyright (C) 2001-2024 German Aerospace Center (DLR) and others.
// This program and the accompanying materials are made available under the
// terms of the Eclipse Public License 2.0 which is available at
// https://www.eclipse.org/legal/epl-2.0/
// This Source Code may also be made available under the following Secondary
// Licenses when the conditions for such availability set forth in the Eclipse
// Public License 2.0 are satisfied: GNU General Public License, version 2
// or later which is available at
// https://www.gnu.org/licenses/old-licenses/gpl-2.0-standalone.html
// SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
/****************************************************************************/
/// @file    MFXGLCanvas.h
/// @author  Mirko Barthauer
/// @date    09.01.2025
///
// GL canvas ready for OpenGL3.3
/****************************************************************************/
#pragma once
#include <config.h>

#include "fxheader.h"

#ifdef WIN32
#define NOMINMAX
#endif
#include <fx3d.h>
#ifdef WIN32
#undef NOMINMAX
#endif

typedef HGLRC WINAPI wglCreateContextAttribsARB_type(HDC hdc, HGLRC hShareContext, const int* attribList);
typedef BOOL WINAPI wglChoosePixelFormatARB_type(HDC hdc, const int* piAttribIList,
    const FLOAT* pfAttribFList, UINT nMaxFormats, int* piFormats, UINT* nNumFormats);

class MFXGLVisual;

/// MFXGLCanvas, an area drawn by another object
class MFXGLCanvas : public FXGLCanvas {
    FXDECLARE(MFXGLCanvas)
private:
    MFXGLCanvas* sgnext;  // Share group next in share list
    MFXGLCanvas* sgprev;  // Share group previous in share list
protected:
    void* ctx;     // GL Context
    wglCreateContextAttribsARB_type* wglCreateContextAttribsARB = nullptr;
    wglChoosePixelFormatARB_type* wglChoosePixelFormatARB = nullptr;

protected:
    MFXGLCanvas();
private:
    MFXGLCanvas(const FXGLCanvas&);
    MFXGLCanvas& operator=(const FXGLCanvas&);

#ifdef WIN32
    virtual const char* GetClass() const;
#endif
    public:
        /**
        * Construct an OpenGL-capable canvas, with its own private display list.
        */
        MFXGLCanvas(FXComposite* p, MFXGLVisual* vis, FXObject* tgt = NULL, FXSelector sel = 0, FXuint opts = 0, FXint x = 0, FXint y = 0, FXint w = 0, FXint h = 0);

        /**
        * Construct an OpenGL-capable canvas, sharing display
        * list with another GL canvas.  This canvas becomes a member
        * of a display list share group.  All members of the display
        * list share group have to have the same visual.
        */
        MFXGLCanvas(FXComposite* p, MFXGLVisual* vis, MFXGLCanvas* sharegroup, FXObject* tgt = NULL, FXSelector sel = 0, FXuint opts = 0, FXint x = 0, FXint y = 0, FXint w = 0, FXint h = 0);

        /// Return TRUE if it is sharing display lists
        FXbool isShared() const;

        /// Create all of the server-side resources for this window
        void create();

        /// Detach the server-side resources for this window
        void detach();

        /// Destroy the server-side resources for this window
        void destroy();

        /// Make OpenGL context current prior to performing OpenGL commands
        FXbool makeCurrent();

        /// Make OpenGL context non current
        FXbool makeNonCurrent();

        /// Return TRUE if this window's context is current
        FXbool isCurrent() const;

        /// Return current context, if any
        static void* getCurrentContext();

        /// Get GL context handle
        void* getContext() const { return ctx; }

        /// Swap front and back buffer
        void swapBuffers();

        /// Save object to stream
        void save(FXStream& store) const;

        /// Load object from stream
        void load(FXStream& store);

        /// Destructor
        virtual ~MFXGLCanvas();
    };
