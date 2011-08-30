// this file is part of liqbase by Gary Birkett
		
#include <liqbase/liqbase.h>
#include <liqbase/liqcell.h>
#include <liqbase/liqcell_prop.h>
#include <liqbase/liqcell_easyrun.h>
#include <liqbase/liqcell_easyhandler.h>
#include <liqbase/liqtag.h>
			
		
//#####################################################################
//#####################################################################
//##################################################################### liqtasks_run :: by gary birkett
//#####################################################################
//#####################################################################
		
		
/**	
 * liqtasks_run widget filter, the system is asking you to filter to the specified .
 */	
static int liqtasks_run_filter(liqcell *self,liqcellfiltereventargs *args, liqcell *context)
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
 * liqtask_item click - occurs when a short mouse stroke occured
 */	
static int liqtask_itemtodo_click(liqcell *self, liqcellclickeventargs *args,liqcell *liqtasks)
{
	liqcell *backplane = liqcell_child_lookup(liqtasks, "backplane");
		liqcell *bodytodo = liqcell_child_lookup(backplane, "bodytodo");
		liqcell *bodydone = liqcell_child_lookup(backplane, "bodydone");
		liqcell *bodyarchive = liqcell_child_lookup(backplane, "bodyarchive");
	liqcell *cmdcomplete = liqcell_child_lookup(liqtasks, "cmdcomplete");

	liqcell_setcaption(cmdcomplete,"Complete");
	liqcell_setvisible(cmdcomplete,1);
	liqcell_child_selectnone(bodytodo);
	liqcell_child_selectnone(bodydone);
	liqcell_child_selectnone(bodyarchive);
	liqcell_setselected(self,1);
	return 0;
}
static int liqtask_itemdone_click(liqcell *self, liqcellclickeventargs *args,liqcell *liqtasks)
{
	liqcell *backplane = liqcell_child_lookup(liqtasks, "backplane");
		liqcell *bodytodo = liqcell_child_lookup(backplane, "bodytodo");
		liqcell *bodydone = liqcell_child_lookup(backplane, "bodydone");
		liqcell *bodyarchive = liqcell_child_lookup(backplane, "bodyarchive");
	liqcell *cmdcomplete = liqcell_child_lookup(liqtasks, "cmdcomplete");

	liqcell_setcaption(cmdcomplete,"Archive");
	liqcell_setvisible(cmdcomplete,1);
	liqcell_child_selectnone(bodytodo);
	liqcell_child_selectnone(bodydone);
	liqcell_child_selectnone(bodyarchive);
	liqcell_setselected(self,1);
	return 0;

}
static int liqtask_itemarchive_click(liqcell *self, liqcellclickeventargs *args,liqcell *liqtasks)
{
	liqcell *backplane = liqcell_child_lookup(liqtasks, "backplane");
		liqcell *bodytodo = liqcell_child_lookup(backplane, "bodytodo");
		liqcell *bodydone = liqcell_child_lookup(backplane, "bodydone");
		liqcell *bodyarchive = liqcell_child_lookup(backplane, "bodyarchive");
	liqcell *cmdcomplete = liqcell_child_lookup(liqtasks, "cmdcomplete");

	liqcell_setcaption(cmdcomplete,"Restore");
	liqcell_setvisible(cmdcomplete,0);
	liqcell_child_selectnone(bodytodo);
	liqcell_child_selectnone(bodydone);
	liqcell_child_selectnone(bodyarchive);
	liqcell_setselected(self,1);
	return 0;

}

/**	
 * liqtasks_run widget refresh, all params set, present yourself to the user.
 */	
