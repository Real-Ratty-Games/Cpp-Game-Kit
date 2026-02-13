/*======================================================
	Copyright (c) 2026 Real Ratty Games.
	Created by Norbert Gerberg.
======================================================*/
#import <Cocoa/Cocoa.h>
#include <SDL3/SDL_system.h>

extern "C" void* GetMetalLayerFromSDL(SDL_PropertiesID* wid)
{
	NSWindow* nswindow = (NSWindow*)SDL_GetPointerProperty(*wid, SDL_PROP_WINDOW_COCOA_WINDOW_POINTER, nullptr);
	NSView* contentView = [nswindow contentView];
	return contentView.layer;
}
