/****************************************************************************/
// Eclipse SUMO, Simulation of Urban MObility; see https://eclipse.dev/sumo
// Copyright (C) 2001-2025 German Aerospace Center (DLR) and others.
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
/// @file    GLBufferStruct.h
/// @author  Mirko Barthauer
/// @date    24.01.2025
///
//
/****************************************************************************/

struct GLBufferStruct {
    float x;
    float y;
    float r;
    float g;
    float b;
    float a;
    
    static const unsigned int getSize() {
        return 6 * sizeof(float);
    }
};


struct GLBufferStruct3D : GLBufferStruct {
    float z;

    static const unsigned int getSize() {
        return 7 * sizeof(float);
    }
};