static int liqtasks_run_refresh(liqcell *self,liqcelleventargs *args, liqcell *liqtasks)
{
	liqcell *backplane = liqcell_child_lookup(liqtasks, "backplane");
		liqcell *todolabel = liqcell_child_lookup(backplane, "todolabel");
		liqcell *bodytodo = liqcell_child_lookup(backplane, "bodytodo");
		liqcell *donelabel = liqcell_child_lookup(backplane, "donelabel");
		liqcell *bodydone = liqcell_child_lookup(backplane, "bodydone");
		liqcell *archivelabel = liqcell_child_lookup(backplane, "archivelabel");
		liqcell *bodyarchive = liqcell_child_lookup(backplane, "bodyarchive");

	liqcell *cmdcomplete = liqcell_child_lookup(liqtasks, "cmdcomplete");

	liqcell_setcaption(cmdcomplete,"Complete");
	liqcell_setvisible(cmdcomplete,0);



		liqtagnode *todo = liqtagcloud_findnode( system_tagcloud, "todo");
		liqtagnode *done = liqtagcloud_findnode( system_tagcloud, "done");
		liqtagnode *archive = liqtagcloud_findnode( system_tagcloud, "archive");

		liqcell_child_removeallvisual(bodytodo);
		liqcell_child_removeallvisual(bodydone);		
		liqcell_child_removeallvisual(bodyarchive);		
		{
			liqtagleaf *leaf = todo->leaffirst;
			while(leaf)
			{
				int isarchive = archive && liqtagnode_findleaf(archive, leaf->key);
				int istodo    = todo    && liqtagnode_findleaf(todo   , leaf->key);
				int isdone    = done    && liqtagnode_findleaf(done   , leaf->key);
				if( istodo && !isdone && !isarchive )
				{
					// add this item if it is not in done
					//if( liqcell_child_lookup_simple( bodytodo, leaf->key) ==NULL)
					{

						liqcell *item = liqcell_quickcreatevis(leaf->key, "sketch", 0, 0, 100,100);
						liqcell_setsketch(item, liqsketch_newfromfile( leaf->filename ) );
						liqcell_handleradd_withcontext(item, "click",		(void*)liqtask_itemtodo_click ,self);
						liqcell_child_insertsortedbyname(  bodytodo, item,0);
					}

				}
				leaf=leaf->linknext;
			}
		}
		{
			liqtagleaf *leaf = done->leaffirst;
			while(leaf)
			{
				int isarchive = archive && liqtagnode_findleaf(archive, leaf->key);
				int istodo    = todo    && liqtagnode_findleaf(todo   , leaf->key);
				int isdone    = done    && liqtagnode_findleaf(done   , leaf->key);
				if( istodo && isdone && !isarchive )
				{
					// add this item if it is in todo
					//if( liqcell_child_lookup_simple( bodydone, leaf->key) ==NULL)
					{
					
						liqcell *item = liqcell_quickcreatevis(leaf->key, "sketch", 0, 0, 100,100);
						liqcell_setsketch(item, liqsketch_newfromfile( leaf->filename ) );
						liqcell_handleradd_withcontext(item, "click",		(void*)liqtask_itemdone_click ,self);
						liqcell_child_insertsortedbyname(  bodydone, item,0);
					}
				}
				leaf=leaf->linknext;
			}
		}
		{
			liqtagleaf *leaf = archive->leaffirst;
			while(leaf)
			{
				int isarchive = archive && liqtagnode_findleaf(archive, leaf->key);
				int istodo    = todo    && liqtagnode_findleaf(todo   , leaf->key);
				int isdone    = done    && liqtagnode_findleaf(done   , leaf->key);
				if( istodo && isdone && isarchive )
				{
					// add this item if it is in todo
					//if( liqcell_child_lookup_simple( bodydone, leaf->key) ==NULL)
					{
					
						liqcell *item = liqcell_quickcreatevis(leaf->key, "sketch", 0, 0, 100,100);
						liqcell_setsketch(item, liqsketch_newfromfile( leaf->filename ) );
						liqcell_handleradd_withcontext(item, "click",		(void*)liqtask_itemarchive_click ,self);
						liqcell_child_insertsortedbyname(  bodyarchive, item,0);
					}
				}
				leaf=leaf->linknext;
			}
		}
		liqcell_handlerrun(self,"layout",NULL);
		liqcell_handlerrun(self,"resize",NULL);
		
	return 0;
}




/**	
 * liqtasks_run dialog_open - the user zoomed into the dialog
 */	
static int liqtasks_run_dialog_open(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	 return 0;
}
/**	
 * liqtasks_run dialog_close - the dialog was closed
 */	
static int liqtasks_run_dialog_close(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	 return 0;
}
/**	
 * liqtasks_run widget shown - occurs once per lifetime
 */	
static int liqtasks_run_shown(liqcell *self,liqcelleventargs *args, liqcell *context)
{




	return 0;
}
/**	
 * liqtasks_run mouse - occurs all the time as you stroke the screen
 */	
