#pragma once


// By c5 from guidedhacking.com

/* IDXGISwapChain virtuals (SC_ prefix for swapchain or we'll redefine) */
#define SC_QUERYINTERFACE 					0
#define SC_ADDREF 							1
#define SC_RELEASE 							2
#define SC_SETPRIVATEDATA 					3
#define SC_SETPRIVATEDATAINTERFACE 			4
#define SC_GETPRIVATEDATA 					5
#define SC_GETPARENT 						6
#define SC_GETDEVICE 						7
#define SC_PRESENT 							8
#define SC_GETBUFFER 						9
#define SC_SETFULLSCREENSTATE 				10
#define SC_GETFULLSCREENSTATE 				11
#define SC_GETDESC 							12
#define SC_RESIZEBUFFERS 					13
#define SC_RESIZETARGET 					14
#define SC_GETCONTAININGOUTPUT 				15
#define SC_GETFRAMESTATISTICS 				16
#define SC_GETLASTPRESENTCOUNT 				17