#include <ClockService.h>
#include <font8x8_basic.h>

ClockService::ClockService(AsyncWebServer* server) :
    _httpEndpoint(ClockState::read, ClockState::update, this, server, CLOCK_SETTINGS_PATH) {

  // configure settings service update handler to update time state
  addUpdateHandler([&](const String& originId) { onConfigUpdated(); }, false);
}

ClockService::~ClockService() {
    delete this->topo;
    delete this->strip;
}

void ClockService::begin() {
    _state.brightness = DEFAULT_BRIGHTNESS;
    _state.colorRed = DEFAULT_RED;
    _state.colorGreen = DEFAULT_GREEN;
    _state.colorBlue = DEFAULT_BLUE;

    this->topo = new NeoTopology<MyPanelLayout>(PANEL_WIDTH, PANEL_HEIGHT);
    this->strip = new NeoPixelBrightnessBus<NeoRgbFeature, Neo800KbpsMethod>(NUMPIXELS, NEOPIXEL_PIN);
    this->strip->Begin();
    this->strip->SetBrightness(_state.brightness);
    this->strip->Show();
}

void ClockService::onConfigUpdated() {
    this->force_update = true;
};

void ClockService::render(char c, int offset_x, int offset_y) {
    RgbColor color(_state.colorGreen, _state.colorRed, _state.colorBlue);
    RgbColor black(0);

    for(int x = 0; x < 8; x++) {
        for(int y = 0; y < 8; y++) {
            if(font8x8_basic[c][x] & 1 << y) {
                this->strip->SetPixelColor(this->topo->Map(y+offset_y, x+offset_x), color);
            } else {
                this->strip->SetPixelColor(this->topo->Map(y+offset_y, x+offset_x), black);
            }
        }
    }
}

void ClockService::update(int hour, int minute) {
    int hour_tens = hour / 10;
    int hour_units = hour % 10;
    int minute_tens = minute / 10;
    int minute_units = minute % 10;

    this->render(hour_tens + 0x30, 0, 0);
    this->render(hour_units + 0x30, 0, 8);
    this->render(minute_tens + 0x30, 8, 0);
    this->render(minute_units + 0x30, 8, 8);

    this->old_hour = hour;
    this->old_minute = minute;

    this->strip->SetBrightness(_state.brightness);

    this->strip->Show();
}

void ClockService::loop() {
    time_t now = time(nullptr);
    struct tm * ptm = localtime(&now);

    int hour = ptm->tm_hour;
    int minute = ptm->tm_min;

    if(this->force_update) {
        delay(500);
    }

    if(this->force_update || this->old_hour != hour || this->old_minute != minute) {
        this->update(hour, minute);
        this->force_update = false;
    }
}