static int liqtasks_run_mouse(liqcell *self, liqcellmouseeventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * liqtasks_run click - occurs when a short mouse stroke occured
 */	
static int liqtasks_run_click(liqcell *self, liqcellclickeventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * liqtasks_run keypress - the user pressed a key
 */	
static int liqtasks_run_keypress(liqcell *self, liqcellkeyeventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * liqtasks_run keyrelease - the user released a key
 */	
static int liqtasks_run_keyrelease(liqcell *self, liqcellkeyeventargs *args,liqcell *context)
{
	return 0;
}
/**	
 * liqtasks_run paint - being rendered.  use the vgraph held in args to do custom drawing at scale
 */	
//static int liqtasks_run_paint(liqcell *self, liqcellpainteventargs *args,liqcell *context)
//{
//	// big heavy event, use sparingly
//	return 0;
//}
/**	
 * liqtasks_run dynamic resizing
 */	
static int liqtasks_run_resize(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	float iw=((float)self->w);
	float ih=((float)self->h);
	
	liqcell *cmdnew = liqcell_child_lookup(self, "cmdnew");
	liqcell *cmdcomplete = liqcell_child_lookup(self, "cmdcomplete");
	liqcell *cmdrestore = liqcell_child_lookup(self, "cmdrestore");
	liqcell *backplane = liqcell_child_lookup(self, "backplane");
		liqcell *todolabel = liqcell_child_lookup(backplane, "todolabel");
		liqcell *bodytodo = liqcell_child_lookup(backplane, "bodytodo");
		liqcell *donelabel = liqcell_child_lookup(backplane, "donelabel");
		liqcell *bodydone = liqcell_child_lookup(backplane, "bodydone");
		liqcell *archivelabel = liqcell_child_lookup(backplane, "archivelabel");
		liqcell *bodyarchive = liqcell_child_lookup(backplane, "bodyarchive");


			
			
	liqcell_setrect( donelabel, iw*0.000,ih*0.000, iw*1.000,ih*0.085);
	liqcell_setrect( bodydone, iw*0.000,ih*0.388, iw*1.000,ih*0.0);
	
	liqcell_setrect( todolabel, iw*0.000,ih*0.000, iw*1.000,ih*0.085);
	liqcell_setrect( bodytodo, iw*0.000,ih*0.000, iw*1.000,ih*0.0);
	
	liqcell_setrect( archivelabel, iw*0.000,ih*0.000, iw*1.000,ih*0.085);
	liqcell_setrect( bodyarchive, iw*0.000,ih*0.000, iw*1.000,ih*0.0);
	
	liqcell_setrect( backplane, iw*0.000,ih*0.000, iw*1.000,ih*0.890);



		{
			liqcell *c = liqcell_getlinkchild_visible(bodytodo);
			while(c)
			{
				liqcell_setrect( c, 0,0, iw/6,ih/6);
				c=liqcell_getlinknext_visible(c);
			}
			liqcell_child_arrange_autoflow( bodytodo );
		}

		
		{
			liqcell *c = liqcell_getlinkchild_visible(bodydone);
			while(c)
			{
				liqcell_setrect( c, 0,0, iw/6,ih/6);
				c=liqcell_getlinknext_visible(c);
			}
			liqcell_child_arrange_autoflow( bodydone );
		}
		{
			liqcell *c = liqcell_getlinkchild_visible(bodyarchive);
			while(c)
			{
				liqcell_setrect( c, 0,0, iw/6,ih/6);
				c=liqcell_getlinknext_visible(c);
			}
			liqcell_child_arrange_autoflow( bodyarchive );
		}		
	liqcell_child_arrange_autoflow( backplane );

		liqcell_setrect( bodytodo, iw*0.000,bodytodo->y, iw*1.000,bodytodo->h);
		liqcell_setrect( bodydone, iw*0.000,bodydone->y, iw*1.000,bodydone->h);
		liqcell_setrect( bodyarchive, iw*0.000,bodyarchive->y, iw*1.000,bodyarchive->h);
		liqcell_setrect( backplane, iw*0.000,ih*0.000, iw*1.000,backplane->h);

			
	
	liqcell_setrect( cmdnew, iw*0.826,ih*0.900, iw*0.174,ih*0.102);
	liqcell_setrect( cmdcomplete, iw*0.422,ih*0.900, iw*0.228,ih*0.102);
	liqcell_setrect( cmdrestore, iw*0.657,ih*0.900, iw*0.161,ih*0.102);
	return 0;
}

/**	
 * liqtasks_run dynamic layout
 */	
static int liqtasks_run_layout(liqcell *self,liqcelleventargs *args, liqcell *context)
{
	float ww=canvas.pixelwidth;
	float hh=canvas.pixelheight;
	liqcell_setrect(self,		0,0,  ww,hh);
	return 0;
}
/**	
 * liqtasks_run.cmdnew clicked
 */	
static int cmdnew_click(liqcell *self,liqcellclickeventargs *args, liqcell *liqtasks_run)
{
	liqcell *mydialog = liqcell_quickcreatevis("todo", "liqsketchedit", 0,0, -1,-1);
	liqcell_propsets(mydialog, "monitortag",   "todo" );
	liqcell_easyrun(mydialog);
	liqcell_release(mydialog);

	liqcell_handlerrun(liqtasks_run,"refresh",NULL);
	return 0;
}
/**	
 * liqtasks_run.cmdcomplete clicked
 */	
static int cmdcomplete_click(liqcell *self,liqcellclickeventargs *args, liqcell *liqtasks)
{
	liqcell *backplane = liqcell_child_lookup(liqtasks, "backplane");
		liqcell *bodytodo = liqcell_child_lookup(backplane, "bodytodo");
		liqcell *bodydone = liqcell_child_lookup(backplane, "bodydone");
	liqcell *cmdcomplete = liqcell_child_lookup(liqtasks, "cmdcomplete");

	//################################### check todo
	{
		liqcell *c = liqcell_child_getfirstselected( bodytodo);
		if(c)
		{
			liqsketch *s = liqcell_getsketch(c);
			liqtag_quicksaveas( "done", s->filename );
		}
	}
	//################################### check done
	{
		liqcell *c = liqcell_child_getfirstselected( bodydone);
		if(c)
		{
			liqsketch *s = liqcell_getsketch(c);
			liqtag_quicksaveas( "archive", s->filename );
		}
	}
	//################################### check archive
	{
		liqcell *c = liqcell_child_getfirstselected( bodydone);
		if(c)
		{
			liqsketch *s = liqcell_getsketch(c);
			//liqtag_quicksaveas( "archive", s->filename );
			// this should be cleaning item from tag
		}
	}

	liqcell_handlerrun(liqtasks,"refresh",NULL);


	return 0;
}
/**	
 * liqtasks_run.cmdrestore clicked
 */	
static int cmdrestore_click(liqcell *self,liqcellclickeventargs *args, liqcell *liqtasks_run)
{
	return 0;
}
/**	
 * liqtasks_run_child_test_seek this function shows how to access members
 */	
	  
static void liqtasks_run_child_test_seek(liqcell *liqtasks_run)
{	  
	liqcell *cmdnew = liqcell_child_lookup(liqtasks_run, "cmdnew");
	liqcell *cmdcomplete = liqcell_child_lookup(liqtasks_run, "cmdcomplete");
	liqcell *cmdrestore = liqcell_child_lookup(liqtasks_run, "cmdrestore");
	liqcell *backplane = liqcell_child_lookup(liqtasks_run, "backplane");
		liqcell *todolabel = liqcell_child_lookup(backplane, "todolabel");
		liqcell *bodytodo = liqcell_child_lookup(backplane, "bodytodo");
		liqcell *donelabel = liqcell_child_lookup(backplane, "donelabel");
		liqcell *bodydone = liqcell_child_lookup(backplane, "bodydone");
		liqcell *archivelabel = liqcell_child_lookup(backplane, "archivelabel");
		liqcell *bodyarchive = liqcell_child_lookup(backplane, "bodyarchive");
}	  
/**	
 * create a new liqtasks_run widget
 */	
liqcell *liqtasks_run_create()
{
	liqcell *self = liqcell_quickcreatewidget("liqtasks_run", "form", 800, 480);
	if(!self) {liqapp_log("liqcell error not create 'liqtasks_run'"); return NULL;  } 
	
	// Optimization:  The aim is to REDUCE the number of drawn layers and operations called.
	// Optimization:  use only what you NEED to get an effect
	// Optimization:  Minimal layers and complexity
	// Optimization:  defaults: background, prefer nothing, will be shown through if there is a wallpaper
	// Optimization:  defaults: text, white, very fast rendering

		

	//############################# cmdnew:label
	liqcell *cmdnew = liqcell_quickcreatevis("cmdnew", "label", 662, 432, 138, 48);
	liqcell_setfont(	cmdnew, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (29), 0) );
	liqcell_setcaption(cmdnew, "New" );
	liqcell_propsets(  cmdnew, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  cmdnew, "backcolor", "xrgb(0,64,0)" );
	liqcell_propsets(  cmdnew, "bordercolor", "rgb(255,255,255)" );
	liqcell_propseti(  cmdnew, "textalign", 2 );
	liqcell_propseti(  cmdnew, "textaligny", 2 );
	liqcell_handleradd_withcontext(cmdnew, "click", (void*)cmdnew_click, self );
	liqcell_child_append(  self, cmdnew);
	//############################# cmdcomplete:label
	liqcell *cmdcomplete = liqcell_quickcreatevis("cmdcomplete", "label", 338, 432, 182, 48);
	liqcell_setfont(	cmdcomplete, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (29), 0) );
	liqcell_setcaption(cmdcomplete, "Complete" );
	liqcell_propsets(  cmdcomplete, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  cmdcomplete, "backcolor", "xrgb(0,64,64)" );
	liqcell_propsets(  cmdcomplete, "bordercolor", "rgb(255,255,255)" );
	liqcell_propseti(  cmdcomplete, "textalign", 2 );
	liqcell_propseti(  cmdcomplete, "textaligny", 2 );
	liqcell_handleradd_withcontext(cmdcomplete, "click", (void*)cmdcomplete_click, self );
	liqcell_child_append(  self, cmdcomplete);
	liqcell_setvisible(cmdcomplete,0);
	//############################# cmdrestore:label
	liqcell *cmdrestore = liqcell_quickcreatevis("cmdrestore", "label", 526, 432, 128, 48);
	liqcell_setfont(	cmdrestore, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (29), 0) );
	liqcell_setcaption(cmdrestore, "Restore" );
	liqcell_propsets(  cmdrestore, "textcolor", "rgb(255,255,255)" );
	liqcell_propsets(  cmdrestore, "backcolor", "xrgb(0,64,64)" );
	liqcell_propsets(  cmdrestore, "bordercolor", "rgb(255,255,255)" );
	liqcell_propseti(  cmdrestore, "textalign", 2 );
	liqcell_propseti(  cmdrestore, "textaligny", 2 );
	liqcell_handleradd_withcontext(cmdrestore, "click", (void*)cmdrestore_click, self );
	liqcell_child_append(  self, cmdrestore);
	liqcell_setvisible(cmdrestore,0);


	//############################# backplane:picturebox
	liqcell *backplane = liqcell_quickcreatevis("backplane", "picturebox", 0, 0, 800, 426);
	//liqcell_setfont(	backplane, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (12), 0) );
	//liqcell_propsets(  backplane, "textcolor", "rgb(0,0,0)" );
	//liqcell_propsets(  backplane, "backcolor", "rgb(0,0,0)" );

		//############################# todolabel:label
		liqcell *todolabel = liqcell_quickcreatevis("todolabel", "label", 0, 0, 800, 40);
		liqcell_setfont(	todolabel, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (24), 0) );
		liqcell_setcaption(todolabel, "Todo items" );
		liqcell_propsets(  todolabel, "textcolor", "rgb(255,255,255)" );
		liqcell_propsets(  todolabel, "backcolor", "rgb(0,64,0)" );
		liqcell_propseti(  todolabel, "textalign", 0 );
		liqcell_propseti(  todolabel, "textaligny", 0 );
		liqcell_child_append(  backplane, todolabel);

		//############################# bodytodo:picturebox
		liqcell *bodytodo = liqcell_quickcreatevis("bodytodo", "picturebox", 0, 0, 800, 176);
		//liqcell_setfont(	bodytodo, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (12), 0) );
		//liqcell_propsets(  bodytodo, "textcolor", "rgb(0,0,0)" );
		liqcell_propsets(  bodytodo, "backcolor", "rgb(0,32,0)" );
		liqcell_child_append(  backplane, bodytodo);

		//############################# donelabel:label
		liqcell *donelabel = liqcell_quickcreatevis("donelabel", "label", 0, 0, 800, 40);
		liqcell_setfont(	donelabel, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (24), 0) );
		liqcell_setcaption(donelabel, "Completed items" );
		liqcell_propsets(  donelabel, "textcolor", "rgb(255,255,255)" );
		liqcell_propsets(  donelabel, "backcolor", "rgb(0,64,64)" );
		liqcell_propseti(  donelabel, "textalign", 0 );
		liqcell_propseti(  donelabel, "textaligny", 0 );
		liqcell_child_append(  backplane, donelabel);
			
		//############################# bodydone:picturebox
		liqcell *bodydone = liqcell_quickcreatevis("bodydone", "picturebox", 0, 186, 800, 176);
		//liqcell_setfont(	bodydone, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (12), 0) );
		//liqcell_propsets(  bodydone, "textcolor", "rgb(0,0,0)" );
		liqcell_propsets(  bodydone, "backcolor", "rgb(0,32,32)" );

		liqcell_child_append(  backplane, bodydone);


		//############################# donelabel:label
		liqcell *archivelabel = liqcell_quickcreatevis("archivelabel", "label", 0, 0, 800, 40);
		liqcell_setfont(	archivelabel, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (24), 0) );
		liqcell_setcaption(archivelabel, "Archived items" );
		liqcell_propsets(  archivelabel, "textcolor", "rgb(255,255,255)" );
		liqcell_propsets(  archivelabel, "backcolor", "rgb(64,64,64)" );
		liqcell_propseti(  archivelabel, "textalign", 0 );
		liqcell_propseti(  archivelabel, "textaligny", 0 );
		liqcell_child_append(  backplane, archivelabel);
			
		//############################# bodydone:picturebox
		liqcell *bodyarchive = liqcell_quickcreatevis("bodyarchive", "picturebox", 0, 186, 800, 176);
		//liqcell_setfont(	bodyarchive, liqfont_cache_getttf("/usr/share/fonts/nokia/nosnb.ttf", (12), 0) );
		//liqcell_propsets(  bodyarchive, "textcolor", "rgb(0,0,0)" );
		liqcell_propsets(  bodyarchive, "backcolor", "rgb(32,32,32)" );

		liqcell_child_append(  backplane, bodyarchive);


		liqcell_handleradd(backplane,    "mouse",   liqcell_easyhandler_kinetic_mouse );



		

	liqcell_child_insert(  self, backplane);
	//liqcell_propsets(  self, "backcolor", "rgb(0,0,0)" );
	//liqcell_setimage(  self ,  liqimage_cache_getfile( "/usr/share/liqbase/liqtasks/media/liqtasks_run_back.png",0,0,0) );
	liqcell_handleradd_withcontext(self, "filter",		 (void*)liqtasks_run_filter ,self);
	liqcell_handleradd_withcontext(self, "refresh",		(void*)liqtasks_run_refresh ,self);
	liqcell_handleradd_withcontext(self, "shown",		  (void*)liqtasks_run_shown ,self);
	liqcell_handleradd_withcontext(self, "resize",	  (void*)liqtasks_run_resize ,self);
	liqcell_handleradd_withcontext(self, "layout",	  (void*)liqtasks_run_layout ,self);
	//liqcell_handleradd_withcontext(self, "keypress",	(void*)liqtasks_run_keypress,self );
	//liqcell_handleradd_withcontext(self, "keyrelease", (void*)liqtasks_run_keyrelease ,self);
	//liqcell_handleradd_withcontext(self, "mouse",		(void*)liqtasks_run_mouse,self );
	//liqcell_handleradd_withcontext(self, "click",		(void*)liqtasks_run_click ,self);
	//liqcell_handleradd_withcontext(self, "paint",		(void*)liqtasks_run_paint ,self); // use only if required, heavyweight
	liqcell_handleradd_withcontext(self, "dialog_open",  (void*)liqtasks_run_dialog_open ,self);
	liqcell_handleradd_withcontext(self, "dialog_close", (void*)liqtasks_run_dialog_close ,self);

	liqcell_handlerrun(self,"refresh",NULL);

	return self;
}

