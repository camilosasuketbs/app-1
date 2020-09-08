//
//  RoundWindow.m
//  RoundWindow
//
//  Created by Matt Gallagher on 12/12/08.
//  Copyright 2008 Matt Gallagher. All rights reserved.
//
//  Permission is given to use this source code file without charge in any
//  project, commercial or otherwise, entirely at your risk, with the condition
//  that any redistribution (in part or whole) of source code must retain
//  this copyright and permission notice. Attribution in compiled projects is
//  appreciated but not required.
//
#import "_mm.h"
#import "RoundWindowApp.h"


@implementation RoundWindow


//
// initWithContentRect:styleMask:backing:defer:screen:
//
// Init method for the generic.
//
- (id)initWithFrame:(CGRect)contentRect
{
   
	self = [super initWithFrame:contentRect ];

	if(self == NULL)
   {
      
      return NULL;
      
   }
   
   [self setWindowLevel:UIWindowLevelNormal];

	[self setOpaque:YES];

   [self setBackgroundColor: [ UIColor whiteColor ] ];
		
//	[[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(mainWindowChanged:) name:NSWindowDidBecomeMainNotification generic:self];
		
//	[[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(mainWindowChanged:) name:NSWindowDidResignMainNotification generic:self];
   
//   [[UINotificationCenter defaultCenter] addObserver:self selector:@selector(windowDidResize:) name:NSWindowDidResizeNotification generic:self];
//   
//   [[UINotificationCenter defaultCenter] addObserver:self selector:@selector(windowDidMove:) name:NSWindowDidMoveNotification generic:self];
//   
//   [[UINotificationCenter defaultCenter] addObserver:self selector:@selector(windowWillClose:) name:NSWindowWillCloseNotification generic:self];
//   
//   [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(windowDidExpose:) name:NSWindowDidExposeNotification generic:self];
   

   
// [self setAcceptsMouseMovedEvents : YES];
      
   m_controller = [[RoundViewController alloc] init];
   
   m_controller->m_pwindow = self;

   [self create_view];
   
   [self setRootViewController:m_controller];
   
   CGRect rect;
   
   rect.origin.x = 0;
   rect.origin.y = 0;
   rect.size = contentRect.size;
   
   m_pwindow->round_window_resized(rect.size.width, rect.size.height);
   
	return self;
   
   
   
   //
   // initWithContentRect:styleMask:backing:defer:screen:
   //
   // Init method for the generic.
   //
   //- (id)initWithFrame:(CGRect)contentRect
  // {
      
      //self = [super initWithFrame:contentRect ];
      
      //if(self == NULL)
        // return NULL;
      
      //[self setWindowLevel:UIWindowLevelAlert];
      
      //[self setOpaque:NO];
      
      //[self setBackgroundColor:[UIColor clearColor]];
		
      //	[[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(mainWindowChanged:) name:NSWindowDidBecomeMainNotification generic:self];
		
      //	[[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(mainWindowChanged:) name:NSWindowDidResignMainNotification generic:self];
      
      //   [self setAcceptsMouseMovedEvents : YES];
      
      //m_controller = [[UIViewController alloc] init];
      
      
      //[self create_view];
      
    //  [self setRootViewController : m_controller];
      
      
  //    return self;
      
//   }
}

//
// dealloc
//
// Releases instance memory.
//
- (void)dealloc
{
   
//	[[NSNotificationCenter defaultCenter] removeObserver:self];
   
//	[super dealloc];
   
}


//
// setContentSize:
//
// Convert from childContentView to frameView for size.
//
- (void)setContentSize:(CGSize)newSize
{
	
//	[super setContentSize:newSize];
   
}

//
// mainWindowChanged:
//
// Redraw the close button when the main window status changes.
//
- (void)mainWindowChanged:(NSNotification *)aNotification
{
   
}

//
// setContentView:
//
// Keep our frame view as the content view and make the specified "aView"
// the child of that.
//
- (void)create_view
{

	CGRect bounds = [self frame];
	
//   bounds.origin = NSZeroPoint;
    bounds.origin.x = 0;
    bounds.origin.y = 0;

	RoundWindowFrameView * frameView = [[RoundWindowFrameView alloc] initWithFrame : bounds] ;
   
  	m_controller->childContentView = frameView;
   
   frameView->m_roundwindow =  self;
   
   frameView->m_bShift = false;
   frameView->m_bControl = false;
   frameView->m_bAlt = false;
   
   [frameView setTintColor:[UIColor clearColor]];
   //[frameView setTextColor:[UIColor clearColor]];
   //[frameView setContentInset:UIEdgeInsetsMake(0, -4, 0, 0)];
//	[super setContentView : frameView];

	[frameView setFrame : bounds];
   
	[frameView setAutoresizingMask: 0];
   
   [m_controller.view addSubview: frameView];
   
   RoundWindowApp * papp = (RoundWindowApp *) [[UIApplication sharedApplication] delegate];
   
   [papp setView: frameView];
   

   
   //
   // setContentView:
   //
   // Keep our frame view as the content view and make the specified "aView"
   // the child of that.
   //
  // - (void)create_view
  // {
      
     // CGRect bounds = [self frame];
      
      //   bounds.origin = CGZeroPoint;
      
      
     // RoundWindowFrameView * frameView = [[RoundWindowFrameView alloc] initWithFrame : bounds] ;
      
     // frameView->m_roundwindow =  self;
      
    //  frameView->m_bShift = false;
     // frameView->m_bControl = false;
      //frameView->m_bAlt = false;
      
     // childContentView = frameView;
      
		
      //	[super setContentView : frameView];
      
      //[frameView setFrame : bounds];
      
    //  [frameView setAutoresizingMask: 0];
      
  //    [ m_controller.view addSubview : frameView];
      
//   }

   
}

