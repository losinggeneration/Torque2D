//-----------------------------------------------------------------------------
// Copyright (c) 2013 GarageGames, LLC
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to
// deal in the Software without restriction, including without limitation the
// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
// sell copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.
//-----------------------------------------------------------------------------



#include "platform/platform.h"
#include "platformX86UNIX/platformX86UNIX.h"
#include "console/console.h"
#include "string/stringTable.h"
#include <math.h>

// PlatformSystemInfo_struct PlatformSystemInfo;

extern void PlatformBlitInit();
extern void SetProcessorInfo(TorqueSystemInfo::Processor& pInfo, 
   char* vendor, U32 processor, U32 properties); // platform/platformCPU.cc

#if defined(TORQUE_SUPPORTS_NASM)
// asm cpu detection routine from platform code
extern "C"
{
   void detectX86CPUInfo(char *vendor, U32 *processor, U32 *properties);
}
#endif

/* used in the asm */
static U32 time[2];
U32 clockticks = 0;
static char vendor[13] = {0,};
static U32 properties = 0;
static U32 processor  = 0;
U32 timeHi = 0;
U32 timeLo = 0;

void Processor::init()
{
   // Reference:
   //    www.cyrix.com
   //    www.amd.com
   //    www.intel.com
   //       http://developer.intel.com/design/PentiumII/manuals/24512701.pdf
   PlatformSystemInfo.processor.type = CPU_X86Compatible;
   PlatformSystemInfo.processor.name = StringTable->insert("Unknown x86 Compatible");
   PlatformSystemInfo.processor.mhz  = 0;
   PlatformSystemInfo.processor.properties = CPU_PROP_C;

   clockticks = properties = processor = time[0] = 0;
   dStrcpy(vendor, "");

#if defined(TORQUE_SUPPORTS_NASM)
   detectX86CPUInfo(vendor, &processor, &properties);
#else
   //TODO Actually test this --HL
   // totally untested...
   asm(
      //--------------------------------------
      // is CPUID supported
      "push   %%ebx\n"
      "push   %%edx\n"
      "push   %%ecx\n"
      "pushf\n"
      "pushf\n"
      "pop    %%eax\n"
      "mov    %%eax,%%ebx\n"
      "xor    $0x200000,%%eax\n"
      "push   %%eax\n"
      "popf\n"
      "pushf\n"
      "pop    %%eax\n"
      "cmp    %%ebx,%%eax\n"
      "jz     EXIT\n"                // doesn't support CPUID instruction

      //--------------------------------------
      // Get Vendor Informaion using CPUID eax==0
      "xor    %%eax,%%eax\n"
      "cpuid\n"

      "mov    %%ebx, (%1)\n"
      "mov    %%ebx, 0x4(%1)\n"
      "mov    %%ebx, 0x8(%1)\n"

      // get Generic Extended CPUID info
      "mov    $0x1,%%eax\n"
      "cpuid\n"

      "and    $0xff0,%%eax\n"
      "mov    %%eax,%0\n"
      "mov    %%edx,%0\n"

      // Want to check for 3DNow(tm).  Need to see if extended cpuid functions present.
      "mov    $0x80000000,%%eax\n"
      "cpuid\n"
      "cmp    $0x80000000,%%eax\n"
      "jbe    EXIT\n"
      "mov    $0x80000001,%%eax\n"
      "cpuid\n"
      "and    $0x80000000,%%edx\n"
      "or     %%edx,%0\n"

      "EXIT:\n"
      "popf\n"
      "pop    %%ecx\n"
      "pop    %%edx\n"
      "pop    %%ebx\n"
      : "=r" (properties)
      : "r" (vendor)
      : "%eax", "%ecx", "%edx", "%ebx"
   );
#endif
   SetProcessorInfo(PlatformSystemInfo.processor, 
      vendor, processor, properties);

   //--------------------------------------
   // if RDTSC support calculate the aproximate Mhz of the CPU
   if (PlatformSystemInfo.processor.properties & CPU_PROP_RDTSC && 
       PlatformSystemInfo.processor.properties & CPU_PROP_FPU)
   {
      const U32 MS_INTERVAL = 750;
      
#if defined(TORQUE_COMPILER_GCC) && ((__GNUC__ >= 3) && (__GNUC_MINOR__ >=4)) || ((__GNUC__ >= 4) && (__GNUC_MINOR__ >=0))
      asm("rdtsc" : "=a" (timeLo), "=d" (timeHi));
#else
      __asm__(
         "pushl  %eax\n"
         "pushl  %edx\n"
         "rdtsc\n"
         "movl   %eax, (time)\n"
         "movl   %edx, (time+4)\n"
         "popl   %edx\n"
         "popl   %eax\n"
         );
#endif
      U32 ms = Platform::getRealMilliseconds();
      while ( Platform::getRealMilliseconds() < ms+MS_INTERVAL )
      { /* empty */ }
      ms = Platform::getRealMilliseconds()-ms;
#if defined(TORQUE_COMPILER_GCC) && ((__GNUC__ >= 3) && (__GNUC_MINOR__ >= 4)) || ((__GNUC__ >= 4) && (__GNUC_MINOR__ >=0))
      asm(
         "pushl  %eax\n"
         "pushl  %edx\n"
         "rdtsc\n"
         "sub    (timeHi), %edx\n"
         "sbb    (timeLo), %eax\n"
         "mov    %eax, (clockticks)\n"
         "popl   %edx\n"
         "popl   %eax\n"
         );
#else      
      asm(
         "pushl  %eax\n"
         "pushl  %edx\n"
         "rdtsc\n"
         "sub    (time+4), %edx\n"
         "sbb    (time), %eax\n"
         "mov    %eax, (clockticks)\n"
         "popl   %edx\n"
         "popl   %eax\n"
         );
#endif
      U32 mhz = static_cast<U32>(F32(clockticks) / F32(ms) / 1000.0f);
      
      // catch-22 the timing method used above to calc Mhz is generally
      // wrong by a few percent so we want to round to the nearest clock
      // multiple but we also want to be careful to not touch overclocked 
      // results

      // measure how close the Raw Mhz number is to the center of each clock
      // bucket
      U32 bucket25 = mhz % 25;
      U32 bucket33 = mhz % 33;
      U32 bucket50 = mhz % 50;
      
      if (bucket50 < 8 || bucket50 > 42)
         PlatformSystemInfo.processor.mhz = 
            U32((mhz+(50.0f/2.0f))/50.0f) * 50; 
      else if (bucket25 < 5 || bucket25 > 20)
         PlatformSystemInfo.processor.mhz = 
            U32((mhz+(25.0f/2.0f))/25.0f) * 25; 
      else if (bucket33 < 5 || bucket33 > 28)
         PlatformSystemInfo.processor.mhz = 
            U32((mhz+(33.0f/2.0f))/33.0f) * 33; 
      else 
         PlatformSystemInfo.processor.mhz = U32(mhz); 
   }

   Con::printf("Processor Init:");
   Con::printf("   %s, %d Mhz", PlatformSystemInfo.processor.name, PlatformSystemInfo.processor.mhz);
   if (PlatformSystemInfo.processor.properties & CPU_PROP_FPU)
      Con::printf("   FPU detected");
   if (PlatformSystemInfo.processor.properties & CPU_PROP_MMX)
      Con::printf("   MMX detected");
   if (PlatformSystemInfo.processor.properties & CPU_PROP_3DNOW)
      Con::printf("   3DNow detected");
   if (PlatformSystemInfo.processor.properties & CPU_PROP_SSE)
      Con::printf("   SSE detected");
   Con::printf(" ");

   PlatformBlitInit();
}

