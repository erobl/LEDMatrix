#ifndef ClockService_h
#define ClockService_h


#include <HttpEndpoint.h>
#include <MqttPubSub.h>
#include <WebSocketTxRx.h>

#include <time.h>
#include <lwip/apps/sntp.h>

#define NEOPIXEL_PIN 16
#define PANEL_WIDTH 16
#define PANEL_HEIGHT 16
#define NUMPIXELS PANEL_WIDTH*PANEL_HEIGHT
#define MIN_BRIGHTNESS 8
#define MAX_BRIGHTNESS 255

#define DEFAULT_BRIGHTNESS 64
#define DEFAULT_RED 128
#define DEFAULT_BLUE 128
#define DEFAULT_GREEN 128

#include <NeoPixelBrightnessBus.h>

typedef RowMajorAlternatingLayout MyPanelLayout;

#define CLOCK_SETTINGS_FILE "/config/clockSettings.json"
#define CLOCK_SETTINGS_PATH "/rest/clockSettings"

class ClockState {
 public:
  uint8_t brightness;
  uint8_t colorRed;
  uint8_t colorGreen;
  uint8_t colorBlue;
  
  static void read(ClockState& settings, JsonObject& root) {
    root["brightness"] = settings.brightness;
    root["colorRed"] = settings.colorRed;
    root["colorGreen"] = settings.colorGreen;
    root["colorBlue"] = settings.colorBlue;
  }

  static StateUpdateResult update(JsonObject& root, ClockState& clockState) {
    uint8_t brightness = root["brightness"] | DEFAULT_BRIGHTNESS;
    uint8_t colorRed = root["colorRed"] | DEFAULT_RED;
    uint8_t colorGreen = root["colorGreen"] | DEFAULT_GREEN;
    uint8_t colorBlue = root["colorBlue"] | DEFAULT_BLUE;
    bool changed = false;
    if (clockState.brightness != brightness) {
      clockState.brightness = brightness;
      changed = true;
    }
    if (clockState.colorRed != colorRed) {
      clockState.colorRed = colorRed;
      changed = true;
    }
    if (clockState.colorGreen != colorGreen) {
      clockState.colorGreen = colorGreen;
      changed = true;
    }
    if (clockState.colorBlue != colorBlue) {
      clockState.colorBlue = colorBlue;
      changed = true;
    }
    if(changed) {
        return StateUpdateResult::CHANGED;
    }
    return StateUpdateResult::UNCHANGED;
  }
};

class ClockService : public StatefulService<ClockState> {
 public:
  ClockService(AsyncWebServer* server);
  ~ClockService();

  void begin();
  void loop();
  void render(char c, int offset_x, int offset_y);
  void update(int hour, int minute);

 private:
  void onConfigUpdated();
  NeoTopology<MyPanelLayout>* topo;
  NeoPixelBrightnessBus<NeoRgbFeature, Neo800KbpsMethod>* strip;
  int old_hour = 0;
  int old_minute = 0;
  bool force_update = false;
  HttpEndpoint<ClockState> _httpEndpoint;
};

#endif
