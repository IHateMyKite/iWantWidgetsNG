Scriptname iWant_Widgets extends SKI_WidgetBase
{iWant Scaleform (Flash) interface for widgets}

String PARAMETER_DEMARC = "|" ; Must match ActionScript code, used to pass strings as arrays, ideally the most unused character possible, really obscure values got messy with Unicode
Bool loadInProgress = False

Int Function loadWidget(String filename, Int xpos = 10000, Int ypos = 10000, Bool visible = False)
	return iwant_widgets_native.LoadWidget(WidgetRoot,filename,xpos,ypos,visible)
EndFunction

Int Function loadLibraryWidget(String filename, Int xpos = 10000, Int ypos = 10000, Bool visible = False)
	String libraryPrefix = "widgets/iwant/widgets/library/"
	String path = libraryPrefix + filename + ".dds"
	return loadWidget(path, xpos, ypos, visible)
EndFunction

Int Function loadText(String displayString, String font = "$EverywhereFont", Int size = 24, Int xpos = 10000, Int ypos = 10000, Bool visible = False)
	return iwant_widgets_native.LoadText(WidgetRoot,displayString,font,size,xpos,ypos,visible)
EndFunction

Int Function loadMeter(Int xpos = 10000, Int ypos = 10000, Bool visible = False)
    return iwant_widgets_native.LoadMeter(WidgetRoot,xpos,ypos,visible)
EndFunction

Function _waitForReadyToLoad()
	int breakout = 0

	; Make sure we have a valid SkyUI widget
	While (WidgetRoot == "")
		Utility.Wait(1.0)
	EndWhile

	; Make sure SkyUI say we're Ready
	While (!Ready)
		Utility.Wait(1.0)
	EndWhile


	; Make sure another loading call is not underway
	While loadInProgress
		Utility.Wait(0.1)

		; Seems like there's a race condition in how this check gets executed (funny since it was made to avoid a different race condition)
		; Based on reports from users, it seems there is a way for parallel changes to loadInProgress to happen
		;  resulting in a corruption of the variable and a permanent true state
		; This new breakout counter code adds a sanity check, arbitrarily I've added logic that loading shouldn't take more than 5 seconds
		; After this arbitrary timer, break out of the loop regardless.  Hopefully the odds of this being incorrect are so low
		;  they will not impact any game in actual practice and forcing the breakout clears the problems users have seen.
		breakout += 1
		If breakout > 50
			loadInProgress = False
		EndIf

	EndWhile
EndFunction

String Function _getMessageFromFlash()
	return "!!!DO NOT USE!!!"
EndFunction

Function setMeterPercent(Int id, Int percent)
    iwant_widgets_native.SetMeterPercent(WidgetRoot,id,percent)
EndFunction

Function setMeterFillDirection(Int id, String direction)
	iwant_widgets_native.SetMeterFillDirection(WidgetRoot,id,direction)
EndFunction

Function sendToBack(Int id)
	iwant_widgets_native.SendToBack(WidgetRoot,id)
EndFunction

Function sendToFront(Int id)
	iwant_widgets_native.SendToFront(WidgetRoot,id)
EndFunction

Function doMeterFlash(Int id)
	iwant_widgets_native.DoMeterFlash(WidgetRoot,id)
EndFunction

Function setMeterRGB(Int id, Int lightR = 255, Int lightG = 255, Int lightB = 255, Int darkR = 0, Int darkG = 0, Int darkB = 0, Int flashR = 127, Int flashG = 127, Int flashB = 127)
	iwant_widgets_native.SetMeterRGB(WidgetRoot,id,lightR,lightG,lightB,darkR,darkG,darkB,flashR,flashG,flashB)
EndFunction

Function setText(Int id, String displayString)
	iwant_widgets_native.SetText(WidgetRoot,id,displayString)
EndFunction

Function appendText(Int id, String displayString)
	iwant_widgets_native.AppendText(WidgetRoot,id,displayString)
EndFunction

Function swapDepths(Int id1, Int id2)
	iwant_widgets_native.swapDepths(WidgetRoot,id1,id2)
EndFunction

