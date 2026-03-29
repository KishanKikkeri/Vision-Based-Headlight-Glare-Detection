#include "esp_camera.h"

// =================== CAMERA PIN DEFINITIONS ===================
// AI Thinker ESP32-CAM
#define PWDN_GPIO_NUM     32
#define RESET_GPIO_NUM    -1
#define XCLK_GPIO_NUM      0
#define SIOD_GPIO_NUM     26
#define SIOC_GPIO_NUM     27

#define Y9_GPIO_NUM       35
#define Y8_GPIO_NUM       34
#define Y7_GPIO_NUM       39
#define Y6_GPIO_NUM       36
#define Y5_GPIO_NUM       21
#define Y4_GPIO_NUM       19
#define Y3_GPIO_NUM       18
#define Y2_GPIO_NUM        5
#define VSYNC_GPIO_NUM    25
#define HREF_GPIO_NUM     23
#define PCLK_GPIO_NUM     22

// =================== SETTINGS ===================
#define BRIGHT_PIXEL_THRESHOLD 230   // pixel brightness threshold
#define BRIGHT_PIXEL_COUNT 500       // number of bright pixels needed
#define ALERT_PIN 4                 // onboard flash LED

void setup() {
  Serial.begin(115200);
  Serial.println("\nStarting Headlight Glare Detection...");

  pinMode(ALERT_PIN, OUTPUT);
  digitalWrite(ALERT_PIN, LOW);

  camera_config_t config;
  config.ledc_channel = LEDC_CHANNEL_0;
  config.ledc_timer   = LEDC_TIMER_0;
  config.pin_d0       = Y2_GPIO_NUM;
  config.pin_d1       = Y3_GPIO_NUM;
  config.pin_d2       = Y4_GPIO_NUM;
  config.pin_d3       = Y5_GPIO_NUM;
  config.pin_d4       = Y6_GPIO_NUM;
  config.pin_d5       = Y7_GPIO_NUM;
  config.pin_d6       = Y8_GPIO_NUM;
  config.pin_d7       = Y9_GPIO_NUM;
  config.pin_xclk     = XCLK_GPIO_NUM;
  config.pin_pclk     = PCLK_GPIO_NUM;
  config.pin_vsync    = VSYNC_GPIO_NUM;
  config.pin_href     = HREF_GPIO_NUM;
  config.pin_sscb_sda = SIOD_GPIO_NUM;
  config.pin_sscb_scl = SIOC_GPIO_NUM;
  config.pin_pwdn     = PWDN_GPIO_NUM;
  config.pin_reset    = RESET_GPIO_NUM;
  config.xclk_freq_hz = 20000000;

  // Use grayscale to save memory
  config.pixel_format = PIXFORMAT_GRAYSCALE;

  config.frame_size   = FRAMESIZE_QQVGA; // 160x120
  config.jpeg_quality = 12;
  config.fb_count     = 1;

  // Init camera
  esp_err_t err = esp_camera_init(&config);
  if (err != ESP_OK) {
    Serial.printf("Camera init failed: 0x%x\n", err);
    return;
  }

  Serial.println("Camera initialized successfully!");
}

void loop() {
  camera_fb_t *fb = esp_camera_fb_get();

  if (!fb) {
    Serial.println("Camera capture failed");
    return;
  }

  uint8_t *img = fb->buf;
  int len = fb->len;

  int brightPixels = 0;

  // Count very bright pixels (glare spots)
  for (int i = 0; i < len; i++) {
    if (img[i] > BRIGHT_PIXEL_THRESHOLD) {
      brightPixels++;
    }
  }

  Serial.print("Bright Pixels: ");
  Serial.println(brightPixels);

  // Glare detection logic
  if (brightPixels > BRIGHT_PIXEL_COUNT) {
    Serial.println("⚠️ HEADLIGHT GLARE DETECTED!");

    digitalWrite(ALERT_PIN, HIGH);  // Turn ON LED
  } else {
    Serial.println("No glare");

    digitalWrite(ALERT_PIN, LOW);   // Turn OFF LED
  }

  esp_camera_fb_return(fb);

  delay(300);
}