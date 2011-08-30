// this file is part of liqbase by Gary Birkett
		
#include <liqbase/liqbase.h>
#include <liqbase/liqcell.h>
#include <liqbase/liqcell_prop.h>
#include <liqbase/liqcell_easyrun.h>
#include <liqbase/liqcell_easyhandler.h>
		
		
//#####################################################################
//#####################################################################
//##################################################################### liqtasks_new :: by gary birkett
//#####################################################################
//#####################################################################
		
		
/**	
 * liqtasks_new widget filter, the system is asking you to filter to the specified .
 */	
static int liqtasks_new_filter(liqcell *self,liqcellfiltereventargs *args, liqcell *context)
{
	// system is indicating the user has typed into the search box
	// you are expected to filter your content based upon this searchterm.
	// show or hide details and rearrange contents to apply this filter.
	char *searchterm = NULL;
	args->resultoutof=0;  // total number of searchable contents
	args->resultshown=0;  // count of options remaining after filtering.
	searchterm = args->searchterm;
	if(searchterm && *searchterm)
	{
		 // check the name property
		 args->resultoutof++;
		 if( stristr(self->name,searchterm) != NULL )
		 {
			  args->resultshown++;
		 }
		 // check the classname property
		 args->resultoutof++;
		 if( stristr(self->classname,searchterm) != NULL )
		 {
			  args->resultshown++;
		 }
		 // check any other properties or children and increment counters
		 // filter out list items recursively
	}
	return 0;
}
/**	
 * liqtasks_new widget refresh, all params set, present yourself to the user.
 */	
static int liqtasks_new_refresh(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	return 0;
}
/**	
 * liqtasks_new dialog_open - the user zoomed into the dialog
 */	
static int liqtasks_new_dialog_open(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	 return 0;
}
/**	
 * liqtasks_new dialog_close - the dialog was closed
 */	
static int liqtasks_new_dialog_close(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	 return 0;
}
/**	
 * liqtasks_new widget shown - occurs once per lifetime
 */	
static int liqtasks_new_shown(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	return 0;
}
/**	
 * liqtasks_new mouse - occurs all the time as you stroke the screen
 */	
