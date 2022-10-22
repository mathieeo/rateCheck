// Poco.h
//
//    INNOVATIVE INTEGRATION CORPORATION PROPRIETARY INFORMATION
//  This software is supplied under the terms of a license agreement or nondisclosure
//  agreement with Innovative Integration Corporation and may not be copied or
//  disclosed except in accordance with the terms of that agreement.
//  Copyright (c) 2000..2005 Innovative Integration Corporation.
//  All Rights Reserved.
//

#ifndef PocoH
#define PocoH


#ifdef _MSC_VER

	#ifndef __CLR_VER
		#ifndef _NO_MFC_INCLUDES
		#include <afx.h>
		#endif
		#ifdef _AFXDLL  
		#pragma warning(push)	
		#pragma warning(disable : 4005)		
		#define _DLL  
		#pragma warning(pop)	
		#endif
	#endif

    #ifdef _DLL
        // Dynamic linked
        #ifdef _DEBUG
			#pragma comment(lib, "Poco_Debug.lib")
        #else
            #pragma comment(lib, "Poco.lib")
        #endif // _DEBUG
	#endif
#endif

#ifdef __BORLANDC__
    #ifdef _WIN64       // 64 bit compiler
	#pragma link "Poco_Foundation.a"
	#pragma link "Poco_Net.a"
	#pragma link "Iphlpapi.a"
    #else
	#pragma link "Poco_Foundation.lib"
	#pragma link "Poco_Net.lib"
    #endif
	
	    
#endif
#endif
