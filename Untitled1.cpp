



  # include < iostream > 

  # ifdef _MSC_VER 

  # include < intrin.h > 

  # endif 



  # ifdef __GNUC__ 



  void __cpuid ( int * cpuinfo, int info) 

  { 

  __asm__ __volatile__ ( 

  " xchg %% ebx, %% edi; " 

  " cpuid; " 

  " xchg %% ebx, %% edi; " 

  : " = a " (cpuinfo [ 0 ]), " = D " (cpuinfo [ 1 ]), " = c " (cpuinfo [ 2 ]), " = d " (cpuinfo [ 3 ]) 

  : " 0 " (ข้อมูล) 

  ); 

  } 



  unsigned ยาว ยาว _xgetbv ( unsigned int index) 

  { 

  unsigned int eax, edx; 

  __asm__ __volatile__ ( 

  " xgetbv; " 

  : " = a " (eax), " = d " (edx) 

  : " c " ( ดัชนี ) 

  ); 

  return (( unsigned long long ) edx << 32 ) |  EAX; 

  } 



  # endif 



  int main () 

  { 

  bool sseSupportted = เท็จ ; 

  bool sse2Supportted = เท็จ ; 

  bool sse3Supportted = เท็จ ; 

  bool ssse3Supportted = เท็จ ; 

  bool sse4_1Supportted = false ; 

  bool sse4_2 สนับสนุน = เท็จ ; 

  bool sse4aSupportted = เท็จ ; 

  bool sse5Supportted = เท็จ ; 

  bool avxSupportted = เท็จ ; 



  int cpuinfo [ 4 ]; 

  __cpuid (cpuinfo, 1 ); 



  // ตรวจสอบ SSE, SSE2, SSE3, SSSE3, SSE4.1 และ SSE4.2 

  sseSupportted = cpuinfo [ 3 ] & ( 1 << 25 ) ||  เท็จ ; 

  sse2Supportted = cpuinfo [ 3 ] & ( 1 << 26 ) ||  เท็จ ; 

  sse3Supportted = cpuinfo [ 2 ] & ( 1 << 0 ) ||  เท็จ ; 

  ssse3Supportted = cpuinfo [ 2 ] & ( 1 << 9 ) ||  เท็จ ; 

  sse4_1Supportted = cpuinfo [ 2 ] & ( 1 << 19 ) ||  เท็จ ; 

  sse4_2Supportted = cpuinfo [ 2 ] & ( 1 << 20 ) ||  เท็จ ; 



  // ------------------------------------------------ ---------------------- 



  // ตรวจสอบการสนับสนุน AVX 

  // เอกสารอ้างอิง 

  // http://software.intel.com/en-us/blogs/2011/04/14/is-avx-enabled/ 

  // http://insufficientlycomplicated.wordpress.com/2011/11/07/detecting-intel-advanced-vector-extensions-avx-in-visual-studio/ 



  avxSupportted = cpuinfo [ 2 ] & ( 1 << 28 ) ||  เท็จ ; 

  bool osxsaveSupported = cpuinfo [ 2 ] & ( 1 << 27 ) ||  เท็จ ; 

  if (osxsaveSupported && avxSupportted) 

  { 

  // _XCR_XFEATURE_ENABLED_MASK = 0 

  unsigned long long xcrFeatureMask = _xgetbv ( 0 ); 

  avxSupportted = (xcrFeatureMask & 0x6) == 0x6 ; 

  } 



  // ------------------------------------------------ ---------------------- 



  // ตรวจสอบ SSE4a และ SSE5 



  // รับหมายเลขรหัสที่ถูกต้องที่ถูกต้อง 

  __cpuid (cpuinfo, 0x80000000 ); 

  int numExtendedIds = cpuinfo [ 0 ]; 

  if (numExtendedIds> = 0x80000001 ) 

  { 

  __cpuid (cpuinfo, 0x80000001 ); 

  sse4aSupportted = cpuinfo [ 2 ] & ( 1 << 6 ) ||  เท็จ ; 

  sse5Supportted = cpuinfo [ 2 ] & ( 1 << 11 ) ||  เท็จ ; 

  } 



  // ------------------------------------------------ ---------------------- 



  std :: cout << " SSE: " << (sseSupportted? 1 : 0 ) << std :: endl; 

  std :: cout << " SSE2: " << (sse2Supportted? 1 : 0 ) << std :: endl; 

  std :: cout << " SSE3: " << (sse3Supportted? 1 : 0 ) << std :: endl; 

  std :: cout << " SSE4.1: " << (sse4_1Supportted? 1 : 0 ) << std :: endl; 

  std :: cout << " SSE4.2: " << (sse4_2Supportted? 1 : 0 ) << std :: endl; 

  std :: cout << " SSE4a: " << (sse4aSupportted? 1 : 0 ) << std :: endl; 

  std :: cout << " SSE5: " << (sse5Supportted? 1 : 0 ) << std :: endl; 

  std :: cout << " AVX: " << (avxSupportted? 1 : 0 ) << std :: endl; 



  return 0 ; 

  } 
