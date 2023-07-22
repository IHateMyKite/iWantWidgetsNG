Scriptname iwant_widgets_native hidden

;loading
Int Function LoadMeter(String asRoot,Int aiXPos = 10000, Int aiYPos = 10000, Bool abVisible = False) global native
Int Function LoadText(String asRoot, String asDisplayString, String asFont = "$EverywhereFont", Int asSize = 24, Int aiXpos = 10000, Int asYpos = 10000, Bool asVisible = False) global native
Int Function LoadWidget(String asRoot,String asFilename, Int aiXpos = 10000, Int aiYpos = 10000, Bool abVisible = False) global native

;generic
Function SetPos(String asRoot, Int aiId, Int aiXpos, Int aiYpos) global native
Function SetSize(String asRoot, Int aiId, Int aiH, Int aiW) global native
Int Function GetSize(String asRoot, Int aiId, Int aiType) global native
Function SetZoom(String asRoot, Int aiId, Int aiScaleX, Int aiScaleY) global native
Function SetVisible(String asRoot, Int aiId, Int aiVisible) global native
Function SetRotation(String asRoot, Int aiId, Int aiRotation) global native
Function SetTransparency(String asRoot, Int aiId, Int aiAlpha) global native
Function SetRGB(String asRoot, Int aiId, Int aiRed, Int aiGreen, Int aiBlue) global native
Function Destroy(String asRoot, Int aiId) global native
Function SwapDepths(String asRoot, Int aiId1, Int aiId2) global native

;meters
Function SetMeterPercent(String asRoot,Int aiId, Int aiPercent) global native
Function SetMeterFillDirection(String asRoot,Int aiId, String asDirection) global native
Function SendToBack(String asRoot,Int aiId) global native
Function SendToFront(String asRoot,Int aiId) global native
Function DoMeterFlash(String asRoot, Int aiId) global native
Function SetMeterRGB(String asRoot, Int aiId, Int aiLightR = 255, Int aiLightG = 255, Int aiLightB = 255, Int aiDarkR = 0, \
                        Int aiDarkG = 0, Int aiDarkB = 0, Int aiFlashR = 127, Int aiFlashG = 127, Int aiFlashB = 127) global native


;text
Function SetText(String asRoot, Int aiId, String asDisplayString) global native
Function AppendText(String asRoot, Int aiId, String asDisplayString) global native





