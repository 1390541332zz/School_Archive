//------------------------------------------
// BUTTON API API (Application Programming Interface)
// Also known as BUTTON HAL (Hardware Abstraction Layer)
// HAL is a specific form of API that designs the interface with a certain hardware

void InitButtons();

// The below functions return true if the button mentioned in the function name is pressed
// These functions use raw button status
bool Booster_Top_Button_Pressed();
bool Booster_Bottom_Button_Pressed();
bool Launchpad_Left_Button_Pressed();
bool Launchpad_Right_Button_Pressed();

// The below functions return true if the button mentioned in the function name is pushed
// Pushing means pressing followed by releasing. The function returns true as soon as the button is released.
// These functions use debounced button status
bool Booster_Top_Button_Pushed();
bool Booster_Bottom_Button_Pushed();