Function setPos(Int id, Int xpos, Int ypos)
    iwant_widgets_native.setPos(WidgetRoot,id,xpos,ypos)
EndFunction

Function setSize(Int id, Int h, Int w)
	iwant_widgets_native.setSize(WidgetRoot,id,h,w)
EndFunction

Int Function getXsize(Int id)
	return iwant_widgets_native.GetSize(WidgetRoot,id,0)
EndFunction

Int Function getYsize(Int id)
	return iwant_widgets_native.GetSize(WidgetRoot,id,1)
EndFunction

Function setZoom(Int id, Int xscale, Int yscale)
	iwant_widgets_native.SetZoom(WidgetRoot,id,xscale,yscale)
EndFunction

Function setVisible(Int id, Int visible = 1)
	iwant_widgets_native.SetVisible(WidgetRoot,id,visible)
EndFunction

Function setRotation(Int id, Int rotation)
	iwant_widgets_native.SetRotation(WidgetRoot,id,rotation)
EndFunction

Function setTransparency(Int id, Int a)
	iwant_widgets_native.SetTransparency(WidgetRoot,id,a)
EndFunction

Function setRGB(Int id, Int r, Int g, Int b)
	iwant_widgets_native.SetRGB(WidgetRoot,id,r,g,b)
EndFunction

Function destroy(Int id)
	iwant_widgets_native.Destroy(WidgetRoot,id)
EndFunction

Function drawShapeLine(Int[] list, Int XPos = 639, Int YPos = 359, Int XChange = 25, Int YChange = 25, Bool skipInvisible = True, Bool skipAlpha0 = True)
    iwant_widgets_native.drawShapeLine(WidgetRoot,list,XPos,YPos,XChange,YChange,skipInvisible,skipAlpha0)
EndFunction

Function drawShapeCircle(Int[] list, Int XPos = 639, Int YPos = 359, Int radius = 50, Int startAngle = 0, Int degreeChange = 45, Bool skipInvisible = True, Bool skipAlpha0 = True, Bool autoSpace = False)
	iwant_widgets_native.drawShapeCircle(WidgetRoot,list,XPos,YPos,radius,startAngle,degreeChange,skipInvisible,skipAlpha0,autoSpace)
EndFunction

Function drawShapeOrbit(Int[] list, Int XPos = 639, Int YPos = 359, Int radius = 50, Int startAngle = 0, Int degreeChange = 45, Bool skipInvisible = True, Bool skipAlpha0 = True, Bool autoSpace = False)
	iwant_widgets_native.drawShapeOrbit(WidgetRoot,list,XPos,YPos,radius,startAngle,degreeChange,skipInvisible,skipAlpha0,autoSpace)
EndFunction

Function doTransition(Int id, Int targetValue, Int frames = 60, String targetAttribute = "alpha", String easingClass = "none", String easingMethod = "none", Int delay = 0)
	doTransitionByFrames(id, targetValue, frames, targetAttribute, easingClass, easingMethod, delay, fps = 30)
EndFunction

Function doTransitionByFrames(Int id, Int targetValue, Int frames = 120, String targetAttribute = "alpha", String easingClass = "none", String easingMethod = "none", Int delay = 0, Int fps = 60)
	String[] value
	String s
	Int i = 0
	Float seconds
	Float delaySeconds

	seconds = (frames As Float) / (fps As Float)
	delaySeconds = (delay As Float) / (fps As Float)

	doTransitionByTime(id, targetValue, seconds, targetAttribute, easingClass, easingMethod, delaySeconds)
EndFunction

Function doTransitionByTime(Int id, Int targetValue, Float seconds = 2.0, String targetAttribute = "alpha", String easingClass = "none", String easingMethod = "none", Float delay = 0.0)
	iwant_widgets_native.DoTransitionByTime(WidgetRoot,id,targetValue,seconds,targetAttribute,easingClass,easingMethod,delay)
EndFunction

Function setAllVisible(Bool visible = True)
	UI.InvokeBool(HUD_MENU, WidgetRoot + ".setAllVisible", visible)
EndFunction