static int liqtasks_new_mouse(liqcell *self, liqcellmouseeventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * liqtasks_new click - occurs when a short mouse stroke occured
 */	
static int liqtasks_new_click(liqcell *self, liqcellclickeventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * liqtasks_new keypress - the user pressed a key
 */	
static int liqtasks_new_keypress(liqcell *self, liqcellkeyeventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * liqtasks_new keyrelease - the user released a key
 */	
static int liqtasks_new_keyrelease(liqcell *self, liqcellkeyeventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * liqtasks_new paint - being rendered.  use the vgraph held in args to do custom drawing at scale
 */	
//static int liqtasks_new_paint(liqcell *self, liqcellpainteventargs *args,liqcell *context)
//{
//	// big heavy event, use sparingly
//	return 0;
//}
/**	
 * liqtasks_new dynamic resizing
 */	
static int liqtasks_new_resize(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	float iw=((float)self->w);
	float ih=((float)self->h);
	
	liqcell *editor = liqcell_child_lookup(self, "editor");
	liqcell *title = liqcell_child_lookup(self, "title");
	liqcell *cmdsave = liqcell_child_lookup(self, "cmdsave");
	liqcell_setrect( editor, iw*0.000,ih*0.000, iw*1.000,ih*1.002);
	liqcell_setrect( title, iw*0.000,ih*0.000, iw*1.000,ih*0.110);
	liqcell_setrect( cmdsave, iw*0.742,ih*0.900, iw*0.258,ih*0.102);
	return 0;
}

/**	
 * liqtasks_new dynamic layout
 */	
static int liqtasks_new_layout(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	float ww=canvas.pixelwidth;
	float hh=canvas.pixelheight;
	liqcell_setrect(self,		0,0,  ww,hh);
	return 0;
}
/**	
 * liqtasks_new.cmdsave clicked
 */	
static int cmdsave_click(liqcell *self,liqcellclickeventargs *args, liqcell *liqtasks_new)
{
	return 0;
}
/**	
 * liqtasks_new_child_test_seek this function shows how to access members
 */	
	  
static void liqtasks_new_child_test_seek(liqcell *liqtasks_new)
{	  
	liqcell *editor = liqcell_child_lookup(liqtasks_new, "editor");
	liqcell *title = liqcell_child_lookup(liqtasks_new, "title");
	liqcell *cmdsave = liqcell_child_lookup(liqtasks_new, "cmdsave");
}	  
/**	
 * create a new liqtasks_new widget
 */	
liqcell *liqtasks_new_create()
{
	liqcell *self = liqcell_quickcreatewidget("liqtasks_new", "form", 800, 480);
	if(!self) {liqapp_log("liqcell error not create 'liqtasks_new'"); return NULL;  } 
	
	// Optimization:  The aim is to REDUCE the number of drawn layers and operations called.
	// Optimization:  use only what you NEED to get an effect
	// Optimization:  Minimal layers and complexity
	// Optimization:  defaults: background, prefer nothing, will be shown through if there is a wallpaper
	// Optimization:  defaults: text, white, very fast rendering
	//############################# editor:label
	liqcell *editor = liqcell_quickcreatevis("editor", "label", 0, 0, 800, 480);
	liqcell_setfont(	editor, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (12), 0) );
	liqcell_setcaption(editor, "backplane" );
	liqcell_propsets(  editor, "textcolor", "rgb(255,0,0)" );
	liqcell_propsets(  editor, "backcolor", "rgb(64,64,64)" );
	liqcell_propseti(  editor, "textalign", 2 );
	liqcell_propseti(  editor, "textaligny", 2 );
	liqcell_child_append(  self, editor);
	//############################# title:label
	liqcell *title = liqcell_quickcreatevis("title", "label", 0, 0, 800, 52);
	liqcell_setfont(	title, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (29), 0) );
	liqcell_setcaption(title, "New Task" );
	liqcell_propsets(  title, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  title, "backcolor", "xrgb(128,128,128)" );
	liqcell_propseti(  title, "textalign", 0 );
	liqcell_propseti(  title, "textaligny", 0 );
	liqcell_child_append(  self, title);
	//############################# cmdsave:label
	liqcell *cmdsave = liqcell_quickcreatevis("cmdsave", "label", 594, 432, 206, 48);
	liqcell_setfont(	cmdsave, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (29), 0) );
	liqcell_setcaption(cmdsave, "Save" );
	liqcell_propsets(  cmdsave, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  cmdsave, "backcolor", "xrgb(0,64,0)" );
	liqcell_propsets(  cmdsave, "bordercolor", "rgb(255,255,255)" );
	liqcell_propseti(  cmdsave, "textalign", 2 );
	liqcell_propseti(  cmdsave, "textaligny", 2 );
	liqcell_handleradd_withcontext(cmdsave, "click", (void*)cmdsave_click, self );
	liqcell_child_append(  self, cmdsave);
	//liqcell_propsets(  self, "backcolor", "rgb(0,0,0)" );
	//liqcell_setimage(  self ,  liqimage_cache_getfile( "/usr/share/liqbase/liqtasks/media/liqtasks_new_back.png",0,0,0) );
	liqcell_handleradd_withcontext(self, "filter",		 (void*)liqtasks_new_filter ,self);
	liqcell_handleradd_withcontext(self, "refresh",		(void*)liqtasks_new_refresh ,self);
	liqcell_handleradd_withcontext(self, "shown",		  (void*)liqtasks_new_shown ,self);
	liqcell_handleradd_withcontext(self, "resize",	  (void*)liqtasks_new_resize ,self);
	liqcell_handleradd_withcontext(self, "layout",	  (void*)liqtasks_new_layout ,self);
	//liqcell_handleradd_withcontext(self, "keypress",	(void*)liqtasks_new_keypress,self );
	//liqcell_handleradd_withcontext(self, "keyrelease", (void*)liqtasks_new_keyrelease ,self);
	//liqcell_handleradd_withcontext(self, "mouse",		(void*)liqtasks_new_mouse,self );
	//liqcell_handleradd_withcontext(self, "click",		(void*)liqtasks_new_click ,self);
	//liqcell_handleradd_withcontext(self, "paint",		(void*)liqtasks_new_paint ,self); // use only if required, heavyweight
	liqcell_handleradd_withcontext(self, "dialog_open",  (void*)liqtasks_new_dialog_open ,self);
	liqcell_handleradd_withcontext(self, "dialog_close", (void*)liqtasks_new_dialog_close ,self);
	return self;
}

