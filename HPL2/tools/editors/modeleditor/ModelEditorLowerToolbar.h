/*
 * Copyright © 2009-2020 Frictional Games
 * 
 * This file is part of Amnesia: The Dark Descent.
 * 
 * Amnesia: The Dark Descent is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version. 

 * Amnesia: The Dark Descent is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with Amnesia: The Dark Descent.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef MODEL_EDITOR_LOWER_TOOLBAR_H
#define MODEL_EDITOR_LOWER_TOOLBAR_H

#include "../common/StdAfx.h"
using namespace hpl;

#include "../common/EditorWindowLowerToolbar.h"

//---------------------------------------------------------------

class cModelEditorLowerToolbar : public iEditorWindowLowerToolbar
{
public:
	cModelEditorLowerToolbar(iEditorBase* apEditor);
	~cModelEditorLowerToolbar();

	void OnUpdate(float afTimeStep);

protected:
	////////////////////////////////
	// Own functions
	bool ButtonPressed(iWidget* apWidget, const cGuiMessageData& aData);
	kGuiCallbackDeclarationEnd(ButtonPressed);
	
	////////////////////////////////
	// Implemented functions
	void OnInitLayout();

	////////////////////////////////
	// Data
	cWidgetButton* mpButtonTest;

	iEditorWindow* mpTestWindow;

	//Credits
	cWidgetDummy* mpVersionLabelDummy;
	cWidgetLabel* mpVersionLabel;
	cWidgetImage* mpVanityLogo;
};

//--------------------------------------------------------------------

#endif //MODEL_EDITOR_LOWER_TOOLBAR_H