String Function _serializeArray(String[] a)
	Int i;
	String s = "";
	
	; Avoid demarc after last value
	While (i < (a.Length - 1))
		s += a[i]+PARAMETER_DEMARC
		i += 1
	EndWhile
	
	s += a[a.Length - 1]
	
	Return (s)
EndFunction

Function logWidgetData(Int id)
	String[] value
	String s

	value = Utility.CreateStringArray(1, "")
	value[0] = id As String
	s = _serializeArray(value)
	UI.InvokeString(HUD_MENU, WidgetRoot + ".loadWidgetData", s)
	
	Debug.Trace("======logWidgetData Start=======")

	Debug.Trace("Calculated Name: "+UI.GetString(HUD_MENU, WidgetRoot + ".widget_namecalc"))
	Debug.Trace("Object Name: "+UI.GetString(HUD_MENU, WidgetRoot + ".widget_name"))
	Debug.Trace("X: "+UI.GetInt(HUD_MENU, WidgetRoot + ".widget_x"))
	Debug.Trace("Y: "+UI.GetInt(HUD_MENU, WidgetRoot + ".widget_y"))
	Debug.Trace("Height: "+UI.GetInt(HUD_MENU, WidgetRoot + ".widget_height"))
	Debug.Trace("Width: "+UI.GetInt(HUD_MENU, WidgetRoot + ".widget_width"))
	Debug.Trace("Xscale: "+UI.GetInt(HUD_MENU, WidgetRoot + ".widget_xscale"))
	Debug.Trace("Yscale: "+UI.GetInt(HUD_MENU, WidgetRoot + ".widget_yscale"))
	Debug.Trace("Rotation: "+UI.GetInt(HUD_MENU, WidgetRoot + ".widget_rotation"))
	Debug.Trace("Alpha: "+UI.GetInt(HUD_MENU, WidgetRoot + ".widget_alpha"))
	Debug.Trace("Visible: "+UI.GetBool(HUD_MENU, WidgetRoot + ".widget_visible"))

	Debug.Trace("=======logWidgetData End========")

EndFunction

Function triggerReset()
	Debug.Trace("iWant Widgets: ***LIBRARY RESET***")
	UI.Invoke(HUD_MENU, WidgetRoot + "._reset")
	RegisterForModEvent("iWantWidgetsReset", "OniWantWidgetsReset")
	SendModEvent("iWantWidgetsReset")
EndFunction

Event OniWantWidgetsReset(String eventName, String strArg, Float numArg, Form sender)
	Debug.Trace("iWant Widgets: iWant Widgets Reset Event Fired")
EndEvent

Function setSkyrimTemperature(Int level)
	;0 = Neutral
	;1 = Fire
	;2 = Warm
	;3 = Cold
	;4 = Freezing

	UI.InvokeInt("HUD Menu", "_root.HUDMovieBaseInstance.SetCompassTemperature", level)
	UI.Invoke   ("HUD Menu", "_root.HUDMovieBaseInstance.TemperatureMeterAnim")
EndFunction

Function setSkyrimHealthMeterPercent(Int percent)
	UI.InvokeInt("HUD Menu", "_root.HUDMovieBaseInstance.SetHealthMeterPercent", percent)
EndFunction

Function setSkyrimStaminaMeterPercent(Int percent)
	UI.InvokeInt("HUD Menu", "_root.HUDMovieBaseInstance.SetStaminaMeterPercent", percent)
EndFunction

Function setSkyrimMagickaMeterPercent(Int percent)
	UI.InvokeInt("HUD Menu", "_root.HUDMovieBaseInstance.SetMagickaMeterPercent", percent)
EndFunction

String Function _getSkyrimTargetBase(String element)
	String targetBase = ""
	
	If element == "health"
		targetBase = "_root.HUDMovieBaseInstance.Health."
	ElseIf element == "magicka"
		targetBase = "_root.HUDMovieBaseInstance.Magica."
	ElseIf element == "stamina"
		targetBase = "_root.HUDMovieBaseInstance.Stamina."
	ElseIf element == "enemyhealth"
		targetBase = "_root.HUDMovieBaseInstance.EnemyHealth."
	ElseIf element == "crosshair"
		targetBase = "_root.HUDMovieBaseInstance.CrosshairInstance."
	ElseIf element == "crosshairalert"
		targetBase = "_root.HUDMovieBaseInstance.CrosshairAlert."
	ElseIf element == "stealthmeter"
		targetBase = "_root.HUDMovieBaseInstance.StealthMeterInstance."
	ElseIf element == "questmarker"
		targetBase = "_root.HUDMovieBaseInstance.FloatingQuestMarker."
	ElseIf element == "compass"
		targetBase = "_root.HUDMovieBaseInstance.CompassShoutMeterHolder."
	EndIf
	
	Return(targetBase)
