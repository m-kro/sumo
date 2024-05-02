#!/usr/bin/env python
# Eclipse SUMO, Simulation of Urban MObility; see https://eclipse.dev/sumo
# Copyright (C) 2011-2024 German Aerospace Center (DLR) and others.
# This program and the accompanying materials are made available under the
# terms of the Eclipse Public License 2.0 which is available at
# https://www.eclipse.org/legal/epl-2.0/
# This Source Code may also be made available under the following Secondary
# Licenses when the conditions for such availability set forth in the Eclipse
# Public License 2.0 are satisfied: GNU General Public License, version 2
# or later which is available at
# https://www.gnu.org/licenses/old-licenses/gpl-2.0-standalone.html
# SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later

# @file    buildFullGraph.py
# @author  Jakob Erdmann
# @date    2024-05-02

"""
Extend network with direct connection between all edges that permit the given vClass
"""
from __future__ import absolute_import
from __future__ import print_function

import sys
import os
import subprocess
sys.path.append(os.path.dirname(os.path.dirname(os.path.realpath(__file__))))
import sumolib  # noqa
from sumolib.options import ArgumentParser  # noqa


def parse_args():
    optParser = ArgumentParser()
    optParser.add_option("net", category="input", type=optParser.net_file,
                         help="the network to patch")
    optParser.add_option("-o", "--output-file", dest="outfile", category="output", type=optParser.net_file,
                         help="the output network file")
    optParser.add_option("--vclass", 
                         help="class for which the fully connected graph should be built")
    optParser.add_option("--speed", type=float, default=100/3.6,
                         help="speed of added edges")
    optParser.add_option("--numlanes", type=int, default=1,
                         help="number of lanes for added edges")
    options = optParser.parse_args()
    if not options.outfile:
        options.outfile = "patched." + options.net

    return options


def main(options):
    net = sumolib.net.readNet(options.net)
    baseEdges = [e for e in net.getEdges() if e.allows(options.vclass)]
    edgePatch = options.net[:-7] + ".patch.edg.xml"
    with open(edgePatch, 'w') as outf:
        sumolib.writeXMLHeader(outf, "$Id$", "edges", options=options)
        for e1 in baseEdges:
            for e2 in baseEdges:
                if e1 != e2 and e2 not in e1.getOutgoing():
                    outf.write('    <edge id="%s_%s" from="%s" to="%s" speed="%s" numLanes="%s" width="%s" allow="%s"/>\n' % (
                        e1.getToNode().getID(), e2.getFromNode().getID(),
                        e1.getToNode().getID(), e2.getFromNode().getID(),
                        options.speed, options.numlanes, e1.getLanes()[-1].getWidth(), options.vclass))
        outf.write("</edges>\n")

    NETCONVERT = sumolib.checkBinary('netconvert')
    subprocess.call([NETCONVERT, '-s', options.net, '-e', edgePatch, '-o', options.outfile])

if __name__ == "__main__":
    main(parse_args())