//
// contentView
//
// Returns the child of our frame view instead of our frame view.
//
- (UIView *)contentView
{
//	return [super contentView];
    return NULL;
}

//
// canBecomeKeyWindow
//
// Overrides the default to allow a borderless window to be the key window.
//
- (BOOL)canBecomeKeyWindow
{
	return YES;
}

//
// canBecomeMainWindow
//
// Overrides the default to allow a borderless window to be the main window.
//
- (BOOL)canBecomeMainWindow
{
	return YES;
}

//
// contentRectForFrameRect:
//
// Returns the rect for the content rect, taking the frame.
//
- (CGRect)contentRectForFrameRect:(CGRect)windowFrame
{
  // bounds = windowFrame;
//
	//windowFrame.origin = NSZeroPoint;
    windowFrame.origin.x = 0;
    windowFrame.origin.y = 0;
    windowFrame.origin.x += NS_ROUND_WINDOW_FRAME_PADDING;
    windowFrame.origin.y += NS_ROUND_WINDOW_FRAME_PADDING;
    windowFrame.size.width -= 2 * NS_ROUND_WINDOW_FRAME_PADDING;
    windowFrame.size.height -= 2 * NS_ROUND_WINDOW_FRAME_PADDING;
	return windowFrame;
}

//
// frameRectForContentRect:styleMask:
//
// Ensure that the window is make the appropriate amount bigger than the content.
//
+ (CGRect)frameRectForContentRect:(CGRect)windowContentRect styleMask:(NSUInteger)windowStyle
{
    windowContentRect.origin.x = 0;
    windowContentRect.origin.y = 0;
    windowContentRect.origin.x -= NS_ROUND_WINDOW_FRAME_PADDING;
    windowContentRect.origin.y -= NS_ROUND_WINDOW_FRAME_PADDING;
    windowContentRect.size.width += 2 * NS_ROUND_WINDOW_FRAME_PADDING;
    windowContentRect.size.height += 2 * NS_ROUND_WINDOW_FRAME_PADDING;
	return windowContentRect;
}



- (void) unsafe_boot_window_has_focus : (bool *) pbool
{

  /* NSWindow * pkeywindow = [NSApp keyWindow];
   
   NSWindow * pwindow = self;
   
   if(pkeywindow != NULL)
   {

      *pbool = pkeywindow == pwindow;
      
   
   }
   else
   {
      *pbool = false;
   }*/
    
    
}


- (void)windowDidResize:(NSNotification *)notification
{
   
   
   try
   {
      
      CGRect rect = [self frame];
      
      int cx = rect.size.width;
      
      int cy = rect.size.height;
 
      m_pwindow->round_window_resized(cx, cy);
      
   }
   catch (...)
   {
      
   }
   
   
}



- (void)windowDidMove:(NSNotification *)notification
{
   
   try
   {
      
//      NSRect rect = [self frame];
//      
//      CGPoint point;
//      
//      point.x        = rect.origin.x;
//      
//      point.y        = [[NSScreen mainScreen] frame ].size.height - (rect.origin.y + rect.size.height);
//      
//      m_pwindow->round_window_moved(point);
      
   }
   catch (...)
   {
      
   }
   
}

-(void)windowDidExpose
{
   
   try
   {
      
      m_pwindow->round_window_on_show();
      
   }
   catch (...)
   {
      
   }
   
}



-(void)windowWillClose
{
   
   try
   {
      
      m_pwindow->round_window_on_hide();
      
   }
   catch (...)
   {
      
   }
   
}



//
// contentRectForFrameRect:
//
// Returns the rect for the content rect, taking the frame.
//
/*- (CGRect)contentRectForFrameRect:(CGRect)windowFrame
{
  // bounds = windowFrame;
//	windowFrame.origin = NSZeroPoint;
//	return NSInsetRect(windowFrame, NS_ROUND_WINDOW_FRAME_PADDING, NS_ROUND_WINDOW_FRAME_PADDING);
}

//
// frameRectForContentRect:styleMask:
//
// Ensure that the window is make the appropriate amount bigger than the content.
//
+ (NSRect)frameRectForContentRect:(NSRect)windowContentRect styleMask:(NSUInteger)windowStyle
{
	return NSInsetRect(windowContentRect, -NS_ROUND_WINDOW_FRAME_PADDING, -NS_ROUND_WINDOW_FRAME_PADDING);
}
*/

- (void) on_destroy;
{
   
   m_pwindow = NULL;
   
   m_controller->childContentView->m_roundwindow = nil;
   
   m_controller->childContentView = nil;
   
//   [m_controller release];
   
}





@end
