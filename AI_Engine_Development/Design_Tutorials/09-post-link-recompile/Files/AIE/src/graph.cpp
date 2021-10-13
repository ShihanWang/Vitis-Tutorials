/*
 * (c) Copyright 2021 Xilinx, Inc. All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */


#include "graph.h"

PLIO *in0 = new PLIO("DataIn1", adf::plio_32_bits,"data/input.txt");
PLIO *out0 = new PLIO("DataOut1",adf::plio_32_bits, "data/output.txt");

simulation::platform<1,1> platform(in0, out0);

clipped clipgraph;

connect<> net0(platform.src[0], clipgraph.in);

connect<> net1(clipgraph.out, platform.sink[0]);

#define NUMBER_OF_ITERATIONS 4
#if defined(__AIESIM__) || defined(__PTHREAD_API__)
//  __AIESIM__ is for Emulation-AIE build configuration
// __PTHREAD_API__ is for Emulations-SW build configuration
int main(int argc, char ** argv) {
 	clipgraph.init();
    clipgraph.run(NUMBER_OF_ITERATIONS);
    clipgraph.end();
    return 0;
}
#endif