EndFunction

Function setSkyrimTransparency(String element, Int a = 100)
	String targetBase = _getSkyrimTargetBase(element)
	String attribute = "_alpha"
	
	If targetBase != ""
		UI.SetInt(HUD_MENU, (targetBase + attribute), a)
	EndIf
EndFunction

Function setSkyrimZoom(String element, Int xscale = 100, Int yscale = 100)
	String targetBase = _getSkyrimTargetBase(element)
	String attribute = "_xscale"
	
	If targetBase != ""
		UI.SetInt(HUD_MENU, (targetBase + attribute), xscale)
		attribute = "_yscale"
		UI.SetInt(HUD_MENU, (targetBase + attribute), yscale)
	EndIf
EndFunction

Function setSkyrimVisible(String element, Int visible = 1)
	String targetBase = _getSkyrimTargetBase(element)
	String attribute = "_visible"
	
	If targetBase != ""
		UI.SetInt(HUD_MENU, (targetBase + attribute), visible)
	EndIf
EndFunction

Function _setSkyrimPos(String element, Int xpos = 0, Int ypos = 0)
	; This function is undocumented and included for experimentation only
	; Do not expect it to be available in all future releases
	String targetBase = _getSkyrimTargetBase(element)
	String attribute = "_x"
	
	If targetBase != ""
		UI.SetInt(HUD_MENU, (targetBase + attribute), xpos)
		attribute = "_y"
		UI.SetInt(HUD_MENU, (targetBase + attribute), ypos)
	EndIf
EndFunction

Int Function _getSkyrimXPos(String element)
	; This function is undocumented and included for experimentation only
	; Do not expect it to be available in all future releases
	String targetBase = _getSkyrimTargetBase(element)
	String attribute = "_x"
	
	If targetBase != ""
		Return(UI.GetInt(HUD_MENU, (targetBase + attribute)))
	EndIf
EndFunction

Int Function _getSkyrimYPos(String element)
	; This function is undocumented and included for experimentation only
	; Do not expect it to be available in all future releases
	String targetBase = _getSkyrimTargetBase(element)
	String attribute = "_y"
	
	If targetBase != ""
		Return(UI.GetInt(HUD_MENU, (targetBase + attribute)))
	EndIf
EndFunction

Function _setSkyrimSize(String element, Int h, Int w)
	; This function is undocumented and included for experimentation only
	; Do not expect it to be available in all future releases
	String targetBase = _getSkyrimTargetBase(element)
	String attribute = "_height"
	
	If targetBase != ""
		UI.SetInt(HUD_MENU, (targetBase + attribute), h)
		attribute = "_width"
		UI.SetInt(HUD_MENU, (targetBase + attribute), w)
	EndIf
EndFunction

Function _setSkyrimRotation(String element, Int rot = 0)
	; This function is undocumented and included for experimentation only
	; Do not expect it to be available in all future releases
	String targetBase = _getSkyrimTargetBase(element)
	String attribute = "_rotation"
	
	If targetBase != ""
		UI.SetInt(HUD_MENU, (targetBase + attribute), rot)
	EndIf
EndFunction

Event OnWidgetReset()
	; Overrides SKI_WidgetBase
	Parent.OnWidgetReset()
	
	triggerReset()
EndEvent

String Function GetWidgetSource()
	; Overrides SKI_WidgetBase
	Return("iwant\\widgets\\iWantWidgets.swf")
EndFunction

String Function GetWidgetType()
	; Overrides SKI_WidgetBase
	; Must be the same as script name
	Return "iWant_Widgets"
endFunction
