/*
 *  yummy/cheese/widget.c
 *
 *  Copyright (C) 2013-2015  Mateus de Lima Oliveira
 */

#include <cheese.h>
#include <toolkit.h>
#include <debug.h>
#include "widget.h"

#define NUM_GUIDS 43

struct widget_s {
	struct guid_s guid;
	char *name;
	void (*create)();
	void (*destroy)();
};

static const struct widget_s widgets[] = {
	{
		.name = "Object",
		.guid = {0x51654971, 0x0d87, 0x4a51,
			{0x91, 0xe3, 0xa6, 0xb5, 0x32, 0x35, 0xf3, 0xe7}},
	},
	
	{
		.name = "System",
		.guid = {0xd6f50f64, 0x93fa, 0x49b7,
			{0x93, 0xf1, 0xba, 0x66, 0xef, 0xae, 0x3e, 0x98}},
	},
	
	{
		.name = "Container",
		.guid = {0xe90dc47b, 0x840d, 0x4ae7,
			{0xb0, 0x2c, 0x04, 0x0b, 0xd2, 0x75, 0xf7, 0xfc}},
	},
	
	{
		.name = "Wac",
		.guid = {0x00c074a0, 0xfea2, 0x49a0,
			{0xbe, 0x8d, 0xfa, 0xbb, 0xdb, 0x16, 0x16, 0x40}},
	},
	
	{
		.name = "List",
		.guid = {0xb2023ab5, 0x434d, 0x4ba1,
			{0xbe, 0xae, 0x59, 0x63, 0x75, 0x03, 0xf3, 0xc6}},
	},
	
	{
		.name = "BitList",
		.guid = {0x87c65778, 0xe743, 0x49fe,
			{0x85, 0xf9, 0x09, 0xcc, 0x53, 0x2a, 0xfd, 0x56}},
	},
	
	{
		.name = "Map",
		.guid = {0x38603665, 0x461b, 0x42a7,
			{0xaa, 0x75, 0xd8, 0x3f, 0x66, 0x67, 0xbf, 0x73}},
	},
	
	{
		.name = "PopupMenu",
		.guid = {0xf4787af4, 0xb2bb, 0x4ef7,
			{0x9c, 0xfb, 0xe7, 0x4b, 0xa9, 0xbe, 0xa8, 0x8d}},
	},
	
	{
		.name = "Region",
		.guid = {0x3a370c02, 0x3cbf, 0x439f,
			{0x84, 0xf1, 0x86, 0x88, 0x5b, 0xcf, 0x1e, 0x36}},
	},
	
	{
		.name = "Timer",
		.guid = {0x5d0c5bb6, 0x7de1, 0x4b1f,
			{0xa7, 0x0f, 0x8d, 0x16, 0x59, 0x94, 0x19, 0x41}},
	},
	
	{
		.name = "FeedWatcher",
		.guid = {0xa5376fa1, 0x4e94, 0x411a,
			{0x83, 0xf6, 0x05, 0xec, 0x5e, 0xea, 0x5f, 0x0a}},
	},
	
	{
		.name = "GuiObject",
		.guid = {0x4ee3e199, 0xc636, 0x4bec,
			{0x97, 0xcd, 0x78, 0xbc, 0x9c, 0x86, 0x28, 0xb0}},
	},
	
	{
		.name = "Group",
		.guid = {0x45be95e5, 0x2072, 0x4191,
			{0x93, 0x5c, 0xbb, 0x5f, 0xf9, 0xf1, 0x17, 0xfd}},
	},
	
	{
		.name = "Layout",
		.guid = {0x60906d4e, 0x537e, 0x482e,
			{0xb0, 0x04, 0xcc, 0x94, 0x61, 0x88, 0x56, 0x72}},
	},
	
	{
		.name = "WindowHolder",
		.guid = {0x403abcc0, 0x6f22, 0x4bd6,
			{0x8b, 0xa4, 0x10, 0xc8, 0x29, 0x93, 0x25, 0x47}},
	},
	
	{
		.name = "ComponentBucket",
		.guid = {0x97aa3e4d, 0xf4d0, 0x4fa8,
			{0x81, 0x7b, 0x0a, 0xf2, 0x2a, 0x45, 0x49, 0x83}},
	},
	
	{
		.name = "Edit",
		.guid = {0x64e4bbfa, 0x81f4, 0x49d9,
			{0xb0, 0xc0, 0xa8, 0x5b, 0x2e, 0xc3, 0xbc, 0xfd}},
	},
	
	{
		.name = "Slider",
		.guid = {0x62b65e3f, 0x375e, 0x408d,
			{0x8d, 0xea, 0x76, 0x81, 0x4a, 0xb9, 0x1b, 0x77}},
	},
	
	{
		.name = "Vis",
		.guid = {0xce4f97be, 0x77b0, 0x4e19,
			{0x99, 0x56, 0xd4, 0x98, 0x33, 0xc9, 0x6c, 0x27}},
	},
	
	{
		.name = "Browser",
		.guid = {0xa8c2200d, 0x51eb, 0x4b2a,
			{0xba, 0x7f, 0x5d, 0x4b, 0xc6, 0x5d, 0x4c, 0x71}},
	},
	
	{
		.name = "EqVis",
		.guid = {0x8d1eba38, 0x489e, 0x483e,
			{0xb9, 0x60, 0x8d, 0x1f, 0x43, 0xc5, 0xc4, 0x05}},
	},
	
	{
		.name = "Staus",
		.guid = {0x0f08c940, 0xaf39, 0x4b23,
			{0x80, 0xf3, 0xb8, 0xc4, 0x8f, 0x7e, 0xbb, 0x59}},
	},
	
	{
		.name = "Text",
		.guid = {0xefaa8672, 0x310e, 0x41fa,
			{0xb7, 0xdc, 0x85, 0xa9, 0x52, 0x5b, 0xcb, 0x4b}},
	},
	
	{
		.name = "Title",
		.guid = {0x7dfd3244, 0x3751, 0x4e7c,
			{0xbf, 0x40, 0x82, 0xae, 0x5f, 0x3a, 0xdc, 0x33}},
	},
	
	{
		.name = "Layer",
		.guid = {0x5ab9fa15, 0x9a7d, 0x4557,
			{0xab, 0xc8, 0x65, 0x57, 0xa6, 0xc6, 0x7c, 0xa9}},
	},
	
	{
		.name = "Button",
		.guid = {0x698eddcd, 0x8f1e, 0x4fec,
			{0x9b, 0x12, 0xf9, 0x44, 0xf9, 0x09, 0xff, 0x45}},
	},
	
	{
		.name = "AnimatedLayer",
		.guid = {0x6b64cd27, 0x5a26, 0x4c4b,
			{0x8c, 0x59, 0xe6, 0xa7, 0x0c, 0xf6, 0x49, 0x3a}},
	},
	
	{
		.name = "AlbumArtLayer",
		.guid = 0
	}, 
	
	{
		.name = "ToggleButton",
		.guid = {0xb4dccfff, 0x81fe, 0x4bcc,
			{0x96, 0x1b, 0x72, 0x0f, 0xd5, 0xbe, 0x0f, 0xff}},
	},
	
	{
		.name = "GroupList",
		.guid = {0x01e28ce1, 0xb059, 0x11d5,
			{0x97, 0x9f, 0xe4, 0xde, 0x6f, 0x51, 0x76, 0x0a}},
	},
	
	{
		.name = "CfgGroup",
		.guid = {0x80f0f8bd, 0x1ba5, 0x42a6,
			{0xa0, 0x93, 0x32, 0x36, 0xa0, 0x0c, 0x8d, 0x4a}},
	},
	
	{
		.name = "QueryList",
		.guid = {0xcdcb785d, 0x81f2, 0x4253,
			{0x8f, 0x05, 0x61, 0xb8, 0x72, 0x28, 0x3c, 0xfa}},
	},
	
	{
		.name = "MouseRedir",
		.guid = {0x9b2e341b, 0x6c98, 0x40fa,
			{0x8b, 0x85, 0x0c, 0x1b, 0x6e, 0xe8, 0x94, 0x05}},
	},
	
	{
		.name = "DropDownList",
		.guid = {0x36d59b71, 0x03fd, 0x4af8,
			{0x97, 0x95, 0x05, 0x02, 0xb7, 0xdb, 0x26, 0x7a}},
	},
	
	{
		.name = "LayoutStatus",
		.guid = {0x7fd5f210, 0xacc4, 0x48df,
			{0xa6, 0xa0, 0x54, 0x51, 0x57, 0x6c, 0xdc, 0x76}},
	},
	
	{
		.name = "TabSheet",
		.guid = {0xb5baa535, 0x05b3, 0x4dcb,
			{0xad, 0xc1, 0xe6, 0x18, 0xd2, 0x8f, 0x68, 0x96}},
	},
	
	{
		.name = "GuiList",
		.guid = {0x6129fec1, 0xdab7, 0x4d51,
			{0x91, 0x65, 0x01, 0xca, 0x0c, 0x1b, 0x70, 0xdb}},
	},
	
	{
		.name = "GuiTree",
		.guid = {0xd59514f7, 0xed36, 0x45e8,
			{0x98, 0x0f, 0x3f, 0x4e, 0xa0, 0x52, 0x2c, 0xd9}},
	},
	
	{
		.name = "TreeItem",
		.guid = {0x9b3b4b82, 0x667a, 0x420e,
			{0x8f, 0xfc, 0x79, 0x41, 0x15, 0x80, 0x9c, 0x02}},
	},
	
	{
		.name = "MenuButton",
		.guid = {0x1d8631c8, 0x80d0, 0x4792,
			{0x9f, 0x98, 0xbd, 0x5d, 0x36, 0xb4, 0x91, 0x36}},
	},
	
	{
		.name = "CheckBox",
		.guid = {0xc7ed3199, 0x5319, 0x4798,
			{0x98, 0x63, 0x60, 0xb1, 0x5a, 0x29, 0x8c, 0xaa}},
	},
	
	{
		.name = "Form",
		.guid = {0x2d2d1376, 0xbe0a, 0x4cb9,
			{0xbc, 0x0c, 0x57, 0xe6, 0xe4, 0xc9, 0x99, 0xf5}},
	},
	
	{
		.name = "Frame",
		.guid = {0xe2bbc14d, 0x84f6, 0x4173,
			{0xbd, 0xb3, 0xb2, 0xeb, 0x2f, 0x66, 0x55, 0x50}},
	},
	
	{
		.name = "Menu"
		.guid = {0x73c00594, 0x961f, 0x401b,
			{0x9b, 0x1b, 0x67, 0x24, 0x27, 0xac, 0x41, 0x65}}
	}
};

#ifdef DEBUG
const char *widget_names[] =
{

	"System",
	"Container",
	"Wac",
	"List",
	"BitList",
	"Map",
	"PopupMenu",
	"Region",
	"Timer",
	"FeedWatcher",
	"GuiObject",
	"Group",
	"Layout",
	"WindowHolder",
	"ComponentBucket",
	"Edit",
	"Slider",
	"Vis",
	"Browser",
	"EqVis",
	"Staus",
	"Text",
	"Title",
	"Layer",
	"Button",
	"AnimatedLayer",
	"AlbumArtLayer",
	"ToggleButton",
	"GroupList",
	"CfgGroup",
	"QueryList",
	"MouseRedir",
	"DropDownList",
	"LayoutStatus",
	"TabSheet",
	"GuiList",
	"GuiTree",
	"TreeItem",
	"MenuButton",
	"CheckBox",
	"Form",
	"Frame",
	"Menu"
};
#endif

void * cheese_create_widget(struct guid_s *guid)
{
	int i;

	DEBUG_TRACE();

	for (i = 0; i < NUM_GUIDS; i++) {
		if (!memcmp(guid, guidsa, sizeof(guid))) {
			DEBUG_PUTS(widget_names[i]);
			return 0;
		}
	}

	return 0;
}
