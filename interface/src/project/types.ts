export interface LightState {
  led_on: boolean;
}

export interface ClockState {
  brightness: number;
  colorRed: number;
  colorGreen: number;
  colorBlue: number;
}

export interface LightMqttSettings { 
  unique_id : string;
  name: string;
  mqtt_path : string;
}
